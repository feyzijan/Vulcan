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



/* TODO: - Separate functions for float, int, bool values
 - Check if the memory is freed from the vector
 - Use the global firm, household size variables
*/

void Log_Household_Properties(Household_Agent* Household_Agent_Array, int size)
{
    cout << "Logging Household data: start" <<endl;
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
    vector<float>* pvec_params;

    //size = 4;
    for (int i=0;i<size;i++){
        
        pvec_params = Household_Agent_Array[i].Get_All_Params();

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

        //delete[] pvec_params;

        pvec_params->clear();
        pvec_params->shrink_to_fit();
    }

    // Store vectors as pairs with column names

    vector<pair<string, vector<float>>> vals = {{ "wealth_human", vec_wealth_financial }, 
    { "expenditure_consumption", vec_expenditure_consumption }, { "expenditure_tax", vec_expenditure_tax }, 
    { "consumption_propensity", vec_consumption_propensity }, { "new_savings", vec_new_savings }, 
    { "cash_on_hand_real_desired", vec_cash_on_hand_real_desired }, { "cash_on_hand_desired", vec_cash_on_hand_desired }, 
    { "cash_on_hand_current", vec_cash_on_hand_current }, { "saving_propensity", vec_savings_propensity }, 
    { "saving_propensity_optimist", vec_savings_propensity_optimist }, { "saving_propensity_pessimist", vec_savings_propensity_pessimist }, 
    { "income_current", vec_income_current }, { "income_average", vec_income_average }, { "income_wage", vec_income_wage }, 
    { "income_unemployment_benefit", vec_income_unemployment_benefit }, { "income_gov_transfers", vec_income_gov_transfers }, 
    { "income_firm_owner_dividend", vec_income_firm_owner_dividend }, { "unemployed", vec_unemployed }, { "reservation_wage", vec_reservation_wage },
     { "unemp_duration", vec_unemp_duration }, { "unemp_duration_upper_bound", vec_unemp_duration_upper_bound }, { "positive_sentiment", vec_sentiment }, 
     { "business_owner", vec_business_owner }, { "c_f", vec_c_f }, { "c_h", vec_c_h }, { "c_excess_money", vec_c_excess_money }, 
     { "p_majority_op_adoption", vec_p_majority_adoption }};


    std::stringstream ss;
    ss << "HouseholdDataInit_t_" << global_date <<".csv";
    std::string filename = ss.str();

    write_csv(filename,vals);
    cout << "Logging Household data: end" <<endl;
}


