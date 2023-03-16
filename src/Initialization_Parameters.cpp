// TODO: Add function here to read all these values from a text file
#include "Initialization_Parameters.hpp"


// Global parameters to be used throughout the simulation
int global_date = 0;// will be in main
int test_global_var = 0; // for testing
int test_global_var_2 = 0; // for testing

const int time_period = 12; // i.e. 12 timesteps make a year - Unused

// Size of simulation - Set properly!
const int n_loops = 60;
const int n_households = 10000;
const int n_consumer_firms = 350;
const int n_capital_firms = 50;
const int n_firms = 400; 


const int n_max_employees = 100; //unused


//------- Household parameters -----------
// Household initialization parameters
// General consumption propensity : c
const float init_c_mean =0.5;
const float init_c_std =0.15;
const float init_c_min =0.1;
const float init_c_max =0.9;
// Propensity to consume financial wealth, c_f
const float init_c_f_mean = 0.5;
const float init_c_f_std = 0.1;
const float init_c_f_min = 0.1;
const float init_c_f_max = 0.9;
// Propensity to consume human wealth, c_h
const float init_c_h_mean = 0.2;
const float init_c_h_std = 0.05;
const float init_c_h_min = 0.0;
const float init_c_h_max = 0.4;
// Propensity to consume excess money : c_excess_money
const float init_c_excess_mean = 0.3;
const float init_c_excess_std = 0.05;
const float init_c_excess_min = 0.0;
const float init_c_excess_max = 0.7;
// Propensity to adopt majority sentiment: p_majority_op_adoption
const float init_p_majority_mean = 0.25;
const float init_p_majority_std = 0.2;
const float init_p_majority_min = 0.01;
const float init_p_majority_max = 0.99;
// Savings propensity - optimist : saving_propensity_optimist 
const float init_s_optimist_mean = 0.2;
const float init_s_optimist_std = 0.05;
const float init_s_optimist_min = 0.0;
const float init_s_optimist_max = 0.5;
// Savings propensity - pessimist : // saving_propensity_pessimist
const float init_s_pessimist_mean = 0.3;
const float init_s_pessimist_std = 0.05;
const float init_s_pessimist_min = 0.1;
const float init_s_pessimist_max = 0.6;
// Starting wealth : wealth
const float init_wealth_mean = 1000.0;
const float init_wealth_std = 300.0;
const float init_wealth_min = 0.0;
const float init_wealth_max = 2000.0;
// Maximum tolerable unemployment duration
const float init_unemp_tolerance_mean = 4.0;
const float init_unemp_tolerance_std = 2.0;
const float init_unemp_tolerance_min = 0.0;
const float init_unemp_tolerance_max = 100.0;
// Reservation Wage:
const float init_res_wage_mean = 950;
const float init_res_wage_std = 300;
const float init_res_wage_min = 100;
const float init_res_wage_max = 999999;

// Exogenous parameters for Households
const float n_res_wage_decrease = 0.05; 
const float targeted_savings_to_income_ratio = 3.0;
const float household_tax_rate = 0.2;
const int init_unemployment_benefit = 500;
const int init_minimum_wage = 600;
const float p_seek_better_job = 0.1;
const float sector_spending_randomization = 0.1;

//---------------------------------------------

//---- Firm parameters----------------------
// Consumer and Capital Firm initialization parameters


const float init_total_assets_mean = 10000;
const float init_total_assets_std = 2500;
const float init_total_assets_min = 1;
const float init_total_assets_max = 999999999;

const float init_dividend_ratio_optimist_mean = 0.05;
const float init_dividend_ratio_optimist_std = 0.02;
const float init_dividend_ratio_optimist_min = 0.005;
const float init_dividend_ratio_optimist_max = 0.2;

const float init_dividend_ratio_pessimist_mean = 0.03;
const float init_dividend_ratio_pessimist_std = 0.02;
const float init_dividend_ratio_pessimist_min = 0.001;
const float init_dividend_ratio_pessimist_max = 0.15;

const float init_wage_offer_mean = 1000;
const float init_wage_offer_std = 300;
const float init_wage_offer_min = 100;
const float init_wage_offer_max = 999999;

const float init_employee_count_desired_mean = 25;
const float init_employee_count_desired_std = 5;
const float init_employee_count_desired_min = 1;
const float init_employee_count_desired_max = 100;


// Consumer Firm initialization parameters 
const float init_cons_production_planned_mean = 1000;
const float init_cons_production_planned_std = 100;
const float init_cons_production_planned_min = 100;
const float init_cons_production_planned_max = 1999;

const float init_cons_good_price_current_mean = 10;
const float init_cons_good_price_current_std = 2;
const float init_cons_good_price_current_min = 1;
const float init_cons_good_price_current_max = 99;

const float init_cons_inventory_mean = 1000;
const float init_cons_inventory_std = 100;
const float init_cons_inventory_min = 1;
const float init_cons_inventory_max = 999999;

const float init_working_capital_inventory_mean = 60;
const float init_working_capital_inventory_std = 5;
const float init_working_capital_inventory_min = 1;
const float init_working_capital_inventory_max = 999999;

const float init_desired_inventory_factor_mean = 1.5;
const float init_desired_inventory_factor_std = 0.25;
const float init_desired_inventory_factor_min = 0.1;
const float init_desired_inventory_factor_max = 4.0;

// Capital Firm Initialization parameters

const float init_cap_production_planned_mean = 100;
const float init_cap_production_planned_std = 10;
const float init_cap_production_planned_min = 10;
const float init_cap_production_planned_max = 999;

const float init_cap_good_price_current_mean = 1000;
const float init_cap_good_price_current_std = 200;
const float init_cap_good_price_current_min = 100;
const float init_cap_good_price_current_max = 9999;

const float init_cap_inventory_mean = 100;
const float init_cap_inventory_std = 10;
const float init_cap_inventory_min = 1;
const float init_cap_inventory_max = 9999;


// Exogenous parameters for all Firms
const int standard_employment_contract_length = 6;
const float firm_tax_rate = 0.2;
const int forced_machine_purchases_min = 5; 
const int forced_machine_purchases_max = 5;

// Exogenous parameters for Consumer Firms
const float cons_good_inv_depr_rate = 0.01;
const float cons_productivity = 100; // # units produced per worker machine pairing
const int cons_workers_per_machine = 1;
const float cons_good_unit_cost = 1.0;
const float max_cons_production_climbdown = 0.25;

// Exogenous parameters for Capital Firms
const float cap_good_inv_depr_rate = 0.01;
const float cap_productivity = 10; // # units produced per worker machine pairing
const int cap_workers_per_machine = 1;
const int machine_lifespan = 100;
const float cap_good_unit_cost = 2.0;

// Constants to initialize all firms with
const float init_production_current_ratio = 0.4;
const float init_quantity_sold_ratio = 0.25;
const float init_good_price_past = 9.5;
const float init_capital_good_price = 100.0;





//---------------------------------------------

//---- Bank parameters --------------
// Bank Initialization parameters
const float bank_initial_interest_rate = 0.02;

// Exogenous Parameters for Bank
const float bank_inflation_reaction = 1.5;
const float bank_inflation_target = 1.05; 
const float bank_inflation_target_monthly=  1.004;
const float bank_risk_premium = 1.0;
const float bank_target_capital_ratio = 10.0;
const int bank_short_term_loan_length = 12;
const int bank_long_term_loan_length = 100;
const float bank_leverage_ratio_lower_threshold = 60;
const float bank_leverage_ratio_upper_threshold = 100;

//---------------------------------------------





