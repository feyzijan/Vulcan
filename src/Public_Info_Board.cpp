
#include "Public_Info_Board.hpp"


using namespace std;

Job* Public_Info_Board::Get_Top_Job() {
    Job * job_pointer = new Job();
    return job_pointer;
}




void Public_Info_Board::Remove_Top_Job_Offer(){
    std::cout << "Top job offer taken" <<std::endl;
}


void Public_Info_Board::Print() const{
    cout << " Public Infor Board at adress " << this << endl;
    cout << " Price Level: " << price_level << " Interest Rate: " << r_rate <<endl;
    cout << " Current Inflation: " << inflation_current << " Target Inflation: " << inflation_target << endl;
    cout << " Household Optimism: " << household_sentiment_percentage << " Firm Optimism: " << firm_sentiment_percentage << endl;

}



void Public_Info_Board::Post_Job_To_Market(Job * pJob_Offer) {
    cout << "Public board posting job with address: " <<  pJob_Offer << " and wage: "  << pJob_Offer->Get_Wage() << endl;
    pJob_Market->Add_Job_Offer(pJob_Offer);
}

