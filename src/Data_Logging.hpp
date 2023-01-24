#ifndef DATA_LOGGING_HPP
#define DATA_LOGGING_HPP

#include <string>
#include <fstream>
#include <vector>
#include <utility> // std::pair
#include <random>


#include "Household_Agent.hpp"
#include "Firm_Agent.hpp"


void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<float>>> dataset);

void Log_Household_Properties(Household_Agent* Household_Agent_Array, int size);

void Log_Firm_Properties(Firm_Agent* Firm_Array, int size);


#endif