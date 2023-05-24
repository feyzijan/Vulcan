
#ifndef CAPITAL_GOODS_MARKET_HPP
#define CAPITAL_GOODS_MARKET_HPP


#include "Capital_Good.hpp"


#include "vector"
#include "algorithm"
 
class Capital_Goods_Market{

    public:
    // Constructors and destructor
    Capital_Goods_Market();
    Capital_Goods_Market(Capital_Goods_Market&);
    ~Capital_Goods_Market();

    // Market operations
    void Add_Capital_Good_To_Market(Capital_Good * cap_good);
    void Sort_Capital_Goods_By_Price();
    int Get_Cost_For_Given_Quantity(int q_desired);
    int* Buy_Capital_Goods(int q_desired);
    void Update_Price_Level();
    void Reset_Market(); 

    // Getters
    float Get_Price_Level(){return price_level;}
    int Get_Size(){return n_total_goods;}
    float Get_Price_Level(){return price_level;}

    // Setters
    void Set_Price_Level(float price_level) {this->price_level = price_level;}

    private:
    vector<Capital_Good*> cap_goods_list;
    int n_total_goods;
    int total_weighed_price;
    float price_level;

};

#endif