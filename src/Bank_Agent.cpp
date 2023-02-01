#include "Bank_Agent.hpp"


// Constructor
Bank_Agent::Bank_Agent(){


    r_rate = initial_interest_rate; // set globally


    inflation_previous = 1.0;
    for(int i=1;i<=12;i++){
        inflation_previous *= inflation_target_monthly;
        inflation_history.push(inflation_target_monthly);
    }

}





//Copy constructor
Bank_Agent::Bank_Agent(Bank_Agent&)
{

}



// Destructor
Bank_Agent::~Bank_Agent()
{

}




/* Function to update price level and inflation rate
Get the latest inflation figure from the public board
*/
void Bank_Agent::Update_Inflation_Rate(){
    
    inflation_previous = inflation_current;
    inflation_past_month = pPublic_Board->Calculate_Inflation();

    inflation_current = inflation_previous / inflation_history.front() * inflation_past_month;

    inflation_history.pop();
    inflation_history.push(inflation_past_month);
}




/* Call this at timestep T=1 to initialize price level
*/



/* Function to update interest rate based on inflation gathered from the consumer goods market
*/
void Bank_Agent::Update_Interest_Rate(){
    Update_Inflation_Rate();

    float inflation_overshoot = inflation_current - inflation_target;

    r_rate = max( double(inflation_reaction* inflation_overshoot), 0.0); // Simplest interest rate rule - From Jamel paper

    /* Alternative interest rate rule:
    r_rate = max(r_target + a*(inflation_current - inflation_target) + b*(output_current - output_target),0)
    */
}

// -- Printing and Logging Methods


void Bank_Agent::Print_Inflation_History(){
    queue<float> temp;
    temp = inflation_history;
    cout << "Inflation History: " << endl;
    while(!temp.empty()){
        cout << temp.front() << endl;
        temp.pop();
    }
}