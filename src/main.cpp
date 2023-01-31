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


    //  ------------------ STEP 0 INITIALIZATION --------------------- 
    cout << "*****************Initialization Phase begun" << endl;

    // STEP 0.10: Initalize Public Board and Job Market
    
    Public_Info_Board* pPublic_Board_1 = new Public_Info_Board();
    Job_Market* pJob_Market_1 = new Job_Market();
    pPublic_Board_1->Set_Job_Market(pJob_Market_1);
    cout << "Public Board at address: " << pPublic_Board_1 << " initialized" <<endl;

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
    

    // STEP 0.14 Assign firm owners - Todo later, minor thing


    // STEP 0.15: Save all Household and Firm properties to a csv file to check success of initialization
    Log_Household_Properties(Household_array, n_households);
    Log_Cons_Firm_Properties(Cons_Firm_array, n_consumer_firms);
    Log_Cap_Firm_Properties(Cap_Firm_array, n_capital_firms);




 

    //pPublic_Board_1->Print_Inflation_History();



    // STEP 0.3: Initialize the Bank and Government



    




//  -------- STEP 1 MAIN LOOP -------------------

    // STEP 1.0: Update Inflation Rate and Interest rate 








    // STEP 1.1: Update Households , Firm
    // Households(n+1/2) =f [InfoBoard(n)] 
    // Firms(n+1/2)      = f[InfoBoard(n)] 

    // STEP 1.2: Add Jobs/Goods/Capital from Firms  (Job/interaction)      
    // JobMarket(n+1/2)  = f(Firms(n+1/2))
    // Sort the job
    // GoodMarket ...
    
    // STEP 1.3: Update Household  based on Markets
    // Households(n+1) = f(JobMarket(n+1/2), Household(n+1/2))
    // JobMarket(n+1)  = f(Firms(n+1))
    

    // Update InfoBoard (done automatically)
    // InfoBoard(n+1) = JobMarket(n+1),CapitalGoodMarket(n+1),CapitalGoodMarket(n+1)







    
    

    cout << "Program end :-)\n";
    return 0;
}

