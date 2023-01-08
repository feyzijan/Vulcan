#include "Capital_Firm_Agent.hpp"




// Constructor
Capital_Firm_Agent::Capital_Firm_Agent(int employee_count, int savings, int wage,int assets,
    float dividend_ratio_opt, float dividend_ratio_pes, int desired_inventory_factor, bool sentiment)
{
    this->employee_count = employee_count;
    this->cash_on_hand = savings;
    this->wage_offer = wage;
    this->total_assets = assets;
    this->dividend_ratio_optimist = dividend_ratio_opt;
    this->dividend_ratio_pessimist = dividend_ratio_pes;
    this->desired_inventory_factor = desired_inventory_factor;
    this->sentiment = sentiment;

    // Some other stuff need to be initialized as well, not sure what to
    /*
    this->production_past;
    this->good_price_past;
    this->quantity_sold;
    this->inventory;
    this->capital_goods_inventory;
    */

    // Some stuff is clear to initialize
    this->bankrupt = false;




    //loan_book = {NULL}; // sett all elements to null

}


// Constructor
Capital_Firm_Agent::Capital_Firm_Agent()
{

}





//Copy constructor
Capital_Firm_Agent::Capital_Firm_Agent(Capital_Firm_Agent&)
{

}



// Destructor
Capital_Firm_Agent::~Capital_Firm_Agent()
{

} 

