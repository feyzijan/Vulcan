#include "Job_Market.hpp"

using namespace std;

Job_Market::Job_Market(){

}


void Job_Market::Print(){
    cout << "Printing Job Market with " << job_list.size()  << " jobs" << endl;
    for (auto i = job_list.begin(); i != job_list.end(); ++i) 
        cout << "Job with address: " << *i << " with wage: " << (*i)->Get_Wage() << endl; 
}





Job* Job_Market::Get_Top_Job(){
    
    if (job_list.empty()) {
        cout << "Job list is empty!" <<endl;
        return NULL; 
    }
    else{
        cout << "Returning job" <<endl;
        return job_list.front();
    } 
}


//TODO: Test this loop,

void Job_Market::Remove_Top_Job_Offer(){
    job_list.erase(job_list.begin());
}


// Implement sorted insertion
void Job_Market::Add_Job_Offer(Job* job_offer) {
    
    //cout << "Job Market adding job with address: "  << job_offer << " with wage " << job_offer->Get_Wage() << endl;

    // to the vector
    job_list.push_back(job_offer); 

}


void Job_Market::Sort_Jobs_by_Wage(){
    
    //std::sort(job_list.begin(), job_list.end(),
    //[] (const Job& lhs, const Job& rhs) -> bool {return lhs < rhs;});

    std::sort(job_list.begin(), job_list.end(),
    [](const Job* j1,const Job*  j2) -> bool {
    return j1->Get_Wage() > j2->Get_Wage() ;});
}


void Job_Market::Print_Size(){
    cout << "Job market has " << job_list.size() << " jobs" << endl;
}