#ifndef INITIALIZATION_PARAMETERS_HPP
#define INITIALIZATION_PARAMETERS_HPP


#include <string>
#include <map>
#include <variant>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

// Declare the initialization_parameters map as an extern variable,
// so it can be accessed from other source files.
extern map<string, float> initialization_parameters;
extern map<string, float> main_loop_parameters;
extern map<string, float> randomness_parameters;


// Declare functions for reading and assigning simulation parameters
void Read_Parameters(map<string, float>& parameter_map, const char* filename);
void Assign_All_Parameters(map<string, float>& initialization_parameters,
map<string, float>& main_loop_parameters, map<string, float>& randomness_parameters);
void Print_Parameter_Map(map<string, float>& parameter_map);
vector<string> split(const string &s, char delimiter);


//-------------------- Simulation Size Parameters ---------------
extern int global_date; 
extern int n_loops;
extern int n_households;
extern int n_consumer_firms;
extern int n_capital_firms;
extern int n_firms;

extern int n_sectors; // not preset currently

extern int time_period; // # timesteps that make a year - Unused right now
extern int n_max_employees;//unused


//---- Public parameters----------------------
// Wage parameters
extern int household_init_unemployment_benefit;
extern int household_init_minimum_wage;


//--------------- Household parameters ---------------
// --- Household initialization parameters
// Below values are used to generate distributions of initial parameters for households
// General consumption propensity : c
extern float household_init_c_mean ;
extern float household_init_c_std ;
extern float household_init_c_min ;
extern float household_init_c_max ;
// Propensity to consume financial wealth, c_f
extern float household_init_c_f_mean;
extern float household_init_c_f_std;
extern float household_init_c_f_min;
extern float household_init_c_f_max;
// Propensity to consume human wealth, c_h
extern float household_init_c_h_mean ;
extern float household_init_c_h_std ;
extern float household_init_c_h_min ;
extern float household_init_c_h_max ;
// Propensity to consume excess money : c_excess_money
extern float household_init_c_excess_mean ;
extern float household_init_c_excess_std ;
extern float household_init_c_excess_min ;
extern float household_init_c_excess_max ;
// Propensity to adopt majority sentiment: p_majority_op_adoption
extern float household_init_p_majority_mean ;
extern float household_init_p_majority_std;
extern float household_init_p_majority_min;
extern float household_init_p_majority_max;
// Savings propensity - optimist : saving_propensity_optimist 
extern float household_init_s_optimist_mean;
extern float household_init_s_optimist_std ;
extern float household_init_s_optimist_min ;
extern float household_init_s_optimist_max ;
// Savings propensity - pessimist : // saving_propensity_pessimist
extern float household_init_s_pessimist_mean;
extern float household_init_s_pessimist_std ;
extern float household_init_s_pessimist_min ;
extern float household_init_s_pessimist_max ;
// Starting wealth : wealth
extern float household_init_wealth_mean;
extern float household_init_wealth_std ;
extern float household_init_wealth_min ;
extern float household_init_wealth_max ;
// Maximum tolerable unemployment duration
extern float household_init_unemp_tolerance_mean;
extern float household_init_unemp_tolerance_std;
extern float household_init_unemp_tolerance_min;
extern float household_init_unemp_tolerance_max;
// Reservation Wage:
extern float household_init_res_wage_mean;
extern float household_init_res_wage_std;
extern float household_init_res_wage_min;
extern float household_init_res_wage_max;

// ---- Household dynamic parameters
extern float household_n_res_wage_decrease; // Household reservation wages are updated with *1-n_uniform*this_value
extern float household_targeted_savings_to_income_ratio;
extern float household_household_tax_rate;
extern float household_p_seek_better_job;
extern float household_sector_spending_randomization;

//---------------------------------------------


