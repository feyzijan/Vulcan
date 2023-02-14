#ifndef CONSUMER_GOOD_HPP
#define CONSUMER_GOOD_HPP


#include <iostream>
#include "General_Good.hpp"

class Consumer_Firm_Agent;


using namespace std;
class Consumer_Good: public General_Good{

    public:
    // Constructor
    Consumer_Good(Consumer_Firm_Agent*  seller_pointer, float seller_price, int seller_quantity);

    //Printing and Debugging
    void Print();
    // Getters
    Consumer_Firm_Agent* GetSeller() {return pSeller;}
    int GetQuantity() {return quantity;}
    float GetPrice() {return price;}
    

    protected:
    Consumer_Firm_Agent*  pSeller;

};
#endif