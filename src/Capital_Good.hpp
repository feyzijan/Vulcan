#ifndef CAPITAL_GOOD_HPP
#define CAPITAL_GOOD_HPP

#include <iostream>

#include "General_Good.hpp"
#include "Initialization_Parameters.hpp"

class Capital_Firm_Agent; // Forward Declaration of Capital Firm Agent


using namespace std;
class Capital_Good: public General_Good{

    public:
    Capital_Good(Capital_Firm_Agent *  seller_pointer, float seller_price, long long seller_quantity, int life_span);
    Capital_Good(const Capital_Good& other);  // Copy constructor

    // Depreciation
    void Depreciate();
    
    // Getters
    Capital_Firm_Agent * Get_Seller() {return pSeller;}
    float Get_Value() const {return value;}
    int Get_Depreciation_Period() const {return depreciation_period;}
    bool Check_Depreciation() const {return depreciated;}

    // Setters
    void Update_Value(float new_value) {value = new_value;}
    void Set_Seller_Pointer(Capital_Firm_Agent * new_seller) {pSeller = new_seller;}

    protected:
    Capital_Firm_Agent *  pSeller;
    float value;
    int sold_date;
    int depreciation_period;
    int expiry_date;
    bool depreciated;
};
#endif