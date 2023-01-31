
#include "Public_Info_Board.hpp"


using namespace std;



Public_Info_Board::Public_Info_Board(){

    //queue<float> inflation_history;
    inflation_previous = 1.0;
    for(int i=1;i<=12;i++){
        inflation_previous *= inflation_target_monthly;
        inflation_history.push(inflation_target_monthly);
    }

    price_level_current =0;
    price_level_previous = 0;
    inflation_current = 0;
}


Job* Public_Info_Board::Get_Top_Job() {

    Job * job = pJob_Market->Get_Top_Job();
    return job;
}



/* Function to update interest rate based on inflation gathered from the consumer goods market
*/
void Public_Info_Board::Update_Interest_Rate(){
    Update_Inflation_Rate();

    float inflation_overshoot = inflation_current - inflation_target;

    r_rate = max( double(inflation_reaction* inflation_overshoot), 0.0); // Simplest interest rate rule - From Jamel paper

    /* Alternative interest rate rule:
    r_rate = max(r_target + a*(inflation_current - inflation_target) + b*(output_current - output_target),0)
    */
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




/* Function to update price level and inflation rate
TODO: Add initializer for inflation rate and price level at t=1, so that prev and current are equal
*/
void Public_Info_Board::Update_Inflation_Rate(){
    price_level_previous = price_level_current;
    inflation_previous = inflation_current;

    price_level_current = pConsumer_Goods_Market->Get_Price_Level();

    float past_month_inflation  = (price_level_current - price_level_previous)/price_level_previous;

    inflation_current = inflation_previous / inflation_history.front() * past_month_inflation;

    inflation_history.pop();
    inflation_history.push(past_month_inflation);
}




/* Call this at timestep T=1 to initialize price level
*/
void Public_Info_Board::Initialize_Price_Level(){
    price_level_previous = pConsumer_Goods_Market->Get_Price_Level();
}





void Public_Info_Board::Remove_Top_Job_Offer(){
    //std::cout << "Top job offer taken" <<std::endl;
    pJob_Market->Remove_Top_Job_Offer();
}


void Public_Info_Board::Take_Job(Job* pJob_Offer) {
    // Remove from market
    Public_Info_Board::Remove_Top_Job_Offer();
    // Notify employer
    pJob_Offer->Update_Status(1); // mark job as taken
    //employer->Hire_Worker(pJob_Offer);


}

void Public_Info_Board::Print() const{
    cout << " Public Infor Board at adress " << this << endl;
    cout << " Price Level: " << price_level_current << " Interest Rate: " << r_rate <<endl;
    cout << " Current Inflation: " << inflation_current << " Target Inflation: " << inflation_target << endl;
    cout << " Household Optimism: " << household_sentiment_percentage << " Firm Optimism: " << firm_sentiment_percentage << endl;

}



void Public_Info_Board::Post_Job_To_Market(Job * pJob_Offer) {
    //cout << "Public board posting job with address: " <<  pJob_Offer << " and wage: "  << pJob_Offer->Get_Wage() << endl;
    pJob_Market->Add_Job_Offer(pJob_Offer);
}


void Public_Info_Board::Sort_Job_Market(){
    pJob_Market->Sort_Jobs_by_Wage();
}



/* Function to print inflation history
*/
void Public_Info_Board::Print_Inflation_History(){
    queue<float> temp;
    temp = inflation_history;
    cout << "Inflation History: " << endl;
    while(!temp.empty()){
        cout << temp.front() << endl;
        temp.pop();
    }
}