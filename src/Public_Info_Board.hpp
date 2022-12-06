#ifndef PUBLIC_INFO_BOARD_HPP
#define PUBLIC_INFO_BOARD_HPP

#include "Job_Market.hpp"

class Public_Info_Board{

    public:
    Public_Info_Board(); //Constructor

    Public_Info_Board(Public_Info_Board&); //Copy constructor
    
    ~Public_Info_Board(); // Destructor



    //---------- Functions for gathering and reading public sentiment----//

    int Get_Household_Sentiment() {return household_sentiment_percentage;}

    void Add_Household_Sentiment(bool positive_sentiment);
    
    void Update_Household_Sentiment();

    void Add_Firm_Sentiment(bool positive_sentiment);
    
    int Get_Firm_Sentiment() {return firm_sentiment_percentage;}
    
    void Update_Firm_Sentiment();
    //--------------------------------------------------------//


    //--- Job Market ---//
    Job_Offer* Get_Top_Job();

    Job_Market* Get_Job_List();

    void Remove_Top_Job_Offer();
    
    void Add_Job_Offer(Job_Offer * pJob_Offer);

    //---------------------------//





    int Get_Unemployment_Benefit() { return public_unemployment_benefit;}

    int Get_Price_Level() { return price_level;}




    private:

    // General price level
    int price_level;

    // Interest rate
    int r_rate;

    
    int inflation_current; // Inflation (trailing 12m)
    int inflation_target; // Inflation (next 12m target)


    // Sentiments
    long household_sentiment_sum; // Sum of household sentiment: +1 for each positive
    long household_sentiment_percentage; // Percentage of households who are optimist
    long firm_sentiment_sum; // Sum of firm sentiment: +1 for each positive
    long firm_sentiment_percentage; // Percentage of firms who are optimist

    // Unemployment benefits

    int public_unemployment_benefit;

    //timestep
    int time_step; // timestep in days


};
#endif