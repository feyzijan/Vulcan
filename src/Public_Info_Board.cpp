
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

    household_wage_income = 0;
    household_unemployment_income = 0;
    household_dividend_income = 0;

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
    cap_good_orders = 0;
    capital_spending = 0;
    cap_good_orders_planned = 0;
    machine_spending_planned = 0;
    // Consumer expenditure
    consumer_spending = 0;
    consumer_spending_planned = 0;
    consumption_budget = 0;

    // Production
    cap_goods_production = 0;
    cap_goods_production_planned = 0;
    cap_goods_quantity_sold = 0;
    cons_good_production = 0;
    cons_good_production_planned = 0;

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
    n_active_job_postings = 0;
    n_employees_quitting = 0;

    // not using this as of yet
    public_unemployment_benefit = household_init_unemployment_benefit;
    minimum_wage = household_init_minimum_wage;

    // Emission allowances
    total_emission_allowance = emission_init_total_allowance; 
    emission_offset_price = emission_init_unit_price;
    total_offsets_sold = 0;

    // Bankruptcy figures
    n_bankrupt_cap_firms = 0;
    n_bankrupt_cons_firms = 0;
    n_active_firms = n_firms;
    p_bankrupt_cons_firms = 0;
    p_bankrupt_cap_firms = 0;
    p_bankrupt_firms = 0;

    current_date = 0;
}


Public_Info_Board::~Public_Info_Board(){}
Public_Info_Board::Public_Info_Board(Public_Info_Board&){}
//------------------------------------
// Dealing with sectors

/* Set the number of sectors, initialize spending by sector vectors with 0
*/
void Public_Info_Board::Initialize_Consumer_Sectors(vector<Consumer_Firm_Sector*> *pConsumer_Firm_Sector_vector){

    consumer_spending_by_sector = vector<long long>(sector_count, 0.0);
    planned_cons_spending_by_sector = vector<long long>(sector_count, 0.0);
    actual_production_by_sector = vector<long long>(sector_count, 0);
    planned_production_by_sector = vector<long long>(sector_count, 0);
    quantity_sold_by_sector = vector<long long>(sector_count, 0);
    inventory_by_sector = vector<long long>(sector_count, 0);

    average_unit_emissions_by_sector = vector<float>(sector_count, 0.0);
    total_consumer_emissions_by_sector = vector<long long>(sector_count, 0);
    offsets_sold_by_sector = vector<long long>(sector_count, 0);
    total_firm_emissions_by_sector = vector<long long> (sector_count, 0);

    // Loop through each sector in the consumer_firm_sector vector and add the sector weighing to the consumer_sector_weighing_vector
    for (int i = 0; i < sector_count; i++){
        consumer_sector_weights.push_back(pConsumer_Firm_Sector_vector->at(i)->weighing);
    }

    // Initialize emissions by looping through each sector and getting the emission_allowance
    total_emission_allowance = 0;
    for (int i = 0; i < sector_count; i++){
        emission_allowances_by_sector.push_back(pConsumer_Firm_Sector_vector->at(i)->emission_allowance);
        total_emission_allowance += pConsumer_Firm_Sector_vector->at(i)->emission_allowance;
    }
}

// ----- Updating Member variables

/* Update the planned consumer spending on each sector by adding the planned spending array figures passed by the
Household agent that calls this method
*/
void Public_Info_Board::Update_Planned_Consumer_Spending_by_Sector( const vector<long long>& planned_spending){
    // loop through the planned_spending vector and add to the planned_cons_spending_by_sector vector
    for (int i = 0; i < sector_count; i++){
        planned_cons_spending_by_sector[i] += planned_spending[i];
        consumer_spending_planned += planned_spending[i];
    }
}


/* Update the actual consumer spending on each sector by adding the planned spending array figures passed by the
Household agent that calls this method
*/
void Public_Info_Board::Update_Actual_Consumer_Spending_by_Sector( const vector<long long>& actual_spending ){
    // loop though the actual_spending vector and add to the consumer_spending_by_sector vector
    for (int i = 0; i < sector_count; i++){
        consumer_spending_by_sector[i] += actual_spending[i];
        consumer_spending += actual_spending[i];
    }
}

