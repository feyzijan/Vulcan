#ifndef INITIALIZATION_PARAMETERS_HPP
#define INITIALIZATION_PARAMETERS_HPP


#include <string>
#include <map>
#include <variant>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Declare the initialization_parameters map as an extern variable,
// so it can be accessed from other source files.
extern std::map<string, std::variant<int, float>> initialization_parameters;
extern std::map<string, std::variant<int, float>> main_loop_parameters;
extern std::map<string, std::variant<int, float>> randomness_parameters;


// Declare the Read_Parameters function.
void Read_Parameters(map<string, std::variant<int, float>>& parameter_map, const string& filename);


//-------------------- Simulation Size Parameters ---------------
extern int global_date; 
extern const int n_loops;
extern const int n_households;
extern const int n_consumer_firms;
extern const int n_capital_firms;
extern const int n_firms;

extern const int n_sectors; // not preset currently

extern const int time_period; // # timesteps that make a year - Unused right now
extern const int n_max_employees;//unused


//---- Public parameters----------------------
// Wage parameters
extern const int public_init_unemployment_benefit;
extern const int public_init_minimum_wage;


//--------------- Household parameters ---------------
// --- Household initialization parameters
// Below values are used to generate distributions of initial parameters for households
// General consumption propensity : c
extern const float household_init_c_mean ;
extern const float household_init_c_std ;
extern const float household_init_c_min ;
extern const float household_init_c_max ;
// Propensity to consume financial wealth, c_f
extern const float household_init_c_f_mean;
extern const float household_init_c_f_std;
extern const float household_init_c_f_min;
extern const float household_init_c_f_max;
// Propensity to consume human wealth, c_h
extern const float household_init_c_h_mean ;
extern const float household_init_c_h_std ;
extern const float household_init_c_h_min ;
extern const float household_init_c_h_max ;
// Propensity to consume excess money : c_excess_money
extern const float household_init_c_excess_mean ;
extern const float household_init_c_excess_std ;
extern const float household_init_c_excess_min ;
extern const float household_init_c_excess_max ;
// Propensity to adopt majority sentiment: p_majority_op_adoption
extern const float household_init_p_majority_mean ;
extern const float household_init_p_majority_std;
extern const float household_init_p_majority_min;
extern const float household_init_p_majority_max;
// Savings propensity - optimist : saving_propensity_optimist 
extern const float household_init_s_optimist_mean;
extern const float household_init_s_optimist_std ;
extern const float household_init_s_optimist_min ;
extern const float household_init_s_optimist_max ;
// Savings propensity - pessimist : // saving_propensity_pessimist
extern const float household_init_s_pessimist_mean;
extern const float household_init_s_pessimist_std ;
extern const float household_init_s_pessimist_min ;
extern const float household_init_s_pessimist_max ;
// Starting wealth : wealth
extern const float household_init_wealth_mean;
extern const float household_init_wealth_std ;
extern const float household_init_wealth_min ;
extern const float household_init_wealth_max ;
// Maximum tolerable unemployment duration
extern const float household_init_unemp_tolerance_mean;
extern const float household_init_unemp_tolerance_std;
extern const float household_init_unemp_tolerance_min;
extern const float household_init_unemp_tolerance_max;
// Reservation Wage:
extern const float household_init_res_wage_mean;
extern const float household_init_res_wage_std;
extern const float household_init_res_wage_min;
extern const float household_init_res_wage_max;

// ---- Household dynamic parameters
extern const float household_n_res_wage_decrease; // Household reservation wages are updated with *1-n_uniform*this_value
extern const float household_targeted_savings_to_income_ratio;
extern const float household_household_tax_rate;
extern const float household_p_seek_better_job;
extern const float household_sector_spending_randomization;

//---------------------------------------------


//---- Consumer Firm parameters----------------------
// --- Consumer Firm initialization parameters
// Starting total asset
extern const float firm_cons_init_total_assets_mean;
extern const float firm_cons_init_total_assets_std;
extern const float firm_cons_init_total_assets_min;
extern const float firm_cons_init_total_assets_max;
// Dividend ratio if firm is optimistic
extern const float firm_cons_init_dividend_ratio_optimist_mean;
extern const float firm_cons_init_dividend_ratio_optimist_std;
extern const float firm_cons_init_dividend_ratio_optimist_min;
extern const float firm_cons_init_dividend_ratio_optimist_max;
// Dividend ratio if firm is pessimistic
extern const float firm_cons_init_dividend_ratio_pessimist_mean;
extern const float firm_cons_init_dividend_ratio_pessimist_std;
extern const float firm_cons_init_dividend_ratio_pessimist_min;
extern const float firm_cons_init_dividend_ratio_pessimist_max;
// Starting wage offers
extern const float firm_cons_init_wage_offer_mean;
extern const float firm_cons_init_wage_offer_std;
extern const float firm_cons_init_wage_offer_min;
extern const float firm_cons_init_wage_offer_max;
// Starting desired employees
extern const float firm_cons_init_employee_count_desired_mean;
extern const float firm_cons_init_employee_count_desired_std;
extern const float firm_cons_init_employee_count_desired_min;
extern const float firm_cons_init_employee_count_desired_max;
// Inital planned production
extern const float firm_cons_init_production_planned_mean;
extern const float firm_cons_init_production_planned_std;
extern const float firm_cons_init_production_planned_min;
extern const float firm_cons_init_production_planned_max;
// Initial good price
extern const float firm_cons_init_good_price_current_mean;
extern const float firm_cons_init_good_price_current_std;
extern const float firm_cons_init_good_price_current_min;
extern const float firm_cons_init_good_price_current_max;
// Good inventory
extern const float firm_cons_init_inventory_mean;
extern const float firm_cons_init_inventory_std;
extern const float firm_cons_init_inventory_min;
extern const float firm_cons_init_inventory_max;
// Working capital inventory
extern const float firm_cons_init_working_capital_inventory_mean;
extern const float firm_cons_init_working_capital_inventory_std;
extern const float firm_cons_init_working_capital_inventory_min;
extern const float firm_cons_init_working_capital_inventory_max;
// Desired inventory factor ( characteristic)
extern const float firm_cons_init_desired_inventory_factor_mean;
extern const float firm_cons_init_desired_inventory_factor_std;
extern const float firm_cons_init_desired_inventory_factor_min;
extern const float firm_cons_init_desired_inventory_factor_max;

