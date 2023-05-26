#ifndef FIRM_AGENT_HPP
#define FIRM_AGENT_HPP

class Public_Info_Board; // Forward declaration

#include "Loan.hpp"
#include "General_Good.hpp"
#include "Capital_Good.hpp"
#include "Consumer_Good.hpp"
#include "Job.hpp"
#include "Public_Info_Board.hpp"
#include "Random_Functions.hpp"
#include "Household_Agent.hpp"
#include "Initialization_Parameters.hpp"

using namespace std;
class Firm_Agent{

    public:
    // Constructors and Destructor
    Firm_Agent() {}; 
    Firm_Agent(float float_vals[2], int int_vals[6]);
    virtual ~Firm_Agent();

    // Initialization methods t = 1
    void Update_Average_Profits_T1();
    void Update_Average_Sales_T1();

    // Main Loop Methods 
    void Depreciate_And_Revalue_Capital_Goods();
    void Check_Employees_Quitting();
    void Cancel_Expired_Contracts();
    virtual void Random_Experimentation();
    virtual void Check_Sales();
    virtual void Update_Sentiment();
    void Update_Average_Profit();
    void Update_Average_Sales();
    long long Get_Dividend() ;
    virtual void Depreciate_Good_Inventory() {};
    virtual void Determine_New_Production() {};
    void Adjust_Wage_Offers();
    void Determine_Labor_Need();
    void Remove_Job_Postings(); 
    void Layoff_Excess_Workers();
    void Post_Jobs();
    void Check_For_New_Employees();
    void Make_Investment_Decision(); // Complete
    virtual void Produce_Goods();
    virtual void Send_Goods_To_Market() {}; 
    virtual void Update_Goods_On_Market() {};
    void Seek_Short_Term_Loan();
    void Seek_Long_Term_Loan();
    void Buy_Capital_Goods();
    void Update_Leverage_Ratio();
    void Update_Loan_List();
    void Pay_Liabilities();
    bool Avoid_Bankruptcy();
    void Notify_Owner_Of_Bankruptcy();
 
    // Getters
    long long Get_Short_Term_Funding_Gap() {return short_term_funding_gap;} 
    long long Get_Long_Term_Funding_Gap() {return long_term_funding_gap;}
    double Get_Leverage_Ratio() {return leverage_ratio;}
    int Get_Sector_ID() {return sector_id;}
    bool Get_Bankruptcy_Status() {return bankrupt;}
    int Get_Employee_Count() {return employee_count;}
    bool Get_Cons_Firm_Status() {return is_cons_firm;}
    virtual float Get_Unit_Emissions() {return 0;} 
    virtual long long Get_Total_Emissions() {return 0;}

    // Setters
    void Set_Public_Info_Board(Public_Info_Board* ptr) {pPublic_Info_Board = ptr;}
    void Set_Wage_Offer(int wage) { this->wage_offer = wage;} // used in testing
    void Set_Owner(Household_Agent* ptr) {owner = ptr;}

    //Print and logging methods
    friend std::ostream& operator<<(std::ostream& os, const Firm_Agent& obj);
    vector<std::pair<string, float>>*  Log_Data();

    
    protected:
    Public_Info_Board* pPublic_Info_Board;
    General_Good* goods_on_market;
    Capital_Good* initial_capital_goods;
    vector<Capital_Good*> capital_goods_list;

    vector<Loan*> loan_book;

    queue<int> past_profits;
    queue<int> past_sale_quantities;

    int sector_id; //0 for capital firms, 1-n for consumer goods firms

    // Employees
    vector<Job*> active_job_list;
    vector<Job*> posted_job_list;

    // Owner
    Household_Agent* owner;


    // Production and sales figures
    long long production_current; // Actual production at t
    long long production_planned; // Production plan for t
    long long quantity_sold; // Sales at t-1
    
    // Inflows
    long long revenue_sales;
    float good_price_current; // good price set for t
    long long average_profit;  
    long long average_sale_quantity; 
    
    // Loan Parameters
    long long short_term_funding_gap; 
    long long long_term_funding_gap; 
    long long loan_issuance_to_date;
    
    // Expenditures
    long long total_liabilities; //Comprises of evt below
    long long labor_wage_bill;
    long long capital_costs;
    long long tax_payments;
    long long debt_principal_payments;
    long long debt_interest_payments;
    long long dividend_payments;
    long long production_costs;
    long long expected_wage_bill; 
    long long layoff_wage_savings; 
    long long outstanding_debt_total;
    
    // Assets and fianncials 
    long long total_assets; // maybe this should be the same as cash in hand?
    double leverage_ratio;
    long long cash_on_hand;
    
    // Dividend characteristics
    float dividend_ratio;
    float dividend_ratio_optimist; // characteristic
    float dividend_ratio_pessimist; // characteristic
    
    // Employee
    int employee_count; 
    int wage_offer;
    int employee_count_desired;
    int n_active_job_postings;
    bool need_worker;
    int w_target; //Desired labor capacity utilization - unused
    float labor_utilization; 
    
    // Inventories
    long long inventory;
    long long working_capital_inventory;
    float target_inv_factor; // Characteristic
    long long desired_inventory; 
    float inv_factor; 
    float inv_reaction_factor;  
    float machine_utilization;  
    float inv_depreciation_rate; // NEWLY ADDDED
    long long desired_machines; 

    long long capital_goods_current_value; // NEWLY ADDED

    // productivities and stuff 
    int workers_per_machine; // NEWLY ADDDED
    int output_per_machine; // NEWLY ADDDED
    float unit_good_cost; // NEWLY ADDDED
    float max_production_climbdown; // NEWLY ADDDED

    
    // Others
    bool sentiment; // pessimistic, optimistic
    bool bankrupt;
    bool recapitalised;
    bool is_cons_firm; // type identifier, may be useful
    int current_date;

};

#endif

