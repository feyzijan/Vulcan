#ifndef CONSUMER_FIRM_AGENT_HPP
#define CONSUMER_FIRM_AGENT_HPP



#include "Firm_Agent.hpp"
#include "Consumer_Good.hpp"


class Consumer_Firm_Agent: public Firm_Agent{

    public:
    
    Consumer_Firm_Agent(int employee_count, int savings, int wage,int assets,
    float dividend_ratio_opt, float dividend_ratio_pes, int desired_inventory_factor, bool sentiment); // Constructor
    
    Consumer_Firm_Agent(Consumer_Firm_Agent&); //Copy Constructor
    ~Consumer_Firm_Agent(); // Destructor

    void Print();


    // Put up Consumer Goods for Sale

    protected:
    Consumer_Good* goods_on_market;



};

#endif
