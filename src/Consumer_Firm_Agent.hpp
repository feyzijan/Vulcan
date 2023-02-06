#ifndef CONSUMER_FIRM_AGENT_HPP
#define CONSUMER_FIRM_AGENT_HPP

#include "Firm_Agent.hpp"
#include "Consumer_Good.hpp"

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
    ~Consumer_Firm_Agent(); 

    // Main Loop methods
    void Depreciate_Capital();
    void Depreciate_Good_Inventory();
    void Produce_Consumer_Goods();

    // Put up Consumer Goods for Sale
    
    protected:
    Consumer_Good* goods_on_market;

};

// Initialization functions
void Initialize_Consumer_Firms(Consumer_Firm_Agent * Cons_Firm_array, Public_Info_Board* pPublic_Board, int size, int* promised_jobs);
void Post_Initial_Job_Offers_Cons(Consumer_Firm_Agent * Cons_Firm_array, int size);
void Check_Initial_Job_Offers_Cons(Consumer_Firm_Agent * Cons_Firm_array, int size);

#endif
