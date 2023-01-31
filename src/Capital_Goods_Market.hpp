
#ifndef CAPITAL_GOODS_MARKET_HPP
#define CAPITAL_GOODS_MARKET_HPP


#include "Capital_Good.hpp"


#include "vector"
 
class Capital_Goods_Market{

    public:
     
    Capital_Goods_Market();
    Capital_Goods_Market(Capital_Goods_Market&);
    ~Capital_Goods_Market();

    void Add_Capital_Good_To_Market(Capital_Good * cap_good);

    float Get_Price_Level();


    private:
    std::vector<Capital_Good*> cap_goods_list;
    int n_total_goods;
    int total_weighed_price;
    float price_level;


};

#endif