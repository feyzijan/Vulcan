#ifndef CAPITAL_GOOD_HPP
#define CAPITAL_GOOD_HPP

// Forward Declaration of Capital Firm Agent

#include "General_Good.hpp"
#include "Initialization_Parameters.hpp"
class Capital_Firm_Agent;



class Capital_Good: public General_Good{

    public:
    Capital_Good(Capital_Firm_Agent *  seller_pointer, float seller_price, int seller_quantity, int life_span);

    // Getters
    Capital_Firm_Agent * GetSeller() {return pSeller;}
    float Get_Value() const {return value;}
    int Get_Depreciation_Period() const {return depreciation_period;}

    // Setters
    void Update_Value(float new_value) {value = new_value;}

    protected:
    Capital_Firm_Agent *  pSeller;
    float value;
    int sold_date;
    int depreciation_period;
    int expiry_date;
};
#endif