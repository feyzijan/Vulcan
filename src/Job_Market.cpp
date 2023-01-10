#include "Job_Market.hpp"


Job_Market::Job_Market(){
    Job * job_offers[job_market_size] = {};
}


void Job_Market::Print(int n){
    //print array
    for(int i = 0; i<n; i++){
        job_offers[i]->Print();
    }

}




Job* Job_Market::Get_Top_Job(){
    return job_offers[0];
}


//TODO: Test this loop,

void Job_Market::Remove_Top_Job_Offer(){
    for (int i=0;i<job_market_size;i++){
        if (job_offers[i] == nullptr){
            break;
        }
        job_offers[i] = job_offers[i+1];
    }

}


// Sort after each insertion or insert to the correct place
void Job_Market::Add_Job_Offer(Job* job_offer) {

    // to the vector
    job_list.push_back(job_offer); 

    // To the array
    for (int i=0;i<sizeof(job_offers);i++){
        if (job_offers[i] == NULL){
            job_offers[i] = job_offer;
        }
    }


    //std::sort(job_list.begin(), job_list.end(),
    //[] (const Job& lhs, const Job& rhs) -> bool {return lhs < rhs;});


}
