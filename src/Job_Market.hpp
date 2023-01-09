#ifndef JOB_MARKET_HPP
#define JOB_MARKET_HPP


class Job;
#include <iostream>
#include "Job.hpp"
//#include "Initialization_Parameters.hpp"



class Job_Market{

    public:
    Job_Market();
    Job_Market(Job_Market&);
    ~Job_Market();

    
    // Getter that returns pointer to first instance in Job list
    Job* Get_Job_List() const; 

    // Remove the highest paying Job offer once its taken
    void Remove_Top_Job_Offer();

    // Add New Job Offer to list, place in proper order
    void Add_Job_Offer(Job* job_offer);

    

    private:
    Job * head_null_job;
   

};

#endif