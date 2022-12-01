#include "Household.hpp"
#include <iostream>
#include <numeric>
using namespace std;



// Constructor
Household_Agent::Household_Agent(int initial_savings, int max_unemp_dur)
{
    initial_savings = initial_savings;
    unemp_duration_upper_bound = max_unemp_dur;
}





//Copy constructor
Household_Agent::Household_Agent(Household_Agent&)
{

}



// Destructor
Household_Agent::~Household_Agent()
{

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


/* Function to check if the household is willing to take the 
highest paying job in the job board
- *** Check the job offer pointer assignment works
- Need to assign new income somewhere
*/
void Household_Agent::Seek_Jobs(Job_Board* job_board)
{
    // Get the top job offer
    Job_Offer * job_offer = job_board->Get_Job_List(); 

    // Compare against reservation wage
    if (job_offer->Get_Wage_Offer() > reservation_wage)
    {
        current_job = job_offer; // set pointers equal
        unemployed = false; // now employed
        job_board->Remove_Top_Job_Offer(); // Remove job offer form board
    } else{
        // Update reservation wage and seek job in next period
        Update_Reservation_Wage();
    }
}


/* Function to update financial wealth based on income, consumption, and 
interest earned
- Check to ensure the data types are sufficient to calculate
*/
void Household_Agent::Update_Wealth()
{
    int new_wealth = (interest_rate_cb + 1.0) * wealth_financial + income_current - expenditure_consumption;
    wealth_financial = new_wealth;
}



/* Function to update the average income of the past n period
 - Check this works
*/
void Household_Agent::Update_Average_Income()
{
    int n = average_income_lookback_period;
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