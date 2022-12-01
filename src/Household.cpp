#include "Household.hpp"
#include <iostream>
#include <numeric>
using namespace std;


int main(){
    return 0;
}




// Constructor
Household_Agent::Household_Agent(int initial_savings)
{
    initial_savings = initial_savings;

}





//Copy constructor
Household_Agent::Household_Agent(Household_Agent&)
{

}



// Destructor
Household_Agent::~Household_Agent()
{

} 



void Household_Agent::Compare_Job_Offers()
{

    
}


/* Function to update financial wealth based on income, consumption, and 
interest earned*/
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