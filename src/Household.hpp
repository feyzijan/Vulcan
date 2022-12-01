#include "Job_Offer.hpp"
#include "Public_Info.hpp"


class Household_Agent{

    public:
    Household_Agent(int initial_savings); //Constructor

    Household_Agent(Household_Agent&); //Copy constructor
    
    ~Household_Agent(); // Destructor


    /* Calculate new financial wealth (eq 6-7) */
    void Update_Wealth();

    /* Calculate average income over the past n_periods*/
    void Update_Average_Income();

    // Determine consumption budget (eq 18)
    void Determine_Consumption_Budget(int financial_wealth, int human_wealth);

    // Determine goods to buy
    void Determine_Consumption_Goods();
    
    // Determine consumer sentiment
    void Determine_Consumer_Sentiment();

    // Update reservation wage
    void Update_Reservation_Wage();

    // Compare two job offers and pick the best one
    void Compare_Job_Offers();



    //Household variables

    private:

    // Wealth
    int wealth_financial; //W_f in equations
    int wealth_human; //W_h in equations
    
    // Consumption and Expenditure
    int expenditure_consumption;
    int tax_payment;
    float consumption_propensity; //c eq(17)

    // Savings
    int new_savings;
    float saving_propensity; //s
    float saving_propensity_pessimist; //s_h
    float saving_propensity_optimist; //s_l
    int targeted_money_holding; //m_targeted
    int actual_money_holding; // m_actual

    // Income variables
    int income_current;
    int income_average; 
    int income_unemployment_benefit;
    int income_gov_transfers;
    int income_firm_owner_dividend;

    int income_past[10]; // must equal average_income_lookback_period


    // Unemployment status
    bool unemployed;
    int reservation_wage;
    int unemp_duration;
    const int unemp_duration_upper_bound;


    // Sentiment 
    bool sentiment; // pessimistic, optimistic

    // Pre-set constants
    bool business_owner; // If True will receive dividend income
    float c_f; // propensity to consume financial wealth
    float c_h; // propensity to consume human wealth
    float p_majority_op_adoption; // mu^m : probablility of adopting majority opinion
    int average_income_lookback_period;







};