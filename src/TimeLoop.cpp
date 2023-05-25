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

    // STEP 1.11: Remove bankrupt agents from the simulation
    cout << "Step 1.11: Removing bankrupt agents from the simulation" << endl;
    Delete_Bankrupt_Firms(pFirm_vector, pConsumer_Firm_vector, pCapital_Firm_vector);
    cout << pConsumer_Firm_vector->size() << " consumer firms, " << pCapital_Firm_vector->size() << " capital firms, " 
    << pFirm_vector->size() << " firms  in total remaining" << endl;

    // Shuffle the firm and households vectors randomly using the random number generator
    std::random_device rd;
    std::shuffle(pHousehold_vector->begin(), pHousehold_vector->end(), std::default_random_engine(rd()));
    std::shuffle(pConsumer_Firm_vector->begin(), pConsumer_Firm_vector->end(), std::default_random_engine(rd()));
    std::shuffle(pCapital_Firm_vector->begin(), pCapital_Firm_vector->end(), std::default_random_engine(rd()));
    std::shuffle(pFirm_vector->begin(), pFirm_vector->end(), std::default_random_engine(rd()));
    
    // STEPS 1.2-1.7: Firms update various parameters
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


    // STEP 1.2: Depreciate Firm's Capital Goods
    cout << "\n------------ Step 1.2: Depreciating capital goods ----------------" <<endl;
    // STEP 1.3: Layoff workers with expired contracts
    cout << " \n ------------ Step 1.3: laying Off Workers Whose contracts expired ----------------" <<endl;
    cout << "Firms have layed off " << pPublic_Info_Board->Get_Contract_Expiries() << " workers due to contract expiries " << endl;
    // STEP 1.4: Random experimentation - randomly tweak firm and household parameters
    cout << " \n ------------ Step 1.4: Random experimentation ----------------" <<endl;
    // STEP 1.5: Firms assess past period's sales data
    cout << " \n ------------ Step 1.5: Firms assess past period's sales data ----------------" <<endl;
    cout << "Capital firms have sold " << pPublic_Info_Board->Get_Capital_Goods_Sales() << " goods  " <<  endl;
    const vector<long long>& quantitySoldBySector =  pPublic_Info_Board->Get_Quantity_Sold_By_Sector();
    for (int i = 0; i < quantitySoldBySector.size(); ++i) {
        long long quantity = quantitySoldBySector[i];
        cout << "Consumer Sector " << i + 1<< ": Quantity sold = " << quantity << endl;
    }
    // STEP 1.6: Depreciate Firms' Good Inventories
    cout << "\n------------ Step 1.6: Depreciating Good inventories ----------------" <<endl;
    // STEP 1.7: Firms set new price and production targets
    cout << " \n ------------ Step 1.7: Firms set new price and production targets ----------------" <<endl;
    cout << "Capital Firms planning to produce " << pPublic_Info_Board->Get_Capital_Goods_Planned_Production() << " capital goods" << endl;
    const vector<long long>& plannedProductionBySector =  pPublic_Info_Board->Get_Planned_Production_By_Sector();
    for (int i = 0; i < plannedProductionBySector.size(); ++i) {
        long long quantity = plannedProductionBySector[i];
        cout << "Consumer Sector " << i + 1<< ": Planned production = " << quantity << endl;
    }



    // STEP 1.8: Firms set wage offers, labor target, and finance expected wage bill
    cout << " \n ------------ Step 1.8: Firms set wage offers, labor target, and finance expected wage bill ----------------" <<endl;

    pPublic_Info_Board->Update_Average_Wage_Job_Market();
    cout << "Job market has " << pJob_Market->Get_Size() << " jobs with an average wage of " << pJob_Market->Get_Average_Wage() << endl; // debugging

    cout << "Firms now adjusting wage offers and posting jobs" << endl;
    for(Firm_Agent* firm_ptr : *pFirm_vector){
        firm_ptr->Adjust_Wage_Offers();
        firm_ptr->Determine_Labor_Need();}


    pJob_Market->Sort_Jobs_by_Wage();
    cout << "Job market after " << pPublic_Info_Board->Get_New_Job_Postings()  << " new postings has " << pJob_Market->Get_Size() 
    << " jobs with an average wage of " << pJob_Market->Get_Average_Wage() << endl;
    pJob_Market->Remove_Unwanted_Jobs();
    cout << "Job market after " << pPublic_Info_Board->Get_Removed_Job_Postings() << " job posting removals has " << pJob_Market->Get_Size() 
    << " jobs with an average wage of " << pJob_Market->Get_Average_Wage() << endl;
    pJob_Market->Sort_Jobs_by_Wage();

    // Step 1.81: Households Check if they are fired
    cout << " \n ------------ Step 1.81: Households Check if they are fired ----------------" << endl;
    cout << "# Fired Employees: " << pPublic_Info_Board->Get_Employee_Firings() << endl;
    // Step 1.82: Households update reservation wages
    cout << " \n ------------ Step 1.82: Households update reservation wages ----------------" <<endl;
    
    for (Household_Agent* household_ptr : *pHousehold_vector){
        household_ptr->Check_Employment_Status();
        household_ptr->Update_Reservation_Wage();}


    // STEP 1.83: Labor market matching process
    cout << " \n ------------ Step 1.83: Labor market matching process ----------------" <<endl;
    pPublic_Info_Board->Calculate_Unemployment_Rate();
    pPublic_Info_Board->Update_Average_Wage_Job_Market();
    cout << "Labor market info before the matching process: N_employed workers: " << pPublic_Info_Board->Get_Employed_Workers() << " N_unemployed workers: " 
    << pPublic_Info_Board->Get_Unemployed_Workers() << " \nUnemployment rate: "<< pPublic_Info_Board->Get_Unemployment_Rate() << " N_job postings: " 
    << pJob_Market->Get_Size()<< " Average market wage: " << pPublic_Info_Board->Get_Average_Wage_Market() << endl;

    for (Household_Agent* household_ptr : *pHousehold_vector){
        household_ptr->Seek_Better_Jobs(); 
        household_ptr->Seek_Jobs();
        household_ptr->Check_Employment_Status();
        household_ptr->Update_Public_Board_On_Employment();}

    for(Firm_Agent* firm_ptr : *pFirm_vector){
        firm_ptr->Check_For_New_Employees();
        firm_ptr->Check_Employees_Quitting();}

    pPublic_Info_Board->Calculate_Unemployment_Rate();
    cout << "Labor market info after the matching process: N_employed workers: " << pPublic_Info_Board->Get_Employed_Workers() << " N_unemployed workers: " 
    << pPublic_Info_Board->Get_Unemployed_Workers() << " \nUnemployment rate: "<< pPublic_Info_Board->Get_Unemployment_Rate() << " N_job postings: " 
    << pJob_Market->Get_Size()<< " Average market wage: " << pPublic_Info_Board->Get_Average_Wage_Market() << endl;



    // Step 1.84: Update Sentiments
    cout << " \n ------------ Step 1.84: Update Agent sentiments ----------------" <<endl;
    pPublic_Info_Board->Calculate_Household_Sentiment_Percentage();
    cout << "Household Sentiment Percentage: " << pPublic_Info_Board->Get_Household_Sentiment() << endl;
    cout << "Household Sentiment Sum: " << pPublic_Info_Board->Get_Household_Sentiment_Sum() << endl;
    pPublic_Info_Board->Calculate_Cons_Firm_Sentiment_Percentage();
    cout << "Consumer Firm Sentiment Percentage: " << pPublic_Info_Board->Get_Cons_Firm_Sentiment() << endl;
    pPublic_Info_Board->Calculate_Cap_Firm_Sentiment_Percentage();
    cout << "Capital Firm Sentiment Percentage: " << pPublic_Info_Board->Get_Cap_Firm_Sentiment() << endl;
    
    // STEP 1.90: Firms make investment decisions and finance these
    cout << " \n ------------ Step 1.90: Firms make investment decisions and finance these ----------------" <<endl;
    // STEP 1.91: Firms produce their goods
    cout << " \n ------------ Step 1.91: Firms produce their goods ----------------" <<endl;
    
    pConsumer_Goods_Market->Update_Price_Level();
    pCapital_Goods_Market->Update_Price_Level();

    cout << "Consumer goods market before firms post goods (what remains of the previous market): " << 
    pConsumer_Goods_Market->Get_Size() << " goods with an average price of " <<  pConsumer_Goods_Market->Get_Price_Level() << endl;
    cout << "Capital goods market before firms post goods ( what remains of the previous market): " <<
    pCapital_Goods_Market->Get_Size() << " goods with an average price of " << pCapital_Goods_Market->Get_Price_Level() << endl;
    
    for (Firm_Agent * firm_ptr : *pFirm_vector){
        firm_ptr->Produce_Goods();
        firm_ptr->Update_Goods_On_Market();}

    cout << "Consumer goods market after firms post goods (after resetting market): " << endl;
    pConsumer_Goods_Market->Sort_Cons_Goods_By_Sector_By_Price_and_Emissions();
    pConsumer_Goods_Market->Update_Price_Level();

    const vector<long long>& production_by_sector = pPublic_Info_Board->Get_Production_By_Sector();
    for (int i = 0; i < production_by_sector.size(); ++i) {
        long long quantity = production_by_sector[i];
        long long quantity_p = plannedProductionBySector[i];
        cout << "Consumer Sector " << i + 1<< ": Produced: " << quantity << " out of planned: " << quantity_p << endl;
    }

    cout << "Capital goods market after firms post goods ( after resetting market): " << endl;
    pCapital_Goods_Market->Sort_Capital_Goods_By_Price();
    pCapital_Goods_Market->Update_Price_Level();
    cout << "Capital market total goods: " << pCapital_Goods_Market->Get_Size() << " Price level: "<<  pCapital_Goods_Market->Get_Price_Level() << endl;
    cout << "Capital Firms have produced " << pPublic_Info_Board->Get_Capital_Goods_Production() << " out of planned: " << pPublic_Info_Board->Get_Capital_Goods_Planned_Production() << endl;
    

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
        household_ptr->Buy_Consumer_Goods_By_Sector_And_Emissions();}

    cout << "Households have spent " << pPublic_Info_Board->Get_Consumer_Spending() << " on consumer goods"  << endl;
    //cout <<  float(pPublic_Info_Board->Get_Consumer_Spending()) / float(pPublic_Info_Board->Get_Consumption_Budget())*100 << "% of household budgets have been spent " << endl;
    pConsumer_Goods_Market->Update_Price_Level();


    // STEP 1.94: Capital good market commences
    cout << " \n ------------ Step 1.94: Investment good market commences ----------------" <<endl;
    
    cout << "Firms have now posted capital goods " << endl;

    pCapital_Goods_Market->Sort_Capital_Goods_By_Price();
    pCapital_Goods_Market->Update_Price_Level(); 

    for ( Firm_Agent* firm_ptr : *pFirm_vector){
        firm_ptr->Make_Investment_Decision(); 
        firm_ptr->Buy_Capital_Goods();}
    

    cout << "Firms have spent " << pPublic_Info_Board->Get_Machine_Spending() << " on capital goods to buy " << pPublic_Info_Board->Get_Machine_Orders() << " capital goods" << endl;


    // STEP 1.95: Firms pay liabilities
    cout << " \n ------------ Step 1.95: Firms pay liabilities ----------------" <<endl;

    for( Firm_Agent* firm_ptr : *pFirm_vector){
        firm_ptr->Pay_Liabilities();}


    // STEP 1.96: Update Public board before logging data
    // Update emission allowance prices and amounts
    pPublic_Info_Board->Update_Emission_Allowance_Amount();
    pPublic_Info_Board->Update_Emission_Allowance_Price();
    pPublic_Info_Board->Calculate_Average_Unit_Emissions_by_Sector();

}





