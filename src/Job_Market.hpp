#ifndef JOB_MARKET_HPP
#define JOB_MARKET_HPP



class Job;
#include <iostream>
#include <vector>
#include <algorithm>
#include "Job.hpp"
#include "Initialization_Parameters.hpp"

//#define job_market_size 1000

class Job_Market{

    public:
    Job_Market() ;
    Job_Market(Job_Market&){};
    ~Job_Market(){};

    void Print();

    
    // Getter that returns pointer to first instance in Job list
    Job* Get_Top_Job(); 

    // Remove the highest paying Job offer once its taken
    void Remove_Top_Job_Offer();

    // Add New Job Offer to list, place in proper order
    void Add_Job_Offer(Job* job_offer) ;

    void Sort_Jobs_by_Wage();

    

    private:
    std::vector<Job*> job_list;

   

};

#endif