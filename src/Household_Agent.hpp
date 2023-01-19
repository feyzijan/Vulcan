#ifndef HOUSEHOLD_AGENT_HPP
#define HOUSEHOLD_AGENT_HPP


#include <numeric>
#include <random>

class Public_Info_Board;

#include "Public_Info_Board.hpp"
#include "Job.hpp"
//#include "Firm_Agent.hpp"

#define income_lookback_period 10


class Household_Agent{

    public:
    // Constructors//


    //Full on Constructor
    Household_Agent(float propensities[7], int unemployment_tolerance, int wealth );
    

    Household_Agent(Household_Agent&); //Copy constructor
    
    ~Household_Agent(); // Destructor

    //--------------------------------//
    void Print();
    void Print_Characteristics();





    // ---- Printing Class contents ----//


    // Update current total income from all sources
    void Update_Income();

    // Assign a value to the unemployment benefits
    void Assign_Unemployment_Benefits(int unemployment_benefit_amount);

    // Calculate average income over the past n_periods
    void Update_Average_Income();
    
    // Determine consumer sentiment
    void Determine_Consumer_Sentiment();

    // Determine consumption budget (eq 18)
    void Determine_Consumption_Budget();
    
    // Determine goods to buy - TO IMPLEMENT
    //void Buy_Consumer_Goods(Consumer_Goods_Market* market);


    // Calculate new financial wealth (eq 6-7)
    void Update_Wealth();




    // Check for jobs in the public market
    void Seek_Jobs();

    // Update reservation wage
    void Update_Reservation_Wage();



    //Setters
    void Set_Public_Info_Board(Public_Info_Board* ptr) {pPublic_Info_Board = ptr;}
    void Set_Job(Job* ptr) { current_job = ptr;}


    //Getters
    int Get_Wage_Dividend() {};
    int Get_Wage() {return income_wage;};
    bool Get_Employment_Status() {return !unemployed;}



    //Household variables
    protected:
    
    // Public info board
    Public_Info_Board* pPublic_Info_Board;

    //Job offer
    Job * current_job;

    // Wealth
    int wealth_financial; //W_f in equations 
    int wealth_human; //W_h in equations * Unsure if this is needed
    
    // Consumption and Expenditure
    int expenditure_consumption;
    int expenditure_tax;
    float consumption_propensity; //c eq(17) - characteristic

    // Savings
    int new_savings;

    int cash_on_hand_real_desired; // M_Total
    int cash_on_hand_desired; //m_targeted
    int cash_on_hand_current; //m_actual
    
    // Savings constants
    float saving_propensity; //s
    float saving_propensity_pessimist; //s_h - characteristic
    float saving_propensity_optimist; //s_l  - characteristic

    // Income 
    int income_current;
    int income_average;
    int income_wage; 
    int income_unemployment_benefit;
    int income_gov_transfers;
    int income_firm_owner_dividend;

    // Initialize this to all zeros
    int income_past[income_lookback_period]; // must equal average_income_lookback_period


    // Unemployment status
    bool unemployed;
    int reservation_wage;
    int unemp_duration;
    int unemp_duration_upper_bound;

    // Sentiment 
    bool positive_sentiment; // pessimistic, optimistic

    // Pre-set constants
    bool business_owner; // If True will receive dividend income
    float c_f; // propensity to consume financial wealth
    float c_h; // propensity to consume human wealth
    float c_excess_money; // propensity yo consume excess money balance 
    float p_majority_op_adoption; // mu^m : probablility of adopting majority opinion
};


/* Initialization Functions

*/

void Initialize_Households(Household_Agent * Household_array, Public_Info_Board* pPublic_Board, int size);

void Initialize_Household_Jobs(Household_Agent * Household_array,  int size);


#endif