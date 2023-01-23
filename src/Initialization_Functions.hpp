
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


void Initialize_Job_Market(Consumer_Firm_Agent* Cons_Firm_array,
Capital_Firm_Agent* Cap_Firm_array, Household_Agent* Household_array,
Public_Info_Board* pPublic_Info_Board);

#endif