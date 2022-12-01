

extern float interest_rate_cb;

class Public_Info_Board{

    public:
    Public_Info_Board(int initial_savings); //Constructor

    Public_Info_Board(Public_Info_Board&); //Copy constructor
    
    ~Public_Info_Board(); // Destructor



    int Get_Household_Sentiment() {return household_sentiment_percentage;}

    void Update_Household_Sentiment();

    void Add_Household_Sentiment(bool positive_sentiment);

    int Get_Firm_Sentiment() {return firm_sentiment_percentage;}
    
    void Update_Firm_Sentiment();

    void Add_Firm_Sentiment(bool positive_sentiment);


    private:

    // General price level
    int price_level;

    // Interest rate
    int r_rate;

    // Inflation (trailing 12m)
    int inflation_current;

    // Inflation (next 12m target)
    int inflation_target;


    // Sentiments
    long household_sentiment_sum; // Sum of household sentiment: +1 for each positive
    
    long household_sentiment_percentage; // Percentage of households who are optimist

    long firm_sentiment_sum; // Sum of firm sentiment: +1 for each positive
    
    long firm_sentiment_percentage; // Percentage of firms who are optimist



};
