#include "Data_Logging.hpp"

using namespace std;

void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<float>>> dataset){
    // Make a CSV file with one or more columns of integer
    // Each column of data is represented by the pair <column name, column data>
    //   as std::pair<std::string, std::vector<int>>
    // The dataset is represented as a vector of these columns
    // Note that all columns should be the same size
    
    // Create an output filestream object
    std::ofstream myFile("DataLogs/" +filename);
    
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



/* TODO: Later separate function for float, int, bool values
*/
void Log_Household_Properties(Household_Agent* Household_Agent_Array, int size)
{
    // Declare the vectors
    std::vector<float> vec_wealth_financial; //int
    std::vector<float> vec_wealth_human;//int
    std::vector<float> vec_expenditure_consumption;//int
    std::vector<float> vec_expenditure_tax;//int
    
    std::vector<float> vec_consumption_propensity;

    std::vector<float> vec_new_savings; //int
    std::vector<float> vec_cash_on_hand_real_desired; //int
    std::vector<float> vec_cash_on_hand_desired; //int
    std::vector<float> vec_cash_on_hand_current;//int

    std::vector<float> vec_savings_propensity;
    std::vector<float> vec_savings_propensity_optimist;
    std::vector<float> vec_savings_propensity_pessimist;

    std::vector<float> vec_income_current;//int
    std::vector<float> vec_income_average;//int
    std::vector<float> vec_income_wage;//int
    std::vector<float> vec_income_unemployment_benefit;//int
    std::vector<float> vec_income_gov_transfers;//int
    std::vector<float> vec_income_firm_owner_dividend;//int

    std::vector<float> vec_unemployed; //bool
    std::vector<float> vec_reservation_wage; //int
    std::vector<float> vec_unemp_duration; //int
    std::vector<float> vec_unemp_duration_upper_bound; //int

    std::vector<float> vec_sentiment;//bool
    std::vector<float> vec_business_owner; //bool

    std::vector<float> vec_c_f;
    std::vector<float> vec_c_h;
    std::vector<float> vec_c_excess_money;
    std::vector<float> vec_p_majority_adoption;
    
    // Loop through household array and fill arrays

    size = 4;
    for (int i=0;i<size;i++){

        vector<float>* pvec_params = Household_Agent_Array[i].Get_All_Params();

      /*   std::vector<float>* pvec_params = new std::vector<float>;
        std::default_random_engine generator;
        std::uniform_real_distribution<float> distribution(0.0,1.0);
        for (int i = 0; i < 30; i++) {
            pvec_params->push_back(distribution(generator));
        } */

        int k = 0;

        vec_wealth_financial.push_back(pvec_params->at(k++)); 
        vec_wealth_human.push_back(pvec_params->at(k++));
        vec_expenditure_consumption.push_back(pvec_params->at(k++));
        vec_expenditure_tax.push_back(pvec_params->at(k++));

        vec_consumption_propensity.push_back(pvec_params->at(k++));

        vec_new_savings.push_back(pvec_params->at(k++)); 
        vec_cash_on_hand_real_desired.push_back(pvec_params->at(k++));
        vec_cash_on_hand_desired.push_back(pvec_params->at(k++));
        vec_cash_on_hand_current.push_back(pvec_params->at(k++));

        vec_savings_propensity.push_back(pvec_params->at(k++));
        vec_savings_propensity_optimist.push_back(pvec_params->at(k++));
        vec_savings_propensity_pessimist.push_back(pvec_params->at(k++));

        vec_income_current.push_back(pvec_params->at(k++));
        vec_income_average.push_back(pvec_params->at(k++));
        vec_income_wage.push_back(pvec_params->at(k++));
        vec_income_unemployment_benefit.push_back(pvec_params->at(k++));
        vec_income_gov_transfers.push_back(pvec_params->at(k++));
        vec_income_firm_owner_dividend.push_back(pvec_params->at(k++));

        vec_unemployed.push_back(pvec_params->at(k++)); 
        vec_reservation_wage.push_back(pvec_params->at(k++)); 
        vec_unemp_duration.push_back(pvec_params->at(k++)); 
        vec_unemp_duration_upper_bound.push_back(pvec_params->at(k++)); 

        vec_sentiment.push_back(pvec_params->at(k++));
        vec_business_owner.push_back(pvec_params->at(k++)); 

        vec_c_f.push_back(pvec_params->at(k++));
        vec_c_h.push_back(pvec_params->at(k++));
        vec_c_excess_money.push_back(pvec_params->at(k++));
        vec_p_majority_adoption.push_back(pvec_params->at(k++));

        k=0;

        delete[] pvec_params;

    }

    // Store vectors as pairs with column names

    vector<pair<string, vector<float>>> vals = {{ "wealth_human", vec_wealth_financial }, { "expenditure_consumption", vec_expenditure_consumption }, 
    { "expenditure_tax", vec_expenditure_tax }, { "consumption_propensity", vec_consumption_propensity }, { "new_savings", vec_new_savings }, 
    { "cash_on_hand_real_desired", vec_cash_on_hand_real_desired }, { "cash_on_hand_desired", vec_cash_on_hand_desired }, 
    { "cash_on_hand_current", vec_cash_on_hand_current }, { "saving_propensity", vec_savings_propensity }, 
    { "saving_propensity_optimist", vec_savings_propensity_optimist }, { "saving_propensity_pessimist", vec_savings_propensity_pessimist }, 
    { "income_current", vec_income_current }, { "income_average", vec_income_average }, { "income_wage", vec_income_wage }, 
    { "income_unemployment_benefit", vec_income_unemployment_benefit }, { "income_gov_transfers", vec_income_gov_transfers }, 
    { "income_firm_owner_dividend", vec_income_firm_owner_dividend }, { "unemployed", vec_unemployed }, { "reservation_wage", vec_reservation_wage },
     { "unemp_duration", vec_unemp_duration }, { "unemp_duration_upper_bound", vec_unemp_duration_upper_bound }, { "positive_sentiment", vec_sentiment }, 
     { "business_owner", vec_business_owner }, { "c_f", vec_c_f }, { "c_h", vec_c_h }, { "c_excess_money", vec_c_excess_money }, 
     { "p_majority_op_adoption", vec_p_majority_adoption }};



    write_csv("HouseholdDataInit.csv",vals);


    


}