#ifndef INITIALIZATION_PARAMETERS_HPP
#define INITIALIZATION_PARAMETERS_HPP


#define job_market_size 200


extern int global_date;


extern const int n_households;
extern const int n_consumer_firms;
extern const int n_capital_firms;

extern const int n_max_employees;

extern const int test_global_var ;

//---- Household initialization parameters -----------

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

//---------------------------------------------

//---- Firm initialization parameters -----------


extern const float init_production_planned_mean;
extern const float init_production_planned_std;
extern const float init_production_planned_min;
extern const float init_production_planned_max;

extern const float init_good_price_current_mean;
extern const float init_good_price_current_std;
extern const float init_good_price_current_min;
extern const float init_good_price_current_max;

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

extern const float init_inventory_mean;
extern const float init_inventory_std;
extern const float init_inventory_min;
extern const float init_inventory_max;

extern const float init_working_capital_inventory_mean;
extern const float init_working_capital_inventory_std;
extern const float init_working_capital_inventory_min;
extern const float init_working_capital_inventory_max;

extern const float init_desired_inventory_factor_mean;
extern const float init_desired_inventory_factor_std;
extern const float init_desired_inventory_factor_min;
extern const float init_desired_inventory_factor_max;




// Initial Parameters for Bank
extern const float initial_interest_rate;

// Exogenous Parameters for Bank
extern const float inflation_reaction;
extern const float inflation_target; // yearly inflation target
extern const float inflation_target_monthly; // monthly inflation target

// Exogenous parameters for Firms
extern const int standard_employment_contract_length;


// Exogenous parameters for Consumer Firms
extern const float cons_good_inv_depr_rate;
extern const float cons_productivity; // # units produced per worker machine pairing
extern const int cons_workers_per_machine;

// Exogenous parameters for Capital Firms
extern const float cap_productivity; // # units produced per worker machine pairing
extern const int cap_workers_per_machine;


// Exogenous parameters for Households
extern const float n_res_wage_decrease; // Household reservation wages are updated with *1-n_uniform*this_value




/*
namespace constants
{
    // since the actual variables are inside a namespace, the forward declarations need to be inside a namespace as well
    //extern const int job_market_size;
    extern const int n_households;
    extern const int n_consumer_firms;
    extern const int n_capital_firms;
    extern const int n_max_employees;
}
*/


#endif