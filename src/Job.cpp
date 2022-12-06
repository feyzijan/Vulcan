#include "Job.hpp"

using namespace std;

Job::Job(){

    
}


Job::Job(Firm_Agent*  firm, int wage_offer, int posting_date){
    wage_offer = wage_offer;
    job_offering_firm = firm;
    posting_date  = posting_date;
    prev_offer = nullptr;
    next_offer = nullptr;
}


void Job::Set_Prev_Job(Job* job_offer){
 prev_offer = job_offer;
}



void Job::Set_Next_Job(Job* job_offer){
    next_offer = job_offer;
}


void Job::Print() const{
    cout << "\n------ Job Object at address : " << this << endl;
    cout << "Employer: " << job_offering_firm << " Post Date: " << posting_date<< " Wage Offer: " << wage_offer << endl;
    cout << "Previous Job Linked*: " << prev_offer << " Next Job Linked*: " << next_offer << endl;
    cout << "--------------------------------------" << endl;

}