//---- Consumer Firm parameters----------------------
// --- Consumer Firm initialization parameters
// Starting total asset
extern float firm_cons_init_total_assets_mean;
extern float firm_cons_init_total_assets_std;
extern float firm_cons_init_total_assets_min;
extern float firm_cons_init_total_assets_max;
// Dividend ratio if firm is optimistic
extern float firm_cons_init_dividend_ratio_optimist_mean;
extern float firm_cons_init_dividend_ratio_optimist_std;
extern float firm_cons_init_dividend_ratio_optimist_min;
extern float firm_cons_init_dividend_ratio_optimist_max;
// Dividend ratio if firm is pessimistic
extern float firm_cons_init_dividend_ratio_pessimist_mean;
extern float firm_cons_init_dividend_ratio_pessimist_std;
extern float firm_cons_init_dividend_ratio_pessimist_min;
extern float firm_cons_init_dividend_ratio_pessimist_max;
// Starting wage offers
extern float firm_cons_init_wage_offer_mean;
extern float firm_cons_init_wage_offer_std;
extern float firm_cons_init_wage_offer_min;
extern float firm_cons_init_wage_offer_max;
// Starting desired employees
extern float firm_cons_init_employee_count_desired_mean;
extern float firm_cons_init_employee_count_desired_std;
extern float firm_cons_init_employee_count_desired_min;
extern float firm_cons_init_employee_count_desired_max;
// Inital planned production
extern float firm_cons_init_production_planned_mean;
extern float firm_cons_init_production_planned_std;
extern float firm_cons_init_production_planned_min;
extern float firm_cons_init_production_planned_max;
// Initial good price
extern float firm_cons_init_good_price_current_mean;
extern float firm_cons_init_good_price_current_std;
extern float firm_cons_init_good_price_current_min;
extern float firm_cons_init_good_price_current_max;
// Good inventory
extern float firm_cons_init_inventory_mean;
extern float firm_cons_init_inventory_std;
extern float firm_cons_init_inventory_min;
extern float firm_cons_init_inventory_max;
// Working capital inventory
extern float firm_cons_init_working_capital_inventory_mean;
extern float firm_cons_init_working_capital_inventory_std;
extern float firm_cons_init_working_capital_inventory_min;
extern float firm_cons_init_working_capital_inventory_max;
// Desired inventory factor ( characteristic)
extern float firm_cons_init_desired_inventory_factor_mean;
extern float firm_cons_init_desired_inventory_factor_std;
extern float firm_cons_init_desired_inventory_factor_min;
extern float firm_cons_init_desired_inventory_factor_max;

// Other inits (not randomised)
extern float firm_cons_init_production_current_ratio;
extern float firm_cons_init_quantity_sold_ratio;
extern float firm_cons_init_good_price;
extern float firm_cons_init_emissions_per_unit;

// --- Consumer Firm dynamic parameters
extern float firm_cons_inv_depr_rate;
extern float firm_cons_productivity; // # units produced per worker machine pairing
extern int firm_cons_workers_per_machine;
extern float firm_cons_good_unit_cost;
extern float firm_cons_max_production_climbdown;


//---------------------------------------------

// Consumer Firm Sectors
struct Consumer_Firm_Sector {
    string sector_name;
    int sector_id; // unique id for this sector
    float consumption_weighing; // % of consumption that goes to this sector
    float firm_weighing;
    float inv_depr_rate;
    int output_per_machine;
    int workers_per_machine;
    float good_unit_cost;
    float max_production_climbdown;
    float emission_per_unit; // NEWLY ADDED

    Consumer_Firm_Sector(string p_name, int p_sector_id, float p_consumption_weighing,
    float p_firm_weighing, float p_inv_depr_rate, int p_output_per_machine, int p_workers_per_machine,
    float p_good_unit_cost, float p_max_production_climbdown, float p_emissions_per_unit)
    : sector_name(p_name), sector_id(p_sector_id), consumption_weighing(p_consumption_weighing),
    firm_weighing(p_firm_weighing), inv_depr_rate(p_inv_depr_rate), output_per_machine(p_output_per_machine),
    workers_per_machine(p_workers_per_machine), good_unit_cost(p_good_unit_cost), 
    max_production_climbdown(p_max_production_climbdown), emission_per_unit(p_emissions_per_unit)
    {}
};

//---------------------------------------------

//---- Capital Firm parameters----------------------

