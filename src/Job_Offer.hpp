#include "Consumer_Firm.hpp"

class Job_Offer{

    public:
    Job_Offer();
    Job_Offer(int wage_offer, Consumer_Firm_Agent*  firm); //Constructor

    Job_Offer(Job_Offer&); //Copy constructor
    
    ~Job_Offer(); // Destructor

    private:
    Consumer_Firm_Agent* offering_firm;
    int wage_offer;



};