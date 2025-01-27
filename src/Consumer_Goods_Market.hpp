
#ifndef CONSUMER_GOODS_MARKET_HPP
#define CONSUMER_GOODS_MARKET_HPP

#include "Initialization_Parameters.hpp"
#include "Consumer_Good.hpp"
#include "Public_Info_Board.hpp"
#include <vector>
#include <algorithm>
#include <cmath>
#include <cmath>
#include <tuple>


using namespace std;

class Consumer_Goods_Market{

    public:
    // Constructors and destructor
    Consumer_Goods_Market();
    Consumer_Goods_Market(Consumer_Goods_Market&);
    ~Consumer_Goods_Market();

    // Initialization functions
    void Add_Consumer_Good_To_Market(Consumer_Good * cons_good);
    void Divide_Goods_Into_Sectors(vector<Consumer_Firm_Sector*> *pConsumer_Firm_Sector_vector);
    void Divide_Goods_Into_Emission_Adjusted_Price_Levels();
    void Sort_Cons_Goods_By_Sector_By_Price();

    // Market operations
    void Sort_Cons_Goods_By_Sector_By_Price_and_Emissions();
    
    tuple<vector<long long>, vector<long long>, vector<long long> >  Buy_Consumer_Goods_By_Sector_And_Emission
        (const vector<long long>& spending_array, const vector<float>& emission_sensitives_array);
    

    // Round emission sensitivities
    float Round_Emission_Sensitivity(float original_emission_sensitivity);

    // Price level operations
    void Update_Price_Level();

    // Getters 
    const vector<float>& Get_Price_Levels_By_Sector() {return price_level_by_sector;}
    long long Get_Size(){return n_total_goods;}
    float Get_Price_Level(){return price_level;}

    // Setters
    void Set_Price_Level(float price_level) {this->price_level = price_level;}

    // Printing and debugging
    void Print();

    protected:

    vector<Consumer_Good*> cons_goods_list; // goods for one sector
    vector<pair<int, vector<Consumer_Good*> >> cons_good_list_by_sector; // goods for all sectors
    // goods for all emission sensitivity levels, for all sectors
    map<float, vector<pair<int, vector<Consumer_Good*> >> > cons_goods_by_emission_adj_price; 
    
    vector<float> price_level_by_sector;
    vector<long long> n_goods_by_sector;
    vector<float> default_emission_sensitivities;
    vector<float> sector_weights;

    long long n_total_goods;
    float price_level;

};


#endif