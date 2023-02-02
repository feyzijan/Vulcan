#ifndef DATA_LOGGING_HPP
#define DATA_LOGGING_HPP

#include <string>
#include <fstream>
#include <vector>
#include <utility> // for std::pair
#include <random>


#include "Household_Agent.hpp"
#include "Consumer_Firm_Agent.hpp"
#include "Capital_Firm_Agent.hpp"
#include "Initialization_Parameters.hpp"

// Write given vector pairings to a csv file
void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<float>>> dataset);

// Call write_csv on all households and firms
void Log_Household_Properties(Household_Agent* Household_Agent_Array, int size);

void Log_Cons_Firm_Properties(Consumer_Firm_Agent* Cons_Firm_Array, int size);

void Log_Cap_Firm_Properties(Capital_Firm_Agent* Cap_Firm_Array, int size);

#endif