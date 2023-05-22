#include "Job.hpp"

using namespace std;

//--- Constructors

/* Constructor to initialize Job object - called by Firms
*/
Job::Job(Firm_Agent*  employer, Household_Agent* employee, int wage_offer, int posting_date){
    this->employer = employer;
    this->employee = employee;
    this->wage_offer = wage_offer;
    this->posting_date  = posting_date;
    this->contract_length = standard_employment_contract_length;
    this->expiry_date = posting_date + contract_length; // Inially non expiring
    status = 0;
}

Job::~Job(){
    //cout << "Job object at address " << this << " destroyed" << endl;    
}


// Overloaded Operators, comparisons made based on wage
bool Job::operator==(const Job& rhs){
 return wage_offer == rhs.wage_offer;
}
bool Job::operator<=(const Job& rhs){
    return wage_offer <= rhs.wage_offer;
}
bool Job::operator>=(const Job& rhs){
    return wage_offer >= rhs.wage_offer;
}
bool Job::operator>(const Job& rhs){
    return wage_offer > rhs.wage_offer;
}
bool Job::operator<(const Job& rhs){
    return wage_offer < rhs.wage_offer;
}
bool Job::operator!=(const Job& rhs){
    return wage_offer != rhs.wage_offer;
}

