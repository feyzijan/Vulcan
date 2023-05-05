// TODO: Add function here to read all these values from a text file
#include "Initialization_Parameters.hpp"


int global_date = 0; // dont put this in a map

// Define the initialization_parameters map.
std::map<string, std::variant<int, float>> initialization_parameters;
std::map<string, std::variant<int, float>> main_loop_parameters;
std::map<string, std::variant<int, float>> randomness_parameters;


// Function to split a string by a delimiter and return a vector of tokens.
vector<string> split(const std::string &s, char delimiter) {
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
void Read_Parameters(map<string, std::variant<int, float>>& parameter_map, const char* filename) {
    // Open the CSV file.
    std::ifstream file(filename);
    string line;
    int line_num = 0;

    // Read lines from the file until the end of the file is reached.
    while (std::getline(file, line)) {

        cout << "Reading line " << ++line_num << endl;
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
}

void Print_Parameter_Map(map<string, std::variant<int, float>>& parameter_map){
        for (const auto& [key, value] : parameter_map) {
        std::cout << key << ": ";
        if (std::holds_alternative<int>(value)) {
            std::cout << std::get<int>(value) << std::endl;
        } else if (std::holds_alternative<float>(value)) {
            std::cout << std::get<float>(value) << std::endl;
        }
    }
}


/* Reassign values to all simulation parameters by reading off the values from the maps we created from the csv files
*/
void Assign_All_Parameters(map<string, std::variant<int, float>>& initialization_parameters,
map<string, std::variant<int, float>>& main_loop_parameters, map<string, std::variant<int, float>>& randomness_parameters){

    // Initialization Parameters

    // --- Household initialization parameters
    // General consumption propensity : c
    household_init_c_mean = std::get<float>(initialization_parameters["household_init_c_mean"]);
    household_init_c_std = std::get<float>(initialization_parameters["household_init_c_std"]);
    household_init_c_min = std::get<float>(initialization_parameters["household_init_c_min"]);
    household_init_c_max = std::get<float>(initialization_parameters["household_init_c_max"]);
    // Propensity to consume financial wealth, c_f
    household_init_c_f_mean = std::get<float>(initialization_parameters["household_init_c_f_mean"]);
    household_init_c_f_std = std::get<float>(initialization_parameters["household_init_c_f_std"]);
    household_init_c_f_min = std::get<float>(initialization_parameters["household_init_c_f_min"]);
    household_init_c_f_max = std::get<float>(initialization_parameters["household_init_c_f_max"]);
    // Propensity to consume human wealth, c_h
    household_init_c_h_mean = std::get<float>(initialization_parameters["household_init_c_h_mean"]);
    household_init_c_h_std = std::get<float>(initialization_parameters["household_init_c_h_std"]);
    household_init_c_h_min = std::get<float>(initialization_parameters["household_init_c_h_min"]);
    household_init_c_h_max = std::get<float>(initialization_parameters["household_init_c_h_max"]);
    // Propensity to consume excess money : c_excess_money
    household_init_c_excess_mean = std::get<float>(initialization_parameters["household_init_c_excess_mean"]);
    household_init_c_excess_std = std::get<float>(initialization_parameters["household_init_c_excess_std"]);
    household_init_c_excess_min = std::get<float>(initialization_parameters["household_init_c_excess_min"]);
    household_init_c_excess_max = std::get<float>(initialization_parameters["household_init_c_excess_max"]);
    // Propensity to adopt majority sentiment: p_majority_op_adoption
    household_init_p_majority_mean = std::get<float>(initialization_parameters["household_init_p_majority_mean"]);
    household_init_p_majority_std = std::get<float>(initialization_parameters["household_init_p_majority_std"]);
    household_init_p_majority_min = std::get<float>(initialization_parameters["household_init_p_majority_min"]);
    household_init_p_majority_max = std::get<float>(initialization_parameters["household_init_p_majority_max"]);
    // Savings propensity - optimist : saving_propensity_optimist 
    household_init_s_optimist_mean = std::get<float>(initialization_parameters["household_init_s_optimist_mean"]);
    household_init_s_optimist_std = std::get<float>(initialization_parameters["household_init_s_optimist_std"]);
    household_init_s_optimist_min = std::get<float>(initialization_parameters["household_init_s_optimist_min"]);
    household_init_s_optimist_max = std::get<float>(initialization_parameters["household_init_s_optimist_max"]);

    // Savings propensity - pessimist : // saving_propensity_pessimist
    household_init_s_pessimist_mean = std::get<float>(initialization_parameters["household_init_s_pessimist_mean"]);
    household_init_s_pessimist_std = std::get<float>(initialization_parameters["household_init_s_pessimist_std"]);
    household_init_s_pessimist_min = std::get<float>(initialization_parameters["household_init_s_pessimist_min"]);
    household_init_s_pessimist_max = std::get<float>(initialization_parameters["household_init_s_pessimist_max"]);
    // Starting wealth : wealth
    household_init_wealth_mean = std::get<float>(initialization_parameters["household_init_wealth_mean"]);
    household_init_wealth_std = std::get<float>(initialization_parameters["household_init_wealth_std"]);
    household_init_wealth_min = std::get<float>(initialization_parameters["household_init_wealth_min"]);
    household_init_wealth_max = std::get<float>(initialization_parameters["household_init_wealth_max"]);
    // Maximum tolerable unemployment duration
    household_init_unemp_tolerance_mean = std::get<float>(initialization_parameters["household_init_unemp_tolerance_mean"]);
    household_init_unemp_tolerance_std = std::get<float>(initialization_parameters["household_init_unemp_tolerance_std"]);
    household_init_unemp_tolerance_min = std::get<float>(initialization_parameters["household_init_unemp_tolerance_min"]);
    household_init_unemp_tolerance_max = std::get<float>(initialization_parameters["household_init_unemp_tolerance_max"]);
    // Reservation Wage
    household_init_res_wage_mean = std::get<float>(initialization_parameters["household_init_res_wage_mean"]);
    household_init_res_wage_std = std::get<float>(initialization_parameters["household_init_res_wage_std"]);
    household_init_res_wage_min = std::get<float>(initialization_parameters["household_init_res_wage_min"]);
    household_init_res_wage_max = std::get<float>(initialization_parameters["household_init_res_wage_max"]);

    // - Public Wage parameters
    household_init_unemployment_benefit = std::get<int>(initialization_parameters["household_init_unemployment_benefit"]);
    household_init_minimum_wage = std::get<int>(initialization_parameters["household_init_minimum_wage"]);

    // --- Consumer Firm initialization parameters
    // Starting total asset
    firm_cons_init_total_assets_mean = std::get<float>(initialization_parameters["firm_cons_init_total_assets_mean"]);
    firm_cons_init_total_assets_std = std::get<float>(initialization_parameters["firm_cons_init_total_assets_std"]);
    firm_cons_init_total_assets_min = std::get<float>(initialization_parameters["firm_cons_init_total_assets_min"]);
    firm_cons_init_total_assets_max = std::get<float>(initialization_parameters["firm_cons_init_total_assets_max"]);

    // Dividend ratio if firm is optimistic
    firm_cons_init_dividend_ratio_optimist_mean = std::get<float>(initialization_parameters["firm_cons_init_dividend_ratio_optimist_mean"]);
    firm_cons_init_dividend_ratio_optimist_std = std::get<float>(initialization_parameters["firm_cons_init_dividend_ratio_optimist_std"]);
    firm_cons_init_dividend_ratio_optimist_min = std::get<float>(initialization_parameters["firm_cons_init_dividend_ratio_optimist_min"]);
    firm_cons_init_dividend_ratio_optimist_max = std::get<float>(initialization_parameters["firm_cons_init_dividend_ratio_optimist_max"]);

    // Dividend ratio if firm is pessimistic
    firm_cons_init_dividend_ratio_pessimist_mean = std::get<float>(initialization_parameters["firm_cons_init_dividend_ratio_pessimist_mean"]);
    firm_cons_init_dividend_ratio_pessimist_std = std::get<float>(initialization_parameters["firm_cons_init_dividend_ratio_pessimist_std"]);
    firm_cons_init_dividend_ratio_pessimist_min = std::get<float>(initialization_parameters["firm_cons_init_dividend_ratio_pessimist_min"]);
    firm_cons_init_dividend_ratio_pessimist_max = std::get<float>(initialization_parameters["firm_cons_init_dividend_ratio_pessimist_max"]);
    // Starting wage offers
    firm_cons_init_wage_offer_mean = std::get<float>(initialization_parameters["firm_cons_init_wage_offer_mean"]);
    firm_cons_init_wage_offer_std = std::get<float>(initialization_parameters["firm_cons_init_wage_offer_std"]);
    firm_cons_init_wage_offer_min = std::get<float>(initialization_parameters["firm_cons_init_wage_offer_min"]);
    firm_cons_init_wage_offer_max = std::get<float>(initialization_parameters["firm_cons_init_wage_offer_max"]);
    // Starting desired employees
    firm_cons_init_employee_count_desired_mean = std::get<float>(initialization_parameters["firm_cons_init_employee_count_desired_mean"]);
    firm_cons_init_employee_count_desired_std = std::get<float>(initialization_parameters["firm_cons_init_employee_count_desired_std"]);
    firm_cons_init_employee_count_desired_min = std::get<float>(initialization_parameters["firm_cons_init_employee_count_desired_min"]);
    firm_cons_init_employee_count_desired_max = std::get<float>(initialization_parameters["firm_cons_init_employee_count_desired_max"]);
    // Inital planned production
    firm_cons_init_production_planned_mean = std::get<float>(initialization_parameters["firm_cons_init_production_planned_mean"]);
    firm_cons_init_production_planned_std = std::get<float>(initialization_parameters["firm_cons_init_production_planned_std"]);
    firm_cons_init_production_planned_min = std::get<float>(initialization_parameters["firm_cons_init_production_planned_min"]);
    firm_cons_init_production_planned_max = std::get<float>(initialization_parameters["firm_cons_init_production_planned_max"]);
    // Initial good price
    firm_cons_init_good_price_current_mean = std::get<float>(initialization_parameters["firm_cons_init_good_price_current_mean"]);
    firm_cons_init_good_price_current_std = std::get<float>(initialization_parameters["firm_cons_init_good_price_current_std"]);
    firm_cons_init_good_price_current_min = std::get<float>(initialization_parameters["firm_cons_init_good_price_current_min"]);
    firm_cons_init_good_price_current_max = std::get<float>(initialization_parameters["firm_cons_init_good_price_current_max"]);
    // Good inventory
    firm_cons_init_inventory_mean = std::get<float>(initialization_parameters["firm_cons_init_inventory_mean"]);
    firm_cons_init_inventory_std = std::get<float>(initialization_parameters["firm_cons_init_inventory_std"]);
    firm_cons_init_inventory_min = std::get<float>(initialization_parameters["firm_cons_init_inventory_min"]);
    firm_cons_init_inventory_max = std::get<float>(initialization_parameters["firm_cons_init_inventory_max"]);

    // Working capital inventory
    firm_cons_init_working_capital_inventory_mean = std::get<float>(initialization_parameters["firm_cons_init_working_capital_inventory_mean"]);
    firm_cons_init_working_capital_inventory_std = std::get<float>(initialization_parameters["firm_cons_init_working_capital_inventory_std"]);
    firm_cons_init_working_capital_inventory_min = std::get<float>(initialization_parameters["firm_cons_init_working_capital_inventory_min"]);
    firm_cons_init_working_capital_inventory_max = std::get<float>(initialization_parameters["firm_cons_init_working_capital_inventory_max"]);
    // Desired inventory factor ( characteristic)
    firm_cons_init_desired_inventory_factor_mean = std::get<float>(initialization_parameters["firm_cons_init_desired_inventory_factor_mean"]);
    firm_cons_init_desired_inventory_factor_std = std::get<float>(initialization_parameters["firm_cons_init_desired_inventory_factor_std"]);
    firm_cons_init_desired_inventory_factor_min = std::get<float>(initialization_parameters["firm_cons_init_desired_inventory_factor_min"]);
    firm_cons_init_desired_inventory_factor_max = std::get<float>(initialization_parameters["firm_cons_init_desired_inventory_factor_max"]);

    // Other inits (not randomised)
    firm_cons_init_production_current_ratio = std::get<float>(initialization_parameters["firm_cons_init_production_current_ratio"]);
    firm_cons_init_quantity_sold_ratio = std::get<float>(initialization_parameters["firm_cons_init_quantity_sold_ratio"]);
    firm_cons_init_good_price = std::get<float>(initialization_parameters["firm_cons_init_good_price"]);

    // --- Capital Firm initialization parameters
    // Starting total asset
    firm_cap_init_total_assets_mean = std::get<float>(initialization_parameters["firm_cap_init_total_assets_mean"]);
    firm_cap_init_total_assets_std = std::get<float>(initialization_parameters["firm_cap_init_total_assets_std"]);
    firm_cap_init_total_assets_min = std::get<float>(initialization_parameters["firm_cap_init_total_assets_min"]);
    firm_cap_init_total_assets_max = std::get<float>(initialization_parameters["firm_cap_init_total_assets_max"]);
    // Dividend ratio if firm is optimistic
    firm_cap_init_dividend_ratio_optimist_mean = std::get<float>(initialization_parameters["firm_cap_init_dividend_ratio_optimist_mean"]);
    firm_cap_init_dividend_ratio_optimist_std = std::get<float>(initialization_parameters["firm_cap_init_dividend_ratio_optimist_std"]);
    firm_cap_init_dividend_ratio_optimist_min = std::get<float>(initialization_parameters["firm_cap_init_dividend_ratio_optimist_min"]);
    firm_cap_init_dividend_ratio_optimist_max = std::get<float>(initialization_parameters["firm_cap_init_dividend_ratio_optimist_max"]);

    // Dividend ratio if firm is pessimistic
    firm_cap_init_dividend_ratio_pessimist_mean = std::get<float>(initialization_parameters["firm_cap_init_dividend_ratio_pessimist_mean"]);
    firm_cap_init_dividend_ratio_pessimist_std = std::get<float>(initialization_parameters["firm_cap_init_dividend_ratio_pessimist_std"]);
    firm_cap_init_dividend_ratio_pessimist_min = std::get<float>(initialization_parameters["firm_cap_init_dividend_ratio_pessimist_min"]);
    firm_cap_init_dividend_ratio_pessimist_max = std::get<float>(initialization_parameters["firm_cap_init_dividend_ratio_pessimist_max"]);
    // Starting wage offers
    firm_cap_init_wage_offer_mean = std::get<float>(initialization_parameters["firm_cap_init_wage_offer_mean"]);
    firm_cap_init_wage_offer_std = std::get<float>(initialization_parameters["firm_cap_init_wage_offer_std"]);
    firm_cap_init_wage_offer_min = std::get<float>(initialization_parameters["firm_cap_init_wage_offer_min"]);
    firm_cap_init_wage_offer_max = std::get<float>(initialization_parameters["firm_cap_init_wage_offer_max"]);
    // Starting desired employees
    firm_cap_init_employee_count_desired_mean = std::get<float>(initialization_parameters["firm_cap_init_employee_count_desired_mean"]);
    firm_cap_init_employee_count_desired_std = std::get<float>(initialization_parameters["firm_cap_init_employee_count_desired_std"]);
    firm_cap_init_employee_count_desired_min = std::get<float>(initialization_parameters["firm_cap_init_employee_count_desired_min"]);
    firm_cap_init_employee_count_desired_max = std::get<float>(initialization_parameters["firm_cap_init_employee_count_desired_max"]);

    // Inital planned production
    firm_cap_init_production_planned_mean = std::get<float>(initialization_parameters["firm_cap_init_production_planned_mean"]);
    firm_cap_init_production_planned_std = std::get<float>(initialization_parameters["firm_cap_init_production_planned_std"]);
    firm_cap_init_production_planned_min = std::get<float>(initialization_parameters["firm_cap_init_production_planned_min"]);
    firm_cap_init_production_planned_max = std::get<float>(initialization_parameters["firm_cap_init_production_planned_max"]);
    // Initial good price
    firm_cap_init_good_price_current_mean = std::get<float>(initialization_parameters["firm_cap_init_good_price_current_mean"]);
    firm_cap_init_good_price_current_std = std::get<float>(initialization_parameters["firm_cap_init_good_price_current_std"]);
    firm_cap_init_good_price_current_min = std::get<float>(initialization_parameters["firm_cap_init_good_price_current_min"]);
    firm_cap_init_good_price_current_max = std::get<float>(initialization_parameters["firm_cap_init_good_price_current_max"]);
    // Good inventory
    firm_cap_init_inventory_mean = std::get<float>(initialization_parameters["firm_cap_init_inventory_mean"]);
    firm_cap_init_inventory_std = std::get<float>(initialization_parameters["firm_cap_init_inventory_std"]);
    firm_cap_init_inventory_min = std::get<float>(initialization_parameters["firm_cap_init_inventory_min"]);
    firm_cap_init_inventory_max = std::get<float>(initialization_parameters["firm_cap_init_inventory_max"]);

    // --- Capital Firm initialization parameters
    // Working capital
    firm_cap_init_working_capital_inventory_mean = std::get<float>(initialization_parameters["firm_cap_init_working_capital_inventory_mean"]);
    firm_cap_init_working_capital_inventory_std = std::get<float>(initialization_parameters["firm_cap_init_working_capital_inventory_std"]);
    firm_cap_init_working_capital_inventory_min = std::get<float>(initialization_parameters["firm_cap_init_working_capital_inventory_min"]);
    firm_cap_init_working_capital_inventory_max = std::get<float>(initialization_parameters["firm_cap_init_working_capital_inventory_max"]);
    // Desired inventory factor ( characteristics)
    firm_cap_init_desired_inventory_factor_mean = std::get<float>(initialization_parameters["firm_cap_init_desired_inventory_factor_mean"]);
    firm_cap_init_desired_inventory_factor_std = std::get<float>(initialization_parameters["firm_cap_init_desired_inventory_factor_std"]);
    firm_cap_init_desired_inventory_factor_min = std::get<float>(initialization_parameters["firm_cap_init_desired_inventory_factor_min"]);
    firm_cap_init_desired_inventory_factor_max = std::get<float>(initialization_parameters["firm_cap_init_desired_inventory_factor_max"]);

    // Other inits (not randomised)
    firm_cap_init_production_current_ratio = std::get<float>(initialization_parameters["firm_cap_init_production_current_ratio"]);
    firm_cap_init_quantity_sold_ratio = std::get<float>(initialization_parameters["firm_cap_init_quantity_sold_ratio"]);
    firm_cap_init_good_price = std::get<float>(initialization_parameters["firm_cap_init_good_price"]);

    //--- Bank Initialization parameters
    bank_init_interest_rate = std::get<float>(initialization_parameters["bank_init_interest_rate"]);


    //---------- Main Loop Parameters ------------
    // --- Simulation size 
    n_loops = std::get<int>(main_loop_parameters["n_loops"]);
    n_households = std::get<int>(main_loop_parameters["n_households"]);
    n_consumer_firms = std::get<int>(main_loop_parameters["n_consumer_firms"]);
    n_capital_firms = std::get<int>(main_loop_parameters["n_capital_firms"]);
    n_firms = std::get<int>(main_loop_parameters["n_firms"]); 
    n_max_employees = std::get<int>(main_loop_parameters["n_max_employees"]); 
    time_period = std::get<int>(main_loop_parameters["time_period"]); 

    // ---- Household dynamic parameters
    household_n_res_wage_decrease = std::get<float>(main_loop_parameters["household_n_res_wage_decrease"]); 
    household_targeted_savings_to_income_ratio = std::get<float>(main_loop_parameters["household_targeted_savings_to_income_ratio"]);
    household_household_tax_rate = std::get<float>(main_loop_parameters["household_household_tax_rate"]);
    household_p_seek_better_job = std::get<float>(main_loop_parameters["household_p_seek_better_job"]);
    household_sector_spending_randomization = std::get<float>(main_loop_parameters["household_sector_spending_randomization"]);

    // ---- General Firm dynamic parameters
    standard_employment_contract_length = std::get<int>(main_loop_parameters["standard_employment_contract_length"]);
    firm_tax_rate = std::get<float>(main_loop_parameters["firm_tax_rate"]);
    forced_machine_purchases_min = std::get<int>(main_loop_parameters["forced_machine_purchases_min"]); 
    forced_machine_purchases_max = std::get<int>(main_loop_parameters["forced_machine_purchases_max"]); 

    // --- Consumer Firm dynamic parameters
    firm_cons_good_inv_depr_rate = std::get<float>(main_loop_parameters["firm_cons_good_inv_depr_rate"]);
    firm_cons_productivity = std::get<float>(main_loop_parameters["firm_cons_productivity"]); // # units produced per worker machine pairing
    firm_cons_workers_per_machine = std::get<int>(main_loop_parameters["firm_cons_workers_per_machine"]);
    firm_cons_good_unit_cost = std::get<float>(main_loop_parameters["firm_cons_good_unit_cost"]);
    firm_max_cons_production_climbdown = std::get<float>(main_loop_parameters["firm_max_cons_production_climbdown"]);

    // --- Capital Firm dynamic parameters
    firm_cap_inv_depr_rate = std::get<float>(main_loop_parameters["firm_cap_inv_depr_rate"]);
    firm_cap_productivity = std::get<float>(main_loop_parameters["firm_cap_productivity"]); // # units produced per worker machine pairing
    firm_cap_workers_per_machine = std::get<int>(main_loop_parameters["firm_cap_workers_per_machine"]);
    firm_cap_good_unit_cost = std::get<float>(main_loop_parameters["firm_cap_good_unit_cost"]);
    firm_cap_machine_lifespan = std::get<int>(main_loop_parameters["firm_cap_machine_lifespan"]);

    // --- Bank dynamic Parameters
    bank_inflation_reaction = std::get<float>(main_loop_parameters["bank_inflation_reaction"]);
    bank_inflation_target = std::get<float>(main_loop_parameters["bank_inflation_target"]); 
    bank_inflation_target_monthly=  std::get<float>(main_loop_parameters["bank_inflation_target_monthly"]);
    bank_risk_premium = std::get<float>(main_loop_parameters["bank_risk_premium"]);
    bank_target_capital_ratio = std::get<float>(main_loop_parameters["bank_target_capital_ratio"]);
    bank_long_term_loan_length = std::get<int>(main_loop_parameters["bank_long_term_loan_length"]);
    bank_leverage_ratio_lower_threshold = std::get<float>(main_loop_parameters["bank_leverage_ratio_lower_threshold"]);
    bank_leverage_ratio_upper_threshold = std::get<float>(main_loop_parameters["bank_leverage_ratio_upper_threshold"]);


    // Randomness Parameters
}


// Initially declare all variables with default values so we don't get errors

//-------------------- Simulation Size Parameters ---------------
int n_loops = 36;
int n_households = 1000;
int n_consumer_firms = 45;
int n_capital_firms = 5;
int n_firms = 50; 

int time_period = 12; 
int n_max_employees = 100; 


//---- Public parameters----------------------
// Wage parameters
int household_init_unemployment_benefit = 500;
int household_init_minimum_wage = 600;



//--------------- Household parameters ---------------
// --- Household initialization parameters
// General consumption propensity : c
float household_init_c_mean =0.5;
float household_init_c_std =0.15;
float household_init_c_min =0.1;
float household_init_c_max =0.9;
// Propensity to consume financial wealth, c_f
float household_init_c_f_mean = 0.5;
float household_init_c_f_std = 0.1;
float household_init_c_f_min = 0.1;
float household_init_c_f_max = 0.9;
// Propensity to consume human wealth, c_h
float household_init_c_h_mean = 0.2;
float household_init_c_h_std = 0.05;
float household_init_c_h_min = 0.0;
float household_init_c_h_max = 0.4;
// Propensity to consume excess money : c_excess_money
float household_init_c_excess_mean = 0.3;
float household_init_c_excess_std = 0.05;
float household_init_c_excess_min = 0.0;
float household_init_c_excess_max = 0.7;
// Propensity to adopt majority sentiment: p_majority_op_adoption
float household_init_p_majority_mean = 0.25;
float household_init_p_majority_std = 0.2;
float household_init_p_majority_min = 0.01;
float household_init_p_majority_max = 0.99;
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
float household_household_tax_rate = 0.2;
float household_p_seek_better_job = 0.1;
float household_sector_spending_randomization = 0.1;


//---------------------------------------------

//---- Consumer Firm parameters----------------------
// --- Consumer Firm initialization parameters
// Starting total asset
float firm_cons_init_total_assets_mean = 10000;
float firm_cons_init_total_assets_std = 2500;
float firm_cons_init_total_assets_min = 1;
float firm_cons_init_total_assets_max = 999999999;
// Dividend ratio if firm is optimistic
float firm_cons_init_dividend_ratio_optimist_mean = 0.05;
float firm_cons_init_dividend_ratio_optimist_std = 0.02;
float firm_cons_init_dividend_ratio_optimist_min = 0.005;
float firm_cons_init_dividend_ratio_optimist_max = 0.2;
// Dividend ratio if firm is pessimistic
float firm_cons_init_dividend_ratio_pessimist_mean = 0.03;
float firm_cons_init_dividend_ratio_pessimist_std = 0.02;
float firm_cons_init_dividend_ratio_pessimist_min = 0.001;
float firm_cons_init_dividend_ratio_pessimist_max = 0.15;
// Starting wage offers
float firm_cons_init_wage_offer_mean = 1000;
float firm_cons_init_wage_offer_std = 300;
float firm_cons_init_wage_offer_min = 100;
float firm_cons_init_wage_offer_max = 999999;
// Starting desired employees
float firm_cons_init_employee_count_desired_mean = 20;
float firm_cons_init_employee_count_desired_std = 5;
float firm_cons_init_employee_count_desired_min = 1;
float firm_cons_init_employee_count_desired_max = 100;
// Inital planned production
float firm_cons_init_production_planned_mean = 1000;
float firm_cons_init_production_planned_std = 100;
float firm_cons_init_production_planned_min = 100;
float firm_cons_init_production_planned_max = 1999;
// Initial good price
float firm_cons_init_good_price_current_mean = 10;
float firm_cons_init_good_price_current_std = 2;
float firm_cons_init_good_price_current_min = 1;
float firm_cons_init_good_price_current_max = 99;
// Good inventory
float firm_cons_init_inventory_mean = 1000;
float firm_cons_init_inventory_std = 100;
float firm_cons_init_inventory_min = 1;
float firm_cons_init_inventory_max = 999999;
// Working capital inventory
float firm_cons_init_working_capital_inventory_mean = 60;
float firm_cons_init_working_capital_inventory_std = 5;
float firm_cons_init_working_capital_inventory_min = 1;
float firm_cons_init_working_capital_inventory_max = 999999;
// Desired inventory factor ( characteristic)
float firm_cons_init_desired_inventory_factor_mean = 1.5;
float firm_cons_init_desired_inventory_factor_std = 0.25;
float firm_cons_init_desired_inventory_factor_min = 0.1;
float firm_cons_init_desired_inventory_factor_max = 4.0;

// Other inits (not randomised)
float firm_cons_init_production_current_ratio = 0.4;
float firm_cons_init_quantity_sold_ratio = 0.25;
float firm_cons_init_good_price = 9.5;


// --- Consumer Firm dynamic parameters
float firm_cons_good_inv_depr_rate = 0.01;
float firm_cons_productivity = 1000; // # units produced per worker machine pairing
int firm_cons_workers_per_machine = 1;
float firm_cons_good_unit_cost = 1.0;
float firm_max_cons_production_climbdown = 0.25;



//---------------------------------------------

//---- Capital Firm parameters----------------------

// --- Capital Firm initialization parameters
// Starting total asset
float firm_cap_init_total_assets_mean = 10000;
float firm_cap_init_total_assets_std = 2500;
float firm_cap_init_total_assets_min = 1;
float firm_cap_init_total_assets_max = 999999999;
// Dividend ratio if firm is optimistic
float firm_cap_init_dividend_ratio_optimist_mean = 0.05;
float firm_cap_init_dividend_ratio_optimist_std = 0.02;
float firm_cap_init_dividend_ratio_optimist_min = 0.005;
float firm_cap_init_dividend_ratio_optimist_max = 0.2;
// Dividend ratio if firm is pessimistic
float firm_cap_init_dividend_ratio_pessimist_mean = 0.03;
float firm_cap_init_dividend_ratio_pessimist_std = 0.02;
float firm_cap_init_dividend_ratio_pessimist_min = 0.001;
float firm_cap_init_dividend_ratio_pessimist_max = 0.15;
// Starting wage offers
float firm_cap_init_wage_offer_mean = 1000;
float firm_cap_init_wage_offer_std = 300;
float firm_cap_init_wage_offer_min = 100;
float firm_cap_init_wage_offer_max = 999999;
// Starting desired employees
float firm_cap_init_employee_count_desired_mean = 20;
float firm_cap_init_employee_count_desired_std = 5;
float firm_cap_init_employee_count_desired_min = 1;
float firm_cap_init_employee_count_desired_max = 100;

// Inital planned production
float firm_cap_init_production_planned_mean = 1000;
float firm_cap_init_production_planned_std = 100;
float firm_cap_init_production_planned_min = 100;
float firm_cap_init_production_planned_max = 1999;
// Initial good price
float firm_cap_init_good_price_current_mean = 10;
float firm_cap_init_good_price_current_std = 2;
float firm_cap_init_good_price_current_min = 1;
float firm_cap_init_good_price_current_max = 99;
// Good inventory
float firm_cap_init_inventory_mean = 1000;
float firm_cap_init_inventory_std = 100;
float firm_cap_init_inventory_min = 1;
float firm_cap_init_inventory_max = 999999;
// Working capital
float firm_cap_init_working_capital_inventory_mean = 60;
float firm_cap_init_working_capital_inventory_std = 5;
float firm_cap_init_working_capital_inventory_min = 1;
float firm_cap_init_working_capital_inventory_max = 999999;
// Desired inventory factor ( characteristics)
float firm_cap_init_desired_inventory_factor_mean = 1.5;
float firm_cap_init_desired_inventory_factor_std = 0.25;
float firm_cap_init_desired_inventory_factor_min = 0.1;
float firm_cap_init_desired_inventory_factor_max = 4.0;


// Other inits (not randomised)
float firm_cap_init_production_current_ratio = 0.4;
float firm_cap_init_quantity_sold_ratio = 0.25;
float firm_cap_init_good_price = 100.0;


// --- Capital Firm dynamic parameters
float firm_cap_inv_depr_rate = 0.01;
float firm_cap_productivity = 10; // # units produced per worker machine pairing
int firm_cap_workers_per_machine = 1;
int firm_cap_machine_lifespan = 100;
float firm_cap_good_unit_cost = 20.0;


//---------------------------------------------
// ---- Parameters for all Firms
int standard_employment_contract_length = 6;
float firm_tax_rate = 0.2;
int forced_machine_purchases_min = 5; 
int forced_machine_purchases_max = 5;


//---------------------------------------------

//---- Bank parameters --------------
// Bank Initialization parameters
float bank_init_interest_rate = 0.02;

// Exogenous Parameters for Bank
float bank_inflation_reaction = 1.5;
float bank_inflation_target = 1.05; 
float bank_inflation_target_monthly=  1.004;
float bank_risk_premium = 1.0;
float bank_target_capital_ratio = 10.0;
int bank_short_term_loan_length = 12;
int bank_long_term_loan_length = 100;
float bank_leverage_ratio_lower_threshold = 60;
float bank_leverage_ratio_upper_threshold = 100;

//---------------------------------------------