#ifndef PUBLIC_INFO_BOARD_HPP
#define PUBLIC_INFO_BOARD_HPP


class Job_Market;
class Bank_Agent;
class Consumer_Goods_Market;

#include "Job_Market.hpp"
#include "Job.hpp"
#include "Consumer_Goods_Market.hpp"
#include "Capital_Goods_Market.hpp"
#include "Bank_Agent.hpp"
#include "Loan.hpp"

//#include "Firm_Agent.hpp"
#include "Initialization_Parameters.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <utility>

using namespace std;

class Public_Info_Board{

    public:
    // Constructors and destructor
    Public_Info_Board(); 
    Public_Info_Board(Public_Info_Board&); 
    ~Public_Info_Board(); 

    // Job Market 
    Job* Get_Top_Job();
    Job_Market* Get_Job_List(); // not implemented/needed yet
    void Remove_Top_Job_Offer();
    void Post_Job_To_Market(Job * pJob_Offer);
    void Take_Job(Job* pJob_Offer); // Notify employer and remove job from market
    void Sort_Job_Market();
    void Update_Average_Wage() {average_wage = pJob_Market->Get_Average_Wage();};
    
    // Consumer Good Market
    void Send_Cons_Good_To_Market(Consumer_Good* pGood);
    std::pair<int, int> Buy_Consumer_Goods(int budget);

    // Capital Good Market
    std::vector<Capital_Good*>*  Buy_Capital_Goods(int q_desired);
    void Send_Cap_Good_To_Market(Capital_Good* pGood);
    int Get_Cost_For_Desired_Cap_Goods(int q_desired);
    
    // Update Member Variables

    // Inflation and price level
    float Calculate_Inflation();
    float Calculate_Manufacturer_Inflation();
    void Initialize_Price_Level();

    // Loan issuance
    Loan* Seek_Short_Term_Loan(Firm_Agent* pFirm);
    Loan* Seek_Long_Term_Loan(Firm_Agent* pFirm);

    // Global Data
    void Reset_Global_Data();
    
    // Gathering and reading public sentiment 
    float Get_Household_Sentiment() {return household_sentiment_percentage;}
    float Get_Cons_Firm_Sentiment() {return cons_firm_sentiment_percentage;}    
    float Get_Cap_Firm_Sentiment() {return cap_firm_sentiment_percentage;}
    float Get_Unemployment_Rate() { return unemployment_rate;}

    // Getters
    int Get_Unemployment_Benefit() { return public_unemployment_benefit;}
    int Get_Price_Level() { return price_level_current;}
    float Get_Capital_Good_Price_Level();
    float Get_Consumer_Good_Price_Level();
    float Get_Average_Wage() { return average_wage;}
    Job_Market* Get_Job_Market_Ptr() { return pJob_Market;}
    int Get_Current_Date() { return current_date;}
    int Get_Machine_Orders() { return machine_orders;}
    int Get_Machine_Spending() { return machine_spending;}
    int Get_Consumer_Orders() { return consumer_orders;}
    int Get_Consumer_Spending() { return consumer_spending;}
    int Get_Consumption_Budget() { return consumption_budgets;}
    int Get_Consumer_Goods_Production() { return consumer_goods_production;}
    int Get_Capital_Goods_Production() { return capital_goods_production;}
    int Get_Consumer_Goods_Production_Planned() { return consumer_goods_production_planned;}
    int Get_Capital_Goods_Production_Planned() { return capital_goods_production_planned;}
    int Get_Employed_Workers() { return n_employed_workers;}
    int Get_Unemployed_Workers() { return n_unemployed_workers;}
    int Get_Employee_Demand() { return new_employee_demand;}
    int Get_Employee_Firings() { return employee_firings;}
    int Get_Employee_Hires() { return employee_hires;}
    int Get_Contract_Expiries() { return contract_expiries;}
    int Get_New_Job_Postings() { return new_job_postings;}
    int Get_Removed_Job_Postings() { return removed_job_postings;}

    // Setters
    void Set_Job_Market(Job_Market* ptr) { pJob_Market = ptr;}
    void Set_Consumer_Goods_Market(Consumer_Goods_Market* ptr) { pConsumer_Goods_Market = ptr;}
    void Set_Capital_Goods_Market(Capital_Goods_Market* ptr) { pCapital_Goods_Market = ptr;}
    void Set_Bank(Bank_Agent* ptr) { pBank = ptr;}
    

