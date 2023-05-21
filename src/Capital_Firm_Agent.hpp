#ifndef CAPITAL_FIRM_AGENT_HPP
#define CAPITAL_FIRM_AGENT_HPP


#include "Capital_Good.hpp"
#include "Firm_Agent.hpp"

#include "Random_Functions.hpp"
#include "Initialization_Parameters.hpp"



class Capital_Firm_Agent: public Firm_Agent{

    public:
    // Constructors and Destructor
    Capital_Firm_Agent(float float_vals[4], int int_vals[6]);
    Capital_Firm_Agent(Capital_Firm_Agent&); 
    ~Capital_Firm_Agent() override;

    // Main Loop methods
    virtual void Depreciate_Good_Inventory() override;
    virtual void Produce_Goods() override;
    virtual void Send_Goods_To_Market() override;
    virtual void Update_Goods_On_Market() override;
    virtual void Update_Sentiment() override;
    virtual void Determine_New_Production() override;

    protected:
    Capital_Good* cap_goods_on_market;

    

};




#endif