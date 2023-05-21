
#ifndef CONSUMER_GOODS_MARKET_HPP
#define CONSUMER_GOODS_MARKET_HPP

#include "Consumer_Good.hpp"
#include "Initialization_Parameters.hpp"
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
    void Divide_Goods_Into_Sectors(int n_sectors);
    void Sort_Consumer_Goods_By_Price();
    void Sort_Cons_Goods_By_Sector_By_Price();
    void Sort_Cons_Goods_By_Sector_By_Price_and_Emissions();
    
    pair<vector<float>, vector<int>> Buy_Consumer_Goods_By_Sector(int budget, const vector<float>& spending_array);
    pair<vector<float>, vector<int>> Buy_Consumer_Goods_By_Sector_And_Emission(int budget, const vector<float>& spending_array, const vector<float>& emission_sensitives_array);
    

    // Price level operations
    void Update_Price_Level_by_Sector();

    void Reset_Market(); 



    // Price level gettter
    const vector<float>& Get_Price_Levels() {return price_level_by_sector;}


    private:
    vector<Consumer_Good*> cons_goods_list;
    vector<pair<int, vector<Consumer_Good*>>> cons_good_list_by_sector;
    // Create a map that maps an int to the cons_good_list_by_sector vector
    
    map<float, vector<pair<int, vector<Consumer_Good*>>>> cons_goods_by_emission_adj_price;
    vector<float> price_level_by_sector;
    vector<int> n_goods_by_sector;
    vector<float> default_emission_sensitivities;


    int n_total_goods;
    float total_weighed_price;
    float price_level;

};


#endif