    // Update global aggregate variables
    void Update_Household_sentiment_sum(int amount) { household_sentiment_sum += amount; }
    void Update_Cons_firm_sentiment_sum(int amount) { cons_firm_sentiment_sum += amount; }
    void Update_Cap_firm_sentiment_sum(int amount) { cap_firm_sentiment_sum += amount; }

    void Update_Machine_orders(int amount) { machine_orders += amount; }
    void Update_Machine_spending(int amount) { machine_spending += amount; }
    void Update_Consumer_orders(int amount) { consumer_orders += amount; }
    void Update_Consumer_spending(int amount) { consumer_spending += amount; }
    void Update_Consumption_Budgets(int amount) { consumption_budgets += amount; }
    
    void Update_Consumer_goods_production(int amount) { consumer_goods_production += amount; }
    void Update_Capital_goods_production(int amount) { capital_goods_production += amount; }
    void Update_Consumer_goods_production_planned(int amount) { consumer_goods_production_planned += amount; }
    void Update_Capital_goods_production_planned(int amount) { capital_goods_production_planned += amount; }
    
    void Update_Employed_Workers(int amount) { n_employed_workers += amount; }
    void Update_Unemployed_Workers(int amount) { n_unemployed_workers += amount; }

    void Update_Employee_Demand(int amount) { new_employee_demand += amount; }
    void Update_Employee_Firings(int amount) { employee_firings += amount; }
    void Update_Employee_Hires(int amount) { employee_hires += amount; }
    void Update_Contract_Expiries(int amount) { contract_expiries += amount; }
    void Update_New_Job_Postings(int amount) { new_job_postings += amount; }
    void Update_Removed_Job_Postings(int amount) { removed_job_postings += amount; }

    void Update_Unemployment_Rate() { unemployment_rate = float(n_unemployed_workers)/float(n_households); }
    void Update_Household_Sentiment_Percentage() { household_sentiment_percentage = household_sentiment_sum/n_households; }
    void Update_Cons_Firm_Sentiment_Percentage() { cons_firm_sentiment_percentage = cons_firm_sentiment_sum/n_consumer_firms; }
    void Update_Cap_Firm_Sentiment_Percentage() { cap_firm_sentiment_percentage = cap_firm_sentiment_sum/n_capital_firms; }


    // Printing and Debugging
    void Print() const;
    void Print_Labor_Market() const;
    // String stream operator
    friend std::ostream& operator<<(std::ostream& os, const Public_Info_Board& obj);
    // Data Logging
    std::vector<std::pair<std::string, float>>*  Log_Data();

    protected:
    Job_Market* pJob_Market;
    Bank_Agent* pBank;
    Consumer_Goods_Market* pConsumer_Goods_Market;
    Capital_Goods_Market* pCapital_Goods_Market;

    // General price level
    float price_level_current;
    float price_level_previous;
    float cap_price_level_current;
    float cap_price_level_previous;
    float average_wage; // Average wage in economy

    // Inflation and interest rate
    float r_rate; 
    float inflation_current; 


    // Global aggregate varaibles

    // Sentiments
    int household_sentiment_sum; // Sum of household sentiment: +1 for each positive
    float household_sentiment_percentage; // Percentage of households who are optimist
    int cons_firm_sentiment_sum; // Sum of firm sentiment: +1 for each positive
    float cons_firm_sentiment_percentage; // Percentage of firms who are optimist
    int cap_firm_sentiment_sum; // Sum of firm sentiment: +1 for each positive
    float cap_firm_sentiment_percentage; // Percentage of firms who are optimist

    // Capital expenditure
    int machine_orders;
    int machine_orders_planned;
    int machine_spending;

    // Consumer expenditure
    int consumer_orders;
    int consumer_spending;
    int consumption_budgets;
    
    // Production
    int consumer_goods_production;
    int capital_goods_production;
    int consumer_goods_production_planned;
    int capital_goods_production_planned;

    // Employment
    int n_employed_workers;
    int n_unemployed_workers;
    float unemployment_rate;

    int employee_hires;
    int new_employee_demand;

    int employee_firings;
    int contract_expiries;

    int new_job_postings;
    int removed_job_postings;


    // Unemployment benefits
    int public_unemployment_benefit;

    //timestep
    int time_step; // timestep in days
    //current date
    int current_date;

};
#endif