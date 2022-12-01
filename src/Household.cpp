#include "Household.hpp"
#include <iostream>
#include <string>

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

void Household_Agent::Update_Average_Income()
{
    int n = average_income_lookback_period;
    // Check if past income array is full
    for (int i=0;i++; i< n)
    {
        
    }

}