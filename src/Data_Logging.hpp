#ifndef DATA_LOGGING_HPP
#define DATA_LOGGING_HPP

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility> // for std::pair
#include <random>
#include <iostream>
#include <type_traits>



#include "Household_Agent.hpp"
#include "Consumer_Firm_Agent.hpp"
#include "Capital_Firm_Agent.hpp"
#include "Initialization_Parameters.hpp"
#include "Public_Info_Board.hpp"

// Write given vector pairings to a csv file
void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<float>>> dataset);

void Log_Everything(vector<Household_Agent*> *pHousehold_vector, vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector,
vector<Capital_Firm_Agent*> *pCapital_Firm_vector,Public_Info_Board *pPublic_Info_Board);


void Log_Households(std::vector<Household_Agent*>* pHousehold_vector);

void Log_Public_Info_Board(Public_Info_Board *pPublic_Info_Board);



/* Function to log all firm data - func is either passed a consumer or capital firm vector
*/
template <typename T>
void Log_Firms(std::vector<T*>* pFirm_vector, bool cons_firm) {
    // Open file for writing in append mode
    
    std::string file_name = cons_firm ? "../DataLogs/Consumer_Firms.csv" : "../DataLogs/Capital_Firms.csv";

    std::ofstream log_file;
    log_file.open(file_name, std::ios_base::app);

    // Write header row if file is empty
    static bool header_written = false;

    // If file is empty, write the header row
    if (!header_written && log_file.tellp() == 0) {
        // Get the header row from the first firm
        std::vector<std::pair<std::string, float>>* header_data = (*pFirm_vector)[0]->Log_Data();
        std::string header;
        for (auto it = header_data->begin(); it != header_data->end(); ++it) {
            header += it->first + ",";
        }
        header.pop_back();
        header += "\n";
        log_file << header;

        delete header_data;
        header_written = true;
    }

    // Write data rows for all firms
    for (auto firm_ptr : *pFirm_vector) {
        std::vector<std::pair<std::string, float>>* data = firm_ptr->Log_Data();
        std::string row;
        for (auto it = data->begin(); it != data->end(); ++it) {
            row += std::to_string(it->second) + ",";
        }
        row.pop_back();
        row += "\n";
        log_file << row;

        delete data;
    }

    log_file.close(); 
}




#endif