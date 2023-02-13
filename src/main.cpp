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

using namespace std;

int main()
{

    cout << "************* Program has started" <<endl;
    global_date = 0;



    //  ------------------ STEP 0 INITIALIZATION --------------------- 
    cout << "*****************Initialization Phase begun" << endl;

    // STEP 0.10: Initalize Public Board, Job Market, Bank
    
    Public_Info_Board* pPublic_Board_1 = new Public_Info_Board();
    Job_Market* pJob_Market_1 = new Job_Market();
    Bank_Agent* pBank_1 = new Bank_Agent(pPublic_Board_1);
    Consumer_Goods_Market* pConsumer_Goods_Market_1 = new Consumer_Goods_Market();
    Capital_Goods_Market* pCapital_Goods_Market_1 = new Capital_Goods_Market();
    pPublic_Board_1->Set_Job_Market(pJob_Market_1);
    pPublic_Board_1->Set_Bank(pBank_1);
    pPublic_Board_1->Set_Consumer_Goods_Market(pConsumer_Goods_Market_1);
    pPublic_Board_1->Set_Capital_Goods_Market(pCapital_Goods_Market_1);

    cout << "Public Board at address: " << pPublic_Board_1 << " initialized" <<endl;
    cout << "Job Market at address: " << pJob_Market_1 << " initialized" <<endl;
    cout << "Bank at address: " << pBank_1 << " initialized" <<endl;


    int n_promised_jobs = 0;  // Debugging variable to keep track of # jobs to be assigned


    //------- STEP 0.11: Initialize Households and Firms
    
    vector<Household_Agent*> *pHousehold_vector = new vector<Household_Agent*>();
    vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector = new vector<Consumer_Firm_Agent*>();
    vector<Capital_Firm_Agent*> *pCapital_Firm_vector = new vector<Capital_Firm_Agent*>();

    Initialize_Households(pHousehold_vector, pPublic_Board_1, n_households); 
    Initialize_Consumer_Firms( pConsumer_Firm_vector, pPublic_Board_1,  n_consumer_firms, &n_promised_jobs);
    Initialize_Capital_Firms(pCapital_Firm_vector, pPublic_Board_1,n_capital_firms, &n_promised_jobs);


    

    //----------- STEP 0.13: Initialize job market
    cout << "Initializing job Market -  " << " Firms are seeking " << n_promised_jobs << " jobs" << endl;
    Initialize_Job_Market(pHousehold_vector,pConsumer_Firm_vector,pCapital_Firm_vector,pPublic_Board_1);


    int n = n_households/10;
    cout << " Household at position " << n << " has job :" <<  pHousehold_vector->at(n)->Get_Employment_Status() << endl;

    // STEP 0.14 Assign firm owners - Todo later, minor thing

    // STEP 0.15: Save all Household and Firm properties to a csv file to check success of initialization

    Log_Everything(pHousehold_vector,pConsumer_Firm_vector,pCapital_Firm_vector, n_households, n_consumer_firms, n_capital_firms);

    //pBank_1->Print();

    //  -------- STEP 1 MAIN LOOP -------------------
    cout << "*****************Main Loop begun" << endl;
    global_date = 1;

    // Timestep t=0.5

    // Send goods to market
    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Send_Goods_To_Market();
    }


    // Set initial price level
    pPublic_Board_1->Initialize_Price_Level();
    



    // Timestep t= 1.0
    // Start from Step 1.61

    // STEP 1.1: Update Inflation Rate and Interest rate  -
    cout << "Step 1.1: Updating inflation and interest rates" <<endl;
    //pBank_1->Print();
    pBank_1->Update_Inflation_Rate();
    pBank_1->Update_Interest_Rate();
    //pBank_1->Print();
    //cout << "Success!" << endl;

    // STEP 1.2: Depreciate Firm's Capital Goods
    cout << "------------ Step 1.2: Depreciating capital goods ----------------" <<endl;

    pConsumer_Firm_vector->at(n_consumer_firms/2)->Print_Capital_Goods();


    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Depreciate_Capital();
    }

    pConsumer_Firm_vector->at(n_consumer_firms/2)->Print_Capital_Goods();




    // STEP 1.3: Depreciate Firm's Good Inventories
    // STEP 1.4: Layoff workers with expired contracts
    // STEP 1.5: Random experimentation - randomly tweak firm and household parameters
    // STEP 1.61: Firms assess past period's sales data

    // STEP 1.62: Firms pay dividend
    // STEP 1.63: Firms set new price and production targets
    // STEP 1.64: Firms set wage offers, labor target, and finance expected wage bill
    // STEP 1.71: Households update reservation wages
    // STEP 1.72: Labor market matching process
    // STEP 1.8: Firms make investment decisions and finance these
    
    // -- t= 1.5

    // STEP 1.91: Firms produce their goods
    // STEP 1.92: Households receive wage and make saving/consumption plans
    // STEP 1.93: Consumer good market commences
    // STEP 1.94: Investment good market commences


    // Timestep t=1










    cout << "Program end :-)\n";
    return 0;
}

