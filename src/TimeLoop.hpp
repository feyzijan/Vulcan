#ifndef TIMELOOP_HPP
#define TIMELOOP_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "Initialization_Parameters.hpp"
#include "Firm_Agent.hpp"
#include "Consumer_Firm_Agent.hpp"
#include "Capital_Firm_Agent.hpp"
#include "Household_Agent.hpp"
#include "Public_Info_Board.hpp"
#include "Random_Functions.hpp"
#include "Consumer_Goods_Market.hpp"
#include "Capital_Goods_Market.hpp"
#include "Bank_Agent.hpp"
#include "Job_Market.hpp"


void Time_Step_1(vector<Household_Agent*> *pHousehold_vector, vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, 
vector<Capital_Firm_Agent*> *pCapital_Firm_vector, vector<Firm_Agent*> *pFirm_vector, Public_Info_Board* pPublic_Info_Board, Job_Market* pJob_Market,
Consumer_Goods_Market* pConsumer_Goods_Market, Capital_Goods_Market* pCapital_Goods_Market, Bank_Agent* pBank);

void Delete_Bankrupt_Firms(vector<Firm_Agent*>* pFirm_vector,vector<Consumer_Firm_Agent*>* pConsumer_Firm_vector, vector<Capital_Firm_Agent*>* pCapital_Firm_vector);


#endif