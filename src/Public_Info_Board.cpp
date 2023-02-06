
#include "Public_Info_Board.hpp"


//-------- Constructors and destructor

Public_Info_Board::Public_Info_Board(){
    price_level_current =0;
    price_level_previous = 0;
    inflation_current = 0;
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

/* Mark a job as taken and remove from the job market*/
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
/* Call the Consumer good Market with the budget, and return the remaining budget
*/
int Public_Info_Board::Buy_Consumer_Goods(int budget){
    return pConsumer_Goods_Market->Buy_Consumer_Goods(budget);
}

/* Call the capital goods market with desired quantities, return q bought and average price paid
*/
std::vector<Capital_Good*>  Public_Info_Board::Buy_Capital_Goods(int q_desired){
    return pCapital_Goods_Market->Buy_Capital_Goods(q_desired);
}


//--------------------------------------------------

//--- Inflation and Price level

float Public_Info_Board::Calculate_Inflation(){
    price_level_previous = price_level_current;
    price_level_current = pConsumer_Goods_Market->Get_Price_Level();
    return (price_level_current - price_level_previous)/price_level_previous;
}

void Public_Info_Board::Initialize_Price_Level(){
    price_level_previous = pConsumer_Goods_Market->Get_Price_Level();
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


// Printing and Debugging

void Public_Info_Board::Print() const{
    cout << " Public Infor Board at adress " << this << endl;
    cout << " Price Level: " << price_level_current << " Interest Rate: " << r_rate <<endl;
    cout << " Current Inflation: " << inflation_current <<  endl;
    cout << " Household Optimism: " << household_sentiment_percentage << " Firm Optimism: " << firm_sentiment_percentage << endl;
}

