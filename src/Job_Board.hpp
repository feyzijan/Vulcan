#include <iostream>
#include "Job_Offer.hpp"

class Job_Board{

    public:
    Job_Board();
    Job_Board(Job_Board&);
    ~Job_Board();

    
    // Getter that returns pointer to first instance in Job list
    Job_Offer* Get_Job_List() const; 

    // Remove the highest paying Job offer once its taken
    void Remove_Top_Job_Offer();

    // Add New Job Offer to list, place in proper order
    void Add_Job_Offer(Job_Offer* job_offer);

    

    private:

    Job_Offer job_list[1000]; // Change this number


};