/* Function to delete bankrupt firms
*/
void Delete_Bankrupt_Firms(vector<Firm_Agent*>* pFirm_vector,vector<Consumer_Firm_Agent*>* pConsumer_Firm_vector, vector<Capital_Firm_Agent*>* pCapital_Firm_vector) {
    
    int temp = 0;
    using namespace std;
    // Erase pointers to bankrupt firms from consumer firm vector
    auto consumerIt = pConsumer_Firm_vector->begin();
    while (consumerIt != pConsumer_Firm_vector->end()) {
        if ((*consumerIt)->Get_Bankruptcy_Status()) {
            //cout << "Deleting bankrupt consumer firm " << *consumerIt <<  endl;
            consumerIt = pConsumer_Firm_vector->erase(consumerIt);
            temp ++;
            //cout << "Erased bankrupt consumer firm " << *consumerIt << endl;
        } else {
            ++consumerIt;
        }
    }
    cout << "Deleted " << temp << " consumer firms" << endl;
    temp = 0;

    // Erase pointers to bankrupt firms from capital firm vector
    auto capitalIt = pCapital_Firm_vector->begin();
    while (capitalIt != pCapital_Firm_vector->end()) {
        if ((*capitalIt)->Get_Bankruptcy_Status()) {
            //cout << "Deleting bankrupt capital firm " << *capitalIt << endl;
            capitalIt = pCapital_Firm_vector->erase(capitalIt);
            temp ++;
            //cout << "Erased bankrupt capital firm " << *capitalIt << endl;
        } else {
            ++capitalIt;
        }
    }
    cout << "Deleted " << temp << " capital firms" << endl;
    temp = 0;

    // Erase pointers and delete objects from combined firm vector
    auto firmIt = pFirm_vector->begin();
    while (firmIt != pFirm_vector->end()) {
        if ((*firmIt)->Get_Bankruptcy_Status()) {
            //cout << "Deleting bankrupt firm " << *firmIt << endl;
            delete *firmIt;
            firmIt = pFirm_vector->erase(firmIt);
            temp ++;
            //cout << "Deleted and erased bankrupt firm " << endl;
        } else {
            ++firmIt;
        }
    }
    cout << "Deleted " << temp << " firms in total " << endl;

}
