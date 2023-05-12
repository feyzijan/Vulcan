#ifndef CONSUMER_FIRM_AGENT_HPP
#define CONSUMER_FIRM_AGENT_HPP

#include "Firm_Agent.hpp"
#include "Consumer_Good.hpp"
#include "Capital_Good.hpp"
#include "Random_Functions.hpp"
#include "Initialization_Parameters.hpp"

#include <iostream>
#include <vector>
using namespace std;

class Consumer_Firm_Agent: public Firm_Agent{

    public:
    //Constructors and Destructor
    Consumer_Firm_Agent(float float_vals[4], int int_vals[6]);
    Consumer_Firm_Agent(Consumer_Firm_Agent&); 
    ~Consumer_Firm_Agent() override;

    // Main Loop methods
    /* void Depreciate_Capital(); */
    virtual void Depreciate_Good_Inventory() override;
    virtual void Produce_Goods() override;
    virtual void Send_Goods_To_Market() override;
    virtual void Update_Goods_On_Market() override;
    virtual void Update_Sentiment() override;

    void Assign_Sector(Consumer_Firm_Sector* pSector_Struct);

    // Put up Consumer Goods for Sale
    
    protected:
    Consumer_Good* cons_goods_on_market;


};


#endif