// --- Capital Firm initialization parameters
// Starting total asset
extern float firm_cap_init_total_assets_mean;
extern float firm_cap_init_total_assets_std;
extern float firm_cap_init_total_assets_min;
extern float firm_cap_init_total_assets_max;
// Dividend ratio if firm is optimistic
extern float firm_cap_init_dividend_ratio_optimist_mean;
extern float firm_cap_init_dividend_ratio_optimist_std;
extern float firm_cap_init_dividend_ratio_optimist_min;
extern float firm_cap_init_dividend_ratio_optimist_max;
// Dividend ratio if firm is pessimistic
extern float firm_cap_init_dividend_ratio_pessimist_mean;
extern float firm_cap_init_dividend_ratio_pessimist_std;
extern float firm_cap_init_dividend_ratio_pessimist_min;
extern float firm_cap_init_dividend_ratio_pessimist_max;
// Starting wage offers
extern float firm_cap_init_wage_offer_mean;
extern float firm_cap_init_wage_offer_std;
extern float firm_cap_init_wage_offer_min;
extern float firm_cap_init_wage_offer_max;
// Starting desired employees
extern float firm_cap_init_employee_count_desired_mean;
extern float firm_cap_init_employee_count_desired_std;
extern float firm_cap_init_employee_count_desired_min;
extern float firm_cap_init_employee_count_desired_max;

// Inital planned production
extern float firm_cap_init_production_planned_mean;
extern float firm_cap_init_production_planned_std;
extern float firm_cap_init_production_planned_min;
extern float firm_cap_init_production_planned_max;
// Initial good price
extern float firm_cap_init_good_price_current_mean;
extern float firm_cap_init_good_price_current_std;
extern float firm_cap_init_good_price_current_min;
extern float firm_cap_init_good_price_current_max;
// Good inventory
extern float firm_cap_init_inventory_mean;
extern float firm_cap_init_inventory_std;
extern float firm_cap_init_inventory_min;
extern float firm_cap_init_inventory_max;
// Working capital
extern float firm_cap_init_working_capital_inventory_mean;
extern float firm_cap_init_working_capital_inventory_std;
extern float firm_cap_init_working_capital_inventory_min;
extern float firm_cap_init_working_capital_inventory_max;
// Desired inventory factor ( characteristics)
extern float firm_cap_init_desired_inventory_factor_mean;
extern float firm_cap_init_desired_inventory_factor_std;
extern float firm_cap_init_desired_inventory_factor_min;
extern float firm_cap_init_desired_inventory_factor_max;

// Other inits (not randomised)
extern float firm_cap_init_production_current_ratio;
extern float firm_cap_init_quantity_sold_ratio;
extern float firm_cap_init_good_price;
extern float firm_cap_init_emissions_per_unit;

// --- Capital Firm dynamic parameters
extern float firm_cap_inv_depr_rate;
extern float firm_cap_productivity; // # units produced per worker machine pairing
extern int firm_cap_workers_per_machine;
extern int firm_cap_machine_lifespan;
extern float firm_cap_max_production_climbdown;
extern float firm_cap_good_unit_cost;


//---------------------------------------------
// ---- Parameters for all Firms
extern int standard_employment_contract_length;
extern float firm_tax_rate;
// Below parameters define lower and upper bound of a uniform distribution 
// that forces machine purchases on companies
extern int forced_machine_purchases_min; 
extern int forced_machine_purchases_max;


//---------------------------------------------

//---- Bank parameters --------------
// Bank Initialization parameters
extern float bank_init_interest_rate;

// Dynamic parameters
extern float bank_inflation_reaction;
extern float bank_inflation_target; // yearly inflation target
extern float bank_inflation_target_monthly; // monthly inflation target
extern float bank_risk_premium; // added yearly interest rate to charge per leverage ratio above threshold
extern float bank_target_capital_ratio;
extern int bank_short_term_loan_length;
extern int bank_long_term_loan_length;
extern float bank_leverage_ratio_lower_threshold;
extern float bank_leverage_ratio_upper_threshold;


#endif