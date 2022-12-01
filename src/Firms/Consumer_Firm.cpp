#include "Consumer_Firm.hpp"
#include <iostream>

int main(){
    return 0;
}




// Constructor
Consumer_Firm_Agent::Consumer_Firm_Agent()
{

}





//Copy constructor
Consumer_Firm_Agent::Consumer_Firm_Agent(Consumer_Firm_Agent&)
{

}



// Destructor
Consumer_Firm_Agent::~Consumer_Firm_Agent()
{

} 



void Consumer_Firm_Agent::Plan_Production()
{
    int n_uniform = 1; //Update this to be from uniform dist

    if (Inventory_Above_Desire())
    {
        planned_production = current_production *  (1 + n_uniform);
    } else {
        good_price = current_production *  (1 - n_uniform);
    }

}


void Consumer_Firm_Agent::Update_Price()
{
    //int current_price = GetPrice();
    //n_uniform = uniform_dist(0,0.5);
    float n_uniform = 1; //Update this to be from uniform dist

    if (Inventory_Above_Desire())
    {
        good_price *= (1 + n_uniform);
    } else{
        good_price *= (1 - n_uniform);
    }


}

void Consumer_Firm_Agent::Adjust_Wage_Offers()
{
    float w_stoc; // a stochastic cutoff value for labor
    float n_uniform; // value drawn from uniform dist

    if (w_current - w_target >= w_current)
    {
        wage_offer*= (1+n_uniform);
    } else{
        wage_offer*= (1-n_uniform);
    }


}
