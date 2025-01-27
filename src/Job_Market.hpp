#ifndef JOB_MARKET_HPP
#define JOB_MARKET_HPP



class Job;
#include <iostream>
#include <vector>
#include <algorithm>

#include "Initialization_Parameters.hpp"
#include "Job.hpp"


//#define job_market_size 1000

class Job_Market{

    public:
    // Constructors and destructor
    Job_Market() ;
    Job_Market(Job_Market&);
    ~Job_Market();

    
    // Job Market Implementation Functions
    Job* Get_Top_Job(); 
    void Remove_Top_Job_Offer();
    void Add_Job_Offer(Job* job_offer);
    void Sort_Jobs_by_Wage();
    void Remove_Unwanted_Jobs();

    // Information needed by firms
    void Calculate_Average_Wage();

    // Getters
    long long Get_Size(){ return job_list.size();}
    float Get_Average_Wage(){ return average_wage;}


    private:
    vector<Job*> job_list;
    float average_wage;
};

#endif