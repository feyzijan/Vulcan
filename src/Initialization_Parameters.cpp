// TODO: Add function here to read all these values from a text file
#include "Initialization_Parameters.hpp"


// Global parameters to be used throughout the simulation
int global_date = 0;// will be in main

const int n_households = 10000;
const int n_consumer_firms = 100;
const int n_capital_firms = 100;
const int n_max_employees = 100;
const int test_global_var = 999; // for testing

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
const float init_wealth_mean = 10000.0;
const float init_wealth_std = 3000.0;
const float init_wealth_min = 0.0;
const float init_wealth_max = 999999.0;
// Starting wealth : wealth
const float init_unemp_tolerance_mean = 10.0;
const float init_unemp_tolerance_std = 2.0;
const float init_unemp_tolerance_min = 0.0;
const float init_unemp_tolerance_max = 100.0;

// Exogenous parameters for Households
const float n_res_wage_decrease = 0.02; 
const float targeted_savings_to_income_ratio = 3.0;


//---------------------------------------------

//---- Firm parameters----------------------
//Firm initialization parameters 
const float init_production_planned_mean = 1000;
const float init_production_planned_std = 100;
const float init_production_planned_min = 100;
const float init_production_planned_max = 1900;

const float init_good_price_current_mean = 10;
const float init_good_price_current_std = 2;
const float init_good_price_current_min = 1;
const float init_good_price_current_max = 99;

const float init_total_assets_mean = 1000000;
const float init_total_assets_std = 250000;
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

const float init_employee_count_desired_mean = 50;
const float init_employee_count_desired_std = 5;
const float init_employee_count_desired_min = 1;
const float init_employee_count_desired_max = 999999;

const float init_inventory_mean = 1000;
const float init_inventory_std = 100;
const float init_inventory_min = 1;
const float init_inventory_max = 999999;

const float init_working_capital_inventory_mean = 50;
const float init_working_capital_inventory_std = 5;
const float init_working_capital_inventory_min = 1;
const float init_working_capital_inventory_max = 999999;

const float init_desired_inventory_factor_mean = 1.5;
const float init_desired_inventory_factor_std = 0.25;
const float init_desired_inventory_factor_min = 0.1;
const float init_desired_inventory_factor_max = 4.0;

// Exogenous parameters for Firms
const int standard_employment_contract_length = 12;


// Exogenous parameters for Consumer Firms
const float cons_good_inv_depr_rate = 0.01;
const float cons_productivity = 100; // # units produced per worker machine pairing
const int cons_workers_per_machine = 1;

// Exogenous parameters for Capital Firms
const float cap_good_inv_depr_rate = 0.01;
const float cap_productivity = 0.05; // # units produced per worker machine pairing
const int cap_workers_per_machine = 1;
const int machine_lifespan = 100;

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
//---------------------------------------------





