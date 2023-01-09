#ifndef JOB_HPP
#define JOB_HPP


class Household_Agent;
class Firm_Agent;

#include <iostream>
//#include "Firm_Agent.hpp"
#include "Household_Agent.hpp"



class Job{

    public:
    // Constructors
    Job(){};
    Job(Firm_Agent*  employer, Household_Agent* employee, int wage_offer, int posting_date);

    Job(Job&); //Copy constructor 
    
    ~Job(); // Destructor

    // Print info on job
    void Print() const;

    //Getters
    int Get_Wage() const {return wage_offer;} 
    int Get_Posting_Date() const {return posting_date;}
    Firm_Agent* Get_Employer() const {return employer;} 
    Household_Agent* Get_Employee() const {return employee;}


    //Setters
    void Update_Wage(int new_wage);


    private:
    Firm_Agent* employer;
    Household_Agent* employee;
    int wage_offer;
    int posting_date;




};

#endif