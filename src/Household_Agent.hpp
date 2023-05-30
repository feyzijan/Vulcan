#ifndef HOUSEHOLD_AGENT_HPP
#define HOUSEHOLD_AGENT_HPP




class Public_Info_Board;
#include "Initialization_Parameters.hpp"
#include "Public_Info_Board.hpp"
#include "Job.hpp"
#include "Random_Functions.hpp"


#define income_lookback_period 10

using namespace std;
class Household_Agent{

    public:
    // Constructors and destructor
    Household_Agent(float propensities[5], int vals[3], Public_Info_Board* pPublic_Board );

    // Initialization methods
    void Set_Firm_Owner(Firm_Agent* firm_ptr);
    void Initialize_Sector_Weights(vector<Consumer_Firm_Sector*> *pConsumer_Firm_Sector_vector);
    void Initialize_Sector_Emission_Sensitivities(vector<Consumer_Firm_Sector*> *pConsumer_Firm_Sector_vector);

    // Main Loop methods
    void Check_Employment_Status();
    void Update_Public_Board_On_Employment();
    void Update_Reservation_Wage();
    void Random_Experimentation();
    void Consumption_Savings_Decisions();
    void Update_Income();
    void Update_Average_Income();
    void Update_Average_Income_T1(); // Use in t=1 only
    void Determine_Consumer_Sentiment();
    void Determine_Consumption_Budget(); //(eq 18)
    void Buy_Consumer_Goods_By_Sector_And_Emissions();
    void Seek_Jobs();
    void Seek_Better_Jobs();

    void Notify_Of_Bankruptcy();

    //Setters
    void Set_Public_Info_Board(Public_Info_Board* ptr) {pPublic_Info_Board = ptr;}
    void Set_Job(Job* ptr) { current_job = ptr;}

    //Getters
    int Get_Wage() {return income_wage;};
    bool Get_Employment_Status() {return !unemployed;}

    Public_Info_Board* Get_Public_Board() {return pPublic_Info_Board;};
    
    // Printing and Logging
    friend std::ostream& operator<<(std::ostream& os, const Household_Agent& obj);
    vector<std::pair<string, float>>* Log_Data();

    protected:
    Public_Info_Board* pPublic_Info_Board;
    Job * current_job;
    
    // Consumption and Expenditure
    long long consumption_budget;
    float consumption_propensity; //c eq(17) - characteristic
    vector<float> spending_weight_by_sector;

    // Savings
    long long savings;
    long long savings_desired; //m_targeted
    
    // Savings constants
    float saving_propensity; //s
    float saving_propensity_optimist; //s_l  - characteristic
    float saving_propensity_pessimist; //s_h - characteristic

    // Income 
    long long income_current;
    long long income_average;
    int income_wage; 
    int income_unemployment_benefit;
    long long income_dividend;
    queue<long long> past_incomes;

    // Emissions
    long long total_emissions; 
    float emission_sensitivity_avg; 
    vector<float> emission_sensitivity_by_sector; 
    
    // Unemployment status
    bool unemployed;
    int reservation_wage;
    int unemp_duration;
    int unemp_duration_upper_bound;

    // Sentiment 
    bool sentiment; // pessimistic, optimistic

    // Firm Ownership
    bool firm_owner; 
    Firm_Agent * owned_firm;
    
    // Pre-set constants
    float c_f; // propensity to consume financial wealth
    float c_excess_money; // propensity yo consume excess money balance 
    
    int current_date;
};


/* Unused variables that have been removed
// Wealth
//long long wealth_financial; //W_f in equations 
//long long wealth_human; //W_h in equations * Unsure if this is needed
//int cash_on_hand_real_desired; // M_Total


*/


#endif