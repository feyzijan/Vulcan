#include "Household_Agent.hpp"
#include <iostream>
#include <numeric>



//----------- Constructors

// New Constructor to use
Household_Agent::Household_Agent(float propensities[7], int vals[3], Public_Info_Board* pPublic_Board )
{

    wealth_financial = vals[0];
    unemp_duration_upper_bound = vals[1];
    reservation_wage = vals[2];

    consumption_propensity = propensities[0];
    saving_propensity_optimist = propensities[1];
    saving_propensity_pessimist = propensities[2];
    c_f = propensities[3];
    c_h = propensities[4];
    c_excess_money = propensities[5];
    p_majority_op_adoption = propensities[6];

    // Set Pointers
    //Public_Info_Board* pPublic_Info_Board = pPublic_Board;
    this->pPublic_Info_Board = pPublic_Board;
    this->current_job = nullptr;

    // Set default initialization values

    unemployed = true;
    positive_sentiment = true;
    business_owner = false;
    saving_propensity = saving_propensity_optimist;

    // Set everything else to zero initiallly

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

    // Unemployment status
    unemp_duration = 0;

    current_date = 0;
}

Household_Agent::Household_Agent(Household_Agent&){}
Household_Agent::~Household_Agent(){} 

//----- Main Loop


/* Household r eceives wages, and updates the following
Average income over past n windows
Current financial wealth
Effective saving : Cash_on_hand - average_income
Targeted saving : factor * average_income
Targeted Consumption Expenditures: - some formula
*/
void Household_Agent::Consumption_Savings_Decisions(){
    Update_Reservation_Wage();
    Update_Income();
    if (global_date == 1) {
        Update_Average_Income_T1();
    }
    Update_Average_Income();
    Update_Savings();
    Determine_Consumer_Sentiment();
    Determine_Consumption_Budget();
}



/* Function to check if current_job status is 0 or 1
if 0 then mark as unemployed, and update the unemployment duration, and delete the job object, 
and set the current_job pointer to nullptr
*/
void Household_Agent::Check_Employment_Status()
{
    if (current_job == nullptr){
        unemployed = true;
        unemp_duration += 1;
    } else {
        if (current_job->Get_Status() == 0){ // Laid off by firm
            unemployed = true;
            unemp_duration += 1;
            delete current_job;
            current_job = nullptr;
        } else {
            unemployed = false;
            unemp_duration = 0;
        }
    }
    // Update Public Records
    pPublic_Info_Board->Update_Employed_Workers(!unemployed);
    pPublic_Info_Board->Update_Unemployed_Workers(unemployed);
}


/* Function to update reservation wage
 If unemployed for longer than upper bound randomly reduce wage by a "lot", if not reduce by less
 TODO: Check if you want to keep the duration condition
*/
void Household_Agent::Update_Reservation_Wage()
{
    float n_decrease = Uniform_Dist_Float(0.0,n_res_wage_decrease);
    if( unemp_duration > unemp_duration_upper_bound){
        reservation_wage = reservation_wage * (1-n_decrease);
    } else {
        reservation_wage = reservation_wage * (1-n_decrease/2.0);
    }
} 

