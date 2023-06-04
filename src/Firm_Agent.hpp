#ifndef FIRM_AGENT_HPP
#define FIRM_AGENT_HPP

class Public_Info_Board; // Forward declaration

#include "Initialization_Parameters.hpp"
#include "Loan.hpp"
#include "General_Good.hpp"
#include "Capital_Good.hpp"
#include "Consumer_Good.hpp"
#include "Job.hpp"
#include "Public_Info_Board.hpp"
#include "Random_Functions.hpp"
#include "Household_Agent.hpp"

using namespace std;
class Firm_Agent{

    public:
    // Constructors and Destructor
    Firm_Agent() {}; 
    Firm_Agent(float init_values[7]);
    virtual ~Firm_Agent();

    // Initialization methods t = 1
    virtual void Initialize_Production();

    // Main Loop Methods 
    void Depreciate_And_Revalue_Capital_Goods();
    void Check_Employees_Quitting();
    void Cancel_Expired_Contracts();
    virtual void Random_Experimentation() {};
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
    void Make_Investment_Decision();
    virtual void Produce_Goods();
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
    Household_Agent* owner;             //  Variable :Initialized

    vector<Capital_Good*> capital_goods_list;
    vector<Loan*> loan_book;
    vector<Job*> active_job_list;       // Initialized automatically
    vector<Job*> posted_job_list;       // Initialized automatically

    queue<long long> past_profits;
    queue<long long> past_sale_quantities;
    int sector_id; //0 for capital firms, 1-n for consumer goods firms

    // Production and sales figures
    long long production_current;       //  Variable :Initialized
    long long production_planned;       //  Variable :Initialized
    long long quantity_sold;            //  Variable :Initialized
    
    // Inflows
    long long revenue_sales;            //  Variable :Initialized
    float good_price_current;           //  Variable :Initialized
    long long average_profit;           //  Variable :Initialized, updated
    long long average_sale_quantity;    //  Variable :Initialized , updated
    
    // Loan Parameters
    long long short_term_funding_gap;   //  Variable :Initialized 
    long long long_term_funding_gap;    //  Variable :Initialized 
    long long loan_issuance_to_date;    //  Variable :Initialized, updated
    
    // Expenditures
    long long total_liabilities;        //  Variable :Initialized
    long long labor_wage_bill;          //  Variable :Initialized
    long long capital_costs;            //  Variable :Initialized
    long long tax_payments;             //  Variable :Initialized
    long long debt_principal_payments;  //  Variable :Initialized
    long long debt_interest_payments;   //  Variable :Initialized
    long long dividend_payments;        //  Variable :Initialized
    long long production_costs;         //  Variable :Initialized
    long long expected_wage_bill;       //  Variable :Initialized
    long long layoff_wage_savings;      //  Variable :Initialized
    long long outstanding_debt_total;   //  Variable :Initialized
    
    // Assets and fianncials 
    long long total_assets;         // Variable : Initialized
    double leverage_ratio;          // Variable: Initialized
    long long cash_on_hand;         // Variable: Initialized
    
    // Dividend characteristics
    float dividend_ratio;           // Variable: Initialized
    float dividend_ratio_optimist;  // Characteristic: Initialized
    float dividend_ratio_pessimist; // Characteristic: Initialized
    
    // Employee
    int employee_count;             // Variable: Initialized,
    int wage_offer;                 // Variable: Initialized,
    int employee_count_desired;     // Variable: Initialized,
    int n_active_job_postings;      // Variable: Initialized,
    bool need_worker;               // Variable: Initialized,
    float labor_utilization;        // Variable: Initialized,

    // Inventories
    long long inventory;                    // Variable: Initialized
    long long working_capital_inventory;    // Variable: Initialized
    float target_inv_factor;                // Characteristic: Initialized
    long long desired_inventory;            // Initialized **
    float inv_factor;                       // Variable: Initialized
    float inv_reaction_factor;              // Characteristic: Initialised, used, not logged
    float machine_utilization;              // Variable: Initialized, used, logged
    long long desired_machines;             // Variable: Initialized
    float inv_depreciation_rate;            // Initialized
    long long capital_goods_current_value;  //  Variable: Initialized , not logged

    // productivities and stuff 
    int workers_per_machine;        // Constant: Initialised,
    int output_per_machine;         // Constant: Initialised,
    float unit_good_cost;           // Constant: Initialised,
    
    // Others
    bool sentiment;                 // Variable: Initialized,
    bool bankrupt;                  // Variable: Initialized,
    bool recapitalised;             //  Variable: Initialized,
    bool is_cons_firm;              //  Variable: Initialized,
    int current_date;               //  Variable: Initialized,
    int id;                  //  Constant: Initialized,

};

#endif

