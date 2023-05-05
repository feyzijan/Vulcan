#include <iostream>
#include <chrono>
#include <fstream>
#include <Windows.h>
#include <string>

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
#include "TimeLoop.hpp"

using namespace std;


int main()
{
    cout << "************* Program has started ***************" <<endl;

    // Output print lines to file
    std::ofstream output_file("../DataLogs/SimulationOutput.txt"); // create output file
    std::streambuf* old_cout_buf = std::cout.rdbuf(); // save old cout buffer
    std::cout.rdbuf(output_file.rdbuf()); // redirect cout to file

    //std::cout.rdbuf(old_cout_buf); // uncomment this line if you want to output to console

    // Testing the maps are accessible 
    initialization_parameters["test_param_int"] = 10;
    initialization_parameters["test_param_float"] = 3.14f;




    //  ------------------ STEP 0 INITIALIZATION --------------------- 
    cout << "***************** Initialization Phase begun *********" << endl;

    // Read parameters
    Read_Parameters(initialization_parameters,"../InitializationData/Initialization_Parameters.csv");
    Read_Parameters(main_loop_parameters,"../InitializationData/Main_Loop_Parameters.csv");
    Read_Parameters(randomness_parameters,"../InitializationData/Randomness_Parameters.csv");



    cout << "This simulation is with the following parameters: n_households: " << n_households << "n_consumer_firms: " << n_consumer_firms 
    << "n_capital_firms: " << n_capital_firms <<  "n_loops: " << n_loops  << endl;

    auto start = std::chrono::high_resolution_clock::now(); // Time program

    // Allocate memory and initialize agents, markets, and sectors
    Public_Info_Board* pPublic_Board_1 = new Public_Info_Board();
    Bank_Agent* pBank_1 = new Bank_Agent(pPublic_Board_1);

    Job_Market* pJob_Market_1 = new Job_Market();
    Consumer_Goods_Market* pConsumer_Goods_Market_1 = new Consumer_Goods_Market();
    Capital_Goods_Market* pCapital_Goods_Market_1 = new Capital_Goods_Market();

    vector<Household_Agent*> *pHousehold_vector = new vector<Household_Agent*>();
    vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector = new vector<Consumer_Firm_Agent*>();
    vector<Capital_Firm_Agent*> *pCapital_Firm_vector = new vector<Capital_Firm_Agent*>();

    vector<Consumer_Firm_Sector*> *pConsumer_Firm_Sector_vector = new vector<Consumer_Firm_Sector*>();
    vector<pair<int, float>>* pFirm_Weighing_vector = new vector<pair<int, float>>(); // TODO: Remove use of this


    Initialize_Households_Firms_Jobs(pHousehold_vector, pConsumer_Firm_vector, pCapital_Firm_vector,
    pPublic_Board_1, pJob_Market_1, pConsumer_Goods_Market_1, pCapital_Goods_Market_1, pBank_1, pConsumer_Firm_Sector_vector,
    pFirm_Weighing_vector);
    
    // Manual Check - remove this later
    int num_sectors = pConsumer_Firm_Sector_vector->size();
    cout << "There are " << num_sectors << " sectors" << endl;
   
    // Create vector housing all firms 
    vector<Firm_Agent*> *pAll_Firms_vector = new vector<Firm_Agent*>();
    std::copy(pConsumer_Firm_vector->begin(), pConsumer_Firm_vector->end(), std::back_inserter(*pAll_Firms_vector));
    std::copy(pCapital_Firm_vector->begin(), pCapital_Firm_vector->end(), std::back_inserter(*pAll_Firms_vector));
    
    // STEP 0.15: Save all Household and Firm properties to a csv file to check success of initialization
    cout << "Step 0.15: Log initial Household and Firm data" << endl;
    Log_Everything(pHousehold_vector,pConsumer_Firm_vector,pCapital_Firm_vector, pPublic_Board_1, pBank_1);


    //  -------- STEP 1 MAIN LOOP -------------------
    cout << "\n***************** Main Loop begun" << endl;
    global_date = 1;

    for ( int i = 0; i < n_loops; i++){
        Time_Step_1(pHousehold_vector, pConsumer_Firm_vector, pCapital_Firm_vector, pAll_Firms_vector,
        pPublic_Board_1, pJob_Market_1, pConsumer_Goods_Market_1, pCapital_Goods_Market_1, pBank_1);
        cout << "Time step " << i << " completed - Logging data now" << endl;
        //Log_Everything(pHousehold_vector,pConsumer_Firm_vector,pCapital_Firm_vector, pPublic_Board_1,pBank_1);
        global_date++;
    }

    cout << "----------------------"<<endl;

    // End program
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    cout << "Program has finished. Execution time: " <<  elapsed_seconds << " s" << endl;
    cout << "Program ran for " << n_loops << " timesteps with " << n_households << " households, " << n_consumer_firms<< " consumer firms and " << n_capital_firms << " capital firms." << endl;


    std::cout.rdbuf(old_cout_buf);
    cout << "Program end :-)\n";


    // Log short description of Simulation
/*     string file_name= "Simulation_H_" + to_string(n_households) + "_Cons_" + to_string(n_consumer_firms) +"_Cap_" + to_string(n_capital_firms) + ".txt";
    cout  << "File name: " << file_name << endl;
    ofstream file( "DataLogs/" + file_name );
    file << "Ran simulation with n_households = " << n_households << "n_consumer_firms = " << 
    n_consumer_firms << "n_capital_firms = " << n_capital_firms << endl;
    file.close();
 */
    
    return 0;
}

