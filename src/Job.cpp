#include "Job.hpp"


Job::Job(){
    
}


void Job::Set_Prev_Job(Job* job_offer)
{
 prev_offer = job_offer;
}



void Job::Set_Next_Job(Job* job_offer)
{
    next_offer = job_offer;
}