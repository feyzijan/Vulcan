#include <iostream>


#include "Initialization_Parameters.hpp"
#include "Public_Info_Board.hpp"
#include "Household_Agent.hpp"
#include "Job.hpp"
#include "Job_Market.hpp"
#include "Firm_Agent.hpp"
#include "Loan.hpp"
#include "General_Good.hpp"
#include "Consumer_Firm_Agent.hpp"
#include "Capital_Firm_Agent.hpp"
#include "Initialization_Functions.hpp"
#include "Random_Functions.hpp"
#include "Data_Logging.hpp"
#include "TimeLoop.hpp"

using namespace std;


int main()
{

    cout << "************* Program has started" <<endl;
    //  ------------------ STEP 0 INITIALIZATION --------------------- 
    cout << "*****************Initialization Phase begun*********" << endl;

    // Allocate memory
    Public_Info_Board* pPublic_Board_1 = new Public_Info_Board();
    Job_Market* pJob_Market_1 = new Job_Market();
    Bank_Agent* pBank_1 = new Bank_Agent(pPublic_Board_1);
    Consumer_Goods_Market* pConsumer_Goods_Market_1 = new Consumer_Goods_Market();
    Capital_Goods_Market* pCapital_Goods_Market_1 = new Capital_Goods_Market();

    vector<Household_Agent*> *pHousehold_vector = new vector<Household_Agent*>();
    vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector = new vector<Consumer_Firm_Agent*>();
    vector<Capital_Firm_Agent*> *pCapital_Firm_vector = new vector<Capital_Firm_Agent*>();


    Initialize_Households_Firms_Jobs(pHousehold_vector, pConsumer_Firm_vector, pCapital_Firm_vector,
    pPublic_Board_1, pJob_Market_1, pConsumer_Goods_Market_1, pCapital_Goods_Market_1, pBank_1);


    // STEP 0.15: Save all Household and Firm properties to a csv file to check success of initialization
    cout << "Step 0.15: Log initial Household and Firm data" << endl;
    Log_Everything(pHousehold_vector,pConsumer_Firm_vector,pCapital_Firm_vector, n_households, n_consumer_firms, n_capital_firms);





    //  -------- STEP 1 MAIN LOOP -------------------
    cout << "\n***************** Main Loop begun" << endl;
    global_date = 1;


    for ( int i = 0; i < 2; i++){
        Time_Step_1(pHousehold_vector, pConsumer_Firm_vector, pCapital_Firm_vector, 
        pPublic_Board_1, pJob_Market_1, pConsumer_Goods_Market_1, pCapital_Goods_Market_1, pBank_1);
        Log_Everything(pHousehold_vector,pConsumer_Firm_vector,pCapital_Firm_vector, n_households, n_consumer_firms, n_capital_firms);
        global_date++;
    }


    cout << "Program end :-)\n";
    return 0;
}

