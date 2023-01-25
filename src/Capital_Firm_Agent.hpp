#ifndef CAPITAL_FIRM_AGENT_HPP
#define CAPITAL_FIRM_AGENT_HPP


#include "Capital_Good.hpp"
#include "Firm_Agent.hpp"

#include "Random_Functions.hpp"
#include "Initialization_Parameters.hpp"



class Capital_Firm_Agent: public Firm_Agent{

    public:


    Capital_Firm_Agent(float float_vals[4], int int_vals[6]);



    Capital_Firm_Agent(Capital_Firm_Agent&); //Copy Constructor
    ~Capital_Firm_Agent(); // Destructor

    void Print();

    protected:
    //Capital_Good* goods_on_market;



};


// Initialization 

void Initialize_Capital_Firms(Capital_Firm_Agent * Cap_Firm_array, Public_Info_Board* pPublic_Board, int size, int* promised_jobs);


void Post_Initial_Job_Offers_Cap(Capital_Firm_Agent * Cap_Firm_array, int size);

void Check_Initial_Job_Offers_Cap(Capital_Firm_Agent * Cap_Firm_array, int size);



#endif