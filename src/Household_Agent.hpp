#ifndef HOUSEHOLD_AGENT_HPP
#define HOUSEHOLD_AGENT_HPP

#include <numeric>
#include <random>
#include <vector>
#include <queue>
#include <sstream>
#include <string>


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
    Household_Agent(float propensities[7], int vals[3], Public_Info_Board* pPublic_Board );
    Household_Agent(Household_Agent&);
    ~Household_Agent();

    // Initialization methods
    void Set_Firm_Owner(Firm_Agent* firm_ptr);
    void Initialize_Sector_Weights(vector<Consumer_Firm_Sector*> *pConsumer_Firm_Sector_vector);

    // Main Loop methods
    void Check_Employment_Status();
    void Update_Public_Board();
    void Update_Reservation_Wage();

    void Random_Experimentation();

    void Consumption_Savings_Decisions();
    void Update_Income();
    void Update_Average_Income();
    void Update_Average_Income_T1(); // Use in t=1 only
    void Update_Savings(); // TO Implement
    void Determine_Consumer_Sentiment();
    void Determine_Consumption_Budget(); //(eq 18)

    void Buy_Consumer_Goods(); 
    void Buy_Consumer_Goods_By_Sector();
    void Seek_Jobs();
    void Seek_Better_Jobs();


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
    
    // Printing and Logging
    void Print();
    void Print_Characteristics();
    friend std::ostream& operator<<(std::ostream& os, const Household_Agent& obj);
    std::vector<std::pair<std::string, float>>* Log_Data();



    protected:
    Public_Info_Board* pPublic_Info_Board;
    Job * current_job;
    queue<int> past_incomes;
    Firm_Agent * owned_firm;
    vector<float> spending_weight_by_sector;

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
    bool sentiment; // pessimistic, optimistic

    // Pre-set constants
    bool firm_owner; // If True will receive dividend income
    float c_f; // propensity to consume financial wealth
    float c_h; // propensity to consume human wealth
    float c_excess_money; // propensity yo consume excess money balance 
    float p_majority_op_adoption; // mu^m : probablility of adopting majority opinion
    
    int current_date;
};



#endif