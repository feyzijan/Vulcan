#include "Household_Agent.hpp"
#include <iostream>
#include <numeric>

//----------- Constructors
// New Constructor to use
Household_Agent::Household_Agent(float propensities[7], int vals[3], Public_Info_Board* pPublic_Board )
{
    // -- Set Given starting parameters and propensities
    wealth_financial = vals[0];
    unemp_duration_upper_bound = vals[1];
    reservation_wage = vals[2];

    consumption_propensity = propensities[0];
    saving_propensity_optimist = propensities[1];
    saving_propensity_pessimist = propensities[2];
    c_f = propensities[3];
    c_h = propensities[4];
    c_excess_money = propensities[5];

    // Set Pointers
    // Public_Info_Board* pPublic_Info_Board = pPublic_Board;
    this->pPublic_Info_Board = pPublic_Board;
    current_job = nullptr;
    owned_firm = nullptr;

    //-- Set default non_zero initialization values
    unemployed = true;
    firm_owner = false;
    sentiment = true;
    saving_propensity = saving_propensity_optimist;
    
    //-- Set everything else to zero initiallly
    // Wealth
    wealth_human = 0;
    // Consumption and Expenditure
    expenditure_consumption = 0;
    expenditure_tax = 0;
    // Savings
    new_savings = 0;
    cash_on_hand_real_desired = 0;
    cash_on_hand_desired = 0;  
    cash_on_hand_current = 0;
    // Income
    income_current = 0;
    income_average = 0;
    income_wage = 0;
    income_unemployment_benefit = 0;
    income_gov_transfers = 0;
    income_firm_owner_dividend = 0;
    // Emisisons
    total_emissions = 0;
    emission_sensitivity_avg = 0.0;
    // Unemployment status
    unemp_duration = 0;
    // Date
    current_date = 0;
}

// ------------------- Initialization Functions ------------------------------

/* Function to set the Household as a firm owner and assign the owned fimr
This method is called at the initialization stage
*/
void Household_Agent::Set_Firm_Owner(Firm_Agent* firm_ptr){
    firm_owner = true;
    owned_firm = firm_ptr;
    unemployed = false;
    owned_firm->Set_Owner(this);
}

/* Function to initialize the spending weights for each consumer sectors
Loops throgh each sector, and push to the spending_weighing_by_sector vector the weight of the sector
Called at the Initialization stage when initializing consumer sectors
*/
void Household_Agent::Initialize_Sector_Weights(vector<Consumer_Firm_Sector*> *pConsumer_Firm_Sector_vector)
{
    for (int i = 0; i < pConsumer_Firm_Sector_vector->size(); i++){
        float temp = pConsumer_Firm_Sector_vector->at(i)->weighing;
        temp = std::round(temp * 1000) / 1000.0; // round to the nearest three decimals
        spending_weight_by_sector.push_back(temp);
        if (temp < 0){
            cout << "Error Sector weight is negative" << endl;
        }
    }
}


/* Function to initialize the emission sensitivities for each consumer sectors
Loops throgh each sector, and push to the emission_sensitivity_by_sector vector
The pushed value is randomly generated from a normal distribution specified in the initialization parameters
Called at the Initialization stage when initializing consumer sectors
*/
void Household_Agent::Initialize_Sector_Emission_Sensitivities(vector<Consumer_Firm_Sector*> *pConsumer_Firm_Sector_vector)
{
    for (int i = 0; i < pConsumer_Firm_Sector_vector->size(); i++){
        float mean_sensitivity = pConsumer_Firm_Sector_vector->at(i)->emission_sensitivity_mean;
        // Do a random number generation 
        float temp = Normal_Dist_Generator(mean_sensitivity, emission_sensitivity_std, emission_sensitivity_min, emission_sensitivity_max)(); 
        temp = std::round(temp * 1000) / 1000.0; // round to the nearest three decimals
        if (temp < 0){
            cout << "Error in Household_Agent::Initialize_Sector_Emission_Sensitivities(): Sector weight is negative" << endl;
            temp = 0;
        }
        emission_sensitivity_by_sector.push_back(temp);
    }

    emission_sensitivity_avg = std::inner_product(emission_sensitivity_by_sector.begin(), emission_sensitivity_by_sector.end(), spending_weight_by_sector.begin(), 0.0);
}


//------------ Main Loop Methods ----------------------- //

/* Function to check if current_job status is 0 or 1
if 0 then mark as unemployed, and update the unemployment duration, and delete the job object, 
and set the current_job pointer to nullptr
*/
void Household_Agent::Check_Employment_Status()
{
    if (current_job == nullptr && firm_owner == false){
        unemployed = true;
        unemp_duration += 1;
    } else {
        if (firm_owner){
            unemployed = false;
        } else if (current_job->Get_Status() == -1){ // Laid off by firm
            unemployed = true;
            unemp_duration = 1;
            delete current_job;
            current_job = nullptr;
        } else { // Either has a job or is a firm owner
            unemployed = false;
            unemp_duration = 0;
        }
    }
}

