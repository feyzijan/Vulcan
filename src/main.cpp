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


    int starting_employees = init_employee_count_desired_mean * (n_consumer_firms + n_capital_firms);
    cout << "Expected employee desire: " << starting_employees << endl;





    //  ------------------ STEP 0 INITIALIZATION --------------------- 
    cout << "*****************Initialization Phase begun" << endl;

    // STEP 0.10: Initalize Public Board, Job Market, Bank, Markets
    
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
    pJob_Market_1->Print_Size();


    // STEP 0.14 Assign firm owners - Todo later, minor thing


    // STEP 0.15: Save all Household and Firm properties to a csv file to check success of initialization
    //Log_Everything(pHousehold_vector,pConsumer_Firm_vector,pCapital_Firm_vector, n_households, n_consumer_firms, n_capital_firms);


    // STEP 0.16: Send goods to markets and initialize price level
    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Send_Goods_To_Market();}
    for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Send_Goods_To_Market();}

    pPublic_Board_1->Initialize_Price_Level();


    //  -------- STEP 1 MAIN LOOP -------------------
    cout << "*****************Main Loop begun" << endl;
    global_date = 1;
    
    // Timestep t= 1.0

    // STEP 1.1: Update Inflation Rate and Interest rate  -
    cout << "|n------------ Step 1.1: Updating inflation and interest rates" <<endl;

    pBank_1->Update_Inflation_Rate();
    pBank_1->Update_Interest_Rate();


    // STEP 1.2: Depreciate Firm's Capital Goods
    cout << "\n------------ Step 1.2: Depreciating capital goods ----------------" <<endl;

    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Depreciate_Capital();}
    for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Depreciate_Capital();}

    
    // STEP 1.4: Layoff workers with expired contracts
    cout << " \n ------------ Step 1.4: Depreciating Good inventories ----------------" <<endl;

    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Cancel_Expired_Contracts();}
    for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Cancel_Expired_Contracts();}
    

    // STEP 1.5: Random experimentation - randomly tweak firm and household parameters
    cout << " \n ------------ Step 1.5: Random experimentation ----------------" <<endl;

    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Random_Experimentation();}
    for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Random_Experimentation();}
    

    // STEP 1.61: Firms assess past period's sales data
    cout << " \n ------------ Step 1.61: Firms assess past period's sales data ----------------" <<endl;
    
    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Check_Sales();
        firm_ptr->Update_Average_Profits_T1();
        firm_ptr->Update_Average_Sales_T1();
    }
    
    for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Check_Sales();
        firm_ptr->Update_Average_Profits_T1();
        firm_ptr->Update_Average_Sales_T1();
    }


    // STEP 1.62: Firms pay dividends - not yet implemented
    cout << " \n ------------ Step 1.62: Firms pay dividend ----------------" <<endl;

    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Pay_Dividends();}
    for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Pay_Dividends();}


    // STEP 1.625: Depreciate Firms' Good Inventories
    cout << "\n------------ Step 1.625: Depreciating Good inventories ----------------" <<endl;

    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Depreciate_Good_Inventory();}
    for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Depreciate_Good_Inventory();}


    // STEP 1.63: Firms set new price and production targets
    cout << " \n ------------ Step 1.63: Firms set new price and production targets ----------------" <<endl;
    
    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Determine_New_Production();}

    for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Determine_New_Production();}


    // STEP 1.64: Firms set wage offers, labor target, and finance expected wage bill
    cout << " \n ------------ Step 1.64: Firms set wage offers, labor target, and finance expected wage bill ----------------" <<endl;

    pJob_Market_1->Calculate_Average_Wage(); 
    pPublic_Board_1->Update_Average_Wage();

    cout << "Job market before any new operations" << endl;
    pJob_Market_1->Print_Size();
    
    for (Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Adjust_Wage_Offers();
        firm_ptr->Determine_Labor_Need();}

    for (Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Adjust_Wage_Offers();
        firm_ptr->Determine_Labor_Need();}

    pJob_Market_1->Sort_Jobs_by_Wage();

    cout << "Job market after the requested " << pPublic_Board_1->Get_New_Job_Postings()  << " new postings" << endl;
    pJob_Market_1->Print_Size();
    
    pJob_Market_1->Remove_Unwanted_Jobs();
    cout << "Job market after the requested " << pPublic_Board_1->Get_Removed_Job_Postings() << " job posting removals" << endl;
    pJob_Market_1->Print_Size();
    

    // Step 1.65: Households Check if they are fired
    cout << " \n ------------ Step 1.65: Households Check if they are fired ----------------" <<endl;
    for (Household_Agent* household_ptr : *pHousehold_vector){
        household_ptr->Check_Employment_Status();}

    // STEP 1.71: Households update reservation wages
    cout << " \n ------------ Step 1.71: Households update reservation wages ----------------" <<endl;

    for (Household_Agent* household_ptr : *pHousehold_vector){
        household_ptr->Update_Reservation_Wage();}

    // STEP 1.72: Labor market matching process
    cout << " \n ------------ Step 1.72: Labor market matching process ----------------" <<endl;
    pJob_Market_1->Sort_Jobs_by_Wage();
    cout << pPublic_Board_1->Get_Employed_Workers() << " workers are employed, " << pPublic_Board_1->Get_Unemployed_Workers() << 
    " workers are unemployed " << " Unemployment rate at :" << pPublic_Board_1->Get_Unemployment_Rate() <<  endl;

    for (Household_Agent* household_ptr : *pHousehold_vector){
        household_ptr->Seek_Jobs();}
    for (Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Check_For_New_Employees();}
    for (Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Check_For_New_Employees();}

    cout << "Job market after the matching process" << endl;
    pJob_Market_1->Print_Size();
    cout << pPublic_Board_1->Get_Employed_Workers() << " workers are employed, " << pPublic_Board_1->Get_Unemployed_Workers() << 
    " workers are unemployed " << " Unemployment rate at :" << pPublic_Board_1->Get_Unemployment_Rate() <<  endl;



    // Step 1.73: Sentiments Updating
    cout << " \n ------------ Step 1.73: Sentiments Updating ----------------" <<endl;

    pPublic_Board_1->Update_Household_Sentiment_Percentage();
    pPublic_Board_1->Update_Cons_Firm_Sentiment_Percentage();
    pPublic_Board_1->Update_Cap_Firm_Sentiment_Percentage();
    pPublic_Board_1->Update_Unemployment_Rate();



    // STEP 1.8: Firms make investment decisions and finance these
    cout << " \n ------------ Step 1.8: Firms make investment decisions and finance these ----------------" <<endl;
    // loop though all firms and make investment decisions
    test_global_var = 0;
    for (Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Make_Investment_Decision();
        //firm_ptr->Buy_Machines();
        }
    for (Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Make_Investment_Decision();
        //firm_ptr->Buy_Machines();
        }

    cout << "Firms have committed to buying " << test_global_var << " machines" << endl;

    
    // -- t= 1.5
    // STEP 1.91: Firms produce their goods
    cout << " \n ------------ Step 1.91: Firms produce their goods ----------------" <<endl;
    
    for (Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Produce_Consumer_Goods();}
    for (Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Produce_Capital_Goods();}

    cout << "Consumer Firms have produced " << pPublic_Board_1->Get_Consumer_Goods_Production() << " consumer goods, though they planned to produce " << pPublic_Board_1->Get_Capital_Goods_Production_Planned() << endl;
    cout << "Capital Firms have produced " << pPublic_Board_1->Get_Capital_Goods_Production() << " capital goods, though they planned to produce " << pPublic_Board_1->Get_Capital_Goods_Production_Planned() << endl;


    // STEP 1.92: Households receive wage and make saving/consumption plans
    cout << " \n ------------ Step 1.92: Households receive wage and make saving/consumption plans ----------------" <<endl;

    for (Household_Agent* household_ptr : *pHousehold_vector){
        household_ptr->Consumption_Savings_Decisions();}
    
    // STEP 1.93: Consumer good market commences
    cout << " \n ------------ Step 1.93: Consumer good market commences ----------------" <<endl;
    
    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Send_Goods_To_Market();}

    pConsumer_Goods_Market_1->Sort_Consumer_Goods_By_Price();

    for(Household_Agent* household_ptr : *pHousehold_vector){
        household_ptr->Buy_Consumer_Goods();}

    cout << "Households have spent " << pPublic_Board_1->Get_Consumer_Spending() << " on consumer goods to buy " << pPublic_Board_1->Get_Consumer_Orders() << " consumer goods" << endl;

    // STEP 1.94: Capital good market commences
    cout << " \n ------------ Step 1.94: Investment good market commences ----------------" <<endl;

    for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Send_Goods_To_Market();}

    pCapital_Goods_Market_1->Sort_Capital_Goods_By_Price();
    
    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Buy_Capital_Goods();}
    for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Buy_Capital_Goods();}

    cout << "Firms have spent " << pPublic_Board_1->Get_Machine_Spending() << " on capital goods to buy " << pPublic_Board_1->Get_Machine_Orders() << " capital goods" << endl;


    // Timestep t=1
    //Log_Everything(pHousehold_vector,pConsumer_Firm_vector,pCapital_Firm_vector, n_households, n_consumer_firms, n_capital_firms);

    // Timestep t=2 and onward

    cout << "Program end :-)\n";
    return 0;
}

