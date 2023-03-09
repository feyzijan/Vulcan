#ifndef INITIALIZATION_PARAMETERS_HPP
#define INITIALIZATION_PARAMETERS_HPP


// Global parameters to be used throughout the simulation
extern int global_date; 
extern int test_global_var; // for testing
extern int test_global_var_2; // for testing

extern const int time_period; 
extern const int n_loops;

extern const int n_households;
extern const int n_consumer_firms;
extern const int n_capital_firms;
extern const int n_firms;
extern const int n_max_employees;

//------- Household parameters ------------------
// Household initialization parameters
// Below values are used to generate distributions of initial parameters for households

// General consumption propensity : c
extern const float init_c_mean ;
extern const float init_c_std ;
extern const float init_c_min ;
extern const float init_c_max ;
// Propensity to consume financial wealth, c_f
extern const float init_c_f_mean;
extern const float init_c_f_std;
extern const float init_c_f_min;
extern const float init_c_f_max;
// Propensity to consume human wealth, c_h
extern const float init_c_h_mean ;
extern const float init_c_h_std ;
extern const float init_c_h_min ;
extern const float init_c_h_max ;
// Propensity to consume excess money : c_excess_money
extern const float init_c_excess_mean ;
extern const float init_c_excess_std ;
extern const float init_c_excess_min ;
extern const float init_c_excess_max ;
// Propensity to adopt majority sentiment: p_majority_op_adoption
extern const float init_p_majority_mean ;
extern const float init_p_majority_std;
extern const float init_p_majority_min;
extern const float init_p_majority_max;
// Savings propensity - optimist : saving_propensity_optimist 
extern const float init_s_optimist_mean;
extern const float init_s_optimist_std ;
extern const float init_s_optimist_min ;
extern const float init_s_optimist_max ;
// Savings propensity - pessimist : // saving_propensity_pessimist
extern const float init_s_pessimist_mean;
extern const float init_s_pessimist_std ;
extern const float init_s_pessimist_min ;
extern const float init_s_pessimist_max ;
// Starting wealth : wealth
extern const float init_wealth_mean;
extern const float init_wealth_std ;
extern const float init_wealth_min ;
extern const float init_wealth_max ;
// Maximum tolerable unemployment duration
extern const float init_unemp_tolerance_mean;
extern const float init_unemp_tolerance_std;
extern const float init_unemp_tolerance_min;
extern const float init_unemp_tolerance_max;
// Reservation Wage:
extern const float init_res_wage_mean;
extern const float init_res_wage_std;
extern const float init_res_wage_min;
extern const float init_res_wage_max;

// Exogenous parameters for Households
extern const float n_res_wage_decrease; // Household reservation wages are updated with *1-n_uniform*this_value
extern const float targeted_savings_to_income_ratio;
extern const float household_tax_rate;
extern const int init_unemployment_benefit;
extern const int init_minimum_wage;

//---------------------------------------------

//---- Firm initialization parameters -----------
// Below values are used to generate distributions of initial parameters for firms

// Consumer and Capital Firm initialization parameters


extern const float init_total_assets_mean;
extern const float init_total_assets_std;
extern const float init_total_assets_min;
extern const float init_total_assets_max;

extern const float init_dividend_ratio_optimist_mean;
extern const float init_dividend_ratio_optimist_std;
extern const float init_dividend_ratio_optimist_min;
extern const float init_dividend_ratio_optimist_max;

extern const float init_dividend_ratio_pessimist_mean;
extern const float init_dividend_ratio_pessimist_std;
extern const float init_dividend_ratio_pessimist_min;
extern const float init_dividend_ratio_pessimist_max;

extern const float init_wage_offer_mean;
extern const float init_wage_offer_std;
extern const float init_wage_offer_min;
extern const float init_wage_offer_max;

extern const float init_employee_count_desired_mean;
extern const float init_employee_count_desired_std;
extern const float init_employee_count_desired_min;
extern const float init_employee_count_desired_max;


// Consumer Firm initialization parameters 
extern const float init_cons_production_planned_mean;
extern const float init_cons_production_planned_std;
extern const float init_cons_production_planned_min;
extern const float init_cons_production_planned_max;

extern const float init_cons_good_price_current_mean;
extern const float init_cons_good_price_current_std;
extern const float init_cons_good_price_current_min;
extern const float init_cons_good_price_current_max;

extern const float init_cons_inventory_mean;
extern const float init_cons_inventory_std;
extern const float init_cons_inventory_min;
extern const float init_cons_inventory_max;

extern const float init_working_capital_inventory_mean;
extern const float init_working_capital_inventory_std;
extern const float init_working_capital_inventory_min;
extern const float init_working_capital_inventory_max;

extern const float init_desired_inventory_factor_mean;
extern const float init_desired_inventory_factor_std;
extern const float init_desired_inventory_factor_min;
extern const float init_desired_inventory_factor_max;


// Capital Firm Initialization parameters
extern const float init_cap_production_planned_mean;
extern const float init_cap_production_planned_std;
extern const float init_cap_production_planned_min;
extern const float init_cap_production_planned_max;

extern const float init_cap_inventory_mean;
extern const float init_cap_inventory_std;
extern const float init_cap_inventory_min;
extern const float init_cap_inventory_max;

extern const float init_cap_good_price_current_mean;
extern const float init_cap_good_price_current_std;
extern const float init_cap_good_price_current_min;
extern const float init_cap_good_price_current_max;


// Exogenous parameters for Firms
extern const int standard_employment_contract_length;
extern const float firm_tax_rate;
// Below parameters define lower and upper bound of a uniform distribution that forces machine purchases on companies
extern const int forced_machine_purchases_min; 
extern const int forced_machine_purchases_max;

// Exogenous parameters for Consumer Firms
extern const float cons_good_inv_depr_rate;
extern const float cons_productivity; // # units produced per worker machine pairing
extern const int cons_workers_per_machine;
extern const float cons_good_unit_cost;

// Exogenous parameters for Capital Firms
extern const float cap_good_inv_depr_rate;
extern const float cap_productivity; // # units produced per worker machine pairing
extern const int cap_workers_per_machine;
extern const int machine_lifespan;
extern const float cap_good_unit_cost;

// Constants to initialize all firms with
extern const float init_production_current_ratio;
extern const float init_quantity_sold_ratio;
extern const float init_good_price_past;
extern const float init_capital_good_price;



//---------------------------------------------

//---- Bank parameters --------------
// Bank Initialization parameters
extern const float bank_initial_interest_rate;

// Exogenous Parameters for Bank
extern const float bank_inflation_reaction;
extern const float bank_inflation_target; // yearly inflation target
extern const float bank_inflation_target_monthly; // monthly inflation target
extern const float bank_risk_premium; // added yearly interest rate to charge per leverage ratio above threshold
extern const float bank_target_capital_ratio;
extern const int bank_short_term_loan_length;
extern const int bank_long_term_loan_length;
extern const float bank_leverage_ratio_lower_threshold;
extern const float bank_leverage_ratio_upper_threshold;


//---------------------------------------------




#endif