#ifndef CAPITAL_FIRM_AGENT_HPP
#define CAPITAL_FIRM_AGENT_HPP


#include "Initialization_Parameters.hpp"
#include "Capital_Good.hpp"
#include "Firm_Agent.hpp"
#include "Random_Functions.hpp"



class Capital_Firm_Agent: public Firm_Agent{

    public:
    // Constructors and Destructor
    Capital_Firm_Agent(float init_values[7]);
    Capital_Firm_Agent(Capital_Firm_Agent&); 
    ~Capital_Firm_Agent() override;

    // Initialization methods t = 1
    virtual void Initialize_Production() override;

    // Main Loop methods
    virtual void Depreciate_Good_Inventory() override;
    virtual void Produce_Goods() override;
    virtual void Check_Sales() override;
    virtual void Update_Goods_On_Market() override;
    virtual void Random_Experimentation() override;
    virtual void Update_Sentiment() override;
    virtual void Determine_New_Production() override;

    // Getters
    virtual float Get_Unit_Emissions() override {return 0;} 
    virtual long long Get_Total_Emissions() override {return 0;}

    protected:
    Capital_Good* cap_goods_on_market; // Object: 

};




#endif