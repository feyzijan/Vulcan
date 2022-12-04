#include "Consumer_Firm.hpp"

class Job_Offer{

    public:
    Job_Offer();

    // Constructor
    Job_Offer(Firm_Agent*  firm, int wage_offer, int posting_date); //Constructor

    Job_Offer(Job_Offer&); //Copy constructor
    
    ~Job_Offer(); // Destructor

    int Get_Wage_Offer() const; 

    private:
    Firm_Agent* job_offering_firm;
    int wage_offer;
    int posting_date;


};