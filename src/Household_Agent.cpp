#include "Household_Agent.hpp"
#include <iostream>
#include <numeric>


using namespace std;





// New Constructor to use
Household_Agent::Household_Agent(float propensities[7], int unemployment_tolerance, int wealth, Public_Info_Board* pPublic_Board )
{

    wealth_financial = wealth;
    unemp_duration_upper_bound = unemployment_tolerance;

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
    income_past[income_lookback_period] = {};

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
    reservation_wage = 0;  //may set this to minimum wage or make random
}








//Copy constructor
Household_Agent::Household_Agent(Household_Agent&)
{

}



// Destructor
Household_Agent::~Household_Agent()
{

} 


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
    
    Print_Characteristics(); 
    cout << "--------------------------------------" << endl;
}



//------------------------------------------------///

/* Function to update the income_current variable to sum of all incomes received
- Check if the household is employed by checking if current_job pointer points to 0
    - It will do so if fired by the firm *** Firm has to manage this
- If unemployed, add the unemployment_benefits, which should be determined beforehand
*/
void Household_Agent::Update_Income()
{
   
    income_current = 0; // Initialize to zero

    // Check if the person is employed, if so get Wage
    if (!unemployed)
    {
        //income_wage = current_job->Get_Wage_Offer();
        income_current += income_wage;
    } else {
        //If unemployed add the unemp_benefits
        income_current += income_unemployment_benefit;
    }
    // Add any additional transfers
    income_current += income_gov_transfers;
    
    // If business owner add dividends
    if (business_owner){
        income_current += income_firm_owner_dividend;
    }
}



/* Function to set unemployment benefit amount
- This can be positive even if household is unemployed as the Update_Income
function only adds this to the income figure if household is unemployed
*/
void Household_Agent::Assign_Unemployment_Benefits(int unemployment_benefit_amount)
{
    income_unemployment_benefit = pPublic_Info_Board->Get_Unemployment_Benefit();
}



/* Function to update the average income of the past n period
 - Check this works
*/
void Household_Agent::Update_Average_Income()
{
    int n = income_lookback_period;
    int i;
    bool unfilled_array;
    // If past income array has not yet been filled
    for (i=0;i++; i< n)
    {
        if (income_past[i] == 0){
            income_past[i] = income_current;
            unfilled_array =  true;
            break;
        }
    }
    if (!unfilled_array)
    {
        income_past[0] = income_current;

    }

    income_average= accumulate(income_past, income_past + n, income_average);
}


/* Determine Household sentiment, and thereby savings propensity and desired cash on hand
Households randomly adopt majority opinion, otherwise check employment status
- TODO: Update the random probability here
*/

void Household_Agent::Determine_Consumer_Sentiment()
{
    if (unemployed){
        positive_sentiment = false;
    } else{
        positive_sentiment = true;
    }
    
    // some chance it adops majority  - UPDATE METHOD HERE
    bool majority_adoption = (rand() % 100) < p_majority_op_adoption*100;
    if (majority_adoption){
        positive_sentiment = (pPublic_Info_Board->Get_Household_Sentiment() > 0.50); 
    }

    // set saving propensities
    if (positive_sentiment){
        saving_propensity = saving_propensity_optimist;
    } else{
        saving_propensity = saving_propensity_pessimist;
    }

    // Set targets for cash on hand
    cash_on_hand_desired = saving_propensity * income_average;
}



/* Function to determine consumption budget
 - Determine based on how the current income compares to average past income
 - Incorporate savings rate and sentiment
*/
void Household_Agent::Determine_Consumption_Budget()
{
    if (income_current > income_average)
    {
        expenditure_consumption = (1-saving_propensity) * income_current;
    } else {
        int new_c = (1-c_excess_money) * (1-consumption_propensity) + consumption_propensity;
        int price_level = pPublic_Info_Board->Get_Price_Level();
        cash_on_hand_real_desired = cash_on_hand_desired * price_level;
        int consumption_from_income = new_c * income_current;
        int consumption_from_excess_savings = c_excess_money * cash_on_hand_real_desired;
        expenditure_consumption = consumption_from_income + consumption_from_excess_savings ; 
    }

}







