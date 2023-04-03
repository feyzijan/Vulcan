
#include "Public_Info_Board.hpp"


//-------- Constructors and destructor

Public_Info_Board::Public_Info_Board(){
    // Genereal price level
    cons_price_level_current = 0;
    cons_price_level_previous = 0;

    // Capital good price level
    cap_price_level_current = 0;
    cap_price_level_previous = 0;

    // Income figures
    average_wage_market = 0.0;
    average_wage_employed = 0.0;
    average_dividend_income = 0.0;
    average_total_income = 0.0,
    household_wage_sum = 0;
    household_dividends_sum = 0;
    household_total_income_sum = 0;


    // Inflation and interest rates
    r_rate = 0;
    cons_inflation_current = 0;

    // Global aggregate variables

    // Sentiments
    household_sentiment_sum = 0;
    household_sentiment_percentage = 0.0;
    cons_firm_sentiment_sum = 0;
    cons_firm_sentiment_percentage = 0.0;
    cap_firm_sentiment_sum = 0;
    cap_firm_sentiment_percentage = 0.0;

    // Capital expenditure
    machine_orders = 0;
    machine_spending = 0;
    machine_orders_planned = 0;
    // Consumer expenditure
    consumer_orders = 0;
    consumer_spending = 0;
    consumption_budgets = 0;
    sector_count = 0;

    // Production
    consumer_goods_production = 0;
    capital_goods_production = 0;
    consumer_goods_production_planned = 0;
    capital_goods_production_planned = 0;
    // Employment
    n_employed_workers = 0;
    n_unemployed_workers = 0;
    new_employee_demand = 0;
    employee_firings = 0;
    employee_hires = 0;
    unemployment_rate = 0.0;
    contract_expiries = 0;
    new_job_postings = 0;
    removed_job_postings = 0;
    n_employees_quitting = 0;

    // not using this as of yet
    public_unemployment_benefit = init_unemployment_benefit;
    minimum_wage = init_minimum_wage;

    // timestep - not using these for now
    time_step = 0;
    current_date = 0;
}


Public_Info_Board::~Public_Info_Board(){}
Public_Info_Board::Public_Info_Board(Public_Info_Board&){}
//------------------------------------
// Dealing with sectors

/* Set the number of sectors, initialize spending by sector vectors with 0
*/
void Public_Info_Board::Set_Consumer_Sectors(vector<Consumer_Firm_Sector*> *pConsumer_Firm_Sector_vector, int num_sectors){
    sector_count = num_sectors;
    actual_spending_by_sector = vector<int>(sector_count, 0);
    planned_spending_by_sector = vector<int>(sector_count, 0);
    // Loop through each sector in the consumer_firm_sector vector and add the sector weighing to the consumer_sector_weighing_vector
    for (int i = 0; i < sector_count; i++){
        consumer_sector_weights.push_back(pConsumer_Firm_Sector_vector->at(i)->consumption_weighing);
    }
}

/*
*/
void Public_Info_Board::Update_Planned_Consumer_Spending_by_Sector( const vector<int>& planned_spending){
    // loop through the planned_spending vector and add to the planned_spending_by_sector vector
    planned_spending_by_sector.clear();
    for (int i = 0; i < sector_count; i++){
        int temp = planned_spending[i];
        planned_spending_by_sector.push_back(temp);
    }
}



/*
*/
void Public_Info_Board::Update_Consumer_Spending_by_Sector( const vector<int>& actual_spending ){
    // loop though the actual_spending vector and add to the actual_spending_by_sector vector
    actual_spending_by_sector.clear();
    for (int i = 0; i < sector_count; i++){
        int temp = actual_spending[i];
        actual_spending_by_sector.push_back(temp);
    }

}




//--- Job Market

Job* Public_Info_Board::Get_Top_Job() {
    Job * job = pJob_Market->Get_Top_Job();
    return job;
}

void Public_Info_Board::Remove_Top_Job_Offer(){
    //std::cout << "Top job offer taken" <<std::endl;
    pJob_Market->Remove_Top_Job_Offer();
}



/* Called by firm to place a job into the market*/
void Public_Info_Board::Post_Job_To_Market(Job * pJob_Offer) {
    //cout << "Public board posting job with address: " <<  pJob_Offer << " and wage: "  << pJob_Offer->Get_Wage() << endl;
    pJob_Market->Add_Job_Offer(pJob_Offer);
}

