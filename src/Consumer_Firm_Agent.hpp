#ifndef CONSUMER_FIRM_AGENT_HPP
#define CONSUMER_FIRM_AGENT_HPP



#include "Firm_Agent.hpp"
#include "Consumer_Good.hpp"


class Consumer_Firm_Agent: public Firm_Agent{

    public:


    //new constructor to use
    Consumer_Firm_Agent(float propensities[3], int assets, int employee_count, int capital_inventory);


    Consumer_Firm_Agent(Consumer_Firm_Agent&); //Copy Constructor
    ~Consumer_Firm_Agent(); // Destructor

    void Print();


    // Put up Consumer Goods for Sale

    protected:
    Consumer_Good* goods_on_market;



};

// Initialization 

void Initialize_Consumer_Firms(Consumer_Firm_Agent * Cons_Firm_array, Public_Info_Board* pPublic_Board, int size, int* promised_jobs);




#endif
