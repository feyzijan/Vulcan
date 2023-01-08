#ifndef CONSUMER_GOOD_HPP
#define CONSUMER_GOOD_HPP

 
#include "General_Good.hpp"
#include "Consumer_Firm_Agent.hpp" 


class Consumer_Good: public General_Good{

    public:
    Consumer_Good(Consumer_Firm_Agent*  seller_pointer, int seller_price, int seller_quantity);

    // Getters
    Consumer_Firm_Agent* GetSeller() {return pSeller;}

    protected:
    Consumer_Firm_Agent*  pSeller;

};
#endif