/* Mark a job as taken and remove from the job market
 TODO: Edit this to deal with cases when taken job is not at the top of the list
*/
void Public_Info_Board::Take_Job(Job* pJob_Offer) {
    // Remove from market
    Public_Info_Board::Remove_Top_Job_Offer();
    // Notify employer
    pJob_Offer->Update_Status(1); // mark job as taken
}

/* Sort by wage at each timestep*/
void Public_Info_Board::Sort_Job_Market(){
    pJob_Market->Sort_Jobs_by_Wage();
}

//--------------------------------------------------
// Consumer Good Market

/* Add Consumer good to the consumer goods market
*/
void Public_Info_Board::Send_Cons_Good_To_Market(Consumer_Good* pGood){
    pConsumer_Goods_Market->Add_Consumer_Good_To_Market(pGood);
}

/* Call the Consumer good Market with the budget, and return the remaining budget
*/
pair<int, int> Public_Info_Board::Buy_Consumer_Goods(int budget){
    return pConsumer_Goods_Market->Buy_Consumer_Goods(budget);
}


/* Call the consumer good markets relevant method to buy goods by sector
*/
pair<vector<float>, vector<int>> Public_Info_Board::Buy_Consumer_Goods_By_Sector(int budget, const vector<int>& planned_expenditure_by_sector){
    return pConsumer_Goods_Market->Buy_Consumer_Goods_By_Sector(budget, planned_expenditure_by_sector);
}




//--------------------------------------------------



/* Add Capital good to the capital goods market
*/
void Public_Info_Board::Send_Cap_Good_To_Market(Capital_Good* pGood){
    pCapital_Goods_Market->Add_Capital_Good_To_Market(pGood);
}



/* 
*/
int*  Public_Info_Board::Buy_Capital_Goods(int q_desired){
    return pCapital_Goods_Market->Buy_Capital_Goods(q_desired);
}



/* Return how much it would cost to buy the desired # machines
*/
int Public_Info_Board::Get_Cost_For_Desired_Cap_Goods(int q_desired){
    return pCapital_Goods_Market->Get_Cost_For_Given_Quantity(q_desired);
}


//--------------------------------------------------

//--- Inflation and Price level --------------------

/*  Calculate consumer price level given each sector's price level and weighing in the consumer basket
    Also updates consumer inflation records
*/
void Public_Info_Board::Update_Consumer_Price_Level(){
    cons_price_level_previous = cons_price_level_current; // update previous price level
    
    consumer_sectors_price_levels = pConsumer_Goods_Market->Get_Price_Levels();

    float sum = 0.0;
    float sum_weights = 0.0;
    for (int i = 0; i < sector_count; i++){
        sum += consumer_sectors_price_levels[i] * consumer_sector_weights[i];
        sum_weights += consumer_sector_weights[i];
    }
    cons_price_level_current = sum/sum_weights; // incase the sums don't match due to rounding errors

    // Update inflation 
    cons_inflation_current = 1.0 + (cons_price_level_current - cons_price_level_previous)/cons_price_level_previous;

}

/* Update capital price level by simply getting the data from the market
    Also updates capital inflation records
*/
void Public_Info_Board::Update_Capital_Price_Level(){
    cap_price_level_previous = cap_price_level_current;
    cap_price_level_current = pCapital_Goods_Market->Get_Price_Level();
    cap_inflation_current = 1.0 + (cap_price_level_current - cap_price_level_previous)/cap_price_level_previous;
}


/* Initialize price levels at t=0 , without updating inflation
*/
void Public_Info_Board::Initialize_Price_Levels(){

    consumer_sectors_price_levels = pConsumer_Goods_Market->Get_Price_Levels();

    float sum = 0.0;
    float sum_weights = 0.0;
    for (int i = 0; i < sector_count; i++){
        sum += consumer_sectors_price_levels[i] * consumer_sector_weights[i];
        sum_weights += consumer_sector_weights[i];
    }
    cons_price_level_current = sum/sum_weights; // incase the sums don't match due to rounding errors

    cap_price_level_current = pCapital_Goods_Market->Get_Price_Level();

}

