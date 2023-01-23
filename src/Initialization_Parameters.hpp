#ifndef INITIALIZATION_PARAMETERS_HPP
#define INITIALIZATION_PARAMETERS_HPP


#define job_market_size 200



extern const int n_households;
extern const int n_consumer_firms;
extern const int n_capital_firms;

extern const int n_max_employees;

extern const int test_global_var ;

//---- Household initialization parameters ----

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