
#ifndef CONSUMER_GOODS_MARKET_HPP
#define CONSUMER_GOODS_MARKET_HPP

#include "Consumer_Good.hpp"

#include "vector"
#include "algorithm"
 
class Consumer_Goods_Market{

    public:
    // Constructors and destructor
    Consumer_Goods_Market();
    Consumer_Goods_Market(Consumer_Goods_Market&);
    ~Consumer_Goods_Market();

    // Printing and Debugging
    void Print();

    // Market operations
    void Add_Consumer_Good_To_Market(Consumer_Good * cons_good);
    void Sort_Consumer_Goods_By_Price();
    int Buy_Consumer_Goods(int budget);



    // Getters
    float Get_Price_Level() {return price_level;}
    

    private:
    std::vector<Consumer_Good*> cons_goods_list;
    int n_total_goods;
    float total_weighed_price;
    float price_level;

};


#endif