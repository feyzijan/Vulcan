#include "Data_Logging.hpp"

using namespace std;


void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<float>>> dataset){
    // Make a CSV file with one or more columns of integer
    // Each column of data is represented by the pair <column name, column data>
    //   as std::pair<std::string, std::vector<int>>
    // The dataset is represented as a vector of these columns
    // Note that all columns should be the same size
    
    // Create an output filestream object
    std::ofstream myFile("../DataLogs/" +filename);
    
    // Send column names to the stream
    for(int j = 0; j < dataset.size(); ++j)
    {
        myFile << dataset.at(j).first;
        if(j != dataset.size() - 1) myFile << ","; // No comma at end of line
    }
    myFile << "\n";
    
    // Send data to the stream
    for(int i = 0; i < dataset.at(0).second.size(); ++i)
    {
        for(int j = 0; j < dataset.size(); ++j)
        {
            myFile << dataset.at(j).second.at(i);
            if(j != dataset.size() - 1) myFile << ","; // No comma at end of line
        }
        myFile << "\n";
    }
    
    // Close the file
    myFile.close();
}


/* Function to log public info board
*/

void Log_Public_Info_Board(Public_Info_Board* pPublic_Info_Board) {
    // Open file for writing in append mode
    std::ofstream log_file;
    log_file.open("../DataLogs/Public_Info_Board.csv", std::ios_base::app);

    // Write header row if file is empty
    static bool header_written = false;

    // If file is empty, write the header row
    if (!header_written && log_file.tellp() == 0) {
        // Get the header row
        std::vector<std::pair<std::string, float>>* header_data = pPublic_Info_Board->Log_Data();
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

    // Get the data row
    std::vector<std::pair<std::string, float>>* data = pPublic_Info_Board->Log_Data();
    std::string row;
    for (auto it = data->begin(); it != data->end(); ++it) {
        row += std::to_string(it->second) + ",";
    }
    row.pop_back();
    row += "\n";
    log_file << row;

    delete data;
    log_file.close(); 
}

void Log_Bank(Bank_Agent *pBank){
        // Open file for writing in append mode
    std::ofstream log_file;
    log_file.open("../DataLogs/Bank.csv", std::ios_base::app);

    // Write header row if file is empty
    static bool header_written = false;

    // If file is empty, write the header row
    if (!header_written && log_file.tellp() == 0) {
        // Get the header row
        std::vector<std::pair<std::string, float>>* header_data = pBank->Log_Data();
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

    // Get the data row
    std::vector<std::pair<std::string, float>>* data = pBank->Log_Data();
    std::string row;
    for (auto it = data->begin(); it != data->end(); ++it) {
        row += std::to_string(it->second) + ",";
    }
    row.pop_back();
    row += "\n";
    log_file << row;

    delete data;
    log_file.close(); 
}



/* Function to log all firm data 
*/
void Log_Households(std::vector<Household_Agent*>* pHousehold_vector) {
    // Open file for writing in append mode

    std::ofstream log_file;
    log_file.open("../DataLogs/Households.csv", std::ios_base::app);

    // Write header row if file is empty
    static bool header_written = false;

    // If file is empty, write the header row
    if (!header_written && log_file.tellp() == 0) {
        // Get the header row from the first firm
        std::vector<std::pair<std::string, float>>* header_data = (*pHousehold_vector)[0]->Log_Data();
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
    for (auto h_ptr : *pHousehold_vector) {
        std::vector<std::pair<std::string, float>>* data = h_ptr->Log_Data();
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





void Log_Everything(vector<Household_Agent*> *pHousehold_vector,vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector,
vector<Capital_Firm_Agent*> *pCapital_Firm_vector,Public_Info_Board *pPublic_Info_Board,Bank_Agent *pBank){
    Log_Firms(pConsumer_Firm_vector,true);
    Log_Firms(pCapital_Firm_vector,false);
    Log_Households(pHousehold_vector);
    Log_Public_Info_Board(pPublic_Info_Board);
    Log_Bank(pBank);
}