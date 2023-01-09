#ifndef JOB_HPP
#define JOB_HPP


#include <iostream>
#include "Firm_Agent.hpp"
#include "Household_Agent.hpp"

//TODO: Convert Job into a LinkedList struct


/* Job offer objects will hold info on the date of posting, wage, employer, 
and a pointer to the previous or next job offer iin the market
*/



class Job{

    public:
    // Constructors
    Job();
    

    Job(Firm_Agent*  employer, Household_Agent* employee, int wage_offer, int posting_date); //Constructor

    Job(Job&); //Copy constructor 
    
    ~Job(); // Destructor

    //Print
    void Print() const;

    //Getters
    int Get_Wage_Offer() const {return wage_offer;} 
    int Get_Posting_Date() const {return posting_date;}


    //Setters


    private:
    Firm_Agent* employer;
    Household_Agent* employee;
    int wage_offer;
    int posting_date;




};

#endif