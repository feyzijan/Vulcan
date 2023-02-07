#ifndef HOUSEHOLD_AGENT_HPP
#define HOUSEHOLD_AGENT_HPP

#include <numeric>
#include <random>
#include <vector>
#include <queue>

class Public_Info_Board;
#include "Public_Info_Board.hpp"
#include "Job.hpp"
#include "Random_Functions.hpp"
#include "Initialization_Parameters.hpp"

#define income_lookback_period 10

using namespace std;
class Household_Agent{

    public:
    // Constructors and destructor
    Household_Agent(float propensities[7], int unemployment_tolerance, int wealth, Public_Info_Board* pPublic_Board );
    Household_Agent(Household_Agent&);
    ~Household_Agent();

    // Main Loop methods
    void Update_Reservation_Wage();
    void Consumption_Savings_Decisions();
    void Update_Income();
    void Update_Average_Income();
    void Update_Average_Income_T1(); // Use in t=1 only
    void Update_Savings(); // TO Implement
    void Determine_Consumer_Sentiment();
    void Determine_Consumption_Budget(); //(eq 18)
    void Buy_Consumer_Goods(); 
    void Seek_Jobs();
    
    // Printing and Debugging
    void Print();
    void Print_Characteristics();

    //Setters
    void Set_Public_Info_Board(Public_Info_Board* ptr) {pPublic_Info_Board = ptr;}
    void Set_Job(Job* ptr) { current_job = ptr;}

    //Getters
    int Get_Wage() {return income_wage;};
    bool Get_Employment_Status() {return !unemployed;}
    float Get_C_f() {return c_f;}
    float Get_C_h() {return c_h;}
    Public_Info_Board* Get_Public_Board() {return pPublic_Info_Board;};
    std::vector<float>* Get_All_Params();

    protected:
    Public_Info_Board* pPublic_Info_Board;
    Job * current_job;
    queue<int> past_incomes;

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
    float saving_propensity_optimist; //s_l  - characteristic
    float saving_propensity_pessimist; //s_h - characteristic

    // Income 
    int income_current;
    int income_average;
    int income_wage; 
    int income_unemployment_benefit;
    int income_gov_transfers;
    int income_firm_owner_dividend;

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


//----- Initialization Functions
void Initialize_Households(Household_Agent * Household_array, Public_Info_Board* pPublic_Board, int size);
void Initialize_Household_Jobs(Household_Agent * Household_array,  int size);


#endif