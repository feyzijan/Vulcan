#ifndef PUBLIC_INFO_BOARD_HPP
#define PUBLIC_INFO_BOARD_HPP

#endif

#include "Capital_Good.hpp"
#include "Capital_Firm_Agent.hpp" 


 
class Capital_Goods_Market{

    public:
     
    Capital_Goods_Market();
    Capital_Goods_Market(Capital_Goods_Market&);
    ~Capital_Goods_Market();

    void Add_Capital_Good_To_Market(Capital_Good * cap_good);


    private:

    Capital_Good cap_goods_array[1000];


};
