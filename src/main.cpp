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
    
    Household_Agent * Household_array = (Household_Agent*)malloc(sizeof(Household_Agent) * n_households);
    Initialize_Households(Household_array, pPublic_Board_1, n_households); 
    Consumer_Firm_Agent * Cons_Firm_array = (Consumer_Firm_Agent*)malloc(sizeof(Consumer_Firm_Agent) * n_consumer_firms);
    Initialize_Consumer_Firms( Cons_Firm_array, pPublic_Board_1, n_consumer_firms, &n_promised_jobs);
    Capital_Firm_Agent * Cap_Firm_array = (Capital_Firm_Agent*)malloc(sizeof(Capital_Firm_Agent) * n_capital_firms);
    Initialize_Capital_Firms(Cap_Firm_array, pPublic_Board_1, n_capital_firms, &n_promised_jobs);
    

    //----------- STEP 0.13: Initialize job market
    cout << "Initializing job Market -  " << " Firms are seeking " << n_promised_jobs << " jobs" << endl;
    Initialize_Job_Market(Cons_Firm_array,Cap_Firm_array,Household_array,pPublic_Board_1);


    int n = 100;
    cout << " Household at position " << n << " has job :" <<  Household_array[n].Get_Employment_Status() << endl;
    n = 9900;
    cout << " Household at position " << n << " has job :" <<  Household_array[n].Get_Employment_Status() << endl;
    n = 9990;
    cout << " Household at position " << n << " has job :" <<  Household_array[n].Get_Employment_Status() << endl;
    

    // STEP 0.14 Assign firm owners - Todo later, minor thing

    // STEP 0.15: Save all Household and Firm properties to a csv file to check success of initialization

    Log_Everything(Household_array, Cons_Firm_array, Cap_Firm_array, n_households, n_consumer_firms, n_capital_firms);

    //pBank_1->Print();

    //  -------- STEP 1 MAIN LOOP -------------------
    cout << "*****************Main Loop begun" << endl;
    global_date = 1;

    // Timestep t=0.5

    // Post goods to market
    for (int i=0; i<n_consumer_firms; i++) {
        Cons_Firm_array[i].Send_Goods_To_Market();
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
    cout << "Step 1.2: Depreciating capital goods" <<endl;

    Cons_Firm_array[50].Print_Capital_Goods();
    
    for (int i=0; i<n_consumer_firms; i++) {
        Cons_Firm_array[i].Depreciate_Capital();
    }
    for (int i=0; i<n_capital_firms; i++) {
        Cap_Firm_array[i].Depreciate_Capital();
    }

    Cons_Firm_array[50].Print_Capital_Goods();




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

