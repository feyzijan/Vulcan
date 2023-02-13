#ifndef CAPITAL_FIRM_AGENT_HPP
#define CAPITAL_FIRM_AGENT_HPP


#include "Capital_Good.hpp"
#include "Firm_Agent.hpp"

#include "Random_Functions.hpp"
#include "Initialization_Parameters.hpp"



class Capital_Firm_Agent: public Firm_Agent{

    public:
    //Constructors and Destructor
    Capital_Firm_Agent(float float_vals[4], int int_vals[6]);
    Capital_Firm_Agent(Capital_Firm_Agent&); 
    ~Capital_Firm_Agent(); 

    // Main Loop methods
    /* void Depreciate_Capital(); */
    void Depreciate_Good_Inventory();
    void Produce_Capital_Goods();
    void Send_Goods_To_Market();

    protected:
    Capital_Good* goods_on_market;



};


// Initialization 

void Initialize_Capital_Firms(vector<Capital_Firm_Agent*> *pCapital_Firm_vector, Public_Info_Board* pPublic_Board, int size, int* promised_jobs);


void Post_Initial_Job_Offers_Cap(vector<Capital_Firm_Agent*> *pCapital_Firm_vector, int size);

void Check_Initial_Job_Offers_Cap(vector<Capital_Firm_Agent*> *pCapital_Firm_vector, int size);



#endif