void Log_Cons_Firm_Properties(Consumer_Firm_Agent* Cons_Firm_Array, int size)
{
    cout << "Logging Cons Firm data: start" <<endl;
    // Declare the vectors

    std::vector<float> vec_production_current;
    std::vector<float> vec_production_planned;
    std::vector<float> vec_production_past;
    std::vector<float> vec_quantity_sold;

    std::vector<float> vec_total_income;
    std::vector<float> vec_revenue_sales;
    std::vector<float> vec_new_loan_issuance;
    std::vector<float> vec_subsidies;
    std::vector<float> vec_good_price_current;//float
    std::vector<float> vec_good_price_past;//float

    std::vector<float> vec_total_liabilities;
    std::vector<float> vec_labor_wage_bill;
    std::vector<float> vec_capital_costs;
    std::vector<float> vec_tax_payments;
    std::vector<float> vec_debt_principal_payments;
    std::vector<float> vec_debt_interest_payments;
    std::vector<float> vec_dividend_payments;

    std::vector<float> vec_total_assets;
    std::vector<float> vec_leverage_ratio;
    std::vector<float> vec_cash_on_hand;

    std::vector<float> vec_dividend_ratio;//float
    std::vector<float> vec_dividend_ratio_optimist;//float
    std::vector<float> vec_dividend_ratio_pessimist;//float

    std::vector<float> vec_employee_count;
    std::vector<float> vec_wage_offer;
    std::vector<float> vec_employee_count_desired;
    std::vector<float> vec_n_active_job_postings;
    std::vector<float> vec_need_worker; //bool
    std::vector<float> vec_w_target;
    std::vector<float> vec_w_current;

    std::vector<float> vec_inventory;
    std::vector<float> vec_working_capital_inventory;
    std::vector<float> vec_desired_inventory_factor; //float
    std::vector<float> vec_inventory_factor; //float

    std::vector<float> vec_sentiment; //bool
    std::vector<float> vec_bankrupt; //bool
    std::vector<float> vec_is_cons_firm; //bool

    std::vector<float> vec_average_profit;
    std::vector<float> vec_average_sale_quantity;
    std::vector<float> vec_short_term_funding_gap;
    std::vector<float> vec_long_term_funding_gap;
    std::vector<float> vec_expected_wage_bill;
    std::vector<float> vec_layoff_wage_savings;
    std::vector<float> vec_expected_wage_bill_shortfall;
    std::vector<float> vec_expected_long_term_shortfall;
    std::vector<float> vec_labor_utilization;
    std::vector<float> vec_desired_inventory;
    std::vector<float> vec_inventory_reaction_factor;
    std::vector<float> vec_machine_utilization;
    std::vector<float> vec_desired_machines;

    // Loop through Firm array and fill arrays
    vector<float>* pvec_params;

    int k = 0;

    for (int i=0;i<size;i++){
        
        pvec_params = Cons_Firm_Array[i].Get_All_Params();

        vec_production_current.push_back(pvec_params->at(k++));
        vec_production_planned.push_back(pvec_params->at(k++));
        vec_production_past.push_back(pvec_params->at(k++));
        vec_quantity_sold.push_back(pvec_params->at(k++));

        vec_total_income.push_back(pvec_params->at(k++));
        vec_revenue_sales.push_back(pvec_params->at(k++));
        vec_new_loan_issuance.push_back(pvec_params->at(k++));
        vec_subsidies.push_back(pvec_params->at(k++));
        vec_good_price_current.push_back(pvec_params->at(k++));
        vec_good_price_past.push_back(pvec_params->at(k++));

        vec_total_liabilities.push_back(pvec_params->at(k++));
        vec_labor_wage_bill.push_back(pvec_params->at(k++));
        vec_capital_costs.push_back(pvec_params->at(k++));
        vec_tax_payments.push_back(pvec_params->at(k++));
        vec_debt_principal_payments.push_back(pvec_params->at(k++));
        vec_debt_interest_payments.push_back(pvec_params->at(k++));
        vec_dividend_payments.push_back(pvec_params->at(k++));

        vec_total_assets.push_back(pvec_params->at(k++));
        vec_leverage_ratio.push_back(pvec_params->at(k++));
        vec_cash_on_hand.push_back(pvec_params->at(k++));

        vec_dividend_ratio.push_back(pvec_params->at(k++));
        vec_dividend_ratio_optimist.push_back(pvec_params->at(k++));
        vec_dividend_ratio_pessimist.push_back(pvec_params->at(k++));
        vec_employee_count.push_back(pvec_params->at(k++));
        vec_wage_offer.push_back(pvec_params->at(k++));
        vec_employee_count_desired.push_back(pvec_params->at(k++));
        vec_n_active_job_postings.push_back(pvec_params->at(k++));
        vec_need_worker.push_back(pvec_params->at(k++));
        vec_w_target.push_back(pvec_params->at(k++));
        vec_w_current.push_back(pvec_params->at(k++));

        vec_inventory.push_back(pvec_params->at(k++));
        vec_working_capital_inventory.push_back(pvec_params->at(k++));
        vec_desired_inventory_factor.push_back(pvec_params->at(k++));
        vec_inventory_factor.push_back(pvec_params->at(k++));
        
        vec_sentiment.push_back(pvec_params->at(k++));
        vec_bankrupt.push_back(pvec_params->at(k++));
        vec_is_cons_firm.push_back(pvec_params->at(k++));

        vec_average_profit.push_back(pvec_params->at(k++));
        vec_average_sale_quantity.push_back(pvec_params->at(k++));
        vec_short_term_funding_gap.push_back(pvec_params->at(k++));
        vec_long_term_funding_gap.push_back(pvec_params->at(k++));
        vec_expected_wage_bill.push_back(pvec_params->at(k++));
        vec_layoff_wage_savings.push_back(pvec_params->at(k++));
        vec_expected_wage_bill_shortfall.push_back(pvec_params->at(k++));
        vec_expected_long_term_shortfall.push_back(pvec_params->at(k++));
        vec_labor_utilization.push_back(pvec_params->at(k++));
        vec_desired_inventory.push_back(pvec_params->at(k++));
        vec_inventory_reaction_factor.push_back(pvec_params->at(k++));
        vec_machine_utilization.push_back(pvec_params->at(k++));
        vec_desired_machines.push_back(pvec_params->at(k++));

        k=0;
        //delete[] pvec_params;

        pvec_params->clear();
        pvec_params->shrink_to_fit();
    }

    std::vector<std::pair<std::string, std::vector<float>>> vals = { {"production_current", vec_production_current}, {"production_planned", vec_production_planned}, 
    {"production_past", vec_production_past}, {"quantity_sold", vec_quantity_sold}, 
    {"total_income", vec_total_income}, {"revenue_sales", vec_revenue_sales}, {"new_loan_issuance", vec_new_loan_issuance}, 
    {"subsidies", vec_subsidies}, {"good_price_current", vec_good_price_current}, 
    {"good_price_past", vec_good_price_past}, {"total_liabilities", vec_total_liabilities}, 
    {"labor_wage_bill", vec_labor_wage_bill}, {"capital_costs", vec_capital_costs}, {"tax_payments", vec_tax_payments}, 
    {"debt_principal_payments", vec_debt_principal_payments}, {"debt_interest_payments", vec_debt_interest_payments}, 
    {"dividend_payments", vec_dividend_payments}, {"total_assets", vec_total_assets}, {"leverage_ratio", vec_leverage_ratio}, 
    {"cash_on_hand", vec_cash_on_hand}, {"dividend_ratio", vec_dividend_ratio}, {"dividend_ratio_optimist", vec_dividend_ratio_optimist},
    {"dividend_ratio_pessimist", vec_dividend_ratio_pessimist}, {"employee_count", vec_employee_count}, {"wage_offer", vec_wage_offer}, 
    {"employee_count_desired", vec_employee_count_desired}, {"n_active_job_postings", vec_n_active_job_postings}, {"need_worker", vec_need_worker}, 
    {"w_target", vec_w_target}, {"w_current", vec_w_current}, {"inventory", vec_inventory}, {"working_capital_inventory", vec_working_capital_inventory},
    {"desired_inventory_factor", vec_desired_inventory_factor}, {"inventory_factor", vec_inventory_factor}, {"sentiment", vec_sentiment}, 
    {"bankrupt", vec_bankrupt}, {"is_cons_firm", vec_is_cons_firm},
    {"average_profit", vec_average_profit},{"average_sale_quantity", vec_average_sale_quantity},{"short_term_funding_gap", vec_short_term_funding_gap},
    {"long_term_funding_gap", vec_long_term_funding_gap},{"expected_wage_bill", vec_expected_wage_bill},{"layoff_wage_savings", vec_layoff_wage_savings},
    {"expected_wage_bill_shortfall", vec_expected_wage_bill_shortfall},{"expected_long_term_shortfall", vec_expected_long_term_shortfall},{"labor_utilization", vec_labor_utilization},
    {"desired_inventory", vec_desired_inventory},{"inventory_reaction_factor", vec_inventory_reaction_factor},{"machine_utilization", vec_machine_utilization}, {"desired_machines", vec_desired_machines}
    };



    std::stringstream ss;
    ss << "ConsumerFirmAgentDataInit_t_" << global_date <<".csv";
    std::string filename = ss.str();

    write_csv(filename,vals);
    cout << "Logging Consumer Firm data: end" <<endl;
}



