
#ifndef CAPITAL_GOODS_MARKET_HPP
#define CAPITAL_GOODS_MARKET_HPP


#include "Capital_Good.hpp"

#include "vector"
#include "algorithm"

using namespace std;

class Capital_Goods_Market{

    public:
    // Constructors and destructor
    Capital_Goods_Market();
    Capital_Goods_Market(Capital_Goods_Market&);
    ~Capital_Goods_Market();

    // Market operations
    void Add_Capital_Good_To_Market(Capital_Good * cap_good);
    void Sort_Capital_Goods_By_Price();
    long long Get_Cost_For_Given_Quantity(int q_desired);
    long long* Buy_Capital_Goods(int q_desired);
    void Update_Price_Level();
    void Reset_Market(); 

    // Getters
    float Get_Price_Level(){return price_level;}
    long long Get_Size(){return n_total_goods;}
    
    // Setters
    void Set_Price_Level(float price_level) {this->price_level = price_level;}

    // Printing and debugging
    void Print();

    private:
    vector<Capital_Good*> cap_goods_list;
    long long n_total_goods;
    double total_weighed_price;
    float price_level;

};

#endif