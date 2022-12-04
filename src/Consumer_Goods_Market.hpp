#include "Consumer_Good.hpp"
#include "Consumer_Firm_Agent.hpp" 
#ifndef PUBLIC_INFO_BOARD_HPP
#define PUBLIC_INFO_BOARD_HPP

#endif
 
 
class Consumer_Goods_Market{

    public:
     
    Consumer_Goods_Market();
    Consumer_Goods_Market(Consumer_Goods_Market&);
    ~Consumer_Goods_Market();

    void Add_Consumer_Good_To_Market(Consumer_Good * cons_good);
    

    private:

    Consumer_Good cons_goods_array[1000];


};

