// TODO: Add function here to read all these values from a text file


#include "Initialization_Parameters.hpp"

const int n_max_employees = 100;

const int n_households = 100;
const int n_consumer_firms = 9;
const int n_capital_firms = 3;

const int test_global_var = 999;


//---- Household initialization parameters ----

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





/*
namespace constants
{
    // since the actual variables are inside a namespace, the forward declarations need to be inside a namespace as well
    //extern const int job_market_size {100};
    extern const int n_households {100};
    extern const int n_consumer_firms {10};
    extern const int n_capital_firms{2};
    extern const int n_max_employees{100};
}
*/

