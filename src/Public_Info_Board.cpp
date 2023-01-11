
#include "Public_Info_Board.hpp"


using namespace std;

Job* Public_Info_Board::Get_Top_Job() {

    Job * job = pJob_Market->Get_Top_Job();
    return job;
}




void Public_Info_Board::Remove_Top_Job_Offer(){
    std::cout << "Top job offer taken" <<std::endl;
    pJob_Market->Remove_Top_Job_Offer();
}


void Public_Info_Board::Take_Job(Job* pJob_Offer) {
    // Remove from market
    Public_Info_Board::Remove_Top_Job_Offer();
    // Notify employer
    Firm_Agent* employer = pJob_Offer->Get_Employer();
    //employer->Hire_Worker(pJob_Offer);


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