/* Function to update public board with employment status
This is a separate function because the employment status is checked mulitple times but the update 
should be done once*/
void Household_Agent::Update_Public_Board_On_Employment()
{
    pPublic_Info_Board->Update_Employed_Worker_Count(!unemployed); // add 1 if employed, 0 if unemployed
    pPublic_Info_Board->Update_Unemployed_Worker_Count(unemployed); // add 1 if unemployed, 0 if employed
}


/* Function to update reservation wage
 If unemployed for longer than upper bound randomly reduce wage by a "lot", if not reduce by less
 TODO: Check if you want to keep the duration condition
*/
void Household_Agent::Update_Reservation_Wage()
{
    float n_decrease = Uniform_Dist_Float(0.0,household_n_res_wage_decrease);
    if( unemp_duration > unemp_duration_upper_bound){
        reservation_wage = reservation_wage * (1-n_decrease);
    } else {
        reservation_wage = reservation_wage * (1-n_decrease/2.0);
    }

    // Make sure it is not above minimum wage
    reservation_wage = max(reservation_wage, pPublic_Info_Board->Get_Minimum_Wage()); 
} 


/* Randomly alter some household properties
- Loop through the spending_weight_by_sector vector and randomly alter the weights by x%, where x ranges between -0.05 and 0.05 
- Make sure that the total of the weights is 1
*/
void Household_Agent::Random_Experimentation(){

    // Randomly alter desired spending weights for each sector
    float weighing_change = Uniform_Dist_Float(1.0-household_rand_sector_spending_weight_change , 1.0+household_rand_sector_spending_weight_change);

    for (int i = 0; i < spending_weight_by_sector.size(); i++){
        spending_weight_by_sector[i] = spending_weight_by_sector[i] * (weighing_change);}

    // Ensure the total is 1
    float sum = 0;
    for (int i = 0; i < spending_weight_by_sector.size(); i++){
        sum += spending_weight_by_sector[i];}

    for (int i = 0; i < spending_weight_by_sector.size(); i++){
        spending_weight_by_sector[i] = spending_weight_by_sector[i] / sum;}

    // Randomly change emission weights
    weighing_change = Uniform_Dist_Float(1.0-household_rand_emission_sensitivity_change , 1.0+household_rand_emission_sensitivity_change);

    for (int i = 0; i < emission_sensitivity_by_sector.size(); i++){
        emission_sensitivity_by_sector[i] = emission_sensitivity_by_sector[i] * (weighing_change);}

    emission_sensitivity_avg = std::inner_product(emission_sensitivity_by_sector.begin(), emission_sensitivity_by_sector.end(), spending_weight_by_sector.begin(), 0.0);
}

/* Aggregate function to make consumption and savings decisions
Household r eceives wages, and updates the following
Average income over past n windows
Current financial wealth
Effective saving : Cash_on_hand - average_income
Targeted saving : factor * average_income
Targeted Consumption Expenditures: - some formula
// TODO: Get rid of the if else check
*/
void Household_Agent::Consumption_Savings_Decisions(){
    //Update_Reservation_Wage();
    Update_Income();
    if (global_date > 1) {
        Update_Average_Income();
    } else {
        Update_Average_Income_T1();
    }
    Update_Savings();
    Determine_Consumer_Sentiment();
    Determine_Consumption_Budget();
}


/* Function to update the income_current variable to sum of all incomes received
- Check if the household is employed by checking if current_job pointer points to 0
    - It will do so if fired by the firm *** Firm has to manage this
- If unemployed, add the unemployment_benefits, which should be determined beforehand
TODO: Implement dividend income
*/
void Household_Agent::Update_Income()
{
    income_current = 0; // Initialize to zero

    // Check if the person is employed, if so get Wage
    if (!unemployed && !firm_owner){
        income_wage = current_job->Get_Wage();
        pPublic_Info_Board->Update_Household_Wage_Income(income_wage);
        income_current += income_wage;
    } else if (firm_owner){
        income_firm_owner_dividend = owned_firm->Pay_Dividend();
        pPublic_Info_Board->Update_Household_Dividend_Income(income_firm_owner_dividend);
        income_current += income_firm_owner_dividend;
    } else {
        income_wage = 0;
        income_unemployment_benefit = pPublic_Info_Board->Get_Unemployment_Benefit();
        income_current += income_unemployment_benefit;
        pPublic_Info_Board->Update_Household_Unemployment_Income(income_unemployment_benefit);
    }
    income_current += income_gov_transfers; // Add any additional transfers
    
    pPublic_Info_Board->Update_Household_Total_Income(income_current);
}

