#ifndef DATA_LOGGING_HPP
#define DATA_LOGGING_HPP

#include <string>
#include <sstream>
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
void Log_Household_Properties(vector<Household_Agent*> *pHousehold_vectory, int size);

void Log_Cons_Firm_Properties(vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, int size);

void Log_Cap_Firm_Properties(vector<Capital_Firm_Agent*> *pCapital_Firm_vector, int size);

void Log_Firm_Properties(vector<Firm_Agent*> *pFirm_vector, int size);

void Log_Everything(vector<Household_Agent*> *pHousehold_vector,
    vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector,vector<Capital_Firm_Agent*> *pCapital_Firm_vector, 
    int n_households, int n_consumer_firms, int n_capital_firms);

#endif