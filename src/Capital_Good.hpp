#ifndef CAPITAL_GOOD_HPP
#define CAPITAL_GOOD_HPP

// Forward Declaration of Capital Firm Agent

#include "General_Good.hpp"
#include "Capital_Firm_Agent.hpp"



class Capital_Good: public General_Good{

    public:
    Capital_Good(Capital_Firm_Agent *  seller_pointer, int price, int quantity);

    // Getters
    Capital_Firm_Agent * GetSeller() {return pSeller;}

    protected:
    Capital_Firm_Agent *  pSeller;

};
#endif