/* Get the interest rate from the bank
*/
void Public_Info_Board::Update_Interest_Rate(){
    r_rate = pBank->Get_Interest_Rate();
}


//--------------------------------------------------
//--- Loan issuance


/* Function to call the bank's short term loan method
This function will be called by the firm agent
*/
Loan* Public_Info_Board::Seek_Short_Term_Loan(Firm_Agent* pFirm){
    return pBank->Issue_Short_Term_Loan(pFirm);
}

/* Function to call the bank's long term loan method
This function will be called by the firm agent
*/
Loan* Public_Info_Board::Seek_Long_Term_Loan(Firm_Agent* pFirm){
    return pBank->Issue_Long_Term_Loan(pFirm);
}

//--------------------------------------------------
// Global Data
/* Function to reset global data parameters to zero*/
void Public_Info_Board::Reset_Global_Data(){
    int reset_value = 0;

    // General price level
   /*  price_level_current = reset_value;
    price_level_previous = reset_value;
    cap_price_level_current = reset_value;
    cap_price_level_previous = reset_value;
    average_wage_market = reset_value; */

    // Inflation and interest rate
    r_rate = reset_value;
    cons_inflation_current = reset_value;
    cap_inflation_current = reset_value;

    // Income Figures
    average_wage_market = reset_value;
    average_wage_employed = reset_value;
    average_dividend_income = reset_value;
    average_total_income = reset_value;

    household_wage_sum = reset_value;
    household_dividends_sum = reset_value;
    household_total_income_sum = reset_value;
    


    // Global aggregate varaibles

    // Sentiments
    household_sentiment_sum = reset_value;
    household_sentiment_percentage = reset_value;
    cons_firm_sentiment_sum = reset_value;
    cons_firm_sentiment_percentage = reset_value;
    cap_firm_sentiment_sum = reset_value;
    cap_firm_sentiment_percentage = reset_value;

    // Capital expenditure
    machine_orders = reset_value;
    machine_orders_planned = reset_value;
    machine_spending = reset_value;

    // Consumer expenditure
    consumer_orders = reset_value;
    consumer_spending = reset_value;
    consumption_budgets = reset_value;

    planned_spending_by_sector.clear();
    actual_spending_by_sector.clear();

    // Production
    consumer_goods_production = reset_value;
    capital_goods_production = reset_value;

    consumer_goods_production_planned = reset_value;
    capital_goods_production_planned = reset_value;

    planned_production_by_sector.clear();
    actual_production_by_sector.clear();

    
    // Employment
    n_employed_workers = reset_value;
    n_unemployed_workers = reset_value;
    unemployment_rate = reset_value;

    employee_hires = reset_value;
    new_employee_demand = reset_value;
    employee_firings = reset_value;
    contract_expiries = reset_value;
    new_job_postings = reset_value;
    removed_job_postings = reset_value;
    n_employees_quitting = reset_value;
    //public_unemployment_benefit = reset_value; // Do not reset tis
    // minimum_wage = reset_value // Do not reset this

    time_step = reset_value;
    current_date = reset_value;
}


// Printing and Debugging

void Public_Info_Board::Print() const{
    cout << " Public Infor Board at adress " << this << endl;
    cout << " Price Level: " << cons_price_level_current << " Interest Rate: " << r_rate <<endl;
    cout << " Current Inflation: " << cons_inflation_current <<  endl;
    cout << " Household Optimism: " << household_sentiment_percentage << " COns Firm Optimism: " << cons_firm_sentiment_percentage << endl;
}


/* Function to print labor market related variables
*/
void Public_Info_Board::Print_Labor_Market() const{
    cout << " # employed workers: " << n_employed_workers << " # unemployed workers: " << n_unemployed_workers << endl;
    cout << " # new employee demand: " << new_employee_demand << " # employee firings: " << employee_firings << endl;
    cout << " # new employee hires: " << employee_hires << " Unemployment Rate: " << unemployment_rate << endl;
    cout << "average_wage_market: " << average_wage_market <<  " # contract expiries: " << contract_expiries << endl;
}

