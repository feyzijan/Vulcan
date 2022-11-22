class Consumer_Firm_Agent{

    public:
    
    Consumer_Firm_Agent(); // Constructor
    Consumer_Firm_Agent(Consumer_Firm_Agent&); //Copy Constructor
    ~Consumer_Firm_Agent(); // Destructor


    private:
    //----Outflows
    int labor_wage_bill;
    int capital_costs;
    int tax_payments;
    int debt_payments;
    int interest_payments;
    int dividend_payments;
    //int research_spending;

    //----Inflows
    int consumer_good_revenue;
    int consumer_goods_sold;
    int new_loans;
    int subsidies;
    //int total_carbon_emissions;

    //----State variables
    int consumer_goods_inventory;
    //int carbon_intensity_of_production;
    int capital_goods_inventory;
    int total_assets;
    int total_debts_liabilities;
    int total_employee_count;
    int leverage_ratio;
    //int research_spending_ratio;



};

