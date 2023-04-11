#include "TimeLoop.hpp"

void Time_Step_1(vector<Household_Agent*> *pHousehold_vector, vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, 
vector<Capital_Firm_Agent*> *pCapital_Firm_vector, vector<Firm_Agent*> *pFirm_vector, Public_Info_Board* pPublic_Info_Board, Job_Market* pJob_Market,
Consumer_Goods_Market* pConsumer_Goods_Market, Capital_Goods_Market* pCapital_Goods_Market, Bank_Agent* pBank){
    
    using namespace std;

    cout << "\n___________________TIMESTEP #______________ " << global_date << endl;

    pPublic_Info_Board->Reset_Global_Data();

    // STEP 1.1: Update Inflation Rate and Interest rate  -
    cout << "|n------------ Step 1.1: Updating inflation and interest rates" <<endl;
    
    pBank->Update_Inflation();
    pBank->Update_Interest_Rate();
    pPublic_Info_Board->Update_Interest_Rate();



    // Shuffle the firm and households vectors randomly using the random number generator
    std::random_device rd;
    std::shuffle(pHousehold_vector->begin(), pHousehold_vector->end(), std::default_random_engine(rd()));
    std::shuffle(pConsumer_Firm_vector->begin(), pConsumer_Firm_vector->end(), std::default_random_engine(rd()));
    std::shuffle(pCapital_Firm_vector->begin(), pCapital_Firm_vector->end(), std::default_random_engine(rd()));
    std::shuffle(pFirm_vector->begin(), pFirm_vector->end(), std::default_random_engine(rd()));
    
    // STEP 1.2: Depreciate Firm's Capital Goods
    cout << "\n------------ Step 1.2: Depreciating capital goods ----------------" <<endl;
    // STEP 1.3: Layoff workers with expired contracts
    cout << " \n ------------ Step 1.3: laying Off Workers Whose contracts expired ----------------" <<endl;
    // STEP 1.4: Random experimentation - randomly tweak firm and household parameters
    cout << " \n ------------ Step 1.4: Random experimentation ----------------" <<endl;
    // STEP 1.5: Firms assess past period's sales data
    cout << " \n ------------ Step 1.5: Firms assess past period's sales data ----------------" <<endl;
    // STEP 1.51: Firms pay dividends - not yet implemented
    cout << " \n ------------ Step 1.51: Firms pay dividend ----------------" <<endl;
    // STEP 1.6: Depreciate Firms' Good Inventories
    cout << "\n------------ Step 1.6: Depreciating Good inventories ----------------" <<endl;
    // STEP 1.7: Firms set new price and production targets
    cout << " \n ------------ Step 1.7: Firms set new price and production targets ----------------" <<endl;

    for( Firm_Agent* firm_ptr : *pFirm_vector){
        firm_ptr->Depreciate_Capital();
        firm_ptr->Cancel_Expired_Contracts();
        firm_ptr->Random_Experimentation();
        firm_ptr->Check_Sales();
        firm_ptr->Update_Average_Profit();
        firm_ptr->Update_Average_Sales();
        firm_ptr->Update_Sentiment();
        firm_ptr->Depreciate_Good_Inventory();
        firm_ptr->Determine_New_Production();
    }

    // STEP 1.8: Firms set wage offers, labor target, and finance expected wage bill
    cout << " \n ------------ Step 1.8: Firms set wage offers, labor target, and finance expected wage bill ----------------" <<endl;

    pJob_Market->Calculate_Average_Wage(); 
    pPublic_Info_Board->Update_Average_Wage_Job_Market();
    cout << "Job market before any new operations" << std::endl; // debugging
    pJob_Market->Print_Size(); //debugging

    for( Firm_Agent* firm_ptr : *pFirm_vector){
        firm_ptr->Adjust_Wage_Offers();
        firm_ptr->Determine_Labor_Need();}


    pJob_Market->Sort_Jobs_by_Wage();

    cout << "Job market after the requested " << pPublic_Info_Board->Get_New_Job_Postings()  << " new postings" << std::endl;
    pJob_Market->Print_Size();

    pJob_Market->Remove_Unwanted_Jobs();
    cout << "Job market after the requested " << pPublic_Info_Board->Get_Removed_Job_Postings() << " job posting removals" << std::endl;
    pJob_Market->Print_Size();


    // Step 1.81: Households Check if they are fired
    cout << " \n ------------ Step 1.81: Households Check if they are fired ----------------" <<endl;
    // Step 1.82: Households update reservation wages
    cout << " \n ------------ Step 1.82: Households update reservation wages ----------------" <<endl;
    
    for (Household_Agent* household_ptr : *pHousehold_vector){
        household_ptr->Check_Employment_Status();
        household_ptr->Update_Reservation_Wage();}


    // STEP 1.83: Labor market matching process
    cout << " \n ------------ Step 1.83: Labor market matching process ----------------" <<endl;
    pJob_Market->Sort_Jobs_by_Wage();

    pPublic_Info_Board->Calculate_Unemployment_Rate();
    pJob_Market->Calculate_Average_Wage(); 
    pPublic_Info_Board->Update_Average_Wage_Job_Market();
    pPublic_Info_Board->Print_Labor_Market();

    cout << "Commencing labor market matching with " << pJob_Market->Get_Size() << " job postings"  << endl;


    for (Household_Agent* household_ptr : *pHousehold_vector){
        household_ptr->Seek_Better_Jobs(); 
        household_ptr->Seek_Jobs();
        household_ptr->Check_Employment_Status();
        household_ptr->Update_Public_Board();}

    for(Firm_Agent* firm_ptr : *pFirm_vector){
        firm_ptr->Check_For_New_Employees();
        firm_ptr->Check_Employees_Quitting();
        }

    pPublic_Info_Board->Calculate_Unemployment_Rate();
    cout << "Labor market matching ended with " << pJob_Market->Get_Size() << " job postings remaining"  << endl;
    pPublic_Info_Board->Print_Labor_Market();


    // Step 1.84: Sentiments Updating
    cout << " \n ------------ Step 1.84: Sentiments Updating ----------------" <<endl;
    pPublic_Info_Board->Calculate_Household_Sentiment_Percentage();
    cout << "Household Sentiment Percentage: " << pPublic_Info_Board->Get_Household_Sentiment() << endl;
    pPublic_Info_Board->Calculate_Cons_Firm_Sentiment_Percentage();
    cout << "Consumer Firm Sentiment Percentage: " << pPublic_Info_Board->Get_Cons_Firm_Sentiment() << endl;
    pPublic_Info_Board->Calculate_Cap_Firm_Sentiment_Percentage();
    cout << "Capital Firm Sentiment Percentage: " << pPublic_Info_Board->Get_Cap_Firm_Sentiment() << endl;


    
    // STEP 1.90: Firms make investment decisions and finance these
    cout << " \n ------------ Step 1.90: Firms make investment decisions and finance these ----------------" <<endl;
    // STEP 1.91: Firms produce their goods
    cout << " \n ------------ Step 1.91: Firms produce their goods ----------------" <<endl;
    
    cout << "Consumer goods market before firms post goods ( what remains of the previous market): " << endl;
    //pConsumer_Goods_Market->Update_Price_Level();
    pConsumer_Goods_Market->Update_Price_Level_by_Sector();
    pConsumer_Goods_Market->Print();
    cout << "Capital goods market before firms post goods ( what remains of the previous market): " << endl;
    pCapital_Goods_Market->Update_Price_Level();
    pCapital_Goods_Market->Print();


    for (Firm_Agent * firm_ptr : *pFirm_vector){
        firm_ptr->Produce_Goods();
        firm_ptr->Update_Goods_On_Market();}

    cout << "Consumer goods market after firms post goods ( after resetting market): " << endl;
    //pConsumer_Goods_Market->Sort_Consumer_Goods_By_Price();
    //pConsumer_Goods_Market->Update_Price_Level();
    pConsumer_Goods_Market->Sort_Cons_Goods_By_Sector_By_Price();
    pConsumer_Goods_Market->Update_Price_Level_by_Sector();
    pConsumer_Goods_Market->Print();
    cout << "Consumer Firms have produced " << pPublic_Info_Board->Get_Consumer_Goods_Production() << " consumer goods, though they planned to produce " << pPublic_Info_Board->Get_Consumer_Goods_Production_Planned() << endl;
    
    cout << "Capital goods market after firms post goods ( after resetting market): " << endl;
    pCapital_Goods_Market->Sort_Capital_Goods_By_Price();
    pCapital_Goods_Market->Update_Price_Level();
    pCapital_Goods_Market->Print();
    cout << "Capital Firms have produced " << pPublic_Info_Board->Get_Capital_Goods_Production() << " capital goods, though they planned to produce " << pPublic_Info_Board->Get_Capital_Goods_Production_Planned() << endl;
    

    // STEP 1.92: Households receive wage and make saving/consumption plans
    cout << " \n ------------ Step 1.92: Households receive wage and make saving/consumption plans ----------------" <<endl;

    for (Household_Agent* household_ptr : *pHousehold_vector){
        household_ptr->Consumption_Savings_Decisions();}


    pPublic_Info_Board->Calculate_Average_Wage_Employed(); // update average wage data after households update their wages
    
    // STEP 1.93: Consumer good market commences
    cout << " \n ------------ Step 1.93: Consumer good market commences ----------------" <<endl;

    cout << "Households have set aside " << pPublic_Info_Board->Get_Consumption_Budget() << " to spend on consumer goods" << endl;
    

    for(Household_Agent* household_ptr : *pHousehold_vector){
        //household_ptr->Buy_Consumer_Goods();
        household_ptr->Buy_Consumer_Goods_By_Sector();}

    cout << "Households have spent " << pPublic_Info_Board->Get_Consumer_Spending() << " on consumer goods to buy " << pPublic_Info_Board->Get_Consumer_Orders() << " consumer goods" << endl;
    cout <<  float(pPublic_Info_Board->Get_Consumer_Spending()) / float(pPublic_Info_Board->Get_Consumption_Budget())*100 << "% of household budgets have been spent " << endl;
    //pConsumer_Goods_Market->Update_Price_Level();
    pConsumer_Goods_Market->Update_Price_Level_by_Sector();
    pConsumer_Goods_Market->Print();

    pPublic_Info_Board->Calculate_Consumer_Demand_Shortfall_by_Sector();


    // STEP 1.94: Capital good market commences
    cout << " \n ------------ Step 1.94: Investment good market commences ----------------" <<endl;
    
    cout << "Firms have now posted capital goods " << endl;

    pCapital_Goods_Market->Sort_Capital_Goods_By_Price();
    pCapital_Goods_Market->Update_Price_Level(); 
    pCapital_Goods_Market->Print();

    for ( Firm_Agent* firm_ptr : *pFirm_vector){
        firm_ptr->Make_Investment_Decision(); 
        firm_ptr->Buy_Capital_Goods();}
    

    cout << "Firms have spent " << pPublic_Info_Board->Get_Machine_Spending() << " on capital goods to buy " << pPublic_Info_Board->Get_Machine_Orders() << " capital goods" << endl;


    // STEP 1.95: Firms pay liabilities
    cout << " \n ------------ Step 1.95: Firms pay liabilities ----------------" <<endl;

    for( Firm_Agent* firm_ptr : *pFirm_vector){
        firm_ptr->Pay_Liabilities();}


    // STEP 1.96: Update Public board before logging data
    pPublic_Info_Board->Calculate_Average_Dividend_Income();
    pPublic_Info_Board->Calculate_Average_Total_Income();

        

}