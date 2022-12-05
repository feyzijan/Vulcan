#ifndef CONSUMER_GOOD_HPP
#define CONSUMER_GOOD_HPP

 
 


class Consumer_Good{

    public:
    Consumer_Good(Consumer_Firm_Agent *  seller_pointer, int seller_price, int seller_quantity);
    Consumer_Good(Consumer_Good&);
    ~Consumer_Good();

    // Getters
    int GetPrice() const {return price;}
    int GetQuantity() const { return quantity;}
    Consumer_Firm_Agent * GetSeller() {return pSeller;}
    // Setters
    void SetPrice(int new_price) { price = new_price;}
    void SetQuantity(int new_quantity)  { quantity = new_quantity;}


    protected:
    int price;
    int quantity;
    Consumer_Firm_Agent *  pSeller;

};
#endif