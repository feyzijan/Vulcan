
#ifndef INITIALIZATION_FUNCTIONS_HPP
#define  INITIALIZATION_FUNCTIONS_HPP


#include <iostream>
#include <vector>

#include "Firm_Agent.hpp"
#include "Consumer_Firm_Agent.hpp"
#include "Capital_Firm_Agent.hpp"
#include "Household_Agent.hpp"
#include "Public_Info_Board.hpp"
#include "Initialization_Parameters.hpp"

using namespace std;

// Function to set up Job market at t=0
void Initialize_Job_Market(vector<Household_Agent*> *pHousehold_vector,
    vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, vector<Capital_Firm_Agent*> *pCapital_Firm_vector,
    Public_Info_Board* pPublic_Info_Board);



#endif