/* Function to calculate average income and fill in array at t=1
*/
void Household_Agent::Update_Average_Income_T1()
{
    for(int i=1;i<=12;i++){past_incomes.push(income_current);}
    income_average = income_current;
}

/* Function to update the average income of the past n periods
*/
void Household_Agent::Update_Average_Income()
{
    income_average = income_average - past_incomes.front()/12.0 + income_current/12.0;
    past_incomes.pop();
    past_incomes.push(income_current);
}


/* Function to update financial wealth based on income andconsumption
TODO : Check if this is necessary
*/
void Household_Agent::Update_Savings()
{
    long long effective_savings = cash_on_hand_current - income_average; // maybe make this the same as current savings
    cash_on_hand_desired = household_targeted_savings_to_income_ratio * income_average;
}

/* Determine Household sentiment, and thereby savings propensity and desired cash on hand
Households randomly adopt majority opinion, otherwise check employment status
*/
void Household_Agent::Determine_Consumer_Sentiment()
{
    if (unemployed){
        sentiment = 0;} 
    else{
        sentiment = 1;}

    bool adopt_majority = Uniform_Dist_Float(0,1)  < household_rand_sentiment_adoption;
    if(adopt_majority){
        sentiment = (pPublic_Info_Board->Get_Household_Sentiment() > 0.50); }

    if (sentiment){saving_propensity = saving_propensity_optimist;
    } else{saving_propensity = saving_propensity_pessimist;}

    cash_on_hand_desired = saving_propensity * income_average;// Set targets for cash on hand

    pPublic_Info_Board->Update_Household_sentiment_sum(sentiment);
}


/* Function to determine consumption budget
 - Using Jamel functions
*/
void Household_Agent::Determine_Consumption_Budget()
{
    long long excess_savings = cash_on_hand_current - cash_on_hand_desired;
    if (excess_savings < 0){
        expenditure_consumption = (1.0-saving_propensity) * income_current;
    } else {
        expenditure_consumption = (1.0-saving_propensity) * income_current + c_f * excess_savings;
    }

    if (expenditure_consumption < 0) { // make sure expenditure isnt negative
        cout << "Error Expenditure consumption is negative" << endl;
        expenditure_consumption = max(expenditure_consumption, static_cast<long long>(0.0)); 
    }

    // Let the public board know how much the household has set aside to consume
    pPublic_Info_Board->Update_Consumption_Budget(expenditure_consumption);
}


/* /*  Interact with the market through the public board to buy goods
- Pass in the consumption budget along with the vector with the sector weights
- Receive back a pair of two vectors, leftover budget and goods bought for each sector
*/
void Household_Agent::Buy_Consumer_Goods_By_Sector_And_Emissions(){

    // Multiply each element in spending_weight_by_sector by expenditure_consumption and form a new vector
    vector<long long> planned_expenditure_by_sector;

    // Fill this with the planned spending numbers
    for (int i = 0; i < spending_weight_by_sector.size(); ++i) {
        if (spending_weight_by_sector[i] < 0){
            cout << "Error: Spending weight by sector is negative" << endl;
            spending_weight_by_sector[i] = max(spending_weight_by_sector[i], 0.0f);
        }
        planned_expenditure_by_sector.push_back(spending_weight_by_sector[i] * expenditure_consumption);
    }

    // Buy consumer goods and receive leftover budget and quantity bought for each sector
    tuple<vector<long long>, vector<long long>, vector<long long>> purchases_by_sector = pPublic_Info_Board->Buy_Consumer_Goods_By_Sector_And_Emission(expenditure_consumption, planned_expenditure_by_sector, emission_sensitivity_by_sector);

    vector<long long> remaining_consumption_budget =  std::get<0>(purchases_by_sector);
    vector<long long> goods_bought =  std::get<1>(purchases_by_sector);
    vector<long long> emissions_generated =  std::get<2>(purchases_by_sector);
    vector<long long> actual_spending_by_sector(planned_expenditure_by_sector);

    long long total_goods_bought = 0;

    for (int i=0; i<remaining_consumption_budget.size(); i++){
        // Deal with the leftover budget
        expenditure_consumption -= remaining_consumption_budget[i];
        new_savings += remaining_consumption_budget[i];
        wealth_financial += remaining_consumption_budget[i]; 
        actual_spending_by_sector[i] -= remaining_consumption_budget[i];

        // Add up tally of goods bought
        total_goods_bought += goods_bought[i];
    }
    // Update the public board with relevant stuff
    pPublic_Info_Board->Update_Actual_Consumer_Spending_by_Sector(actual_spending_by_sector);
    pPublic_Info_Board->Update_Planned_Consumer_Spending_by_Sector(planned_expenditure_by_sector);
    pPublic_Info_Board->Update_Consumer_Emissions_By_Sector(emissions_generated);
}


