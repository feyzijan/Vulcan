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
    Consumer_Firm_Agent(float init_values[6]);
    Consumer_Firm_Agent(Consumer_Firm_Agent&); 
    ~Consumer_Firm_Agent() override;

    // Initialization methods t = 1
    virtual void Initialize_Production() override;
    void Initialize_Emission_Allowances();

    // Main Loop methods
    virtual void Depreciate_Good_Inventory() override;
    virtual void Produce_Goods() override;
    virtual void Check_Sales() override;
    virtual void Send_Goods_To_Market() override;
    virtual void Update_Goods_On_Market() override;
    virtual void Random_Experimentation() override;
    virtual void Update_Sentiment() override;
    virtual void Determine_New_Production() override;
    void Buy_Emission_Offsets(long long offsets_neeeded);

    void Assign_Sector(Consumer_Firm_Sector* pSector_Struct);
    void Update_Emission_Allowances();

    // Getters
    virtual float Get_Unit_Emissions() override {return unit_emissions;}
    float Get_Adj_Unit_Emissions() {return unit_emissions_adj;}
    virtual long long Get_Total_Emissions() override {return total_emissions;}

    protected:
    Consumer_Good* cons_goods_on_market;

    // CO2 Emissions
    float unit_emissions; // NEWLY ADDDED
    float unit_emissions_adj; // NEWLY ADDDED
    long long total_emissions; // NEWLY ADDDED

    // Emission allowances
    long long emission_total_allowance;

};


#endif
