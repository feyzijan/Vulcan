#ifndef PUBLIC_INFO_BOARD_HPP
#define PUBLIC_INFO_BOARD_HPP
#endif

#ifndef JOB_OFFER_HPP
#define JOB_OFFER_HPP
#endif

#include <numeric>
#include <random>


//TODO: Decide how to initialize

class Household_Agent{

    public:
    // Constructors//
    Household_Agent(int initial_savings, 
    int max_unemp_dur, bool unemployed, bool positive_sentiment, int reservation_wage,
    float saving_propensity_pessimist, float saving_propensity_optimist); //Constructor

    Household_Agent(Household_Agent&); //Copy constructor
    
    ~Household_Agent(); // Destructor

    //--------------------------------//
    void Print();




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




    // Compare two job offers and pick the best one
    void Seek_Jobs();

    // Update reservation wage
    void Update_Reservation_Wage();



    //Getters
    int Get_Wage_Dividend() {};



    //Household variables
    protected:
    
    


    // Public info board
    Public_Info_Board* pPublic_Info_Board;

    //Job offer
    Job_Offer * current_job;

    // Wealth
    int wealth_financial; //W_f in equations
    int wealth_human; //W_h in equations
    
    // Consumption and Expenditure
    int expenditure_consumption;
    int expenditure_tax;
    float consumption_propensity; //c eq(17)

    // Savings
    int new_savings;

    int cash_on_hand_real_desired; // M_Total
    int cash_on_hand_desired; //m_targeted
    int cash_on_hand_current; //m_actual
    
    // Savings constants
    float saving_propensity; //s
    float saving_propensity_pessimist; //s_h
    float saving_propensity_optimist; //s_l

    // Income variables
    int income_current;
    int income_average;
    int income_wage; 
    int income_unemployment_benefit;
    int income_gov_transfers;
    int income_firm_owner_dividend;

    // Initialize this to all zeros
    int income_past[10]; // must equal average_income_lookback_period


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
    int average_income_lookback_period;







};