// Other inits (not randomised)
extern const float firm_cons_init_production_current_ratio;
extern const float firm_cons_init_quantity_sold_ratio;
extern const float firm_cons_init_good_price;

// --- Consumer Firm dynamic parameters
extern const float firm_cons_good_inv_depr_rate;
extern const float firm_cons_productivity; // # units produced per worker machine pairing
extern const int firm_cons_workers_per_machine;
extern const float firm_cons_good_unit_cost;
extern const float firm_max_cons_production_climbdown;


//---------------------------------------------

// Consumer Firm Sectors
struct Consumer_Firm_Sector {
    const std::string sector_name;
    const float consumption_weighing; // % of consumption that goes to this sector
    const int sector_id; // unique id for this sector

    Consumer_Firm_Sector(std::string name, float weighing, int id)
        : sector_name(name), consumption_weighing(weighing), sector_id(id) {}
};

//---------------------------------------------

//---- Capital Firm parameters----------------------

// --- Capital Firm initialization parameters
// Starting total asset
extern const float firm_cap_init_total_assets_mean;
extern const float firm_cap_init_total_assets_std;
extern const float firm_cap_init_total_assets_min;
extern const float firm_cap_init_total_assets_max;
// Dividend ratio if firm is optimistic
extern const float firm_cap_init_dividend_ratio_optimist_mean;
extern const float firm_cap_init_dividend_ratio_optimist_std;
extern const float firm_cap_init_dividend_ratio_optimist_min;
extern const float firm_cap_init_dividend_ratio_optimist_max;
// Dividend ratio if firm is pessimistic
extern const float firm_cap_init_dividend_ratio_pessimist_mean;
extern const float firm_cap_init_dividend_ratio_pessimist_std;
extern const float firm_cap_init_dividend_ratio_pessimist_min;
extern const float firm_cap_init_dividend_ratio_pessimist_max;
// Starting wage offers
extern const float firm_cap_init_wage_offer_mean;
extern const float firm_cap_init_wage_offer_std;
extern const float firm_cap_init_wage_offer_min;
extern const float firm_cap_init_wage_offer_max;
// Starting desired employees
extern const float firm_cap_init_employee_count_desired_mean;
extern const float firm_cap_init_employee_count_desired_std;
extern const float firm_cap_init_employee_count_desired_min;
extern const float firm_cap_init_employee_count_desired_max;

// Inital planned production
extern const float firm_cap_init_production_planned_mean;
extern const float firm_cap_init_production_planned_std;
extern const float firm_cap_init_production_planned_min;
extern const float firm_cap_init_production_planned_max;
// Initial good price
extern const float firm_cap_init_good_price_current_mean;
extern const float firm_cap_init_good_price_current_std;
extern const float firm_cap_init_good_price_current_min;
extern const float firm_cap_init_good_price_current_max;
// Good inventory
extern const float firm_cap_init_inventory_mean;
extern const float firm_cap_init_inventory_std;
extern const float firm_cap_init_inventory_min;
extern const float firm_cap_init_inventory_max;
// Working capital
extern const float firm_cap_init_working_capital_inventory_mean;
extern const float firm_cap_init_working_capital_inventory_std;
extern const float firm_cap_init_working_capital_inventory_min;
extern const float firm_cap_init_working_capital_inventory_max;
// Desired inventory factor ( characteristics)
extern const float firm_cap_init_desired_inventory_factor_mean;
extern const float firm_cap_init_desired_inventory_factor_std;
extern const float firm_cap_init_desired_inventory_factor_min;
extern const float firm_cap_init_desired_inventory_factor_max;

// Other inits (not randomised)
extern const float firm_cap_init_production_current_ratio;
extern const float firm_cap_init_quantity_sold_ratio;
extern const float firm_cap_init_good_price;

// --- Capital Firm dynamic parameters
extern const float firm_cap_good_inv_depr_rate;
extern const float firm_cap_productivity; // # units produced per worker machine pairing
extern const int firm_cap_workers_per_machine;
extern const int firm_cap_machine_lifespan;
extern const float firm_cap_good_unit_cost;


//---------------------------------------------
// ---- Parameters for all Firms
extern const int standard_employment_contract_length;
extern const float firm_tax_rate;
// Below parameters define lower and upper bound of a uniform distribution 
// that forces machine purchases on companies
extern const int forced_machine_purchases_min; 
extern const int forced_machine_purchases_max;


//---------------------------------------------

//---- Bank parameters --------------
// Bank Initialization parameters
extern const float bank_init_interest_rate;

// Dynamic parameters
extern const float bank_inflation_reaction;
extern const float bank_inflation_target; // yearly inflation target
extern const float bank_inflation_target_monthly; // monthly inflation target
extern const float bank_risk_premium; // added yearly interest rate to charge per leverage ratio above threshold
extern const float bank_target_capital_ratio;
extern const int bank_short_term_loan_length;
extern const int bank_long_term_loan_length;
extern const float bank_leverage_ratio_lower_threshold;
extern const float bank_leverage_ratio_upper_threshold;


#endif