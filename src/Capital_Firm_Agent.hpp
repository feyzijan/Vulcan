#ifndef CAPITAL_FIRM_AGENT_HPP
#define CAPITAL_FIRM_AGENT_HPP


#include "Capital_Good.hpp"
#include "Firm_Agent.hpp"



class Capital_Firm_Agent: public Firm_Agent{

    public:
    
    Capital_Firm_Agent(); // Constructor

    Capital_Firm_Agent(int employee_count, int savings, int wage,int assets,
    float dividend_ratio_opt, float dividend_ratio_pes, int desired_inventory_factor, bool sentiment); // Constructor

    Capital_Firm_Agent(Capital_Firm_Agent&); //Copy Constructor
    ~Capital_Firm_Agent(); // Destructor

    void Print();

    protected:
    //Capital_Good* goods_on_market;



};


#endif