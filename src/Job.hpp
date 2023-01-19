#ifndef JOB_HPP
#define JOB_HPP


class Household_Agent;
class Firm_Agent;

#include <iostream>
//#include "Firm_Agent.hpp"
//#include "Household_Agent.hpp"



class Job{

    public:
    // Constructors
    Job(){};
    Job(Firm_Agent*  employer, Household_Agent* employee, int wage_offer, int posting_date);

    Job(Job&); //Copy constructor 
    
    ~Job(); // Destructor

    // Print info on job
    void Print() const;

    // Overload Operators
    bool operator==(const Job& rhs);
    bool operator<=(const Job& rhs);
    bool operator>=(const Job& rhs);
    bool operator>(const Job& rhs);
    bool operator<(const Job& rhs);
    bool operator!=(const Job& rhs);


    //Getters
    int Get_Wage() const {return wage_offer;} 
    int Get_Posting_Date() const {return posting_date;}
    Firm_Agent* Get_Employer() const {return employer;} 
    Household_Agent* Get_Employee() const {return employee;}
    bool Get_Status() const {return taken;}


    //Setters
    void Update_Wage(int new_wage);
    void Set_Employee(Household_Agent* pemployee);
    void Update_Status(bool status);


    private:
    Firm_Agent* employer;
    Household_Agent* employee;
    int wage_offer;
    int posting_date;
    bool taken;




};

#endif