/*
*/
void Public_Info_Board::Calculate_Average_Unit_Emissions_by_Sector(){
    for(int i=0; i<sector_count; i++){
        if ( actual_production_by_sector[i] == 0) {
            average_unit_emissions_by_sector[i] = 0.0;
            cout << "Unexpected behaviour: actual production in sector " << i << " is 0" << endl;
        } else {
            // TODO: Make sure the division is done correctly
            average_unit_emissions_by_sector[i] =  total_consumer_emissions_by_sector[i] / actual_production_by_sector[i]; 
        }
        
    }
}

/* Get latest interest rate from the bank*/
void Public_Info_Board::Update_Interest_Rate() {r_rate = pBank->Get_Interest_Rate();} // Get latest interest rate from the bank

//---- Updating emissions
void Public_Info_Board::Update_Consumer_Emissions_By_Sector(const vector<long long>& emissions_by_sector) {   
    for (int i = 0; i < sector_count; i++){
        total_consumer_emissions_by_sector[i] += emissions_by_sector[i];
    }
}



//---------- Distributing Emission Allowances --------

/* Distribute initial emission allowances based on # employees
*/
long long Public_Info_Board::Distribute_Initial_Emission_Allowances(int employee_count, int sector_id){
    return employee_count/n_employed_workers * emission_allowances_by_sector[sector_id]; // CHECK THE DIVISION IS ACCURATE
}

/* Distribute emission allowances base don sales
*/
long long Public_Info_Board::Distribute_Emission_Allowances(long long sale_quantity, int sector_id){
    double sale_ratio = static_cast<double>(sale_quantity) / static_cast<double>(quantity_sold_by_sector[sector_id]);
    return static_cast<long>(sale_ratio * emission_allowances_by_sector[sector_id]); 
}

// Updating emission allowance amounts
void Public_Info_Board::Update_Emission_Allowance_Amount() { 

    std::transform(emission_allowances_by_sector.begin(), emission_allowances_by_sector.end(), 
    emission_allowances_by_sector.begin(), [=](long long value) {
    float result = static_cast<float>(value) * (1.0f + emission_total_allowance_change);
    return static_cast<unsigned long int>(std::round(result));});

    total_emission_allowance = static_cast<long long>(total_emission_allowance * (1.0 + emission_total_allowance_change));
}



//------------ Interfacing with good, labor, and financial markets ----------------

// Loan market
Loan* Public_Info_Board::Seek_Short_Term_Loan(Firm_Agent* pFirm)
    {return pBank->Issue_Short_Term_Loan(pFirm);
}

Loan* Public_Info_Board::Seek_Long_Term_Loan(Firm_Agent* pFirm) {
    return pBank->Issue_Long_Term_Loan(pFirm);
}

// Capital goods market

long long*  Public_Info_Board::Buy_Capital_Goods(long long q_desired) {
    return pCapital_Goods_Market->Buy_Capital_Goods(q_desired);
}

void Public_Info_Board::Send_Cap_Good_To_Market(Capital_Good* pGood) {
    pCapital_Goods_Market->Add_Capital_Good_To_Market(pGood);
}

long long Public_Info_Board::Get_Cost_For_Desired_Cap_Goods(long long q_desired){
    return pCapital_Goods_Market->Get_Cost_For_Given_Quantity(q_desired);
}

// Consumer Good Market
void Public_Info_Board::Send_Cons_Good_To_Market(Consumer_Good* pGood) { 
    pConsumer_Goods_Market->Add_Consumer_Good_To_Market(pGood);
}


