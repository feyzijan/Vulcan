
#ifndef INITIALIZATION_FUNCTIONS_HPP
#define  INITIALIZATION_FUNCTIONS_HPP


#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <utility>


#include "Firm_Agent.hpp"
#include "Consumer_Firm_Agent.hpp"
#include "Capital_Firm_Agent.hpp"
#include "Household_Agent.hpp"
#include "Public_Info_Board.hpp"
#include "Initialization_Parameters.hpp"
#include "Random_Functions.hpp"


using namespace std;


// Function to do the complete intiialization for all households and firms - calls the functions below in proper order
void Initialize_Households_Firms_Jobs( vector<Household_Agent*> *pHousehold_vector, vector<Consumer_Firm_Agent*>* pConsumer_Firm_vector,
 vector<Capital_Firm_Agent*> *pCapital_Firm_vector,  Public_Info_Board* pPublic_Board, Job_Market* pJob_Market,
Consumer_Goods_Market* pConsumer_Goods_Market, Capital_Goods_Market* pCapital_Goods_Market, Bank_Agent* pBank);


// Functions to initialize Consumer and Capital Firms
void Initialize_Consumer_Firms(vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, Public_Info_Board* pPublic_Board, int size);
void Post_Initial_Job_Offers_Cons(vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, int size);
void Check_Initial_Job_Offers_Cons(vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, int size);

void Initialize_Capital_Firms(vector<Capital_Firm_Agent*> *pCapital_Firm_vector, Public_Info_Board* pPublic_Board, int size);
void Post_Initial_Job_Offers_Cap(vector<Capital_Firm_Agent*> *pCapital_Firm_vector, int size);
void Check_Initial_Job_Offers_Cap(vector<Capital_Firm_Agent*> *pCapital_Firm_vector, vector<Firm_Agent*> pFirm_vector);

// Functions to initialize Households
void Initialize_Households(vector<Household_Agent*> *pHousehold_vector, Public_Info_Board* pPublic_Board, int size);
void Initialize_Household_Jobs(vector<Household_Agent*> *pHousehold_vector,  int size);
void Initialize_Household_Firm_Owners(vector<Household_Agent*> *pHousehold_vector, vector<Consumer_Firm_Agent*>* pConsumer_Firm_vector,
 vector<Capital_Firm_Agent*> *pCapital_Firm_vector);

// Function to set up Job market at t=0
void Initialize_Job_Market(vector<Household_Agent*> *pHousehold_vector,
    vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, vector<Capital_Firm_Agent*> *pCapital_Firm_vector,
    Public_Info_Board* pPublic_Info_Board);

// Function to set up Consumer Goods market at t=0
void Initialize_Cons_Cap_Goods_Markets( vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, vector<Capital_Firm_Agent*> *pCapital_Firm_vector,
    Consumer_Goods_Market* pConsumer_Goods_Market, Capital_Goods_Market* pCapital_Goods_Market,Public_Info_Board* pPublic_Info_Board);


// Initialize Sectors
int Create_Sectors(vector<Consumer_Firm_Sector*> *pConsumer_Firm_Sector_vector,std::vector<std::pair<int, float>>* pFirm_Weighing_vector);

// Allocate firms to sectors
void Allocate_Firms_to_Sectors(vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector,
 vector<Consumer_Firm_Sector*> *pConsumer_Firm_Sector_vector,std::vector<std::pair<int, float>>* pFirm_Weighing_vector);


#endif