class Consumer_Firm_Agent{

    public:
    
    Consumer_Firm_Agent(); // Constructor
    Consumer_Firm_Agent(Consumer_Firm_Agent&); //Copy Constructor
    ~Consumer_Firm_Agent(); // Destructor

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




    private:

    // Production
    int current_production;
    int planned_production;

    // Expenditures
    int labor_wage_bill;
    int capital_costs;
    int tax_payments;
    int debt_payments;
    int interest_payments;
    int dividend_payments;

    //Labor
    int wage_offer;
    int count_worker_desired;
    int count_worker_actual;
    bool need_worker;

    int w_target; //Desired labor capacity utilization
    int w_current; //Current labor capacity utilization

    


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

    // price level
    float good_price;



    // Sentiment
    bool sentiment; // pessimistic, optimistic

    // Constants, characteristics
    int desired_inventory_factor; 




};

