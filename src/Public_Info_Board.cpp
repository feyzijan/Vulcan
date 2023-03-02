
#include "Public_Info_Board.hpp"


//-------- Constructors and destructor

Public_Info_Board::Public_Info_Board(){
    // Genereal price level
    price_level_current =0;
    price_level_previous = 0;

    // Capital good price level
    cap_price_level_current = 0;
    cap_price_level_previous = 0;
    average_wage = 0;
    // Inflation and interest rates
    r_rate = 0;
    inflation_current = 0;

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
    // Consumer expenditure
    consumer_orders = 0;
    consumer_spending = 0;
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

    // not using this as of yet
    public_unemployment_benefit = init_unemployment_benefit;

    // timestep - not using these for now
    time_step = 0;
    current_date = 0;
}


Public_Info_Board::~Public_Info_Board(){}
Public_Info_Board::Public_Info_Board(Public_Info_Board&){}
//------------------------------------

//--- Job Market

Job* Public_Info_Board::Get_Top_Job() {
    Job * job = pJob_Market->Get_Top_Job();
    return job;
}

void Public_Info_Board::Remove_Top_Job_Offer(){
    //std::cout << "Top job offer taken" <<std::endl;
    pJob_Market->Remove_Top_Job_Offer();
}

/* Function to return average capital good price level
*/
float Public_Info_Board::Get_Capital_Good_Price_Level(){
    return pCapital_Goods_Market->Get_Price_Level();
}

/* Function to return average consumer good price level
*/
float Public_Info_Board::Get_Consumer_Good_Price_Level(){
    return pConsumer_Goods_Market->Get_Price_Level();
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
std::pair<int, int> Public_Info_Board::Buy_Consumer_Goods(int budget){
    return pConsumer_Goods_Market->Buy_Consumer_Goods(budget);
 }

/* Add Capital good to the capital goods market
*/
void Public_Info_Board::Send_Cap_Good_To_Market(Capital_Good* pGood){
    pCapital_Goods_Market->Add_Capital_Good_To_Market(pGood);
}

/* Call the capital goods market with desired quantities, return q bought and average price paid
*/
std::vector<Capital_Good*>*  Public_Info_Board::Buy_Capital_Goods(int q_desired){
    return pCapital_Goods_Market->Buy_Capital_Goods(q_desired);
}
/* Return how much it would cost to buy the desired # machines
*/
int Public_Info_Board::Get_Cost_For_Desired_Cap_Goods(int q_desired){
    return pCapital_Goods_Market->Get_Cost_For_Given_Quantity(q_desired);
}


//--------------------------------------------------

//--- Inflation and Price level

float Public_Info_Board::Calculate_Inflation(){
    price_level_previous = price_level_current;
    price_level_current = pConsumer_Goods_Market->Get_Price_Level();
    return 1.0 + (price_level_current - price_level_previous)/price_level_previous;
}

float Public_Info_Board::Calculate_Manufacturer_Inflation(){
    cap_price_level_previous = cap_price_level_current;
    cap_price_level_current = pCapital_Goods_Market->Get_Price_Level();
    return 1.0 + (cap_price_level_current - cap_price_level_previous)/cap_price_level_previous;
}

void Public_Info_Board::Initialize_Price_Level(){
    price_level_current = pConsumer_Goods_Market->Get_Price_Level();
    cap_price_level_current = pCapital_Goods_Market->Get_Price_Level();
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
    // Capital expenditure
    machine_orders = 0;
    machine_spending = 0;
    // Consumer expenditure
    consumer_orders = 0;
    consumer_spending = 0;
    consumption_budgets = 0;
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
}


// Printing and Debugging

void Public_Info_Board::Print() const{
    cout << " Public Infor Board at adress " << this << endl;
    cout << " Price Level: " << price_level_current << " Interest Rate: " << r_rate <<endl;
    cout << " Current Inflation: " << inflation_current <<  endl;
    cout << " Household Optimism: " << household_sentiment_percentage << " COns Firm Optimism: " << cons_firm_sentiment_percentage << endl;
}


/* Function to print labor market related variables
*/
void Public_Info_Board::Print_Labor_Market() const{
    cout << " # employed workers: " << n_employed_workers << " # unemployed workers: " << n_unemployed_workers << endl;
    cout << " # new employee demand: " << new_employee_demand << " # employee firings: " << employee_firings << endl;
    cout << " # new employee hires: " << employee_hires << " Unemployment Rate: " << unemployment_rate << endl;
    cout << "average_wage: " << average_wage <<  " # contract expiries: " << contract_expiries << endl;
}

/* Function to make string stream operator << work
*/
std::ostream& operator<<(std::ostream& os, const Public_Info_Board& obj) {
    os << "price_level_current " << obj.price_level_current << std::endl;
    os << "price_level_previous " << obj.price_level_previous << std::endl;
    os << "cap_price_level_current " << obj.cap_price_level_current << std::endl;
    os << "cap_price_level_previous " << obj.cap_price_level_previous << std::endl;
    os << "average_wage " << obj.average_wage << std::endl;
    os << "r_rate " << obj.r_rate << std::endl;
    os << "inflation_current " << obj.inflation_current << std::endl;
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
    os << "date " << obj.current_date << std::endl;
}


/* Function to log all data: Create a vector of pairs where each entry has the member name and the value
*/
std::vector<std::pair<std::string, float>>* Public_Info_Board::Log_Data() {
        current_date = global_date;
        auto result = new std::vector<std::pair<std::string, float>>();

        // Get the names and values of all member variables
        std::stringstream ss;
        ss << *this;
        std::string line;
        while (std::getline(ss, line)) {
            std::string name;
            float value;
            std::stringstream(line) >> name >> value;
            result->emplace_back(name, value);
        }
        return result;
    }
