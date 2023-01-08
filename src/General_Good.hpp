#ifndef GENERAL_GOOD_HPP
#define GENERAL_GOOD_HPP


#include "Firm_Agent.hpp"


class General_Good{

    public:
    General_Good();
    General_Good(Firm_Agent *  seller_pointer, int price, int quantity);
    General_Good(General_Good&);
    ~General_Good();

    int GetPrice() const {return price;}
    Firm_Agent * GetSeller() {return pSeller;}

    protected:
    int price;
    int quantity;

    Firm_Agent *  pSeller;




};
#endif