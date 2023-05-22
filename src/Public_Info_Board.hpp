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
    void Update_Average_Wage_Job_Market() {average_wage_market = pJob_Market->Get_Average_Wage();};

    // Consumer Good Market
    void Send_Cons_Good_To_Market(Consumer_Good* pGood);
    pair<vector<float>, vector<int>> Buy_Consumer_Goods_By_Sector(int budget, const vector<float>& planned_expenditure_by_sector);
    pair<vector<float>, vector<int>> Buy_Consumer_Goods_By_Sector_And_Emission(int budget, const vector<float>& planned_expenditure_by_sector, const vector<float>& emission_sensitives_array);


    // Capital Good Market
    int*  Buy_Capital_Goods(int q_desired);
    void Send_Cap_Good_To_Market(Capital_Good* pGood);
    int Get_Cost_For_Desired_Cap_Goods(int q_desired);
    
    // Update Member Variables

    // Policy Rules
    void Update_Unemployment_Benefits(); // TO Implement later

    // Inflation, price level, interest rate
    void Update_Consumer_Price_Level();
    void Update_Capital_Price_Level();
    void Initialize_Price_Levels();
    void Update_Interest_Rate();

    // Distributing Emission allowances
    unsigned long int Distribute_Initial_Emission_Allowances(int employee_count, int sector_id);
    unsigned long int Distribute_Emission_Allowances(int sale_quantity, int sector_id);
    int Buy_Emission_Offsets(int quantity, int sector_id) { 
        offsets_sold_by_sectors[sector_id-1] += quantity;
        return quantity * emission_offset_price;} // Returns cost, allowances always available

    // Update emission allowance price and amount
    void Update_Emission_Allowance_Price() { emission_offset_price *= (1.0 + emission_unit_price_change); }
    void Update_Emission_Allowance_Amount() { 
        std::transform(emission_allowances_by_sector.begin(), emission_allowances_by_sector.end(), emission_allowances_by_sector.begin(), [=](unsigned long int value) {
        float result = static_cast<float>(value) * (1.0f + emission_total_allowance_change);
        return static_cast<unsigned long int>(std::round(result));
    });}

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
    float Get_Consumer_Inflation() {return cons_inflation_current;}
    float Get_Capital_Inflation() {return cap_inflation_current;}
    int Get_Unemployment_Benefit() { return public_unemployment_benefit;}
    float Get_Cons_Price_Level() { return cons_price_level_current;}
    float Get_Cons_Sector_Price_Level(int sector_id) { return consumer_sectors_price_levels[sector_id]; }
    float Get_Cap_Price_Level() { return cap_price_level_current;}

    float Get_Capital_Good_Price_Level(){return cap_price_level_current;}
    float Get_Consumer_Good_Price_Level() {return cons_price_level_current;}

    float Get_Average_Wage_Market() { return average_wage_market;}
    float Get_Average_Wage_Employed() {return average_wage_employed;}
    Job_Market* Get_Job_Market_Ptr() { return pJob_Market;}
    int Get_Current_Date() { return current_date;}
    int Get_Machine_Orders() { return machine_orders;}
    int Get_Machine_Spending() { return machine_spending;}
    int Get_Consumer_Orders() { return consumer_orders;}
    int Get_Consumer_Spending() { return consumer_spending;}
    int Get_Consumption_Budget() { return consumption_budgets;}
    int Get_Consumer_Goods_Production() { return cons_goods_production_total;}
    int Get_Capital_Goods_Production() { return cap_goods_production_total;}
    int Get_Consumer_Goods_Production_Planned() { return cons_goods_planned_production_total;}
    int Get_Capital_Goods_Production_Planned() { return cap_goods_production_planned_total;}
    int Get_Employed_Workers() { return n_employed_workers;}
    int Get_Unemployed_Workers() { return n_unemployed_workers;}
    int Get_Employee_Demand() { return new_employee_demand;}
    int Get_Employee_Firings() { return employee_firings;}
    int Get_Employee_Hires() { return employee_hires;}
    int Get_Contract_Expiries() { return contract_expiries;}
    int Get_New_Job_Postings() { return new_job_postings;}
    int Get_Removed_Job_Postings() { return removed_job_postings;}
    int Get_Minimum_Wage() { return minimum_wage;}
    float Get_Unit_Emissions_by_Sector(int sector_id) {return average_unit_emission_by_sector[sector_id-1];} 
    float Get_Emission_Offset_Price() {return emission_offset_price;}

    // Setters
    void Set_Job_Market(Job_Market* ptr) { pJob_Market = ptr;}
    void Set_Consumer_Goods_Market(Consumer_Goods_Market* ptr) { pConsumer_Goods_Market = ptr;}
    void Set_Capital_Goods_Market(Capital_Goods_Market* ptr) { pCapital_Goods_Market = ptr;}
    void Set_Bank(Bank_Agent* ptr) { pBank = ptr;}
    void Initialize_Consumer_Sectors(vector<Consumer_Firm_Sector*> *pConsumer_Firm_Sector_vector, int num_sectors);

    //-----------Update global aggregate variables ----------------
    // Sentiment sums
    void Update_Household_sentiment_sum(bool amount) { household_sentiment_sum += amount; }
    void Update_Cons_firm_sentiment_sum(bool amount) { cons_firm_sentiment_sum += amount; }
    void Update_Cap_firm_sentiment_sum(bool amount) { cap_firm_sentiment_sum += amount; }
    // Wages and Income
    void Update_Household_Wage(int amount) { household_wage_sum += amount; }
    void Update_Household_Dividends(int amount) {household_dividends_sum += amount; }
    void Update_Household_Total_Income(int amount) { household_total_income_sum += amount; }
    // Capital Goods
    void Update_Machine_Orders(int amount) { machine_orders += amount; }
    void Update_Machine_Orders_Planned(int amount) { machine_orders_planned += amount; }
    void Update_Machine_Spending(int amount) { machine_spending += amount; }
    void Update_Machine_Spending_Planned(int amount) { machine_spending_planned += amount; }
    void Update_Capital_Goods_Production(int amount) { cap_goods_production_total += amount;}
    void Update_Capital_Goods_Production_Planned(int amount) { cap_goods_production_planned_total += amount; }
    void Update_Capital_Goods_Sale_Quantities(int amount) { cap_good_sale_quantity_total += amount;}

    //-- Consumer Goods and Consumption
    // Updates by Consumer Firms
    void Update_Consumer_Orders(int amount) { consumer_orders += amount; }
    void Update_Consumer_Spending(int amount) { consumer_spending += amount; }
    void Update_Consumption_Budgets(int amount) { consumption_budgets += amount; }
    void Update_Consumer_Goods_Production(int sector_id, int amount) { 
        actual_production_by_sector[sector_id-1] += amount;
        cons_goods_production_total += amount; }
    void Update_Consumer_Goods_Production_Planned(int sector_id, int amount) { 
        planned_production_by_sector[sector_id-1] += amount; 
        cons_goods_planned_production_total += amount; }
    void Update_Consumer_Goods_Sale_Quantities(int sector_id, int amount){ 
        quantity_sold_by_sector[sector_id-1] += amount; 
        cons_goods_sale_quantity_total += amount ;}
    void Update_Consumer_Goods_Inventory(int sector_id, int amount){
        inventory_by_sector[sector_id-1] += amount;}
    // Updates by Households
    void Update_Planned_Consumer_Spending_by_Sector( const vector<float>& planned_spending);
    void Update_Actual_Consumer_Spending_by_Sector(  const vector<float>& actual_spending );

    // Labor Figures
    void Update_Employed_Worker_Count(int amount) { n_employed_workers += amount; }
    void Update_Unemployed_Worker_Count(int amount) { n_unemployed_workers += amount; }
    void Update_Employee_Demand(int amount) { new_employee_demand += amount; }
    void Update_Employee_Firings(int amount) { employee_firings += amount; }
    void Update_Employee_Hires(int amount) { employee_hires += amount; }
    void Update_Contract_Expiries(int amount) { contract_expiries += amount; }
    void Update_New_Job_Postings(int amount) { new_job_postings += amount; }
    void Update_Removed_Job_Postings(int amount) { removed_job_postings += amount; }
    void Update_Employees_Quitting() { n_employees_quitting += 1; }


    // ---- Calculate Global Aggregate Variables ----
    // Labor Figures
    void Calculate_Unemployment_Rate() { unemployment_rate = float(n_unemployed_workers)/float(n_households); }
    void Calculate_Average_Wage_Employed() { average_wage_employed = float(household_wage_sum)/float(n_employed_workers-n_firms); }
    void Calculate_Average_Dividend_Income() { average_dividend_income = float(household_dividends_sum)/float(n_firms); }
    void Calculate_Average_Total_Income() { average_total_income = float(household_total_income_sum)/float(n_households); }
    // Sentiments
    void Calculate_Household_Sentiment_Percentage() { household_sentiment_percentage = float(household_sentiment_sum)/ float(n_households); }
    void Calculate_Cons_Firm_Sentiment_Percentage() { cons_firm_sentiment_percentage = float(cons_firm_sentiment_sum)/float(n_consumer_firms); }
    void Calculate_Cap_Firm_Sentiment_Percentage() { cap_firm_sentiment_percentage = float(cap_firm_sentiment_sum)/float(n_capital_firms); }
    // Consumer Market
    void Calculate_Consumer_Demand_Shortfall_by_Sector();
    // Unit emisisons
    void Calculate_Average_Unit_Emissions_by_Sector();

    // Printing and Debugging
    friend std::ostream& operator<<(std::ostream& os, const Public_Info_Board& obj); // String stream operator
    vector<pair<string, float>>*  Log_Data();     // Data Logging

    protected:
    Job_Market* pJob_Market;
    Bank_Agent* pBank;
    Consumer_Goods_Market* pConsumer_Goods_Market;
    Capital_Goods_Market* pCapital_Goods_Market;

    // General price level
    float cons_price_level_current;
    float cons_price_level_previous;
    float cap_price_level_current;
    float cap_price_level_previous;
    vector<float> consumer_sector_weights;
    vector<float> consumer_sectors_price_levels;

    // Emission Allowances
    vector<unsigned long int> emission_allowances_by_sector; // NEWLY ADDED
    vector<unsigned long int> total_emissions_by_sector; // NEWLY ADDED
    unsigned long int total_emission_allowance; // newly added 
    float emission_offset_price; // newly added

    vector<float> average_unit_emission_by_sector;
    vector<int> offsets_sold_by_sectors; // NEWLY ADDED


    // Income and wage figures
    float average_wage_market; // Average wage in the job market
    float average_wage_employed; // Average active employee wage
    float average_dividend_income; // Average dividend in the market
    float average_total_income; // Average income of all households (wage/unemp benefit/dividend)

    int household_wage_sum;  // Sum of wages of households
    int household_dividends_sum; // Sum of dividends of households
    int household_total_income_sum;

    // Inflation and interest rate
    float r_rate; 
    float cons_inflation_current; 
    float cap_inflation_current;


    // Global aggregate variables

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
    int machine_spending_planned; // NEWLY ADDED

    // Consumer expenditure
    int consumer_orders;
    int consumer_spending;
    int consumption_budgets;

    vector<float> planned_cons_spending_by_sector;
    vector<float> actual_cons_spending_by_sector;
    vector<float> cons_demand_shortfall_by_sector; 

    int sector_count;
    
    // Production
    int cons_goods_production_total;
    int cap_goods_production_total;
    int cons_goods_planned_production_total;
    int cap_goods_production_planned_total;
    int cap_good_sale_quantity_total; // NEWLY ADDED
    int cons_goods_sale_quantity_total; // NEWLY ADDED

    vector<int> planned_production_by_sector;
    vector<int> actual_production_by_sector;
    vector<int> inventory_by_sector;
    vector<int> quantity_sold_by_sector; // NEWLY ADDED

    // Employment
    int n_employed_workers;
    int n_unemployed_workers;
    float unemployment_rate;
    int n_employees_quitting;

    int employee_hires;
    int new_employee_demand;

    int employee_firings;
    int contract_expiries;

    int new_job_postings;
    int removed_job_postings;

    // Bankruptcy figures
    int n_bankrupt_cap_firms; // NEWLY ADDED
    int n_bankrupt_cons_firms; // NEWLY ADDED


    // Unemployment benefits
    int public_unemployment_benefit;

    // Minimum wage
    int minimum_wage;

    //timestep
    int time_step; // timestep in days
    //current date
    int current_date;

};
#endif