/* Class declaration for the government,
A single instance of this class will decide on 
tax policy, subsidies, unemployment benefits, etc.

*/

class Government{


    public:

    Government(); //Constructor
    Government(Government&); //Copy constructor
    ~Government(); // Destructor


    private:

    // --- State Variables
    int budget_imbalance;



    // --- Outflow Variables
    int household_subsidies;
    int consumer_firms_subsidies;
    int capital_firms_subsidies;
    int bond_interest_payments;
    int bond_capital_payments;

    int total_public_spending;


    // --- Inflow Variables
    int tax_revenue;
    int debt_issuance;


};