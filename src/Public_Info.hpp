

extern float interest_rate_cb;

class Public_Info{

    public:
    Public_Info(int initial_savings); //Constructor

    Public_Info(Public_Info&); //Copy constructor
    
    ~Public_Info(); // Destructor


    private:

    // General price level
    int price_level;

    // Interest rate
    int r_rate;

    // Inflation (trailing 12m)
    int inflation_current;

    // Inflation (next 12m target)
    int inflation_target;

};
