#ifndef GENERAL_GOOD_HPP
#define GENERAL_GOOD_HPP


class Firm_Agent;

class General_Good{

    public:
    // Constructors
    General_Good();
    General_Good(General_Good&);
    ~General_Good();

    // Overload Operators
    bool operator==(const General_Good& rhs);
    bool operator<=(const General_Good& rhs);
    bool operator>=(const General_Good& rhs);
    bool operator>(const General_Good& rhs);
    bool operator<(const General_Good& rhs);
    bool operator!=(const General_Good& rhs);



    // Getters
    float Get_Price() const {return price;}
    int Get_Quantity() const {return quantity;}
    Firm_Agent * Get_Seller() {return pSeller;}

    // Setters
    void Update_Quantity(int quantity_change) {quantity += quantity_change;}
    void Update_Price(float new_price) {price = new_price;}
    

    protected:
    Firm_Agent *  pSeller;
    float price;
    int quantity;
    
};
#endif