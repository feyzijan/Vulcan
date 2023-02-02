#ifndef PUBLIC_INFO_BOARD_HPP
#define PUBLIC_INFO_BOARD_HPP


class Job_Market;
class Bank_Agent;
class Consumer_Goods_Market;

#include "Job_Market.hpp"
#include "Job.hpp"
#include "Consumer_Goods_Market.hpp"
#include "Capital_Goods_Market.hpp"
#include "Bank_Agent.hpp"
#include "Loan.hpp"

//#include "Firm_Agent.hpp"
#include "Initialization_Parameters.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

class Public_Info_Board{

    public:
    // Constructors and destructor
    Public_Info_Board(); 
    Public_Info_Board(Public_Info_Board&); 
    ~Public_Info_Board(); 

    // Job Market 
    Job* Get_Top_Job();
    Job_Market* Get_Job_List(); // not implemented/needed yet
    void Remove_Top_Job_Offer();
    void Post_Job_To_Market(Job * pJob_Offer);
    void Take_Job(Job* pJob_Offer); // Notify employer and remove job from market
    void Sort_Job_Market();
    void Update_Average_Wage() {average_wage = pJob_Market->Get_Average_Wage();};
    
    // Inflation and price level
    float Calculate_Inflation();
    void Initialize_Price_Level();

    // Loan issuance
    Loan* Seek_Short_Term_Loan(Firm_Agent* pFirm);
    Loan* Seek_Long_Term_Loan(Firm_Agent* pFirm);

    
    // Gathering and reading public sentiment - TO Implement all
    int Get_Household_Sentiment() {return household_sentiment_percentage;}
    void Add_Household_Sentiment(bool positive_sentiment);
    void Update_Household_Sentiment();
    void Add_Firm_Sentiment(bool positive_sentiment);
    int Get_Firm_Sentiment() {return firm_sentiment_percentage;}    
    void Update_Firm_Sentiment();

    // Getters
    int Get_Unemployment_Benefit() { return public_unemployment_benefit;}
    int Get_Price_Level() { return price_level_current;}
    float Get_Capital_Good_Price_Level();
    float Get_Consumer_Good_Price_Level();
    float Get_Average_Wage() { return average_wage;}
    Job_Market* Get_Job_Market_Ptr() { return pJob_Market;}
    int Get_Current_Date() { return current_date;}

    // Setters
    void Set_Job_Market(Job_Market* ptr) { pJob_Market = ptr;}
    void Set_Consumer_Goods_Market(Consumer_Goods_Market* ptr) { pConsumer_Goods_Market = ptr;}
    void Set_Capital_Goods_Market(Capital_Goods_Market* ptr) { pCapital_Goods_Market = ptr;}
    void Set_Bank(Bank_Agent* ptr) { pBank = ptr;}

    // Printing and Debugging
    void Print() const;

    protected:
    Job_Market* pJob_Market;
    Bank_Agent* pBank;
    Consumer_Goods_Market* pConsumer_Goods_Market;
    Capital_Goods_Market* pCapital_Goods_Market;

    // General price level
    int price_level_current;
    int price_level_previous;
    float average_wage; // Average wage in economy

    // Inflation and interest rate
    float r_rate; 
    float inflation_current; 

    // Sentiments
    long household_sentiment_sum; // Sum of household sentiment: +1 for each positive
    long household_sentiment_percentage; // Percentage of households who are optimist
    long firm_sentiment_sum; // Sum of firm sentiment: +1 for each positive
    long firm_sentiment_percentage; // Percentage of firms who are optimist

    // Unemployment benefits
    int public_unemployment_benefit;

    //timestep
    int time_step; // timestep in days
    //current date
    int current_date;

};
#endif