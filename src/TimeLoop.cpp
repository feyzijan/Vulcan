#include "TimeLoop.hpp"


/* Code for timestep t=1
 - TODO : Reorder steps to make code shorter
 - Move the Update_Profits_T1 methods to initialization phase
*/
void Time_Step_1(vector<Household_Agent*> *pHousehold_vector, vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, 
vector<Capital_Firm_Agent*> *pCapital_Firm_vector, Public_Info_Board* pPublic_Info_Board, Job_Market* pJob_Market,
Consumer_Goods_Market* pConsumer_Goods_Market, Capital_Goods_Market* pCapital_Goods_Market, Bank_Agent* pBank){

    cout << "\n___________________TIMESTEP #______________ " << global_date << endl;
    // STEP 1.1: Update Inflation Rate and Interest rate  -
    std::cout << "|n------------ Step 1.1: Updating inflation and interest rates" <<endl;
    pBank->Update_Inflation_Rate();
    pBank->Update_Interest_Rate();

    

    // Shuffle the vectors randomly using the random number generator
    std::random_device rd;
    std::shuffle(pHousehold_vector->begin(), pHousehold_vector->end(), std::default_random_engine(rd()));
    std::shuffle(pConsumer_Firm_vector->begin(), pConsumer_Firm_vector->end(), std::default_random_engine(rd()));
    std::shuffle(pCapital_Firm_vector->begin(), pCapital_Firm_vector->end(), std::default_random_engine(rd()));
    
    // STEP 1.2: Depreciate Firm's Capital Goods
    std::cout << "\n------------ Step 1.2: Depreciating capital goods ----------------" <<endl;
    // STEP 1.3: Layoff workers with expired contracts
    std::cout << " \n ------------ Step 1.3: laying Off Workers Whose contracts expired ----------------" <<endl;
    // STEP 1.4: Random experimentation - randomly tweak firm and household parameters
    std::cout << " \n ------------ Step 1.4: Random experimentation ----------------" <<endl;
    // STEP 1.5: Firms assess past period's sales data
    std::cout << " \n ------------ Step 1.5: Firms assess past period's sales data ----------------" <<endl;
    // STEP 1.51: Firms pay dividends - not yet implemented
    std::cout << " \n ------------ Step 1.51: Firms pay dividend ----------------" <<endl;
    // STEP 1.6: Depreciate Firms' Good Inventories
    std::cout << "\n------------ Step 1.6: Depreciating Good inventories ----------------" <<endl;
    // STEP 1.7: Firms set new price and production targets
    std::cout << " \n ------------ Step 1.7: Firms set new price and production targets ----------------" <<endl;
    

    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Depreciate_Capital();
        firm_ptr->Cancel_Expired_Contracts();
        firm_ptr->Random_Experimentation();
        firm_ptr->Check_Sales();
        firm_ptr->Pay_Dividends();
        firm_ptr->Depreciate_Good_Inventory();
        firm_ptr->Determine_New_Production();
    }
    
    
    for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Depreciate_Capital();
        firm_ptr->Cancel_Expired_Contracts();
        firm_ptr->Random_Experimentation();
        firm_ptr->Check_Sales();
        firm_ptr->Pay_Dividends();
        firm_ptr->Depreciate_Good_Inventory();
        firm_ptr->Determine_New_Production();
    }

    // special just for first time step
    if( global_date > 1){
        for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
            firm_ptr->Update_Average_Profit();
            firm_ptr->Update_Average_Sales();
        }
        for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
            firm_ptr->Update_Average_Profit();
            firm_ptr->Update_Average_Sales();
        }
    } else {
        for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
            firm_ptr->Update_Average_Profits_T1();
            firm_ptr->Update_Average_Sales_T1();
        }
        for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
            firm_ptr->Update_Average_Profits_T1();
            firm_ptr->Update_Average_Sales_T1();
        }
    }

    // STEP 1.8: Firms set wage offers, labor target, and finance expected wage bill
    std::cout << " \n ------------ Step 1.8: Firms set wage offers, labor target, and finance expected wage bill ----------------" <<endl;


    pJob_Market->Calculate_Average_Wage(); 
    pPublic_Info_Board->Update_Average_Wage();
    std::cout << "Job market before any new operations" << std::endl;
    pJob_Market->Print_Size();


    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Adjust_Wage_Offers();
        firm_ptr->Determine_Labor_Need();
    }
    
    for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Adjust_Wage_Offers();
        firm_ptr->Determine_Labor_Need();
    }

    pJob_Market->Sort_Jobs_by_Wage();

    std::cout << "Job market after the requested " << pPublic_Info_Board->Get_New_Job_Postings()  << " new postings" << std::endl;
    pJob_Market->Print_Size();

    pJob_Market->Remove_Unwanted_Jobs();
    std::cout << "Job market after the requested " << pPublic_Info_Board->Get_Removed_Job_Postings() << " job posting removals" << std::endl;
    pJob_Market->Print_Size();


    // Step 1.81: Households Check if they are fired
    std::cout << " \n ------------ Step 1.81: Households Check if they are fired ----------------" <<endl;
    // Step 1.82: Households update reservation wages
    std::cout << " \n ------------ Step 1.82: Households update reservation wages ----------------" <<endl;
    for (Household_Agent* household_ptr : *pHousehold_vector){
        household_ptr->Check_Employment_Status();
        household_ptr->Update_Reservation_Wage();}


    

    // STEP 1.83: Labor market matching process
    cout << " \n ------------ Step 1.83: Labor market matching process ----------------" <<endl;
    pJob_Market->Sort_Jobs_by_Wage();

    pPublic_Info_Board->Update_Unemployment_Rate();
    pJob_Market->Calculate_Average_Wage(); 
    pPublic_Info_Board->Update_Average_Wage();
    pPublic_Info_Board->Print_Labor_Market();
    pPublic_Info_Board->Reset_Global_Data();
    cout << "Commencing labor market matching with " << pJob_Market->Get_Size() << " job postings"  << endl;


    for (Household_Agent* household_ptr : *pHousehold_vector){
        household_ptr->Seek_Jobs();
        household_ptr->Check_Employment_Status();}
    for (Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Check_For_New_Employees();}
    for (Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Check_For_New_Employees();}

    pPublic_Info_Board->Update_Unemployment_Rate();
    cout << "Labor market matching ended with " << pJob_Market->Get_Size() << " job postings remaining"  << endl;
    pPublic_Info_Board->Print_Labor_Market();


    // Step 1.84: Sentiments Updating
    cout << " \n ------------ Step 1.84: Sentiments Updating ----------------" <<endl;
    pPublic_Info_Board->Update_Household_Sentiment_Percentage();
    pPublic_Info_Board->Update_Cons_Firm_Sentiment_Percentage();
    pPublic_Info_Board->Update_Cap_Firm_Sentiment_Percentage();


    
    // STEP 1.90: Firms make investment decisions and finance these
    cout << " \n ------------ Step 1.90: Firms make investment decisions and finance these ----------------" <<endl;
    // STEP 1.91: Firms produce their goods
    cout << " \n ------------ Step 1.91: Firms produce their goods ----------------" <<endl;
    

    for (Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Make_Investment_Decision(); 
        firm_ptr->Produce_Consumer_Goods();}
    for (Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Make_Investment_Decision();
        firm_ptr->Produce_Capital_Goods();}

    cout << "Firms wish to buy " << test_global_var << " machines" << endl;

    cout << "Consumer Firms have produced " << pPublic_Info_Board->Get_Consumer_Goods_Production() << " consumer goods, though they planned to produce " << pPublic_Info_Board->Get_Consumer_Goods_Production_Planned() << endl;
    cout << "Capital Firms have produced " << pPublic_Info_Board->Get_Capital_Goods_Production() << " capital goods, though they planned to produce " << pPublic_Info_Board->Get_Capital_Goods_Production_Planned() << endl;
    
    // -- t= 1.5 effectively 

    // STEP 1.92: Households receive wage and make saving/consumption plans
    cout << " \n ------------ Step 1.92: Households receive wage and make saving/consumption plans ----------------" <<endl;

    for (Household_Agent* household_ptr : *pHousehold_vector){
        household_ptr->Consumption_Savings_Decisions();}
    
    // STEP 1.93: Consumer good market commences
    cout << " \n ------------ Step 1.93: Consumer good market commences ----------------" <<endl;

    cout << "Households have set aside " << pPublic_Info_Board->Get_Consumption_Budget() << " to spend on consumer goods" << endl;
    
    cout << "Consumer goods market before firms post goods ( what remains of the previous market): " << endl;
    pConsumer_Goods_Market->Update_Price_Level();
    pConsumer_Goods_Market->Print();
    pConsumer_Goods_Market->Reset_Market();

    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Send_Goods_To_Market();}

    cout << "Consumer goods market after firms post goods ( after resetting market): " << endl;
    pConsumer_Goods_Market->Sort_Consumer_Goods_By_Price();
    pConsumer_Goods_Market->Update_Price_Level();
    pConsumer_Goods_Market->Print();

    for(Household_Agent* household_ptr : *pHousehold_vector){
        household_ptr->Buy_Consumer_Goods();}

    cout << "Households have spent " << pPublic_Info_Board->Get_Consumer_Spending() << " on consumer goods to buy " << pPublic_Info_Board->Get_Consumer_Orders() << " consumer goods" << endl;
    cout <<  float(pPublic_Info_Board->Get_Consumer_Spending()) / float(pPublic_Info_Board->Get_Consumption_Budget())*100 << "% of household budgets have been spent " << endl;
    pConsumer_Goods_Market->Update_Price_Level();
    pConsumer_Goods_Market->Print();


    // STEP 1.94: Capital good market commences
    cout << " \n ------------ Step 1.94: Investment good market commences ----------------" <<endl;
    
    pPublic_Info_Board->Reset_Global_Data();
    pCapital_Goods_Market->Reset_Market();

    for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Send_Goods_To_Market();}

    cout << "Firms have now posted capital goods " << endl;

    pCapital_Goods_Market->Sort_Capital_Goods_By_Price();
    pCapital_Goods_Market->Update_Price_Level();
    pCapital_Goods_Market->Print();
    
    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Buy_Capital_Goods();}


    cout << "Cons Firms have now bought capital goods " << endl;
    cout << "Cons Firms have spent " << pPublic_Info_Board->Get_Machine_Spending() << " on capital goods to buy " << pPublic_Info_Board->Get_Machine_Orders() << " capital goods" << endl;

    pCapital_Goods_Market->Sort_Capital_Goods_By_Price();
    pCapital_Goods_Market->Update_Price_Level();
    pCapital_Goods_Market->Print();


    pPublic_Info_Board->Reset_Global_Data();
    for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Buy_Capital_Goods();}

    cout << "Cap Firms have now bought capital goods " << endl;
    pCapital_Goods_Market->Update_Price_Level();
    pCapital_Goods_Market->Print();
    cout << "Cap Firms have spent " << pPublic_Info_Board->Get_Machine_Spending() << " on capital goods to buy " << pPublic_Info_Board->Get_Machine_Orders() << " capital goods" << endl;

}



    

   



    



