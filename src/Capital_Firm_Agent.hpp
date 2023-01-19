#ifndef CAPITAL_FIRM_AGENT_HPP
#define CAPITAL_FIRM_AGENT_HPP


#include "Capital_Good.hpp"
#include "Firm_Agent.hpp"



class Capital_Firm_Agent: public Firm_Agent{

    public:


    Capital_Firm_Agent(float propensities[3], int assets, int employee_count, int capital_inventory);
    



    Capital_Firm_Agent(Capital_Firm_Agent&); //Copy Constructor
    ~Capital_Firm_Agent(); // Destructor

    void Print();

    protected:
    //Capital_Good* goods_on_market;



};


// Initialization 

void Initialize_Capital_Firms(Capital_Firm_Agent * Cap_Firm_array, Public_Info_Board* pPublic_Board, int size, int* promised_jobs);


void Post_Initial_Job_Offers_Cap(Capital_Firm_Agent * Cap_Firm_array, int size);




#endif