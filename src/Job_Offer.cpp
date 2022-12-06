#include "Job_Offer.hpp"


Job_Offer::Job_Offer(){
    
}


void Job_Offer::Set_Prev_Job(Job_Offer* job_offer)
{
 prev_offer = job_offer;
}



void Job_Offer::Set_Next_Job(Job_Offer* job_offer)
{
    next_offer = job_offer;
}