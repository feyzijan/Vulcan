#include "Job_Offer.hpp"
#include "Public_Info_Board.hpp"
#include <numeric>
#include "Job_Board.hpp"
#include "Capital_Firm.hpp"
#include "Firm.hpp"
#include <random>
#include "Consumer_Goods_Market.hpp"


class Household_Agent{

    public:
    Household_Agent(Public_Info_Board*  pPublic_Board, int initial_savings, int max_unemp_dur); //Constructor

    Household_Agent(Household_Agent&); //Copy constructor
    
    ~Household_Agent(); // Destructor

    // Update current total income from all sources
    void Update_Income();

    // Assign a value to the unemployment benefits
    void Assign_Unemployment_Benefits(int unemployment_benefit_amount);

    // Calculate average income over the past n_periods
    void Update_Average_Income();
    
    // Determine consumer sentiment
    void Determine_Consumer_Sentiment();

    // Get price level info
    void Get_Price_Level_Info();

    // Determine consumption budget (eq 18)
    void Determine_Consumption_Budget();
    
    // Determine goods to buy
    void Buy_Consumption_Goods();

    // Calculate new financial wealth (eq 6-7)
    void Update_Wealth();
    




    // Compare two job offers and pick the best one
    void Seek_Jobs(Job_Board* job_board);

    // Update reservation wage
    void Update_Reservation_Wage();



    //Household variables

    private:
    // Relevant pointers for interaction with other classes
    Job_Offer * current_job; 
    Firm_Agent * owned_firm; // for firm owners
    


    // Public info board
    Public_Info_Board* pPublic_Info_Board;

    // Wealth
    int wealth_financial; //W_f in equations
    int wealth_human; //W_h in equations
    
    // Consumption and Expenditure
    int expenditure_consumption;
    int tax_payment;
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

    //Public Info
    int price_level;

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