/* Function to seek jobs and accept any above the reservation wage
If job is accepted remove it from the job market
*/
void Household_Agent::Seek_Jobs()
{
    if(unemployed){
        Job* best_job = pPublic_Info_Board->Get_Top_Job();
        if (best_job != NULL){
            if (best_job->Get_Wage() >= reservation_wage){
                //cout << "Job found" <<endl;
                current_job = best_job;
                current_job->Set_Employee(this); // update job object
                int expiry_date = global_date + current_job->Get_Contract_Length();
                current_job->Set_Expiry_Date();
                unemployed = false;
                pPublic_Info_Board->Take_Job(current_job);
            }
            else {
                //cout << "job not found" <<endl;
                Update_Reservation_Wage();
            }
        }
    }
}

/* Function to seek jobs with a higher wage than the current job with probability 
p_seek_better_job
*/
void Household_Agent::Seek_Better_Jobs()
{
    // execute code with probabilty equal to p_seek_better_job
    bool seek_better_job = Uniform_Dist_Float(0,1)  < household_rand_job_search;
    if ( !unemployed && seek_better_job && !firm_owner) {  
        Job* best_job = pPublic_Info_Board->Get_Top_Job();
        if (best_job != NULL){
            if (best_job->Get_Wage() > current_job->Get_Wage()){
                current_job->Update_Status(-2); // mark as quit so firm can update own records 
                current_job = best_job;
                current_job->Set_Employee(this); // update job object
                current_job->Set_Expiry_Date();
                pPublic_Info_Board->Take_Job(current_job);
                pPublic_Info_Board->Update_Employees_Quitting();
            }
        }
    }
}


/* Convert firm owner to an employee 
*/
void Household_Agent::Notify_Of_Bankruptcy(){
    firm_owner = false;
    unemployed = true;
    current_job = NULL;
    owned_firm = NULL;
}


//-----------------------------------------------------------------
// String stream operator

std::ostream& operator<<(std::ostream& os, const Household_Agent& obj) {
    os << "wealth_financial " << obj.wealth_financial << std::endl;
    os << "wealth_human " << obj.wealth_human << std::endl;
    os << "expenditure_consumption " << obj.expenditure_consumption << std::endl;
    os << "expenditure_tax " << obj.expenditure_tax << std::endl;
    os << "consumption_propensity " << obj.consumption_propensity << std::endl;
    os << "new_savings " << obj.new_savings << std::endl;
    os << "cash_on_hand_real_desired " << obj.cash_on_hand_real_desired << std::endl;
    os << "cash_on_hand_desired " << obj.cash_on_hand_desired << std::endl;
    os << "cash_on_hand_current " << obj.cash_on_hand_current << std::endl;
    os << "saving_propensity " << obj.saving_propensity << std::endl;
    os << "saving_propensity_optimist " << obj.saving_propensity_optimist << std::endl;
    os << "saving_propensity_pessimist " << obj.saving_propensity_pessimist << std::endl;
    
    os << "income_current " << obj.income_current << std::endl;
    os << "income_average " << obj.income_average << std::endl;
    os << "income_wage " << obj.income_wage << std::endl;
    os << "income_unemployment_benefit " << obj.income_unemployment_benefit << std::endl;
    os << "income_gov_transfers " << obj.income_gov_transfers << std::endl;
    os << "income_firm_owner_dividend " << obj.income_firm_owner_dividend << std::endl;

    os << "total_emissions " << obj.total_emissions << std::endl;
    os << "emission_sensitivity_avg " << obj.emission_sensitivity_avg << std::endl;

    os << "unemployed " << obj.unemployed << std::endl;
    os << "reservation_wage " << obj.reservation_wage << std::endl;
    os << "unemp_duration " << obj.unemp_duration << std::endl;
    os << "unemp_duration_upper_bound " << obj.unemp_duration_upper_bound << std::endl;
    os << "sentiment " << obj.sentiment << std::endl;
    os << "business_owner " << obj.firm_owner << std::endl;
    os << "c_f " << obj.c_f << std::endl;
    os << "c_h " << obj.c_h << std::endl;
    os << "c_excess_money " << obj.c_excess_money << std::endl;
    os << "date " << obj.current_date << std::endl;
    return os;
}

vector<std::pair<string, float>>* Household_Agent::Log_Data() {
        current_date = global_date;
        auto result = new vector<std::pair<std::string, float>>();

        // Get the names and values of all member variables
        std::stringstream ss;
        ss << *this;
        string line;
        while (std::getline(ss, line)) {
            string name;
            float value;
            std::stringstream(line) >> name >> value;
            result->emplace_back(name, value);
        }

        return result;
    }
    
//-----------------------------------------------------------------///
