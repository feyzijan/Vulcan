#ifndef GENERAL_GOOD_HPP
#define GENERAL_GOOD_HPP


class Firm_Agent;

class General_Good{

    public:
    // Constructors
    General_Good() {};
    General_Good(General_Good&) {};
    ~General_Good() {};

    // Overload Operators
    bool operator==(const General_Good& rhs);
    bool operator<=(const General_Good& rhs);
    bool operator>=(const General_Good& rhs);
    bool operator>(const General_Good& rhs);
    bool operator<(const General_Good& rhs);
    bool operator!=(const General_Good& rhs);

    // Getters
    float Get_Price()  {return price;}
    long long Get_Quantity() {return quantity;}
    Firm_Agent * Get_Seller() {return pSeller;}
    int Get_Sector_ID() {return sector_id;}


    // Setters
    void Add_Quantity(long long quantity_change) {quantity += quantity_change;}
    void Set_Quantity(long long new_quantity) {quantity = new_quantity;}
    void Set_Price(float new_price) {price = new_price;}
    void Set_Sector_ID(int sector) {sector_id = sector;}
    
    protected:
    Firm_Agent * pSeller;
    float price;
    long long quantity;
    int sector_id;
    
};
#endif