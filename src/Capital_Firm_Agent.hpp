#ifndef CAPITAL_FIRM_AGENT_HPP
#define CAPITAL_FIRM_AGENT_HPP


#include "Capital_Good.hpp"
#include "Firm_Agent.hpp"

#include "Random_Functions.hpp"
#include "Initialization_Parameters.hpp"



class Capital_Firm_Agent: public Firm_Agent{

    public:
    //Constructors and Destructor
    Capital_Firm_Agent(float float_vals[4], int int_vals[6]);
    Capital_Firm_Agent(Capital_Firm_Agent&); 
    ~Capital_Firm_Agent(); 

    // Main Loop methods
    /* void Depreciate_Capital(); */
    void Depreciate_Good_Inventory();
    void Produce_Capital_Goods();
    void Send_Goods_To_Market();

    protected:
    Capital_Good* cap_goods_on_market;



};




#endif