#ifndef GENERAL_GOOD_HPP
#define GENERAL_GOOD_HPP


class Firm_Agent;

class General_Good{

    public:
    General_Good() {};
    General_Good(Firm_Agent *  seller_pointer, float seller_price, int seller_quantity);
    
    General_Good(General_Good&);

    ~General_Good() {};

    int Get_Price() const {return price;}
    int Get_Quantity() const {return quantity;}
    Firm_Agent * Get_Seller() {return pSeller;}

    

    protected:
    float price;
    int quantity;

    Firm_Agent *  pSeller;




};
#endif