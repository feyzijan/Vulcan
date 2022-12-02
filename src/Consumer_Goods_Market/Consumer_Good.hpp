#include "Consumer_Firm.hpp"


class Consumer_Good{

    public:
    Consumer_Good(Consumer_Firm_Agent *  seller_pointer, int seller_price, int seller_quantity);
    Consumer_Good(Consumer_Good&);
    ~Consumer_Good();

    int GetPrice() const {return price;}
    Consumer_Firm_Agent * GetSeller() {return pSeller;}

    protected:
    int price;
    int quantity;
    Consumer_Firm_Agent *  pSeller;




};