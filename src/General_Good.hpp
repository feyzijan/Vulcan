#ifndef GENERAL_GOOD_HPP
#define GENERAL_GOOD_HPP


class Firm_Agent;

class General_Good{

    public:
    // Constructors
    General_Good();
    General_Good(General_Good&);
    ~General_Good();

    //Print methods
    void Print();

    // Overload Operators
    bool operator==(const General_Good& rhs);
    bool operator<=(const General_Good& rhs);
    bool operator>=(const General_Good& rhs);
    bool operator>(const General_Good& rhs);
    bool operator<(const General_Good& rhs);
    bool operator!=(const General_Good& rhs);

    // Getters
    float Get_Price()  {return price;}
    int Get_Quantity() {return quantity;}
    Firm_Agent * Get_Seller() {return pSeller;}

    // Setters
    void Update_Quantity(int quantity_change) {quantity += quantity_change;}
    void Set_Quantity(int new_quantity) {quantity = new_quantity;}
    void Update_Price(float new_price) {price = new_price;}
    

    protected:
    Firm_Agent *  pSeller;
    float price;
    int quantity;
    
};
#endif