#include "Job.hpp"

using namespace std;



Job::Job(Firm_Agent*  employer, Household_Agent* employee, int wage_offer, int posting_date){
    this->employer = employer;
    this->employee = employee;
    this->wage_offer = wage_offer;
    this->posting_date  = posting_date;
    taken = 0;
}




void Job::Print() const{
    cout << "\n------ Job Object at address : " << this << endl;
    cout << "Employer address: " << employer << " Employee address: " << employee << endl;
    cout << "Post Date: " << posting_date<< " Wage Offer: " << wage_offer << " Taken: " << taken << endl;
    cout << "--------------------------------------" << endl;

}

void Job::Update_Wage(int new_wage){
    this->wage_offer = new_wage;
}

void Job::Set_Employee(Household_Agent* pemployee){
    this->employee = pemployee;
}

void Job::Update_Status(bool status){
    taken = status;
}

// Overloaded Operators, comparison based on wage

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