/* Function to update the income_current variable to sum of all incomes received
- Check if the household is employed by checking if current_job pointer points to 0
    - It will do so if fired by the firm *** Firm has to manage this
- If unemployed, add the unemployment_benefits, which should be determined beforehand
*/
void Household_Agent::Update_Income()
{
   
    income_current = 0; // Initialize to zero

    // Check if the person is employed, if so get Wage
    if (!unemployed){

        income_wage = current_job->Get_Wage();
        income_current += income_wage;
    } else {
        income_current += income_unemployment_benefit;
    }
    income_current += income_gov_transfers; // Add any additional transfers
    
    if (business_owner){income_current += income_firm_owner_dividend;}
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
*/
void Household_Agent::Update_Savings()
{
    int effective_savings = cash_on_hand_current - income_average; // maybe make this the same as current savings
    cash_on_hand_desired = targeted_savings_to_income_ratio * income_average;
}

/* Determine Household sentiment, and thereby savings propensity and desired cash on hand
Households randomly adopt majority opinion, otherwise check employment status
- TODO: Update the random probability here
*/
void Household_Agent::Determine_Consumer_Sentiment()
{
    if (unemployed){positive_sentiment = false;} 
    else{positive_sentiment = true;}

    bool adopt_majority= Uniform_Dist_Float(0,1)  < p_majority_op_adoption;
    if(adopt_majority){
        positive_sentiment = (pPublic_Info_Board->Get_Household_Sentiment() > 0.50); }

    if (positive_sentiment){saving_propensity = saving_propensity_optimist;
    } else{saving_propensity = saving_propensity_pessimist;}

    cash_on_hand_desired = saving_propensity * income_average;// Set targets for cash on hand
    pPublic_Info_Board->Update_Household_sentiment_sum(positive_sentiment);
}


/* Function to determine consumption budget
 - Using Jamel functions
*/
void Household_Agent::Determine_Consumption_Budget()
{
    int excess_savings = cash_on_hand_current - cash_on_hand_desired;
    if (excess_savings < 0){
        expenditure_consumption = (1.0-saving_propensity) * income_current;
    } else {
        expenditure_consumption = (1.0-saving_propensity) * income_current + c_f * excess_savings;
    }
    pPublic_Info_Board->Update_Consumption_Budgets(expenditure_consumption);
}

/* Interact with the market through public board to buy goods
- Spend as much of the consumption budget as it can, only buying integer multiple # goods,
- Add the unspent consumption budget to savings
TODO: Update this method once the called Buy_Consumer_Goods method is updated to return other variables
TODO: Check if the savings should be added now or later, to avoid double counting
*/
void Household_Agent::Buy_Consumer_Goods(){
    std::pair<int, int> purchase = pPublic_Info_Board->Buy_Consumer_Goods(expenditure_consumption);
    int remaining_consumption_budget = purchase.first;
    int goods_bought = purchase.second;
    expenditure_consumption -= remaining_consumption_budget;
    new_savings += remaining_consumption_budget;
    wealth_financial += remaining_consumption_budget;
    pPublic_Info_Board->Update_Consumer_spending(expenditure_consumption);
    pPublic_Info_Board->Update_Consumer_orders(goods_bought);
}


/* Function to seek jobs and accept any above the reservation wage
If job is accepted remove it from the job market
*/
void Household_Agent::Seek_Jobs()
{
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


//-----------------------------------------------------------------

// ----Printing and Debugging

void Household_Agent::Print_Characteristics() {
    //cout << "\n------ Household Agent at address : " << this << endl;
    cout << "Consumption Propensity; " << consumption_propensity << " Savings propensities- optimist: " << saving_propensity_optimist << 
     " pessimist: " << saving_propensity_pessimist << endl;
    cout << "Propensity to consume - financial wealth: " << c_f << " human wealth: " << c_h << " excess money: " << c_excess_money << endl;
    cout << "Majority conformity: " << p_majority_op_adoption << " Max unemployment tolerance: " << unemp_duration_upper_bound << endl;
    cout << "--------------------------------------" << endl;
}


void Household_Agent::Print() {
    cout << "\n------ Household Agent at address : " << this << endl;
    //Public Board
    cout << "Connected to public board at address: " << pPublic_Info_Board << endl;
    // Wealth
    cout << "Financial wealth: " << wealth_financial << " human wealth: " << wealth_human << endl;
    // Consumption
    cout << "Consumption - total: " << expenditure_consumption << " tax: " << expenditure_tax << endl;
    // Savings
    cout << "New savings: " << new_savings << " Savings propensity: " << saving_propensity <<  " Desired cash on hand - real: " << 
    cash_on_hand_real_desired << " nominal: " << cash_on_hand_desired << " current: " << cash_on_hand_current << endl;
    // Income
    cout <<"Income - current total: " << income_current << " average: " << income_average << " wage: " << income_wage <<  " unemployment benefit " 
    << income_unemployment_benefit <<  " Government transfer: " << income_gov_transfers << " dividends: " << income_firm_owner_dividend <<endl;
    // Employment
    cout << "Unemployed: " << unemployed << " Reservation wage: " << reservation_wage << " unemp duration: " << unemp_duration << endl;
    // Sentiment
    cout << "Positive Sentiment: " << positive_sentiment << endl;
    // Job 
    if (current_job != nullptr){
        cout << "Current job: " << endl;
        current_job->Print();
    } else {cout << "No current job" << endl;}
    // Characteristics
    Print_Characteristics(); 
    cout << "--------------------------------------" << endl;
}


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
    os << "unemployed " << obj.unemployed << std::endl;
    os << "reservation_wage " << obj.reservation_wage << std::endl;
    os << "unemp_duration " << obj.unemp_duration << std::endl;
    os << "unemp_duration_upper_bound " << obj.unemp_duration_upper_bound << std::endl;
    os << "positive_sentiment " << obj.positive_sentiment << std::endl;
    os << "business_owner " << obj.business_owner << std::endl;
    os << "c_f " << obj.c_f << std::endl;
    os << "c_h " << obj.c_h << std::endl;
    os << "c_excess_money " << obj.c_excess_money << std::endl;
    os << "p_majority_op_adoption " << obj.p_majority_op_adoption;
    os << "current_date " << obj.current_date << std::endl;
}

std::vector<std::pair<std::string, float>>* Household_Agent::Log_Data() {
        current_date = global_date;
        auto result = new std::vector<std::pair<std::string, float>>();

        // Get the names and values of all member variables
        std::stringstream ss;
        ss << *this;
        std::string line;
        while (std::getline(ss, line)) {
            std::string name;
            float value;
            std::stringstream(line) >> name >> value;
            result->emplace_back(name, value);
        }

        return result;
    }






//-----------------------------------------------------------------///

// ----- Initialization Functions



/* Function to return ptr to a vector contianing all class variables
    Used by the function to save the data to a log file
*/
vector<float>* Household_Agent::Get_All_Params(){

    vector<float>* vec_pointer = new vector<float>();

    //vector<float>* vec_pointer;
    
    vec_pointer->push_back(wealth_financial);
    vec_pointer->push_back(wealth_human);
    vec_pointer->push_back(expenditure_consumption);
    vec_pointer->push_back(expenditure_tax);
    vec_pointer->push_back(consumption_propensity);
    vec_pointer->push_back(new_savings);
    vec_pointer->push_back(cash_on_hand_real_desired);
    vec_pointer->push_back(cash_on_hand_desired);
    vec_pointer->push_back(cash_on_hand_current);
    vec_pointer->push_back(saving_propensity);
    vec_pointer->push_back(saving_propensity_optimist);
    vec_pointer->push_back(saving_propensity_pessimist);
    vec_pointer->push_back(income_current);
    vec_pointer->push_back(income_average);
    vec_pointer->push_back(income_wage);
    vec_pointer->push_back(income_unemployment_benefit);
    vec_pointer->push_back(income_gov_transfers);
    vec_pointer->push_back(income_firm_owner_dividend);
    vec_pointer->push_back(unemployed);
    vec_pointer->push_back(reservation_wage);
    vec_pointer->push_back(unemp_duration);
    vec_pointer->push_back(unemp_duration_upper_bound);
    vec_pointer->push_back(positive_sentiment);
    vec_pointer->push_back(business_owner);
    vec_pointer->push_back(c_f);
    vec_pointer->push_back(c_h);
    vec_pointer->push_back(c_excess_money);
    vec_pointer->push_back(p_majority_op_adoption);

    return vec_pointer;
}






