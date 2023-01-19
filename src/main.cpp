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




using namespace std;

// Global variables for initialization
int n_households = 100;
int n_consumer_firms = 10;
int n_capital_firms = 2;

int n_total_jobs_initial = 94;


// To easily switch printing on/off
bool print_households = 0;
bool print_cons_firms = 0;
bool print_cap_firms = 0;


int main()
{

    cout << "************* Program has started" <<endl;

//  ------------------ STEP 0 INITIALIZATION --------------------- 
    cout << "*****************Initialization Phase begun" << endl;

    // STEP 0.10: Initalize global variables and the public board

    Public_Info_Board* pPublic_Board_1 = new Public_Info_Board();
    Job_Market* pJob_Market_1 = new Job_Market();
    pPublic_Board_1->Set_Job_Market(pJob_Market_1);

    
    int n_promised_jobs = 0;  // Variable to keep track of # jobs to be assigned


    // TODO: Make the initialization parameters random according to some rule
    // TODO: Still need to give households jobs and initialize income, firm_ownership, etc.



    //------- STEP 0.11: Initialize Households
    cout << "\n Initializing " << n_households << " households" << endl;

    // Allocate memory for the array to hold the household then fill it
    Household_Agent * Household_array = (Household_Agent*)malloc(sizeof(Household_Agent) * n_households);
    Initialize_Households(Household_array, pPublic_Board_1, n_households); 
   

    /* int i = 5;
    cout << "Iteration: " << i << endl;
    Household_array[i].Print(); */

    //-------- STEP 0.12: Initialize Consumer Firms ----------
    cout << "\n Initializing " << n_consumer_firms << " consumer firms" << endl;

    // Allocate memory for the array to hold the firms then fill it
    Consumer_Firm_Agent * Cons_Firm_array = (Consumer_Firm_Agent*)malloc(sizeof(Consumer_Firm_Agent) * n_consumer_firms);
    Initialize_Consumer_Firms( Cons_Firm_array, pPublic_Board_1, n_consumer_firms, &n_promised_jobs);
    

    //---------- STEP 0.12: Initialize Capital Firms
    cout << "\n Initializing " << n_capital_firms << " capital firms" << endl;

    // Allocate memory for the array to hold the firms then fill it
    Capital_Firm_Agent * Cap_Firm_array = (Capital_Firm_Agent*)malloc(sizeof(Capital_Firm_Agent) * n_capital_firms);
    Initialize_Capital_Firms(Cap_Firm_array, pPublic_Board_1, n_capital_firms, &n_promised_jobs);
    

    //----------- STEP 0.13: Initialize jobs
    cout << n_promised_jobs << " out of " << n_total_jobs_initial <<  " jobs have been promised to firms." << endl;
    

    // Step 0.14 Allocate jobAdd_Job_Offer(Job*s to Households

    // Step 0.141 - Make firms post jobs to the job list   - Todo move these functs to headers  

    // Make all firms post jobs for the number of employees they require
    
    Post_Initial_Job_Offers_Cons(Cons_Firm_array, n_consumer_firms);
    Post_Initial_Job_Offers_Cap(Cap_Firm_array, n_capital_firms);


    //Cons_Firm_array[0].Set_Wage_Offer(3000);
    //Cons_Firm_array[0].Post_Jobs();

/*     Cons_Firm_array[0].Print();
    Cons_Firm_array[0].Post_Jobs();
    Cons_Firm_array[1].Print();
    Cons_Firm_array[1].Post_Jobs(); 
 */

    pJob_Market_1->Print();



    //Testing Job Sorting
    
 /*    Job* job1 = new Job(nullptr,nullptr, 1000,0);
    Job* job2 = new Job(nullptr,nullptr, 800,0);
    Job* job3 = new Job(nullptr,nullptr, 1200,0);
    Job* job4 = new Job(nullptr,nullptr, 1100,0);
    Job* job5 = new Job(nullptr,nullptr, 1900,0);

    pJob_Market_1->Add_Job_Offer(job1);
    pJob_Market_1->Add_Job_Offer(job2);
    pJob_Market_1->Add_Job_Offer(job3);
    pJob_Market_1->Add_Job_Offer(job4);
    pJob_Market_1->Add_Job_Offer(job5);

    pJob_Market_1->Print();
    pJob_Market_1->Sort_Jobs_by_Wage();
    pJob_Market_1->Print();

    pJob_Market_1->Remove_Top_Job_Offer();
    pJob_Market_1->Print();


    cout << "Household has job?:" << Household_array[0].Get_Employment_Status() << endl;
    Household_array[0].Seek_Jobs();
    cout <<  "Household has job?:" <<  Household_array[0].Get_Employment_Status() << endl;

    pJob_Market_1->Print(); */

    










    // STEP 0.13 Assign jobs to households

    //


    




    // STEP 0.14 Assign firm owners


    // STEP 0.15 Set remaining initial parameters for Firms


    // STEP 0.16 Set remaining initial parameters for households





    

    








    // STEP 0.2: Initialize the Public Board
        //Public_Info_Board* pPublic_Info_Board = new Public_Info_Board();

    // STEP 0.3: Initialize the Bank and Government

    // STEP 0.4: Allocate and Initialize Firms

    // STEP 0.5: Allocate and Initialize Jobs and Job Market 
    //Job* job_1 = new Job(nullptr,nullptr,10,1);
    //job_1->Print();


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