void Log_Cap_Firm_Properties(Capital_Firm_Agent* Cap_Firm_Array, int size)
{
    cout << "Logging Capital Firm data: start" <<endl;
    // Declare the vectors

    std::vector<float> vec_production_current;
    std::vector<float> vec_production_planned;
    std::vector<float> vec_production_past;
    std::vector<float> vec_quantity_sold;

    std::vector<float> vec_total_income;
    std::vector<float> vec_revenue_sales;
    std::vector<float> vec_new_loan_issuance;
    std::vector<float> vec_subsidies;
    std::vector<float> vec_good_price_current;//float
    std::vector<float> vec_good_price_past;//float

    std::vector<float> vec_total_liabilities;
    std::vector<float> vec_labor_wage_bill;
    std::vector<float> vec_capital_costs;
    std::vector<float> vec_tax_payments;
    std::vector<float> vec_debt_principal_payments;
    std::vector<float> vec_debt_interest_payments;
    std::vector<float> vec_dividend_payments;

    std::vector<float> vec_total_assets;
    std::vector<float> vec_leverage_ratio;
    std::vector<float> vec_cash_on_hand;

    std::vector<float> vec_dividend_ratio;//float
    std::vector<float> vec_dividend_ratio_optimist;//float
    std::vector<float> vec_dividend_ratio_pessimist;//float

    std::vector<float> vec_employee_count;
    std::vector<float> vec_wage_offer;
    std::vector<float> vec_employee_count_desired;
    std::vector<float> vec_n_active_job_postings;
    std::vector<float> vec_need_worker; //bool
    std::vector<float> vec_w_target;
    std::vector<float> vec_w_current;

    std::vector<float> vec_inventory;
    std::vector<float> vec_working_capital_inventory;
    std::vector<float> vec_desired_inventory_factor; //float
    std::vector<float> vec_inventory_factor; //float

    std::vector<float> vec_sentiment; //bool
    std::vector<float> vec_bankrupt; //bool
    std::vector<float> vec_is_cons_firm; //bool

    std::vector<float> vec_average_profit;
    std::vector<float> vec_average_sale_quantity;
    std::vector<float> vec_short_term_funding_gap;
    std::vector<float> vec_long_term_funding_gap;
    std::vector<float> vec_expected_wage_bill;
    std::vector<float> vec_layoff_wage_savings;
    std::vector<float> vec_expected_wage_bill_shortfall;
    std::vector<float> vec_expected_long_term_shortfall;
    std::vector<float> vec_labor_utilization;
    std::vector<float> vec_desired_inventory;
    std::vector<float> vec_inventory_reaction_factor;
    std::vector<float> vec_machine_utilization;
    std::vector<float> vec_desired_machines;


    // Loop through Firm array and fill arrays
    vector<float>* pvec_params;

    int k = 0;

    for (int i=0;i<size;i++){
        
        pvec_params = Cap_Firm_Array[i].Get_All_Params();

        vec_production_current.push_back(pvec_params->at(k++));
        vec_production_planned.push_back(pvec_params->at(k++));
        vec_production_past.push_back(pvec_params->at(k++));
        vec_quantity_sold.push_back(pvec_params->at(k++));

        vec_total_income.push_back(pvec_params->at(k++));
        vec_revenue_sales.push_back(pvec_params->at(k++));
        vec_new_loan_issuance.push_back(pvec_params->at(k++));
        vec_subsidies.push_back(pvec_params->at(k++));
        vec_good_price_current.push_back(pvec_params->at(k++));
        vec_good_price_past.push_back(pvec_params->at(k++));

        vec_total_liabilities.push_back(pvec_params->at(k++));
        vec_labor_wage_bill.push_back(pvec_params->at(k++));
        vec_capital_costs.push_back(pvec_params->at(k++));
        vec_tax_payments.push_back(pvec_params->at(k++));
        vec_debt_principal_payments.push_back(pvec_params->at(k++));
        vec_debt_interest_payments.push_back(pvec_params->at(k++));
        vec_dividend_payments.push_back(pvec_params->at(k++));

        vec_total_assets.push_back(pvec_params->at(k++));
        vec_leverage_ratio.push_back(pvec_params->at(k++));
        vec_cash_on_hand.push_back(pvec_params->at(k++));

        vec_dividend_ratio.push_back(pvec_params->at(k++));
        vec_dividend_ratio_optimist.push_back(pvec_params->at(k++));
        vec_dividend_ratio_pessimist.push_back(pvec_params->at(k++));
        vec_employee_count.push_back(pvec_params->at(k++));
        vec_wage_offer.push_back(pvec_params->at(k++));
        vec_employee_count_desired.push_back(pvec_params->at(k++));
        vec_n_active_job_postings.push_back(pvec_params->at(k++));
        vec_need_worker.push_back(pvec_params->at(k++));
        vec_w_target.push_back(pvec_params->at(k++));
        vec_w_current.push_back(pvec_params->at(k++));

        vec_inventory.push_back(pvec_params->at(k++));
        vec_working_capital_inventory.push_back(pvec_params->at(k++));
        vec_desired_inventory_factor.push_back(pvec_params->at(k++));
        vec_inventory_factor.push_back(pvec_params->at(k++));
        
        vec_sentiment.push_back(pvec_params->at(k++));
        vec_bankrupt.push_back(pvec_params->at(k++));
        vec_is_cons_firm.push_back(pvec_params->at(k++));

        vec_average_profit.push_back(pvec_params->at(k++));
        vec_average_sale_quantity.push_back(pvec_params->at(k++));
        vec_short_term_funding_gap.push_back(pvec_params->at(k++));
        vec_long_term_funding_gap.push_back(pvec_params->at(k++));
        vec_expected_wage_bill.push_back(pvec_params->at(k++));
        vec_layoff_wage_savings.push_back(pvec_params->at(k++));
        vec_expected_wage_bill_shortfall.push_back(pvec_params->at(k++));
        vec_expected_long_term_shortfall.push_back(pvec_params->at(k++));
        vec_labor_utilization.push_back(pvec_params->at(k++));
        vec_desired_inventory.push_back(pvec_params->at(k++));
        vec_inventory_reaction_factor.push_back(pvec_params->at(k++));
        vec_machine_utilization.push_back(pvec_params->at(k++));
        vec_desired_machines.push_back(pvec_params->at(k++));


        k=0;
        //delete[] pvec_params;

        pvec_params->clear();
        pvec_params->shrink_to_fit();
    }

    std::vector<std::pair<std::string, std::vector<float>>> vals = { {"production_current", vec_production_current}, {"production_planned", vec_production_planned}, 
    {"production_past", vec_production_past}, {"quantity_sold", vec_quantity_sold}, 
    {"total_income", vec_total_income}, {"revenue_sales", vec_revenue_sales}, {"new_loan_issuance", vec_new_loan_issuance}, 
    {"subsidies", vec_subsidies}, {"good_price_current", vec_good_price_current}, 
    {"good_price_past", vec_good_price_past}, {"total_liabilities", vec_total_liabilities}, 
    {"labor_wage_bill", vec_labor_wage_bill}, {"capital_costs", vec_capital_costs}, {"tax_payments", vec_tax_payments}, 
    {"debt_principal_payments", vec_debt_principal_payments}, {"debt_interest_payments", vec_debt_interest_payments}, 
    {"dividend_payments", vec_dividend_payments}, {"total_assets", vec_total_assets}, {"leverage_ratio", vec_leverage_ratio}, 
    {"cash_on_hand", vec_cash_on_hand}, {"dividend_ratio", vec_dividend_ratio}, {"dividend_ratio_optimist", vec_dividend_ratio_optimist},
    {"dividend_ratio_pessimist", vec_dividend_ratio_pessimist}, {"employee_count", vec_employee_count}, {"wage_offer", vec_wage_offer}, 
    {"employee_count_desired", vec_employee_count_desired}, {"n_active_job_postings", vec_n_active_job_postings}, {"need_worker", vec_need_worker}, 
    {"w_target", vec_w_target}, {"w_current", vec_w_current}, {"inventory", vec_inventory}, {"working_capital_inventory", vec_working_capital_inventory},
    {"desired_inventory_factor", vec_desired_inventory_factor}, {"inventory_factor", vec_inventory_factor}, {"sentiment", vec_sentiment}, 
    {"bankrupt", vec_bankrupt}, {"is_cons_firm", vec_is_cons_firm},
    {"average_profit", vec_average_profit},{"average_sale_quantity", vec_average_sale_quantity},{"short_term_funding_gap", vec_short_term_funding_gap},
    {"long_term_funding_gap", vec_long_term_funding_gap},{"expected_wage_bill", vec_expected_wage_bill},{"layoff_wage_savings", vec_layoff_wage_savings},
    {"expected_wage_bill_shortfall", vec_expected_wage_bill_shortfall},{"expected_long_term_shortfall", vec_expected_long_term_shortfall},{"labor_utilization", vec_labor_utilization},
    {"desired_inventory", vec_desired_inventory},{"inventory_reaction_factor", vec_inventory_reaction_factor},{"machine_utilization", vec_machine_utilization}, {"desired_machines", vec_desired_machines}
    };
    


    std::stringstream ss;
    ss << "CapitalFirmAgentDataInit_t_" << global_date <<".csv";
    std::string filename = ss.str();

    write_csv(filename,vals);
    cout << "Logging Capital Firm data: end" <<endl;
}