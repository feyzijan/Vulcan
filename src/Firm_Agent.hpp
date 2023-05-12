#ifndef FIRM_AGENT_HPP
#define FIRM_AGENT_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <sstream>
#include <string>

class Public_Info_Board;
#include "Loan.hpp"
#include "General_Good.hpp"
#include "Capital_Good.hpp"
#include "Consumer_Good.hpp"
#include "Job.hpp"
#include "Public_Info_Board.hpp"
#include "Random_Functions.hpp"
#include "Initialization_Parameters.hpp"


using namespace std;
class Firm_Agent{

    public:
    // Constructors and Destructor
    Firm_Agent() {}; 
    Firm_Agent(float float_vals[4], int int_vals[6]);

    // Initialization methods t = 1
    void Update_Average_Profits_T1();
    void Update_Average_Sales_T1();

    // Main Loop Methods - in order
    void Depreciate_Capital();
    void Check_Employees_Quitting();
    void Cancel_Expired_Contracts();
    void Random_Experimentation();
    void Check_Sales();
    virtual void Update_Sentiment();
    void Update_Average_Profit();
    void Update_Average_Sales();
    int Pay_Dividend() ;
    virtual void Depreciate_Good_Inventory() {};
    void Determine_New_Production();
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
    void Update_Supplier_Network() {}; // To Implement in subclasses
    void Buy_Capital_Goods();
    void Update_Leverage_Ratio();
    void Update_Loan_List(); // calledby Pay_Liabilities
    void Pay_Liabilities();

    // Bankrupcty
    bool Avoid_Bankruptcy();
    void Initiate_Bankruptcy();
    
 
    // Getters
    int Get_Short_Term_Funding_Gap() {return short_term_funding_gap;} 
    int Get_Long_Term_Funding_Gap() {return long_term_funding_gap;}
    float Get_Leverage_Ratio() {return leverage_ratio;}
    int Get_Sector_ID() {return sector_id;}
    bool Get_Bankruptcy_Status() {return bankrupt;}
    
    // Setters
    void Set_Public_Info_Board(Public_Info_Board* ptr) {pPublic_Info_Board = ptr;}
    void Set_Wage_Offer(int wage) { this->wage_offer = wage;} // used in testing

    //Print and logging methods
    void Print(); 
    void Print_Posted_Jobs();
    void Print_Active_Jobs();
    void Print_Capital_Goods();
    friend std::ostream& operator<<(std::ostream& os, const Firm_Agent& obj);
    std::vector<std::pair<std::string, float>>*  Log_Data();

    
    protected:
    Public_Info_Board* pPublic_Info_Board;
    General_Good* goods_on_market;
    Capital_Good* initial_capital_goods;
    vector<Capital_Good*> capital_goods_list;

    std::vector<Loan*> loan_book;

    queue<int> past_profits;
    queue<int> past_sale_quantities;

    int sector_id; //0 for capital firms, 1-n for consumer goods firms

    // Employees
    std::vector<Job*> active_job_list;
    std::vector<Job*> posted_job_list;


    // Production and sales figures
    int production_current; // Actual production at t
    int production_planned; // Production plan for t
    int production_past; // Production at t-1
    int quantity_sold; // Sales at t-1
    
    // Inflows
    int total_income;
    int revenue_sales;
    int new_loan_issuance;
    int subsidies;
    float good_price_current; // good price set for t
    float good_price_past; // good price at t-1
    int average_profit;  
    int average_sale_quantity; 
    
    // Loan Parameters
    int short_term_funding_gap; 
    int long_term_funding_gap; 
    
    // Expenditures
    int total_liabilities; //Comprises of evt below
    int labor_wage_bill;
    int capital_costs;
    int tax_payments;
    int debt_principal_payments;
    int debt_interest_payments;
    int dividend_payments;
    int production_costs;
    int expected_wage_bill; 
    int layoff_wage_savings; 
    int outstanding_debt_total;
    //int max_allowable_debt_total;
    
    // Assets and fianncials 
    int total_assets; // maybe this should be the same as cash in hand?
    float leverage_ratio;
    int cash_on_hand;
    
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
    int w_target; //Desired labor capacity utilization
    float labor_utilization; 
    
    // Inventories
    int inventory;
    int working_capital_inventory;
    float desired_inventory_factor; // Characteristic
    int desired_inventory; 
    float inventory_factor; 
    float inventory_reaction_factor;  
    float machine_utilization;  
    float inventory_depreciation_rate; // NEWLY ADDDED
    int desired_machines; 

    int capital_goods_current_value; // NEWLY ADDED

    // productivities and stuff 
    int workers_per_machine; // NEWLY ADDDED
    int output_per_machine; // NEWLY ADDDED
    float unit_good_cost; // NEWLY ADDDED
    float max_production_climbdown; // NEWLY ADDDED

    // CO2 Emissions
    float emission_per_unit; // NEWLY ADDDED
    int total_emissions; // NEWLY ADDDED
    
    // Others
    bool sentiment; // pessimistic, optimistic
    bool bankrupt;
    bool is_cons_firm; // type identifier, may be useful
    int current_date;


};

#endif

