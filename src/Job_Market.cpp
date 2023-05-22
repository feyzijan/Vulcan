#include "Job_Market.hpp"

using namespace std;


// Constructor and destructors
Job_Market::Job_Market(){
    average_wage = firm_cons_init_wage_offer_mean;
}


Job_Market::~Job_Market(){}
Job_Market::Job_Market(Job_Market&){}



// Job Market Implementation Functions

/* Return job with the highest wage
*/
Job* Job_Market::Get_Top_Job(){
    
    if (job_list.empty()) {
        //cout << "Job list is empty!" <<endl;
        return NULL; 
    }
    else{
        //cout << "Returning job" <<endl;
        return job_list.front();
    } 
}


/*Remove the highest paying Job offer once its taken
*/
void Job_Market::Remove_Top_Job_Offer(){
    //cout << "Removing top job offer" <<endl;
    job_list.erase(job_list.begin());
}

/* Add new Job to Market  TODO: Implement sorted insertion
*/
void Job_Market::Add_Job_Offer(Job* job_offer) { 
    //cout << "Job Market adding job with address: "  << job_offer << " with wage " << job_offer->Get_Wage() << endl;
    job_list.push_back(job_offer); 
}

/* Sort the job market by wage
*/
void Job_Market::Sort_Jobs_by_Wage(){
    std::sort(job_list.begin(), job_list.end(),
    [](const Job* j1,const Job*  j2) -> bool {
    return j1->Get_Wage() > j2->Get_Wage() ;});
}

/* Function to remove jobs from the market that have a status = -1
*/
void Job_Market::Remove_Unwanted_Jobs(){
    //cout << "Removing jobs from the market" <<endl;
    job_list.erase(std::remove_if(job_list.begin(), job_list.end(), [](Job* job) {
        if (job->Get_Status() == -3) {
            delete job; // Free memory of removed object
            return true;
        }
        return false;
    }), job_list.end());
}



//--------------------------
// Information gathering functions
/* Calculate average weight in the market
*/
void Job_Market::Calculate_Average_Wage(){
   float total_wage = 0.0;
    for (Job* job : job_list) {
        total_wage += job->Get_Wage();
    }
    average_wage = total_wage / job_list.size();
}

