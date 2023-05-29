#include "Household_Agent.hpp"
#include <iostream>
#include <numeric>


using namespace std;

//----------- Constructors
// New Constructor to use
Household_Agent::Household_Agent(float propensities[7], int init_values[3], Public_Info_Board* pPublic_Board )
{
    // -- Set Given starting parameters and propensities
    savings= init_values[0];
    unemp_duration_upper_bound = init_values[1];
    reservation_wage = init_values[2];

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

    // Consumption and Expenditure
    consumption_budget = 0;
    // Savings
    savings_desired = 0;  
    // Income
    income_current = 0;
    income_average = 0;
    income_wage = 0;
    income_unemployment_benefit = 0;
    income_dividend = 0;
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
    if (current_job == nullptr && firm_owner == false){ // Set firm as unemployed
        unemployed = true;
        unemp_duration += 1;
    } else {
        if (firm_owner){ // Firm owners count as employed
            unemployed = false;
        } else if (current_job->Get_Status() == -1){ // Laid off by firm
            unemployed = true;
            unemp_duration = 1;
            delete current_job;
            current_job = nullptr;
        } else { // Has a job
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
    Determine_Consumer_Sentiment();
    Random_Experimentation();
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
    income_wage = 0;
    income_dividend = 0;
    income_unemployment_benefit = 0;

    if (!unemployed && !firm_owner){ // Regular worker
        income_wage = current_job->Get_Wage();
        pPublic_Info_Board->Update_Household_Wage_Income(income_wage);
        income_current = income_wage;
    } else if (firm_owner){ // Firm owner
        income_dividend = owned_firm->Get_Dividend();
        pPublic_Info_Board->Update_Household_Dividend_Income(income_dividend);
        income_current = income_dividend;
    } else { // Unemployed
        income_wage = 0;
        income_unemployment_benefit = pPublic_Info_Board->Get_Unemployment_Benefit();
        income_current = income_unemployment_benefit;
        pPublic_Info_Board->Update_Household_Unemployment_Income(income_unemployment_benefit);
    }

    if(income_current < 0 ){
        std::cout << "ERROR: Negative income at Update_Income() - Household: " << this << " has income:  " << income_current << std::endl;
    }
}

/* Function to calculate average income and fill in array at t=1
*/
void Household_Agent::Update_Average_Income_T1()
{
    for(int i = 0;i < 12; i++){past_incomes.push(income_current);}
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



/* Determine Household sentiment, and thereby savings propensity and desired cash on hand
Households randomly adopt majority opinion, otherwise check employment status
*/
void Household_Agent::Determine_Consumer_Sentiment()
{
    if (unemployed) {
        sentiment = 0;} 
    else{
        sentiment = 1;}

    bool adopt_majority = Uniform_Dist_Float(0,1)  < household_rand_sentiment_adoption;
    if(adopt_majority){
        sentiment = (pPublic_Info_Board->Get_Household_Sentiment() > 0.50); }

    if (sentiment){
        saving_propensity = saving_propensity_optimist;
    } else{
        saving_propensity = saving_propensity_pessimist;}

    savings_desired = saving_propensity * income_average;// Set targets for cash on hand

    pPublic_Info_Board->Update_Household_sentiment_sum(static_cast<int>(sentiment));
}


/* Function to determine consumption budget
 - Using Jamel functions
*/
void Household_Agent::Determine_Consumption_Budget()
{
    // Determine shortfall from target savings
    savings_desired = household_targeted_savings_to_income_ratio * income_average;
    long long excess_savings = savings - savings_desired;
    if (excess_savings < 0){
        consumption_budget = (1.0-saving_propensity) * income_current;
    } else {
        consumption_budget = (1.0-saving_propensity) * income_current + c_f * excess_savings;
    }

    if (consumption_budget < 0) { // make sure expenditure isnt negative
        cout << "ERROR: Consumption budget at firm " << this << " is negative: " << consumption_budget << endl;
        consumption_budget = max(consumption_budget, static_cast<long long>(0.0)); 
    }

    // Let the public board know how much the household has set aside to consume
    pPublic_Info_Board->Update_Consumption_Budget(consumption_budget);
}


/* /*  Interact with the market through the public board to buy goods
- Pass in the consumption budget along with the vector with the sector weights
- Receive back a pair of two vectors, leftover budget and goods bought for each sector
*/
void Household_Agent::Buy_Consumer_Goods_By_Sector_And_Emissions(){

    // Multiply each element in spending_weight_by_sector by consumption_budget and form a new vector
    vector<long long> planned_expenditure_by_sector;

    // Fill this with the planned spending numbers
    for (int i = 0; i < spending_weight_by_sector.size(); ++i) {
        if (spending_weight_by_sector[i] < 0){
            cout << "ERROR: in Buy_cons_goods: at firm "<< this << " Spending weight by sector is negative" << endl;
            spending_weight_by_sector[i] = max(spending_weight_by_sector[i], 0.0f);
        }
        planned_expenditure_by_sector.push_back(spending_weight_by_sector[i] * consumption_budget);
        if (planned_expenditure_by_sector[i] <0){
            cout << "ERROR: in Buy_cons_goods: at firm "<< this <<" - Planned expenditure is negative: " <<  planned_expenditure_by_sector[i] << " for sector : " << i <<  endl;
        }
    }

    // Buy consumer goods and receive leftover budget and quantity bought for each sector
    tuple<vector<long long>, vector<long long>, vector<long long>> purchases_by_sector = pPublic_Info_Board->Buy_Consumer_Goods_By_Sector_And_Emission(planned_expenditure_by_sector, emission_sensitivity_by_sector);

    vector<long long> remaining_consumption_budget =  std::get<0>(purchases_by_sector);
    vector<long long> goods_bought =  std::get<1>(purchases_by_sector);
    vector<long long> emissions_generated =  std::get<2>(purchases_by_sector);

    vector<long long> actual_spending_by_sector(planned_expenditure_by_sector); // TODO: Does this set them equal

    long long total_goods_bought = 0;
    total_emissions = 0;


    for (int i=0; i<sector_count; i++){ // Check each sector
        // Deal with the leftover budget in  remaining_consumption_budget 
        consumption_budget -= remaining_consumption_budget[i]; 
        savings += remaining_consumption_budget[i]; // Increment savings
        actual_spending_by_sector[i] -= remaining_consumption_budget[i]; 

        // Tally up goods bought by quantity
        total_goods_bought += goods_bought[i];
        if(remaining_consumption_budget[i] < 0){
            cout << "Error in Buy Consumer Goods: Remaining consumption budget negative: " << remaining_consumption_budget[i] << endl;
        }

        // Tally up emissions
        total_emissions += emissions_generated[i];
    }

    // Update the public board with relevant stuff
    // Sold quantities are logged by firms themselves
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
    // execute code with probabilty equal to the initialization parameter
    bool seek_better_job = Uniform_Dist_Float(0,1)  < household_rand_job_search;
    if ( !unemployed && seek_better_job && !firm_owner) {  // Only do this if you are already employed as a worker
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
    os << "consumption_budget " << obj.consumption_budget << std::endl;
    os << "consumption_propensity " << obj.consumption_propensity << std::endl;
    os << "savings " << obj.savings << std::endl;
    os << "savings_desired " << obj.savings_desired << std::endl;
    os << "saving_propensity " << obj.saving_propensity << std::endl;
    os << "saving_propensity_optimist " << obj.saving_propensity_optimist << std::endl;
    os << "saving_propensity_pessimist " << obj.saving_propensity_pessimist << std::endl;
    
    os << "income_current " << obj.income_current << std::endl;
    os << "income_average " << obj.income_average << std::endl;
    os << "income_wage " << obj.income_wage << std::endl;
    os << "income_unemployment_benefit " << obj.income_unemployment_benefit << std::endl;
    os << "income_dividend " << obj.income_dividend << std::endl;

    os << "total_emissions " << obj.total_emissions << std::endl;
    os << "emission_sensitivity_avg " << obj.emission_sensitivity_avg << std::endl;

    os << "unemployed " << obj.unemployed << std::endl;
    os << "reservation_wage " << obj.reservation_wage << std::endl;
    os << "unemp_duration " << obj.unemp_duration << std::endl;
    os << "unemp_duration_upper_bound " << obj.unemp_duration_upper_bound << std::endl;
    os << "sentiment " << obj.sentiment << std::endl;
    os << "business_owner " << obj.firm_owner << std::endl;
    os << "c_f " << obj.c_f << std::endl;
    //os << "c_h " << obj.c_h << std::endl;
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
