#ifndef CONSUMER_GOOD_HPP
#define CONSUMER_GOOD_HPP


#include <iostream>
#include "General_Good.hpp"

class Consumer_Firm_Agent;


using namespace std;
class Consumer_Good: public General_Good{

    public:
    // Constructor
    Consumer_Good(Consumer_Firm_Agent*  seller_pointer, float seller_price, int seller_quantity, int seller_sector);
    Consumer_Good(Consumer_Firm_Agent *  seller_pointer, float seller_price, int seller_quantity);
    Consumer_Good(Consumer_Firm_Agent *  seller_pointer, float seller_price, int seller_quantity, int seller_sector, float emissions_per_unit);

    //Printing and Debugging
    void Print();
    // Getters
    Consumer_Firm_Agent* GetSeller() {return pSeller;}
    float Get_Unit_Emissions() {return unit_emissions;}


    protected:
    Consumer_Firm_Agent*  pSeller;
    float unit_emissions;


};
#endif