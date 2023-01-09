#include "Job.hpp"

using namespace std;

Job::Job(){

    
}


Job::Job(Firm_Agent*  employer, Household_Agent* employee, int wage_offer, int posting_date){
    
    this->employer = employer;
    this->employee = employee;
    this->wage_offer = wage_offer;
    this->posting_date  = posting_date;
}




void Job::Print() const{
    cout << "\n------ Job Object at address : " << this << endl;
    cout << "Employer: " << employer << "Employee: " << employee <<  "Post Date: " << posting_date<< " Wage Offer: " << wage_offer << endl;
    cout << "--------------------------------------" << endl;

}