#ifndef JOB_OFFER_HPP
#define JOB_OFFER_HPP

#include "Firm_Agent.hpp"

//TODO: Convert Job into a LinkedList struct


/* Job offer objects will hold info on the date of posting, wage, employer, 
and a pointer to the previous or next job offer iin the market
*/


class Job_Offer{

    public:
    Job_Offer();

    // Constructor
    Job_Offer(Firm_Agent*  firm, int wage_offer, int posting_date); //Constructor

    Job_Offer(Job_Offer&); //Copy constructor 
    
    ~Job_Offer(); // Destructor

    //Getters
    int Get_Wage_Offer() const {return wage_offer;} 
    int Get_Posting_Date() const {return posting_date;}
    Job_Offer* Get_Prev_Job() const {return prev_offer;} 
    Job_Offer* Get_Next_Job() const {return next_offer;}

    //Setters
    void Set_Prev_Job(Job_Offer* job_offer);
    void Set_Next_Job(Job_Offer* job_offer);

    private:
    Firm_Agent* job_offering_firm;
    int wage_offer;
    int posting_date;
    Job_Offer* next_offer;
    Job_Offer* prev_offer;



};

#endif