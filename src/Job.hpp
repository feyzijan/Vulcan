#ifndef JOB_HPP
#define JOB_HPP


class Household_Agent;
class Firm_Agent;

#include <iostream>
//#include "Firm_Agent.hpp"
//#include "Household_Agent.hpp"

#include "Initialization_Parameters.hpp"


class Job{

    public:
    // Constructors and Destructor
    Job(Firm_Agent*  employer, Household_Agent* employee, int wage_offer, int posting_date);
    Job(Job&); 
    Job();
    ~Job();

    // Overload Operators
    bool operator==(const Job& rhs);
    bool operator<=(const Job& rhs);
    bool operator>=(const Job& rhs);
    bool operator>(const Job& rhs);
    bool operator<(const Job& rhs);
    bool operator!=(const Job& rhs);

    // Getters
    int Get_Wage() const {return wage_offer;} 
    int Get_Posting_Date() const {return posting_date;}
    int Get_Expiry_Date() const {return expiry_date;}
    int Get_Contract_Length() const {return contract_length;}
    int Get_Status() {return status;}
    bool Get_Expiry_Status() const {return (global_date >= expiry_date);}
    Firm_Agent* Get_Employer() const {return employer;} 
    Household_Agent* Get_Employee() const {return employee;}
    

    //Setters
    void Update_Wage(int new_wage){wage_offer = new_wage;}
    void Set_Employee(Household_Agent* pemployee) {employee = pemployee;}
    void Update_Status(int status) { this->status = status;} 
    /* 1: Posted job has been taken by household,
       0: Posted job still on the market : default status when object is created
      -1: Firm notifies worker they have been fired
      -2: Worker notifies firm they quite
      -3: Firm requested the job be removed from market
    */
    void Set_Expiry_Date() {expiry_date = global_date + contract_length;}
    

    protected:
    Firm_Agent* employer;
    Household_Agent* employee;
    int wage_offer;
    int posting_date;
    int contract_length;
    int expiry_date;
    int status;
};

#endif