/* Function to make string stream operator << work
*/
std::ostream& operator<<(std::ostream& os, const Public_Info_Board& obj) {
    
    os << "r_rate " << obj.r_rate << std::endl;
    os << "cons_inflation_current " << obj.cons_inflation_current << std::endl;
    os << "price_level_current " << obj.cons_price_level_current << std::endl;
    os << "price_level_previous " << obj.cons_price_level_previous << std::endl;
    os << "cap_price_level_current " << obj.cap_price_level_current << std::endl;
    os << "cap_price_level_previous " << obj.cap_price_level_previous << std::endl;

    os << "average_wage_market " << obj.average_wage_market << std::endl;
    os << "average_wage_employed" << obj.average_wage_employed << std::endl;
    os << "average_dividend_income " << obj.average_dividend_income << std::endl;
    os << "average_total_income " << obj.average_total_income << std::endl;
    
    os << "household_wage_sum " << obj.household_wage_sum << std::endl;
    os << "household_dividends_sum " << obj.household_dividends_sum << std::endl;
    os << " household_total_income_sum " << obj.household_total_income_sum << std::endl;
    
    
    os << "household_sentiment_sum " << obj.household_sentiment_sum << std::endl;
    os << "household_sentiment_percentage " << obj.household_sentiment_percentage << std::endl;
    os << "cons_firm_sentiment_sum " << obj.cons_firm_sentiment_sum << std::endl;
    os << "cons_firm_sentiment_percentage " << obj.cons_firm_sentiment_percentage << std::endl;
    os << "cap_firm_sentiment_sum " << obj.cap_firm_sentiment_sum << std::endl;
    os << "cap_firm_sentiment_percentage " << obj.cap_firm_sentiment_percentage << std::endl;
    
    os << "machine_orders " << obj.machine_orders << std::endl;
    os << "machine_orders_planned " << obj.machine_orders_planned << std::endl;
    os << "machine_spending " << obj.machine_spending << std::endl;
    
    os << "consumer_orders " << obj.consumer_orders << std::endl;
    os << "consumer_spending " << obj.consumer_spending << std::endl;
    os << "consumption_budgets " << obj.consumption_budgets << std::endl;
    
    for (int i = 0; i < obj.planned_spending_by_sector.size(); i++) {
        os << "planned_spending_on_sector_" << i << " " << obj.planned_spending_by_sector[i] << std::endl;
        os << "actual_spending_on_sector_" << i << " " << obj.actual_spending_by_sector[i] << std::endl;
        os << "planned_production_on_sector_" << i << " " << obj.planned_production_by_sector[i] << std::endl;
        os << "actual_production_on_sector_" << i << " " << obj.actual_production_by_sector[i] << std::endl;
    } 
    
    os << "consumer_goods_production " << obj.consumer_goods_production << std::endl;
    os << "capital_goods_production " << obj.capital_goods_production << std::endl;
    os << "consumer_goods_production_planned " << obj.consumer_goods_production_planned << std::endl;
    os << "capital_goods_production_planned " << obj.capital_goods_production_planned << std::endl;
    os << "n_employed " << obj.n_employed_workers << std::endl;
    os << "n_unemployed " << obj.n_unemployed_workers << std::endl;
    os << "unemp_rate " << obj.unemployment_rate << std::endl;
    os << "empl_hires " << obj.employee_hires << std::endl;
    os << "new_empl_demand " << obj.new_employee_demand << std::endl;
    os << "empl_firings " << obj.employee_firings << std::endl;
    os << "empl_contract_expiries " << obj.contract_expiries << std::endl;
    os << "n_new_job_postings " << obj.new_job_postings << std::endl;
    os << "n_removed_job_postings " << obj.removed_job_postings << std::endl;
    os << "unempl_benefits " << obj.public_unemployment_benefit << std::endl;
    os << "minimum_wage " << obj.minimum_wage << std::endl;
    os << "n_employees_quitting " << obj.n_employees_quitting << std::endl;

    os << "date " << obj.current_date << std::endl;
}


/* Function to log all data: Create a vector of pairs where each entry has the member name and the value
*/
vector<pair<string, float>>* Public_Info_Board::Log_Data() {
        current_date = global_date;
        auto result = new vector<pair<string, float>>();

        // Get the names and values of all member variables
        stringstream ss;
        ss << *this;
        string line;
        while (std::getline(ss, line)) {
            string name;
            float value;
            stringstream(line) >> name >> value;
            result->emplace_back(name, value);
        }
        return result;
    }