/* Function to update financial wealth based on income, consumption, and 
interest earned
- Check to ensure the data types are sufficient to calculate
*/
void Household_Agent::Update_Wealth()
{
    //wealth_financial = (interest_rate_cb + 1.0) * wealth_financial + income_current - expenditure_consumption;
}







/* Function to update reservation wage
 If unemployed for longer than upper bound randomly reduce wage
 - Check what the uniform dist upper bounds should be
*/
void Household_Agent::Update_Reservation_Wage()
{
    if( unemp_duration > unemp_duration_upper_bound)
    {
        std::random_device rd;  // Obtain a seed for the random number engine
        std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dis(0.0, 0.2);
        reservation_wage = reservation_wage * (1-dis(gen));  
    }
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
            current_job->Set_Expiry_Date(pPublic_Info_Board->Get_Current_Date());
            unemployed = false;
            pPublic_Info_Board->Take_Job(current_job);
        }
        else {
            //cout << "job not found" <<endl;
            Update_Reservation_Wage();
        }
    }
    
}



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



// Non Member Function


void Initialize_Households(Household_Agent * Household_array, Public_Info_Board* pPublic_Board, int size)
{   
    cout << "\n Initializing " << size << " households" << endl;
    
    //Set up Random Generators
    Normal_Dist_Generator init_c(init_c_mean, init_c_std, init_c_min, init_c_max);
    Normal_Dist_Generator init_s_optimist(init_s_optimist_mean, init_s_optimist_std, init_s_optimist_min, init_s_optimist_max);
    Normal_Dist_Generator init_s_pessimist(init_s_pessimist_mean, init_s_pessimist_std, init_s_pessimist_min, init_s_pessimist_max);
    Normal_Dist_Generator init_c_f(init_c_f_mean, init_c_f_std, init_c_f_min, init_c_f_max);
    Normal_Dist_Generator init_c_h(init_c_h_mean, init_c_h_std, init_c_h_min, init_c_h_max);
    Normal_Dist_Generator init_c_excess(init_c_excess_mean, init_c_excess_std, init_c_excess_min, init_c_excess_max);
    Normal_Dist_Generator init_p_majority(init_p_majority_mean, init_p_majority_std, init_p_majority_min, init_p_majority_max);
    Normal_Dist_Generator init_wealth(init_wealth_mean, init_wealth_std, init_wealth_min, init_wealth_max);
    Normal_Dist_Generator init_unemp_tolerance(init_unemp_tolerance_mean, init_unemp_tolerance_std, init_unemp_tolerance_min, init_unemp_tolerance_max);
    
    for (int i=0; i<size; i++) {
        float propensities[] = { 
            init_c(), // consumption propensity
            init_s_optimist(), // saving_propensity_optimist 
            init_s_pessimist(), // saving_propensity_pessimist
            init_c_f(), // c_f
            init_c_h(), // c_h
            init_c_excess(), // c_excess_money
            init_p_majority(), // p_majority_op_adoption
         };

        int wealth = int(init_wealth());
        int unemployment_tolerance = int(init_unemp_tolerance());

        Household_array[i] = Household_Agent(propensities, unemployment_tolerance,wealth,pPublic_Board);
        //Household_array[i].Set_Public_Info_Board(pPublic_Board);
        //cout << "The c_h value is " << Household_array[i].Get_C_h() << endl;

    }

}





void Initialize_Household_Jobs(Household_Agent * Household_array,  int size){
       for (int i=0; i<size; i++) {
        //cout << "Now seeking jobs for household # " << i << endl;
        Household_array[i].Seek_Jobs();
    }
}



