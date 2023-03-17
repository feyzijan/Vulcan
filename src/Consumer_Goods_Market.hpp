
#ifndef CONSUMER_GOODS_MARKET_HPP
#define CONSUMER_GOODS_MARKET_HPP

#include "Consumer_Good.hpp"
#include "vector"
#include "algorithm"
#include <cmath>
#include <tuple>


using namespace std;

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
    void Divide_Goods_Into_Sectors(int* sector_id_list, int n_sectors);
    void Sort_Consumer_Goods_By_Price();
    void Sort_Cons_Goods_By_Sector_By_Price();
    pair<int, int>  Buy_Consumer_Goods(int budget);
    pair<vector<float>, vector<int>> Buy_Consumer_Goods_By_Sector(int budget, const vector<int>& spending_array);
    
    
    void Update_Price_Level();
    void Update_Price_Level_by_Sector();

    void Reset_Market(); 



    // Getters
    float Get_Price_Level() {return price_level;}
    float Get_Price_Level_by_Sector( int sector_id) {return price_level_by_sector[sector_id];}


    private:
    vector<Consumer_Good*> cons_goods_list;
    vector<pair<int, vector<Consumer_Good*>>> cons_good_list_by_sector;
    vector<float> price_level_by_sector;
    vector<int> n_goods_by_sector;

    int n_total_goods;
    float total_weighed_price;
    float price_level;

};


#endif