#include <iostream>


#include "Public_Info_Board.hpp"
#include "Household_Agent.hpp"
//#include "Consumer_Firm_Agent.hpp"
#include "Initialization_Parameters.hpp"


using namespace std;

// Global variables for initialization
int n_households;
int n_consumer_firms;
int n_capital_firms;

int main()
{
//  ------------------ STEP 0 INITIALIZATION ---------------------
    // STEP 0.01: Initalize global variables
    n_households = 10;
    n_consumer_firms = 10;
    n_capital_firms = 2;
    
    // STEP 0.1: Initialize market size, households, etc.
    
    // STEP 0.11: Initialize Households

    cout << "Initializing " << n_households << " households" << endl;

    // Allocate memory for the array to hold the households
    Household_Agent * Household_array = (Household_Agent*)malloc(sizeof(Household_Agent) * n_households);

    // TODO: Make the initialization parameters random according to some rule
    for (int i=0; i<n_households; i++) {
        Household_array[i] = Household_Agent(100*i,i, 100*(i* 11/10), 
        i/n_households + 0.1, i/n_households,
        i%2 == 0, i%2 == 0);

        Household_array[i].Print();
    }

    // TODO: Still need to give households jobs and initialize income, firm_ownership, etc.



    // STEP 0.12: Initialize Consumer Firms
    //Consumer_Firm_Agent * Cons_Firm_array = (Consumer_Firm_Agent*)malloc(sizeof(Consumer_Firm_Agent) * n_consumer_firms);
    // TODO: Make the initialization parameters random according to some rule
    for (int i=0; i<n_consumer_firms; i++) {
        //Cons_Firm_array[i] = Consumer_Firm_Agent(i, i*1000, 1000 + i, i*5000,
        //0.1, 0.05, 2, true);

        //Household_array[i].Print();
    }
    //Consumer_Firm_Agent  my_cons = Consumer_Firm_Agent(1, 1000, 1000 , 5000, 0.1, 0.05, 2, true);



    








    // STEP 0.2: Initialize the Public Board
        //Public_Info_Board* pPublic_Info_Board = new Public_Info_Board();

    // STEP 0.3: Initialize the Bank and Government

    // STEP 0.4: Allocate and Initialize Firms

    // STEP 0.5: Allocate and Initialize Jobs and Job Market 
    Job* job_1 = new Job(nullptr,10,1);
    job_1->Print();


    // STEP 0.6: Allocate and Initialize Households

        // saving = distribution_gauss
        // saving = distribution_data
        // saving = random(0,10)
    
    Household_Agent* Household_1 = new Household_Agent(1000, 10, false, false, 500, 0.4,0.2);

    Household_1->Print();

//  -------- STEP 1 MAIN LOOP -------------------

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

