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
    Consumer_Good(Consumer_Firm_Agent *  seller_pointer, float seller_price, int seller_quantity, float emissions_per_unit);
    Consumer_Good(Consumer_Firm_Agent *  seller_pointer, float seller_price, int seller_quantity, int seller_sector, float emissions_per_unit);

    // Getters
    Consumer_Firm_Agent* Get_Seller() {return pSeller;}
    float Get_Emission() {return unit_emissions;}
    float Get_Emission_Adjusted_Price(float sensitivity) {return price  + sensitivity * unit_emissions;}

    // Setters
    void Set_Seller_Pointer(Consumer_Firm_Agent* new_seller) {pSeller = new_seller;}
    void Set_Unit_Emission(float new_unit_emission) {unit_emissions = new_unit_emission;}


    protected:
    Consumer_Firm_Agent*  pSeller;
    float unit_emissions;


};
#endif