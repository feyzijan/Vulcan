#ifndef CONSUMER_FIRM_AGENT_HPP
#define CONSUMER_FIRM_AGENT_HPP



#include "Firm_Agent.hpp"
#include "Loan.hpp"
#include "Consumer_Good.hpp"
#include "Household_Agent.hpp"

//Forward Declaration
//class Consumer_Good;


class Consumer_Firm_Agent: public Firm_Agent{

    public:
    
    Consumer_Firm_Agent(int employee_count, int savings, int wage,int assets,
    float dividend_ratio_opt, float dividend_ratio_pes, int desired_inventory_factor, bool sentiment); // Constructor
    
    Consumer_Firm_Agent(Consumer_Firm_Agent&); //Copy Constructor
    ~Consumer_Firm_Agent(); // Destructor

    void Print(); // Print all variables

    // Initialize employee list
    void InitializeEmployees();

    //


    // Put up Consumer Goods for Sale




    // Check sales and update revenue and inventory
    void Check_Sales();

    // Pay liabilities and if necessary seek loans
    void Pay_Liabilities();

    int Seek_Loans();


    // Plan the production for the next time step
    void Plan_Production();

    // Update price of goods
    void Update_Price();

    // Post job offers to employ workers
    void Post_JobS();

    // Inventory check
    bool Inventory_Above_Desire();

    // Adjust Wage offer
    void Adjust_Wage_Offers();




    protected:

    Consumer_Good* goods_on_market;

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

    // Expenditures
    int total_liabilities; //Comprises of evt below
    int labor_wage_bill;
    int capital_costs;
    int tax_payments;
    int debt_principal_payments;
    int debt_interest_payments;
    int dividend_payments;

    // Assets and Liabilities
    int total_assets;
    int total_debts_liabilities;
    int total_employee_count;
    int leverage_ratio;
    int cash_on_hand;


    float dividend_ratio;
    float dividend_ratio_optimist; // characteristic
    float dividend_ratio_pessimist; // characteristic



    // List of loans taken out
    Loan* loan_book[100]; // Define this globally for

    // Employees
    Household_Agent* employee_list[100]; // Define this globally 

    int employee_count; 
    int wage_offer;
    int employee_count_desired;
    bool need_worker;
    int w_target; //Desired labor capacity utilization
    int w_current; //Current labor capacity utilization


    // Inventories
    int consumer_goods_inventory;
    int capital_goods_inventory;
    int desired_inventory_factor; // a characteristic


    // Sentiment
    bool sentiment; // pessimistic, optimistic

    // Bankruptcy
    bool bankrupt;;






};

#endif
