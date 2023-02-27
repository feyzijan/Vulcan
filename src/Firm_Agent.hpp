#ifndef FIRM_AGENT_HPP
#define FIRM_AGENT_HPP


#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>


class Public_Info_Board;
#include "Loan.hpp"
#include "General_Good.hpp"
#include "Capital_Good.hpp"
#include "Consumer_Good.hpp"
#include "Job.hpp"
#include "Public_Info_Board.hpp"
#include "Random_Functions.hpp"
#include "Initialization_Parameters.hpp"


class Firm_Agent{

    public:
    // Constructors and Destructor
    Firm_Agent() {}; 
    Firm_Agent(float float_vals[4], int int_vals[6]);
    Firm_Agent(Firm_Agent&){}; 
    ~Firm_Agent(){}; 

    //Print methods
    void Print(); 
    void Print_Posted_Jobs();
    void Print_Active_Jobs();
    void Print_Capital_Goods();

    // Initialization methods t = 0
    

    // Initialization methods t = 1
    void Update_Average_Profits_T1();
    void Update_Average_Sales_T1();


    // Main Loop Methods - in order
    void Depreciate_Capital();
    //void Depreciate_Good_Inventory();
    void Cancel_Expired_Contracts();
    void Random_Experimentation();
    void Check_Sales();
    virtual void Update_Sentiment();
    void Update_Average_Profit();
    void Update_Average_Sales();
    int Pay_Dividends();
    void Determine_New_Production();
    void Adjust_Wage_Offers();
    void Determine_Labor_Need();
    void Compute_Expected_Wage_Bill();
    void Seek_Short_Term_Loan();
    void Layoff_Excess_Workers();
    void Remove_Job_Postings(); // TO implemeent
    void Post_Jobs();
    void Check_For_New_Employees();
    //void Commence_Production(); // Implemented by subclasses
    void Update_Supplier_Networks(); // TO Implement
    void Make_Investment_Decision(); // Complete
    void Seek_Long_Term_Loan();
    void Buy_Capital_Goods(); 
    //virtual void Produce_Goods(); // Implemented by subclasses




    // Pay liabilities 
    void Pay_Liabilities();
    // Seek Loans if needed to pay liabilities
    int Seek_Loans(int shortfall); // remove later
    // Seek long term loan
    
 

    // Getters
    std::vector<float>* Get_All_Params();
    int Get_Short_Term_Funding_Gap() {return short_term_funding_gap;} 
    int Get_Long_Term_Funding_Gap() {return long_term_funding_gap;}
    float Get_Leverage_Ratio() {return leverage_ratio;}
    

    // Setters
    void Set_Public_Info_Board(Public_Info_Board* ptr) {pPublic_Info_Board = ptr;}
    void Set_Wage_Offer(int wage) { this->wage_offer = wage;} // used in testing


    
    protected:
    Public_Info_Board* pPublic_Info_Board;
    General_Good* goods_on_market;
    Capital_Good* initial_capital_goods;
    vector<Capital_Good*> capital_goods_list;

    std::vector<Loan*> loan_book;

    queue<int> past_profits;
    queue<int> past_sale_quantities;

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

    int average_profit; // NEWLY ADDED - 
    int average_sale_quantity; //NEWLY ADDED -
  
    // Loan Parameters
    int short_term_funding_gap; // NEWLY ADDED - 
    int long_term_funding_gap; // NEWLY ADDED - 

    // Expenditures
    int total_liabilities; //Comprises of evt below
    int labor_wage_bill;
    int capital_costs;
    int tax_payments;
    int debt_principal_payments;
    int debt_interest_payments;
    int dividend_payments;
    int production_costs;

    int expected_wage_bill; // NEWLY ADDED- 
    int layoff_wage_savings; // NEWLY ADDED-
    int expected_wage_bill_shortfall; // NEWLY ADDED- 
    int expected_long_term_shortfall; // NEWLY ADDDED- 

    // Assets and fianncials 
    int total_assets; // maybe this should be the same as cash in hand?
    int leverage_ratio;
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

    float labor_utilization; // NEWLY ADDDED

    
    // Inventories
    int inventory;
    int working_capital_inventory;
    float desired_inventory_factor; // a characteristic
    int desired_inventory; // NEWLY ADDED 
    float inventory_factor; 

    float inventory_reaction_factor;  // NEWLY ADDDED

    float machine_utilization;  // NEWLY ADDDED
    int desired_machines; // NEWLY ADDDED

    // Sentiment
    bool sentiment; // pessimistic, optimistic

    // Bankruptcy
    bool bankrupt;;

    // type identifier, may be useful
    bool is_cons_firm;

};

#endif

