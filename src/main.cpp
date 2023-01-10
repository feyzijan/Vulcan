#include <iostream>

#include "Initialization_Parameters.hpp"
#include "Public_Info_Board.hpp"

#include "Household_Agent.hpp"
#include "Job.hpp"

#include "Firm_Agent.hpp"
#include "Loan.hpp"
#include "General_Good.hpp"

#include "Consumer_Firm_Agent.hpp"

#include "Capital_Firm_Agent.hpp"




using namespace std;

// Global variables for initialization
int n_households = 10;
int n_consumer_firms = 5;
int n_capital_firms = 2;

int main()
{

    cout << "************* Program has started" <<endl;
//  ------------------ STEP 0 INITIALIZATION ---------------------
    cout << "*****************Initialization Phase begun" << endl;
    // STEP 0.01: Initalize global variables


    //---- STEP 0.1: Initialize market size, households, etc.


    
    //------- STEP 0.11: Initialize Households
    cout << "\n Initializing " << n_households << " households" << endl;

    // Allocate memory for the array to hold the households
    Household_Agent * Household_array = (Household_Agent*)malloc(sizeof(Household_Agent) * n_households);

    // TODO: Make the initialization parameters random according to some rule

    // Fill Household array
    for (int i=0; i<n_households; i++) {
        float propensities[] = { 
            float(n_households)/float(i), // consumption propensity
            0.3, // saving_propensity_optimist 
            0.4, // saving_propensity_pessimist
            0.1, // c_f
            0.2, // c_h
            0.1, // c_excess_money
            0.25, // p_majority_op_adoption
         };

        int wealth = 1000 *i;
        int unemployment_tolerance = 10;

        Household_array[i] = Household_Agent(propensities, unemployment_tolerance,wealth);


        // Print each instance
        
        cout << "Iteration: " << i << endl;
        Household_array[i].Print();
        cout << "\n";
    }

    // TODO: Still need to give households jobs and initialize income, firm_ownership, etc.



    //-------- STEP 0.12: Initialize Consumer Firms ----------
    
    cout << "\n Initializing " << n_consumer_firms << " consumer firms" << endl;

    // Allocate memory for the array to hold the firms
    Consumer_Firm_Agent * Cons_Firm_array = (Consumer_Firm_Agent*)malloc(sizeof(Consumer_Firm_Agent) * n_consumer_firms);

    // TODO: Make the initialization parameters random according to some rule
    for (int i=0; i<n_consumer_firms; i++) {
        float propensities[] = {
            0.05, // dividend_ratio_optimist 
            0.03, // dividend_ratio_pessimist 
            float(i), // inventory factor
        };
        int assets = i*10000;
        int employee_count = 2*i +2;
        int capital_inventory = employee_count;


        Cons_Firm_array[i] = Consumer_Firm_Agent(propensities, assets, employee_count, capital_inventory);


        // Print each instance for checking
        cout << "Iteration: " << i +1 ;
        Cons_Firm_array[i].Print();
        cout << "\n";
    }
    

    //---------- STEP 0.12: Initialize Capital Firms
    
    cout << "\n Initializing " << n_capital_firms << " capital firms" << endl;

    // Allocate memory for the array to hold the firms
    Capital_Firm_Agent * Cap_Firm_array = (Capital_Firm_Agent*)malloc(sizeof(Capital_Firm_Agent) * n_capital_firms);
    
    // TODO: Make the initialization parameters random according to some rule
    for (int i=0; i<n_capital_firms; i++) {
        float propensities[] = {
            0.05, // dividend_ratio_optimist 
            0.03, // dividend_ratio_pessimist 
            float(i), // inventory factor
        };
        int assets = i*10000;
        int employee_count = 2*i +2;
        int capital_inventory = n_max_employees; // these firms only seek labor


        Cap_Firm_array[i] = Capital_Firm_Agent(propensities, assets, employee_count, capital_inventory);

        // Print each instance for checking
        cout << "Iteration: " << i +1 ;
        Cap_Firm_array[i].Print();
        cout << "\n";
    }
    

    // STEP 0.13 Assign jobs to households

    




    // STEP 0.14 Assign firm owners


    // STEP 0.15 Set remaining initial parameters for Firms


    // STEP 0.16 Set remaining initial parameters for households





    

    








    // STEP 0.2: Initialize the Public Board
        //Public_Info_Board* pPublic_Info_Board = new Public_Info_Board();

    // STEP 0.3: Initialize the Bank and Government

    // STEP 0.4: Allocate and Initialize Firms

    // STEP 0.5: Allocate and Initialize Jobs and Job Market 
    Job* job_1 = new Job(nullptr,nullptr,10,1);
    job_1->Print();


    // STEP 0.6: Allocate and Initialize Households

        // saving = distribution_gauss
        // saving = distribution_data
        // saving = random(0,10)
    
    //Household_Agent* Household_1 = new Household_Agent(1000, 10, false, false, 500, 0.4,0.2);

    //Household_1->Print();





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

