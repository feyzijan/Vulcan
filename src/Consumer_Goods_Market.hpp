
#ifndef CONSUMER_GOODS_MARKET_HPP
#define CONSUMER_GOODS_MARKET_HPP



#include "Consumer_Good.hpp"
#include "Consumer_Firm_Agent.hpp" 

 
 
class Consumer_Goods_Market{

    public:
     
    Consumer_Goods_Market();
    Consumer_Goods_Market(Consumer_Goods_Market&);
    ~Consumer_Goods_Market();

    void Add_Consumer_Good_To_Market(Consumer_Good * cons_good);
    

    private:

    Consumer_Good cons_goods_array[1000];


};


#endif