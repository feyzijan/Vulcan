
#ifndef CONSUMER_GOODS_MARKET_HPP
#define CONSUMER_GOODS_MARKET_HPP



#include "Consumer_Good.hpp"

 
#include "vector"
 
class Consumer_Goods_Market{

    public:
     
    Consumer_Goods_Market();
    Consumer_Goods_Market(Consumer_Goods_Market&);
    ~Consumer_Goods_Market();

    void Add_Consumer_Good_To_Market(Consumer_Good * cons_good);

    float Get_Price_Level();
    

    private:
    std::vector<Consumer_Good*> cons_goods_list;
    int total_weighed_price;
    int n_total_goods;
    float price_level;



};


#endif