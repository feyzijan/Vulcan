#ifndef JOB_HPP
#define JOB_HPP

#include "Firm_Agent.hpp"
#include <iostream>

//TODO: Convert Job into a LinkedList struct


/* Job offer objects will hold info on the date of posting, wage, employer, 
and a pointer to the previous or next job offer iin the market
*/


class Job{

    public:
    // Constructors
    Job();
    

    Job(Firm_Agent*  firm, int wage_offer, int posting_date); //Constructor


    Job(Firm_Agent*  firm, int wage_offer, int posting_date, Job* prev); //Constructor

    Job(Job&); //Copy constructor 
    
    ~Job(); // Destructor

    //Print
    void Print() const;

    //Getters
    int Get_Wage_Offer() const {return wage_offer;} 
    int Get_Posting_Date() const {return posting_date;}
    Job* Get_Prev_Job() const {return prev_offer;} 
    Job* Get_Next_Job() const {return next_offer;}

    //Setters
    void Set_Prev_Job(Job* job_offer);
    void Set_Next_Job(Job* job_offer);

    private:
    Firm_Agent* job_offering_firm;
    int wage_offer;
    int posting_date;
    Job* next_offer;
    Job* prev_offer;



};

#endif