// Consumer Good Market 
tuple<vector<long long>, vector<long long>, vector<long long> > Public_Info_Board::Buy_Consumer_Goods_By_Sector_And_Emission
(const vector<long long>& planned_expenditure_by_sector, const vector<float>& emission_sensitives_array) 
{
    return pConsumer_Goods_Market->Buy_Consumer_Goods_By_Sector_And_Emission(planned_expenditure_by_sector, emission_sensitives_array);
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


/* Update the average wage in the job market*/
void Public_Info_Board::Update_Average_Wage_Job_Market(){
    pJob_Market->Calculate_Average_Wage();
    average_wage_market = pJob_Market->Get_Average_Wage();
}



//--------------------------------------------------

//----------------Inflation and Price level --------------------

/* Function to calculate consumer price level given each sector's price level and weighing in the 
consumer basket. Also updates consumer inflation records
*/
void Public_Info_Board::Update_Consumer_Price_Level()
{
    cons_price_level_previous = cons_price_level_current; // Set current price lvel to previous
    
    // Get Data from consumer goods market
    consumer_sectors_price_levels = pConsumer_Goods_Market->Get_Price_Levels_By_Sector();
    cons_price_level_current = pConsumer_Goods_Market->Get_Price_Level();

    // Update inflation 
    cons_inflation_current = 1.0 + (cons_price_level_current - cons_price_level_previous)/cons_price_level_previous;
}

/* Function to update capital price level by simply getting the data from the market
    Also updates capital inflation records
*/
void Public_Info_Board::Update_Capital_Price_Level(){
    cap_price_level_previous = cap_price_level_current; // Set current price lvel to previous

    // Get Data from market
    cap_price_level_current = pCapital_Goods_Market->Get_Price_Level();

    // Update inflation
    cap_inflation_current = 1.0 + (cap_price_level_current - cap_price_level_previous)/cap_price_level_previous;
    cap_inflation_current = max(cap_inflation_current, 1.001f); // Make sure inflation is slighly positive
}


/* Initialize price levels at t=0 , without updating inflation
*/
void Public_Info_Board::Initialize_Price_Levels()
{    
    consumer_sectors_price_levels = pConsumer_Goods_Market->Get_Price_Levels_By_Sector();
    cons_price_level_current = pConsumer_Goods_Market->Get_Price_Level();
    cap_price_level_current = pCapital_Goods_Market->Get_Price_Level();
    cout << "Initialized price levels: cons: " << cons_price_level_current << " cap: " << cap_price_level_current << endl;
    // print the price lvel by sector
    for (int i = 0; i < sector_count; i++){
        cout << "Sector " << i << " price level: " << consumer_sectors_price_levels[i] << endl;
    }
}


//--------------------------------------------------

/* Function to reset global data parameters to zero*/
void Public_Info_Board::Reset_Global_Data(){
    int reset_value = 0;


    // Income Figures
    average_wage_market = reset_value;
    average_wage_employed = reset_value;

    household_wage_income = reset_value;
    household_dividend_income = reset_value;
    household_unemployment_income = reset_value;

    // Emissions
    total_consumer_emissions_by_sector = vector<long long>(sector_count, 0);
    total_firm_emissions_by_sector = vector<long long>(sector_count, 0);
    offsets_sold_by_sector = vector<long long>(sector_count, 0);
    
    // Global aggregate varaibles

    // Sentiments
    household_sentiment_sum = reset_value;
    household_sentiment_percentage = reset_value;
    cons_firm_sentiment_sum = reset_value;
    cons_firm_sentiment_percentage = reset_value;
    cap_firm_sentiment_sum = reset_value;
    cap_firm_sentiment_percentage = reset_value;

    // Capital expenditure
    cap_good_orders = reset_value;
    cap_good_orders_planned = reset_value;
    capital_spending = reset_value;
    machine_spending_planned = reset_value;

    // Consumer expenditure
    consumer_spending = reset_value;
    consumer_spending_planned = reset_value;
    consumption_budget = reset_value;

    consumer_spending_by_sector = vector<long long>(sector_count, 0);
    planned_cons_spending_by_sector = vector<long long>(sector_count, 0);
    
    // Production
    cap_goods_production = reset_value;
    cap_goods_production_planned = reset_value;
    cap_goods_quantity_sold = reset_value;
    cons_good_production = reset_value;
    cons_good_production_planned = reset_value;

    actual_production_by_sector = vector<long long>(sector_count, 0);
    planned_production_by_sector = vector<long long>(sector_count, 0);
    inventory_by_sector = vector<long long>(sector_count, 0);
    quantity_sold_by_sector = vector<long long>(sector_count, 0);
    
    // Employment
    n_employed_workers = reset_value;
    n_unemployed_workers = reset_value;
    unemployment_rate = -0.1; // So we can see if it isnt properly updated

    employee_hires = reset_value;
    new_employee_demand = reset_value;
    employee_firings = reset_value;
    contract_expiries = reset_value;
    new_job_postings = reset_value;
    n_active_job_postings = reset_value;
    removed_job_postings = reset_value;
    n_employees_quitting = reset_value;

    // Emissions
    total_offsets_sold = reset_value;
}

//-------------------------------------------------------------

/* Function to make string stream operator << work
*/
std::ostream& operator<<(std::ostream& os, const Public_Info_Board& obj) {

    
    //os << "r_rate " << obj.r_rate << std::endl;
    os << "cons_inflation_mom " << obj.cons_inflation_current -1 << std::endl;
    os << "price_level_current " << obj.cons_price_level_current << std::endl;
    //os << "price_level_previous " << obj.cons_price_level_previous << std::endl;
    os << "cap_price_level_current " << obj.cap_price_level_current << std::endl;
    //os << "cap_price_level_previous " << obj.cap_price_level_previous << std::endl;

    // Emission stuff
    os << "total_emission_allowance " << obj.total_emission_allowance << std::endl;
    os << "emission_offset_price " << obj.emission_offset_price << std::endl;

    os << "average_wage_market " << obj.average_wage_market << std::endl;
    //os << "average_wage_employed " << obj.average_wage_employed << std::endl;
    
    //os << "household_wage_income " << obj.household_wage_income << std::endl;
    //os << "household_dividend_income " << obj.household_dividend_income << std::endl;
    //os << "household_unemployment_income " << obj.household_unemployment_income << std::endl;
    
    //os << "household_sentiment_sum " << obj.household_sentiment_sum << std::endl;
    os << "household_sentiment " << obj.household_sentiment_percentage << std::endl;
    //os << "cons_firm_sentiment_sum " << obj.cons_firm_sentiment_sum << std::endl;
    os << "cons_firm_sentiment " << obj.cons_firm_sentiment_percentage << std::endl;
    //os << "cap_firm_sentiment_sum " << obj.cap_firm_sentiment_sum << std::endl;
    os << "cap_firm_sentiment " << obj.cap_firm_sentiment_percentage << std::endl;
    
    os << "cap_good_orders " << obj.cap_good_orders << std::endl;
    os << "cap_good_orders_planned " << obj.cap_good_orders_planned << std::endl;
    os << "capital_spending " << obj.capital_spending << std::endl;
    os << "machine_spending_planned " << obj.machine_spending_planned << std::endl;
    
    os << "consumer_spending " << obj.consumer_spending << std::endl;
    os << "consumer_spending_planned " << obj.consumer_spending_planned << std::endl;
    //os << "consumption_budget " << obj.consumption_budget << std::endl;
    
    // Print the vectors
    for (int i = 0; i < sector_count; i++) {
        os << "planned_spending_on_sector_" << i << " " << obj.planned_cons_spending_by_sector[i] << std::endl;
        os << "actual_spending_on_sector_" << i << " " << obj.consumer_spending_by_sector[i] << std::endl;
        os << "planned_production_on_sector_" << i << " " << obj.planned_production_by_sector[i] << std::endl;
        os << "actual_production_on_sector_" << i << " " << obj.actual_production_by_sector[i] << std::endl;
        os << "price_level_cons_sector_" << i << " " << obj.consumer_sectors_price_levels[i] << std::endl;
        os << "offsets_sold_by_sector_" << i << " " << obj.offsets_sold_by_sector[i] << std::endl;
        //os  << "emission_allowance_by_sector_" << i << " " << obj.emission_allowances_by_sector[i] << std::endl;
        os << "quantity_sold_by_sector_" << i << " " << obj.quantity_sold_by_sector[i] << std::endl;
        os << "inventory_by_sector_" << i << " " << obj.inventory_by_sector[i] << std::endl;
        os << "total_cons_emissions_by_sector_" << i << " " << obj.total_consumer_emissions_by_sector[i] << std::endl;
        os << "total_firm_emissions_by_sector_" << i << " " << obj.total_firm_emissions_by_sector[i] << std::endl;
    } 
    os << "total_offsets_sold " << obj.total_offsets_sold << std::endl;
    
    os << "cap_goods_production " << obj.cap_goods_production << std::endl;
    os << "cap_goods_production_planned " << obj.cap_goods_production_planned << std::endl;
    os << "cap_goods_quantity_sold " << obj.cap_goods_quantity_sold << std::endl;

    //os << "n_bankrupt_cap_firms " << obj.n_bankrupt_cap_firms << std::endl;
    os << "p_bankrupt_cap_firms " << obj.p_bankrupt_cap_firms << std::endl;
    //os << "n_bankrupt_cons_firms " << obj.n_bankrupt_cons_firms << std::endl;
    os << "p_bankrupt_cons_firms " << obj.p_bankrupt_cons_firms << std::endl;
    os << "p_bankrupt_firms " << obj.p_bankrupt_firms << std::endl;

    //os << "n_employed " << obj.n_employed_workers << std::endl;
    //os << "n_unemployed " << obj.n_unemployed_workers << std::endl;
    os << "unemp_rate " << obj.unemployment_rate << std::endl;
    os << "empl_hires " << obj.employee_hires << std::endl;
    os << "new_empl_demand " << obj.new_employee_demand << std::endl;
    os << "empl_firings " << obj.employee_firings << std::endl;
    os << "empl_contract_expiries " << obj.contract_expiries << std::endl;
    os << "n_new_job_postings " << obj.new_job_postings << std::endl;
    os << "n_removed_job_postings " << obj.removed_job_postings << std::endl;
    os << "n_active_job_postings " << obj.n_active_job_postings << std::endl;
    
    //os << "unempl_benefits " << obj.public_unemployment_benefit << std::endl;
    //os << "minimum_wage " << obj.minimum_wage << std::endl;
    
    os << "n_employees_quitting " << obj.n_employees_quitting << std::endl;
    
    os << "date " << obj.current_date << std::endl;

    return os;
}


/* Function to log all data: Create a vector of pairs where each entry has the member name and the value
*/
vector<pair<string, float> >* Public_Info_Board::Log_Data() {
    current_date = global_date;
    // Income and wage figures
    if (global_date > 0){
        household_wage_income /= max(n_employed_workers,1);
        household_dividend_income /= max((n_active_firms),1);
        household_unemployment_income /= max(n_unemployed_workers,1);
    }
    p_bankrupt_cons_firms = static_cast<float>(n_bankrupt_cons_firms)/n_consumer_firms;
    p_bankrupt_cap_firms = static_cast<float>(n_bankrupt_cap_firms)/n_capital_firms;
    p_bankrupt_firms = static_cast<float>(n_bankrupt_cap_firms + n_bankrupt_cons_firms)/n_firms;

    // Job postings
    n_active_job_postings = pJob_Market->Get_Size();




    auto result = new vector<pair<string, float> >();

    // Get the names and values of all member variables
    stringstream ss;
    ss << *this;
    string line;
    while (std::getline(ss, line)) {
        string name;
        float value;
        stringstream(line) > > name > > value;
        result->emplace_back(name, value);
    }
    return result;
}
