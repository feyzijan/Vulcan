// TODO: Add function here to read all these values from a text file
#include "Initialization_Parameters.hpp"


int global_date = 0; // dont put this in a map

// Define the initialization_parameters map.
map<string, float> initialization_parameters;
map<string, float> main_loop_parameters;
map<string, float> randomness_parameters;


// Function to split a string by a delimiter and return a vector of tokens.
vector<string> split(const string &s, char delimiter) {
    vector<string> result;
    std::istringstream iss(s);
    string token;

    // Read tokens from the string and add them to the result vector.
    while (std::getline(iss, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

// Function to read the values from the CSV file and populate the
// initialization_parameters map.
void Read_Parameters(map<string, float>& parameter_map, const char* filename) {
    // Open the CSV file.
    std::ifstream file(filename);
    string line;
    int line_num = 0;
    cout << "Started reading file: " << filename << endl;

    // Read lines from the file until the end of the file is reached.
    while (std::getline(file, line)) {
        // Split the line into columns using the split function.
        vector<string> columns = split(line, ',');
        // Get the variable name from the first column.
        const string &var_name = columns[0];
        // Get the variable value from the second column.
        const string &var_value = columns[1];

        // Insert the variable name and value into the initialization_parameters map.
        parameter_map[var_name] = std::stof(var_value);
    }

    // Close the CSV file.
    file.close();
    cout << "Finished reading and closed file: " << filename << endl;
}

void Print_Parameter_Map(map<string, float>& parameter_map){
        for (const auto& [key, value] : parameter_map) {
        std::cout << key << " : " << parameter_map[key] << std::endl;
    }
}


/* Reassign values to all simulation parameters by reading off the values from the maps we created from reading the csv files
*/
void Assign_All_Parameters(map<string, float>& initialization_parameters,
map<string, float>& main_loop_parameters, map<string, float>& randomness_parameters){

    // Initialization Parameters

    // --- Household initialization parameters
    
    // Propensity to consume financial wealth, c_f
    household_init_c_f_mean = initialization_parameters["household_init_c_f_mean"];
    household_init_c_f_std = initialization_parameters["household_init_c_f_std"];
    household_init_c_f_min = initialization_parameters["household_init_c_f_min"];
    household_init_c_f_max = initialization_parameters["household_init_c_f_max"];
    
    // Propensity to consume excess money : c_excess_money
    household_init_c_excess_mean = initialization_parameters["household_init_c_excess_mean"];
    household_init_c_excess_std = initialization_parameters["household_init_c_excess_std"];
    household_init_c_excess_min = initialization_parameters["household_init_c_excess_min"];
    household_init_c_excess_max = initialization_parameters["household_init_c_excess_max"];
    
    // Savings propensity - optimist : saving_propensity_optimist 
    household_init_s_optimist_mean = initialization_parameters["household_init_s_optimist_mean"];
    household_init_s_optimist_std = initialization_parameters["household_init_s_optimist_std"];
    household_init_s_optimist_min = initialization_parameters["household_init_s_optimist_min"];
    household_init_s_optimist_max = initialization_parameters["household_init_s_optimist_max"];

    // Savings propensity - pessimist : // saving_propensity_pessimist
    household_init_s_pessimist_mean = initialization_parameters["household_init_s_pessimist_mean"];
    household_init_s_pessimist_std = initialization_parameters["household_init_s_pessimist_std"];
    household_init_s_pessimist_min = initialization_parameters["household_init_s_pessimist_min"];
    household_init_s_pessimist_max = initialization_parameters["household_init_s_pessimist_max"];
    
    // Starting wealth : wealth
    household_init_wealth_mean = initialization_parameters["household_init_wealth_mean"];
    household_init_wealth_std = initialization_parameters["household_init_wealth_std"];
    household_init_wealth_min = initialization_parameters["household_init_wealth_min"];
    household_init_wealth_max = initialization_parameters["household_init_wealth_max"];
    
    // Maximum tolerable unemployment duration
    household_init_unemp_tolerance_mean = initialization_parameters["household_init_unemp_tolerance_mean"];
    household_init_unemp_tolerance_std = initialization_parameters["household_init_unemp_tolerance_std"];
    household_init_unemp_tolerance_min = initialization_parameters["household_init_unemp_tolerance_min"];
    household_init_unemp_tolerance_max = initialization_parameters["household_init_unemp_tolerance_max"];
    
    // Reservation Wage
    household_init_res_wage_mean = initialization_parameters["household_init_res_wage_mean"];
    household_init_res_wage_std = initialization_parameters["household_init_res_wage_std"];
    household_init_res_wage_min = initialization_parameters["household_init_res_wage_min"];
    household_init_res_wage_max = initialization_parameters["household_init_res_wage_max"];

    // - Public Wage parameters
    household_init_unemployment_benefit = initialization_parameters["household_init_unemployment_benefit"];
    household_init_minimum_wage = initialization_parameters["household_init_minimum_wage"];

    // --- Consumer Firm initialization parameters
    // Starting total asset
    firm_cons_init_cash_mean = initialization_parameters["firm_cons_init_cash_mean"];
    firm_cons_init_cash_std = initialization_parameters["firm_cons_init_cash_std"];
    firm_cons_init_cash_min = initialization_parameters["firm_cons_init_cash_min"];
    firm_cons_init_cash_max = initialization_parameters["firm_cons_init_cash_max"];
    
    // Starting wage offers
    firm_cons_init_wage_offer_mean = initialization_parameters["firm_cons_init_wage_offer_mean"];
    firm_cons_init_wage_offer_std = initialization_parameters["firm_cons_init_wage_offer_std"];
    firm_cons_init_wage_offer_min = initialization_parameters["firm_cons_init_wage_offer_min"];
    firm_cons_init_wage_offer_max = initialization_parameters["firm_cons_init_wage_offer_max"];
    
    // Starting desired employees
    firm_cons_init_worker_demand_mean = initialization_parameters["firm_cons_init_worker_demand_mean"];
    firm_cons_init_worker_demand_std = initialization_parameters["firm_cons_init_worker_demand_std"];
    firm_cons_init_worker_demand_min = initialization_parameters["firm_cons_init_worker_demand_min"];
    firm_cons_init_worker_demand_max = initialization_parameters["firm_cons_init_worker_demand_max"];
    
    // Initial good price
    firm_cons_init_good_price_mean = initialization_parameters["firm_cons_init_good_price_mean"];
    firm_cons_init_good_price_std = initialization_parameters["firm_cons_init_good_price_std"];
    firm_cons_init_good_price_min = initialization_parameters["firm_cons_init_good_price_min"];
    firm_cons_init_good_price_max = initialization_parameters["firm_cons_init_good_price_max"];
    
    // Good inventory
    firm_cons_init_inv_factor_mean = initialization_parameters["firm_cons_init_inv_factor_mean"];
    firm_cons_init_inv_factor_std = initialization_parameters["firm_cons_init_inv_factor_std"];
    firm_cons_init_inv_factor_min = initialization_parameters["firm_cons_init_inv_factor_min"];
    firm_cons_init_inv_factor_max = initialization_parameters["firm_cons_init_inv_factor_max"];

    // Desired inventory factor ( characteristic)
    firm_cons_init_target_inv_factor_mean = initialization_parameters["firm_cons_init_target_inv_factor_mean"];
    firm_cons_init_target_inv_factor_std = initialization_parameters["firm_cons_init_target_inv_factor_std"];
    firm_cons_init_target_inv_factor_min = initialization_parameters["firm_cons_init_target_inv_factor_min"];
    firm_cons_init_target_inv_factor_max = initialization_parameters["firm_cons_init_target_inv_factor_max"];

    // Other inits (not randomised)
    firm_cons_init_production_current_ratio = initialization_parameters["firm_cons_init_production_current_ratio"];
    firm_cons_init_quantity_sold_ratio = initialization_parameters["firm_cons_init_quantity_sold_ratio"];
    firm_cons_init_emissions_per_unit = initialization_parameters["firm_cons_init_emissions_per_unit"];
    firm_cons_init_dividend_ratio_optimist = initialization_parameters["firm_cons_init_dividend_ratio_optimist"];
    firm_cons_init_dividend_ratio_pessimist = initialization_parameters["firm_cons_init_dividend_ratio_pessimist"];

    // --- Capital Firm initialization parameters
    // Starting total asset
    firm_cap_init_cash_mean = initialization_parameters["firm_cap_init_cash_mean"];
    firm_cap_init_cash_std = initialization_parameters["firm_cap_init_cash_std"];
    firm_cap_init_cash_min = initialization_parameters["firm_cap_init_cash_min"];
    firm_cap_init_cash_max = initialization_parameters["firm_cap_init_cash_max"];
    
    // Starting wage offers
    firm_cap_init_wage_offer_mean = initialization_parameters["firm_cap_init_wage_offer_mean"];
    firm_cap_init_wage_offer_std = initialization_parameters["firm_cap_init_wage_offer_std"];
    firm_cap_init_wage_offer_min = initialization_parameters["firm_cap_init_wage_offer_min"];
    firm_cap_init_wage_offer_max = initialization_parameters["firm_cap_init_wage_offer_max"];
    
    // Starting desired employees
    firm_cap_init_worker_demand_mean = initialization_parameters["firm_cap_init_worker_demand_mean"];
    firm_cap_init_worker_demand_std = initialization_parameters["firm_cap_init_worker_demand_std"];
    firm_cap_init_worker_demand_min = initialization_parameters["firm_cap_init_worker_demand_min"];
    firm_cap_init_worker_demand_max = initialization_parameters["firm_cap_init_worker_demand_max"];
    
    // Initial good price
    firm_cap_init_good_price_mean = initialization_parameters["firm_cap_init_good_price_mean"];
    firm_cap_init_good_price_std = initialization_parameters["firm_cap_init_good_price_std"];
    firm_cap_init_good_price_min = initialization_parameters["firm_cap_init_good_price_min"];
    firm_cap_init_good_price_max = initialization_parameters["firm_cap_init_good_price_max"];
    
    // Good inventory
    firm_cap_init_inv_factor_mean = initialization_parameters["firm_cap_init_inv_factor_mean"];
    firm_cap_init_inv_factor_std = initialization_parameters["firm_cap_init_inv_factor_std"];
    firm_cap_init_inv_factor_min = initialization_parameters["firm_cap_init_inv_factor_min"];
    firm_cap_init_inv_factor_max = initialization_parameters["firm_cap_init_inv_factor_max"];

    // --- Capital Firm initialization parameters
    // Desired inventory factor ( characteristics)
    firm_cap_init_target_inv_factor_mean = initialization_parameters["firm_cap_init_target_inv_factor_mean"];
    firm_cap_init_target_inv_factor_std = initialization_parameters["firm_cap_init_target_inv_factor_std"];
    firm_cap_init_target_inv_factor_min = initialization_parameters["firm_cap_init_target_inv_factor_min"];
    firm_cap_init_target_inv_factor_max = initialization_parameters["firm_cap_init_target_inv_factor_max"];

    // Other inits (not randomised)
    firm_cap_init_production_current_ratio = initialization_parameters["firm_cap_init_production_current_ratio"];
    firm_cap_init_quantity_sold_ratio = initialization_parameters["firm_cap_init_quantity_sold_ratio"];
    firm_cap_init_emissions_per_unit = initialization_parameters["firm_cap_init_emissions_per_unit"];
    firm_cap_init_dividend_ratio_optimist = initialization_parameters["firm_cap_init_dividend_ratio_optimist"];
    firm_cap_init_dividend_ratio_pessimist = initialization_parameters["firm_cap_init_dividend_ratio_pessimist"];

    //--- Bank Initialization parameters
    bank_init_interest_rate = initialization_parameters["bank_init_interest_rate"];

    //--- CO2 initialization Parameters
    emission_sensitivity_min = initialization_parameters["emission_sensitivity_min"];
    emission_sensitivity_max = initialization_parameters["emission_sensitivity_max"];
    emission_sensitivity_std = initialization_parameters["emission_sensitivity_std"];
    emission_sensitivity_threshold = initialization_parameters["emission_sensitivity_threshold"];
    
    //--- Emission allowance parameters
    emission_init_total_allowance = initialization_parameters["emission_init_total_allowance"];
    emission_init_unit_price = initialization_parameters["emission_init_unit_price"];


    //---------- Main Loop Parameters ------------
    // --- Simulation size 
    n_loops = main_loop_parameters["n_loops"];
    n_households = main_loop_parameters["n_households"];
    n_consumer_firms = main_loop_parameters["n_consumer_firms"];
    n_capital_firms = main_loop_parameters["n_capital_firms"];
    n_firms = main_loop_parameters["n_firms"]; 
    sector_count = main_loop_parameters["n_consumer_sectors"];

    // ---- Household dynamic parameters
    household_n_res_wage_decrease = main_loop_parameters["household_n_res_wage_decrease"]; 
    household_targeted_savings_to_income_ratio = main_loop_parameters["household_targeted_savings_to_income_ratio"];

    // ---- General Firm dynamic parameters
    standard_employment_contract_length = main_loop_parameters["standard_employment_contract_length"];
    firm_tax_rate = main_loop_parameters["firm_tax_rate"];

    // --- Consumer Firm dynamic parameters
    firm_cons_inv_depr_rate = main_loop_parameters["firm_cons_inv_depr_rate"];
    firm_cons_productivity = main_loop_parameters["firm_cons_productivity"]; // # units produced per worker machine pairing
    firm_cons_workers_per_machine = main_loop_parameters["firm_cons_workers_per_machine"];
    firm_cons_good_unit_cost = main_loop_parameters["firm_cons_good_unit_cost"];
    firm_cons_inv_reaction_factor = main_loop_parameters["firm_cons_inv_reaction_factor"];

    // --- Capital Firm dynamic parameters
    firm_cap_inv_depr_rate = main_loop_parameters["firm_cap_inv_depr_rate"];
    firm_cap_productivity = main_loop_parameters["firm_cap_productivity"]; // # units produced per worker machine pairing
    firm_cap_workers_per_machine = main_loop_parameters["firm_cap_workers_per_machine"];
    firm_cap_good_unit_cost = main_loop_parameters["firm_cap_good_unit_cost"];
    firm_cap_machine_lifespan = main_loop_parameters["firm_cap_machine_lifespan"];
    firm_cap_inv_reaction_factor = main_loop_parameters["firm_cap_inv_reaction_factor"];


    // --- Bank dynamic Parameters
    bank_inflation_reaction = main_loop_parameters["bank_inflation_reaction"];
    bank_inflation_target = main_loop_parameters["bank_inflation_target"]; 
    bank_inflation_target_monthly =  main_loop_parameters["bank_inflation_target_monthly"];
    bank_risk_premium = main_loop_parameters["bank_risk_premium"];
    bank_long_term_loan_length = main_loop_parameters["bank_long_term_loan_length"];
    bank_leverage_ratio_lower_threshold = main_loop_parameters["bank_leverage_ratio_lower_threshold"];
    bank_leverage_ratio_upper_threshold = main_loop_parameters["bank_leverage_ratio_upper_threshold"];
   
    // the following parameters were added later hence we need to check if they exist in the map
    auto it = main_loop_parameters.find("bank_max_interest_rate");
    if (it != main_loop_parameters.end() || it->first == "bank_max_interest_rate") {
        bank_max_interest_rate = it->second;} 
    
    it = main_loop_parameters.find("bank_max_interest_rate_change");
    if (it != main_loop_parameters.end() || it->first == "bank_max_interest_rate_change") {
        bank_max_interest_rate_change = it->second;}


   // do the same for fixed price and wage change params for cons and cap firms
    it = main_loop_parameters.find("firm_cons_fixed_price_change");
    if (it != main_loop_parameters.end() || it->first == "firm_cons_fixed_price_change") { firm_cons_fixed_price_change = it->second;} 
    it = main_loop_parameters.find("firm_cons_fixed_wage_change");
    if (it != main_loop_parameters.end() || it->first == "firm_cons_fixed_wage_change") { firm_cons_fixed_wage_change = it->second;}
    it = main_loop_parameters.find("firm_cap_fixed_price_change");
    if (it != main_loop_parameters.end() || it->first == "firm_cap_fixed_price_change") { firm_cap_fixed_price_change = it->second;}
    it = main_loop_parameters.find("firm_cap_fixed_wage_change");
    if (it != main_loop_parameters.end() || it->first == "firm_cap_fixed_wage_change") { firm_cap_fixed_wage_change = it->second;}
    

    //---- Bank Emission Penalty Parameters
    bank_total_emission_penalty = main_loop_parameters["bank_total_emission_penalty"];
    bank_unit_emission_penalty = main_loop_parameters["bank_unit_emission_penalty"];
    bank_unit_emission_lower_thr = main_loop_parameters["bank_unit_emission_lower_thr"];
    bank_unit_emission_upper_thr = main_loop_parameters["bank_unit_emission_upper_thr"];
    bank_total_emission_lower_thr = main_loop_parameters["bank_total_emission_lower_thr"];
    bank_total_emission_upper_thr = main_loop_parameters["bank_total_emission_upper_thr"];

    // Emission allowance change parameters
    emission_total_allowance_change = main_loop_parameters["emission_total_allowance_change"];
    emission_unit_price_change = main_loop_parameters["emission_unit_price_change"];



    // Randomness Parameters
    // Household randomness parameters
    household_rand_sentiment_adoption = randomness_parameters["household_rand_sentiment_adoption"];
    household_rand_sector_spending_weight_change = randomness_parameters["household_rand_sector_spending_weight_change"];
    household_rand_emission_sensitivity_change = randomness_parameters["household_rand_emission_sensitivity_change"];
    household_rand_job_search = randomness_parameters["household_rand_job_search"];


    // Cons firm randomness parameters
    firm_cons_rand_dividend_change =  randomness_parameters["firm_cons_rand_dividend_change"];
    firm_cons_rand_sentiment_adoption = randomness_parameters["firm_cons_rand_sentiment_adoption"];
    firm_cons_rand_desired_inventory_factor_change = randomness_parameters["firm_cons_rand_desired_inventory_factor_change"];
    firm_cons_rand_price_change_upper_limit = randomness_parameters["firm_cons_rand_price_change_upper_limit"];
    firm_cons_rand_wage_change = randomness_parameters["firm_cons_rand_wage_change"];
    
    // Cap firm randomness parameters
    firm_cap_rand_dividend_change = randomness_parameters["firm_cap_rand_dividend_change"];
    firm_cap_rand_sentiment_adoption = randomness_parameters["firm_cap_rand_sentiment_adoption"];
    firm_cap_rand_desired_inventory_factor_change = randomness_parameters["firm_cap_rand_desired_inventory_factor_change"];
    firm_cap_rand_price_change_upper_limit = randomness_parameters["firm_cap_rand_price_change_upper_limit"];
    firm_cap_rand_wage_change = randomness_parameters["firm_cap_wage_change"];


    cout << "This simulation is with the following parameters: n_households: " << n_households << " n_consumer_firms: " << n_consumer_firms <<
    " n_consumer_sectors: " << sector_count <<  " n_capital_firms: " << n_capital_firms <<  " n_loops: " << n_loops  << endl;
}


// Initially declare all variables with default values so we don't get errors

//-------------------- Simulation Size Parameters ---------------
int n_loops = 36;
int n_households = 1000;
int n_consumer_firms = 300;
int n_capital_firms = 50;
int n_firms = 350; 

int sector_count = 12;


//---- Public parameters----------------------
// Wage parameters
int household_init_unemployment_benefit = 500;
int household_init_minimum_wage = 600;


//--------------- Household parameters ---------------
// --- Household initialization parameters
// Propensity to consume financial wealth, c_f
float household_init_c_f_mean = 0.5;
float household_init_c_f_std = 0.1;
float household_init_c_f_min = 0.1;
float household_init_c_f_max = 0.9;
// Propensity to consume excess money : c_excess_money
float household_init_c_excess_mean = 0.3;
float household_init_c_excess_std = 0.05;
float household_init_c_excess_min = 0.0;
float household_init_c_excess_max = 0.7;
// Savings propensity - optimist : saving_propensity_optimist 
float household_init_s_optimist_mean = 0.2;
float household_init_s_optimist_std = 0.05;
float household_init_s_optimist_min = 0.0;
float household_init_s_optimist_max = 0.5;
// Savings propensity - pessimist : // saving_propensity_pessimist
float household_init_s_pessimist_mean = 0.3;
float household_init_s_pessimist_std = 0.05;
float household_init_s_pessimist_min = 0.1;
float household_init_s_pessimist_max = 0.6;
// Starting wealth : wealth
float household_init_wealth_mean = 1000.0;
float household_init_wealth_std = 300.0;
float household_init_wealth_min = 0.0;
float household_init_wealth_max = 2000.0;
// Maximum tolerable unemployment duration
float household_init_unemp_tolerance_mean = 4.0;
float household_init_unemp_tolerance_std = 2.0;
float household_init_unemp_tolerance_min = 0.0;
float household_init_unemp_tolerance_max = 100.0;
// Reservation Wage
float household_init_res_wage_mean = 950;
float household_init_res_wage_std = 300;
float household_init_res_wage_min = 100;
float household_init_res_wage_max = 999999;

// ---- Household dynamic parameters
float household_n_res_wage_decrease = 0.05; 
float household_targeted_savings_to_income_ratio = 3.0;

// --- Household randomness parameters
float household_rand_sentiment_adoption = 0.1;
float household_rand_sector_spending_weight_change = 0.1;
float household_rand_emission_sensitivity_change = 0.1;
float household_rand_job_search = 0.1;


//---------------------------------------------

//---- Consumer Firm parameters----------------------
// --- Consumer Firm initialization parameters
// Starting total asset
float firm_cons_init_cash_mean = 10000;
float firm_cons_init_cash_std = 2500;
float firm_cons_init_cash_min = 1;
float firm_cons_init_cash_max = 999999999;
// Starting wage offers
float firm_cons_init_wage_offer_mean = 1000;
float firm_cons_init_wage_offer_std = 300;
float firm_cons_init_wage_offer_min = 100;
float firm_cons_init_wage_offer_max = 999999;
// Starting desired employees
float firm_cons_init_worker_demand_mean = 20;
float firm_cons_init_worker_demand_std = 5;
float firm_cons_init_worker_demand_min = 1;
float firm_cons_init_worker_demand_max = 100;
// Initial good price
float firm_cons_init_good_price_mean = 10;
float firm_cons_init_good_price_std = 2;
float firm_cons_init_good_price_min = 1;
float firm_cons_init_good_price_max = 99;
// Good inventory
float firm_cons_init_inv_factor_mean = 1000;
float firm_cons_init_inv_factor_std = 100;
float firm_cons_init_inv_factor_min = 1;
float firm_cons_init_inv_factor_max = 999999;
// Desired inventory factor ( characteristic)
float firm_cons_init_target_inv_factor_mean = 1.5;
float firm_cons_init_target_inv_factor_std = 0.25;
float firm_cons_init_target_inv_factor_min = 0.1;
float firm_cons_init_target_inv_factor_max = 4.0;

// Other inits (not randomised)
float firm_cons_init_production_current_ratio = 0.4;
float firm_cons_init_quantity_sold_ratio = 0.25;
float firm_cons_init_emissions_per_unit = 10.0;
float firm_cons_init_dividend_ratio_optimist = 0.04;
float firm_cons_init_dividend_ratio_pessimist = 0.02;

// --- Consumer Firm dynamic parameters
float firm_cons_inv_depr_rate = 0.01;
float firm_cons_productivity = 1000; // # units produced per worker machine pairing
int firm_cons_workers_per_machine = 1;
float firm_cons_good_unit_cost = 1.0;
float firm_cons_inv_reaction_factor = 1.0;
float firm_cons_fixed_price_change = 0.05;
float firm_cons_fixed_wage_change = 0.05;

// --- Consumer Firm randomness parameters
float firm_cons_rand_dividend_change = 0.1;
float firm_cons_rand_sentiment_adoption = 0.1;
float firm_cons_rand_desired_inventory_factor_change = 0.1;
float firm_cons_rand_price_change_upper_limit = 0.2;
float firm_cons_rand_wage_change = 0.25;




//---------------------------------------------

//---- Capital Firm parameters----------------------

// --- Capital Firm initialization parameters
// Starting total asset
float firm_cap_init_cash_mean = 10000;
float firm_cap_init_cash_std = 2500;
float firm_cap_init_cash_min = 1;
float firm_cap_init_cash_max = 999999999;
// Starting wage offers
float firm_cap_init_wage_offer_mean = 1000;
float firm_cap_init_wage_offer_std = 300;
float firm_cap_init_wage_offer_min = 100;
float firm_cap_init_wage_offer_max = 999999;
// Starting desired employees
float firm_cap_init_worker_demand_mean = 20;
float firm_cap_init_worker_demand_std = 5;
float firm_cap_init_worker_demand_min = 1;
float firm_cap_init_worker_demand_max = 100;
// Initial good price
float firm_cap_init_good_price_mean = 10;
float firm_cap_init_good_price_std = 2;
float firm_cap_init_good_price_min = 1;
float firm_cap_init_good_price_max = 99;
// Good inventory
float firm_cap_init_inv_factor_mean = 1000;
float firm_cap_init_inv_factor_std = 100;
float firm_cap_init_inv_factor_min = 1;
float firm_cap_init_inv_factor_max = 999999;
// Desired inventory factor ( characteristics)
float firm_cap_init_target_inv_factor_mean = 1.5;
float firm_cap_init_target_inv_factor_std = 0.25;
float firm_cap_init_target_inv_factor_min = 0.1;
float firm_cap_init_target_inv_factor_max = 4.0;

// Other inits (not randomised)
float firm_cap_init_production_current_ratio = 0.4;
float firm_cap_init_quantity_sold_ratio = 0.25;
float firm_cap_init_emissions_per_unit = 100.0;
float firm_cap_init_dividend_ratio_optimist = 0.04;
float firm_cap_init_dividend_ratio_pessimist = 0.02;

// --- Capital Firm dynamic parameters
float firm_cap_inv_depr_rate = 0.01;
float firm_cap_productivity = 10; // # units produced per worker machine pairing
int firm_cap_workers_per_machine = 1;
int firm_cap_machine_lifespan = 100;
float firm_cap_good_unit_cost = 20.0;
float firm_cap_inv_reaction_factor = 1.0;
float firm_cap_fixed_price_change = 0.05;
float firm_cap_fixed_wage_change = 0.05;


// --- Capital Firm randomness parameters
float firm_cap_rand_dividend_change = 0.1;
float firm_cap_rand_sentiment_adoption = 0.1;
float firm_cap_rand_desired_inventory_factor_change = 0.1;
float firm_cap_rand_price_change_upper_limit = 0.2;
float firm_cap_rand_wage_change = 0.25;


//---------------------------------------------
// ---- Parameters for all Firms
int standard_employment_contract_length = 6;
float firm_tax_rate = 0.2;


//---------------------------------------------

//---- Bank parameters --------------
// Bank Initialization parameters
float bank_init_interest_rate = 0.02;

// Bank Dynamic Parameters 
float bank_inflation_reaction = 1.5;
float bank_inflation_target = 1.05; 
float bank_inflation_target_monthly=  1.004;
float bank_risk_premium = 1.0;
int bank_short_term_loan_length = 12;
int bank_long_term_loan_length = 100;
float bank_leverage_ratio_lower_threshold = 60;
float bank_leverage_ratio_upper_threshold = 100;
float bank_max_interest_rate = 0.4;
float bank_max_interest_rate_change = 0.1;

//---------------------------------------------

// --- CO2 Metrics parameters
// CO2 Emission sensitivites initialization for households
float emission_sensitivity_min = 0.0;
float emission_sensitivity_max = 0.5;
float emission_sensitivity_std = 0.05;
float emission_sensitivity_threshold = 0.05;

// Bank Emission Lending Penalty Parameters
float bank_emission_penalty_max = 0.02;
bool bank_total_emission_penalty = 0;
bool bank_unit_emission_penalty  = 1;
float bank_unit_emission_lower_thr = 1;
float bank_unit_emission_upper_thr = 10;
float bank_total_emission_lower_thr = 10000;
float bank_total_emission_upper_thr = 100000;

// Emission allowance parameters
// Initial allowances and unit price
long emission_init_total_allowance = 1000000;
float emission_init_unit_price = 0.500;
// Constant changes in allowance and unit price
float emission_total_allowance_change = -0.001;
float emission_unit_price_change = 0.001;