/*

// STEP 1.1: Update Inflation Rate and Interest rate  -
    std::cout << "|n------------ Step 1.1: Updating inflation and interest rates" <<endl;

    pBank_1->Update_Inflation_Rate();
    pBank_1->Update_Interest_Rate();


    // STEP 1.2: Depreciate Firm's Capital Goods
    std::cout << "\n------------ Step 1.2: Depreciating capital goods ----------------" <<endl;

    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Depreciate_Capital();}
    for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Depreciate_Capital();}

    
    // STEP 1.4: Layoff workers with expired contracts
    std::cout << " \n ------------ Step 1.4: Depreciating Good inventories ----------------" <<endl;

    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Cancel_Expired_Contracts();}
    for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Cancel_Expired_Contracts();}
    

    // STEP 1.5: Random experimentation - randomly tweak firm and household parameters
    std::cout << " \n ------------ Step 1.5: Random experimentation ----------------" <<endl;

    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Random_Experimentation();}
    for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Random_Experimentation();}
    

    // STEP 1.61: Firms assess past period's sales data
    std::cout << " \n ------------ Step 1.61: Firms assess past period's sales data ----------------" <<endl;
    
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
    std::cout << " \n ------------ Step 1.62: Firms pay dividend ----------------" <<endl;

    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Pay_Dividends();}
    for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Pay_Dividends();}


    // STEP 1.625: Depreciate Firms' Good Inventories
    std::cout << "\n------------ Step 1.625: Depreciating Good inventories ----------------" <<endl;

    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Depreciate_Good_Inventory();}
    for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Depreciate_Good_Inventory();}


    // STEP 1.63: Firms set new price and production targets
    std::cout << " \n ------------ Step 1.63: Firms set new price and production targets ----------------" <<endl;
    
    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Determine_New_Production();}

    for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Determine_New_Production();}

    

    // STEP 1.64: Firms set wage offers, labor target, and finance expected wage bill
    cout << " \n ------------ Step 1.64: Firms set wage offers, labor target, and finance expected wage bill ----------------" <<endl;

    pJob_Market->Calculate_Average_Wage(); 
    pPublic_Info_Board->Update_Average_Wage();

    cout << "Job market before any new operations" << endl;
    pJob_Market->Print_Size();
    
    for (Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Adjust_Wage_Offers();
        firm_ptr->Determine_Labor_Need();}

    for (Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Adjust_Wage_Offers();
        firm_ptr->Determine_Labor_Need();}

    pJob_Market->Sort_Jobs_by_Wage();

    cout << "Job market after the requested " << pPublic_Info_Board->Get_New_Job_Postings()  << " new postings" << endl;
    pJob_Market->Print_Size();
    
    pJob_Market->Remove_Unwanted_Jobs();
    cout << "Job market after the requested " << pPublic_Info_Board->Get_Removed_Job_Postings() << " job posting removals" << endl;
    pJob_Market->Print_Size();
    

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
    pJob_Market->Sort_Jobs_by_Wage();

    pPublic_Info_Board->Update_Unemployment_Rate();
    pJob_Market->Calculate_Average_Wage(); 
    pPublic_Info_Board->Update_Average_Wage();

    cout << "# Employed workers: " << pPublic_Info_Board->Get_Employed_Workers() << endl;
    cout << "# Unemployed workers: " << pPublic_Info_Board->Get_Unemployed_Workers() << endl;
    cout << "Unemployment rate: " << pPublic_Info_Board->Get_Unemployment_Rate() << endl;
    cout << "Average wage: " << pPublic_Info_Board->Get_Average_Wage() << endl; 

    pPublic_Info_Board->Reset_Global_Data();
    cout << "Commencing labor market matching with " << pJob_Market->Get_Size() << " job postings"  << endl;


    for (Household_Agent* household_ptr : *pHousehold_vector){
        household_ptr->Seek_Jobs();
        household_ptr->Check_Employment_Status();}
    for (Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Check_For_New_Employees();}
    for (Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Check_For_New_Employees();}

    
    pPublic_Info_Board->Update_Unemployment_Rate();
    cout << "Labor market matching ended with " << pJob_Market->Get_Size() << " job postings remaining"  << endl;
    cout << "# Employed workers: " << pPublic_Info_Board->Get_Employed_Workers() << endl;
    cout << "# Unemployed workers: " << pPublic_Info_Board->Get_Unemployed_Workers() << endl;
    cout << "Unemployment rate: " << pPublic_Info_Board->Get_Unemployment_Rate() << endl;
    cout << "Average wage: " << pPublic_Info_Board->Get_Average_Wage() << endl; 



    
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

    cout << "Firms wish to buy " << test_global_var << " machines" << endl;

    
    // -- t= 1.5
    // STEP 1.91: Firms produce their goods
    cout << " \n ------------ Step 1.91: Firms produce their goods ----------------" <<endl;
    
    for (Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Produce_Consumer_Goods();}
    for (Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Produce_Capital_Goods();}

    cout << "Consumer Firms have produced " << pPublic_Info_Board->Get_Consumer_Goods_Production() << " consumer goods, though they planned to produce " << pPublic_Info_Board->Get_Consumer_Goods_Production_Planned() << endl;
    cout << "Capital Firms have produced " << pPublic_Info_Board->Get_Capital_Goods_Production() << " capital goods, though they planned to produce " << pPublic_Info_Board->Get_Capital_Goods_Production_Planned() << endl;


    // STEP 1.92: Households receive wage and make saving/consumption plans
    cout << " \n ------------ Step 1.92: Households receive wage and make saving/consumption plans ----------------" <<endl;

    for (Household_Agent* household_ptr : *pHousehold_vector){
        household_ptr->Consumption_Savings_Decisions();}
    
    // STEP 1.93: Consumer good market commences
    cout << " \n ------------ Step 1.93: Consumer good market commences ----------------" <<endl;

    cout << "Households have set aside " << pPublic_Info_Board->Get_Consumption_Budget() << " to spend on consumer goods" << endl;
    
    cout << "Consumer goods market before firms post goods ( what remains of the previous market): " << endl;
    pConsumer_Goods_Market->Update_Price_Level();
    pConsumer_Goods_Market->Print();
    pConsumer_Goods_Market->Reset_Market();

    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Send_Goods_To_Market();}

    cout << "Consumer goods market after firms post goods ( after resetting market): " << endl;
    pConsumer_Goods_Market->Sort_Consumer_Goods_By_Price();
    pConsumer_Goods_Market->Update_Price_Level();
    pConsumer_Goods_Market->Print();

    for(Household_Agent* household_ptr : *pHousehold_vector){
        household_ptr->Buy_Consumer_Goods();}

    cout << "Households have spent " << pPublic_Info_Board->Get_Consumer_Spending() << " on consumer goods to buy " << pPublic_Info_Board->Get_Consumer_Orders() << " consumer goods" << endl;
    cout <<  float(pPublic_Info_Board->Get_Consumer_Spending()) / float(pPublic_Info_Board->Get_Consumption_Budget())*100 << "% of household budgets have been spent " << endl;
    pConsumer_Goods_Market->Update_Price_Level();
    pConsumer_Goods_Market->Print();




    // STEP 1.94: Capital good market commences
    cout << " \n ------------ Step 1.94: Investment good market commences ----------------" <<endl;

    
    pPublic_Info_Board->Reset_Global_Data();
    pCapital_Goods_Market->Reset_Market();

    for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Send_Goods_To_Market();}

    cout << "Firms have now posted capital goods " << endl;

    pCapital_Goods_Market->Sort_Capital_Goods_By_Price();
    pCapital_Goods_Market->Update_Price_Level();
    pCapital_Goods_Market->Print();
    
    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Buy_Capital_Goods();}


    cout << "Cons Firms have now bought capital goods " << endl;
    cout << "Cons Firms have spent " << pPublic_Info_Board->Get_Machine_Spending() << " on capital goods to buy " << pPublic_Info_Board->Get_Machine_Orders() << " capital goods" << endl;

    pCapital_Goods_Market->Sort_Capital_Goods_By_Price();
    pCapital_Goods_Market->Update_Price_Level();
    pCapital_Goods_Market->Print();


    pPublic_Info_Board->Reset_Global_Data();
    for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Buy_Capital_Goods();}

    cout << "Cap Firms have now bought capital goods " << endl;
    pCapital_Goods_Market->Update_Price_Level();
    pCapital_Goods_Market->Print();
    cout << "Cap Firms have spent " << pPublic_Info_Board->Get_Machine_Spending() << " on capital goods to buy " << pPublic_Info_Board->Get_Machine_Orders() << " capital goods" << endl;


*/





