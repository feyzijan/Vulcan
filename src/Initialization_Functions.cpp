#include "Initialization_Functions.hpp"

// General Initialization Function
void Initialize_Households_Firms_Jobs( vector<Household_Agent*> *pHousehold_vector, vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector,
 vector<Capital_Firm_Agent*> *pCapital_Firm_vector,  Public_Info_Board* pPublic_Board, Job_Market* pJob_Market,
Consumer_Goods_Market* pConsumer_Goods_Market, Capital_Goods_Market* pCapital_Goods_Market, Bank_Agent* pBank ){
        
    // STEP 0.10: Initalize Public Board, Job Market, Bank, Markets
    cout << " Step 0.10: Initalize Public Board, Job Market, Bank, Markets" << endl;
    pPublic_Board->Set_Job_Market(pJob_Market);
    pPublic_Board->Set_Bank(pBank);
    pPublic_Board->Set_Consumer_Goods_Market(pConsumer_Goods_Market);
    pPublic_Board->Set_Capital_Goods_Market(pCapital_Goods_Market);

    
    //--------- STEP 0.11: Initialize Households and Firms
    cout << " Step 0.11: Initialize Households and Firms" << endl;
    Initialize_Households(pHousehold_vector, pPublic_Board, n_households); 
    Initialize_Consumer_Firms( pConsumer_Firm_vector, pPublic_Board,  n_consumer_firms);
    Initialize_Capital_Firms(pCapital_Firm_vector, pPublic_Board,n_capital_firms);


    //----------- STEP 0.12 Initialize Firm Owners
    cout << " Step 0.12: Initialize Firm Owners" << endl;
    Initialize_Household_Firm_Owners(pHousehold_vector,pConsumer_Firm_vector, pCapital_Firm_vector);

    //----------- STEP 0.13: Initialize job market
    cout << " Step 0.13: Initialize job market" << endl;
    Initialize_Job_Market(pHousehold_vector,pConsumer_Firm_vector,pCapital_Firm_vector,pPublic_Board);
    pJob_Market->Print_Size();
    pPublic_Board->Print_Labor_Market();



    //----------- STEP 0.16: Send initial goods to markets and initialize price level
    cout << "Step 0.16: Send initial goods to markets and initialize price level" << endl;

    Initialize_Cons_Cap_Goods_Markets(pConsumer_Firm_vector,  pCapital_Firm_vector, pConsumer_Goods_Market,
    pCapital_Goods_Market,pPublic_Board);


}




// ----------------------- Consumer firms

/* Initialize a fixed number of households given an array of suitable size allocated
*/
void Initialize_Consumer_Firms(vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, Public_Info_Board* pPublic_Board, int size)
{
    cout << "\n Initializing " << size << " consumer firms" << endl;

    Normal_Dist_Generator init_dividend_ratio_optimist(init_dividend_ratio_optimist_mean, init_dividend_ratio_optimist_std, init_dividend_ratio_optimist_min, init_dividend_ratio_optimist_max);
    Normal_Dist_Generator init_dividend_ratio_pessimist(init_dividend_ratio_pessimist_mean, init_dividend_ratio_pessimist_std, init_dividend_ratio_pessimist_min, init_dividend_ratio_pessimist_max);
    Normal_Dist_Generator init_desired_inventory_factor(init_desired_inventory_factor_mean, init_desired_inventory_factor_std, init_desired_inventory_factor_min, init_desired_inventory_factor_max);
    Normal_Dist_Generator init_total_assets(init_total_assets_mean, init_total_assets_std, init_total_assets_min, init_total_assets_max);
    Normal_Dist_Generator init_employee_count_desired(init_employee_count_desired_mean, init_employee_count_desired_std, init_employee_count_desired_min, init_employee_count_desired_max);
    Normal_Dist_Generator init_working_capital_inventory(init_working_capital_inventory_mean, init_working_capital_inventory_std, init_working_capital_inventory_min, init_working_capital_inventory_max);
    Normal_Dist_Generator init_inventory(init_cons_inventory_mean, init_cons_inventory_std, init_cons_inventory_min, init_cons_inventory_max);
    Normal_Dist_Generator init_wage_offer(init_wage_offer_mean, init_wage_offer_std, init_wage_offer_min, init_wage_offer_max);
    Normal_Dist_Generator init_production_planned(init_cons_production_planned_mean, init_cons_production_planned_std, init_cons_production_planned_min, init_cons_production_planned_max);
    Normal_Dist_Generator init_good_price_current(init_cons_good_price_current_mean, init_cons_good_price_current_std, init_cons_good_price_current_min, init_cons_good_price_current_max);
   
     for (int i=0; i<n_consumer_firms; i++) {
        //cout << " Cons firm initializing #" << i << endl;
        float float_vals[] = {
            init_dividend_ratio_optimist(),  
            init_dividend_ratio_pessimist(),
            init_desired_inventory_factor(), 
            init_good_price_current()
        };
        int int_vals[]{
            int(init_total_assets()),
            int(init_employee_count_desired()),
            int(init_working_capital_inventory()),
            int(init_inventory()),
            int(init_wage_offer()),
            int(init_production_planned()),
        };

        //cout << " set up arrays now passign them in " << endl;
        pConsumer_Firm_vector->push_back(new Consumer_Firm_Agent(float_vals, int_vals));
        //cout << "Cons firm initialized! #" << i << endl;
        pConsumer_Firm_vector->at(i)->Set_Public_Info_Board(pPublic_Board);
        
    }
    //cout << "Consumer Firms initialized" << endl;

}


/* Post all the job offers for all the firms in the array
*/
void Post_Initial_Job_Offers_Cons(vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, int size){
    for (Consumer_Firm_Agent* cons_firm_ptr : *pConsumer_Firm_vector) {
        cons_firm_ptr->Post_Jobs();
    }
}


/* Check all the job offers for all the firms in the array
*/
void Check_Initial_Job_Offers_Cons(vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, int size){
    // loop through all the firms in vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector and call Check_For_new_Employees()
    for (Consumer_Firm_Agent* cons_firm_ptr : *pConsumer_Firm_vector) {
        cons_firm_ptr->Check_For_New_Employees();
    }
}


// ----------------------- Capital firms

void Initialize_Capital_Firms(vector<Capital_Firm_Agent*> *pCapital_Firm_vector, Public_Info_Board* pPublic_Board, int size)
{
    cout << "\n Initializing " << size << " capital firms" << endl;
    Normal_Dist_Generator init_dividend_ratio_optimist(init_dividend_ratio_optimist_mean, init_dividend_ratio_optimist_std, init_dividend_ratio_optimist_min, init_dividend_ratio_optimist_max);
    Normal_Dist_Generator init_dividend_ratio_pessimist(init_dividend_ratio_pessimist_mean, init_dividend_ratio_pessimist_std, init_dividend_ratio_pessimist_min, init_dividend_ratio_pessimist_max);
    Normal_Dist_Generator init_desired_inventory_factor(init_desired_inventory_factor_mean, init_desired_inventory_factor_std, init_desired_inventory_factor_min, init_desired_inventory_factor_max);
    
    Normal_Dist_Generator init_total_assets(init_total_assets_mean, init_total_assets_std, init_total_assets_min, init_total_assets_max);
    Normal_Dist_Generator init_employee_count_desired(init_employee_count_desired_mean, init_employee_count_desired_std, init_employee_count_desired_min, init_employee_count_desired_max);
    Normal_Dist_Generator init_working_capital_inventory(init_working_capital_inventory_mean, init_working_capital_inventory_std, init_working_capital_inventory_min, init_working_capital_inventory_max);
    
    Normal_Dist_Generator init_inventory(init_cap_inventory_mean, init_cap_inventory_std, init_cap_inventory_min, init_cap_inventory_max);
    Normal_Dist_Generator init_wage_offer(init_wage_offer_mean, init_wage_offer_std, init_wage_offer_min, init_wage_offer_max);
    Normal_Dist_Generator init_production_planned(init_cap_production_planned_mean, init_cap_production_planned_std, init_cap_production_planned_min, init_cap_production_planned_max);
    Normal_Dist_Generator init_good_price_current(init_cap_good_price_current_mean, init_cap_good_price_current_std, init_cap_good_price_current_min, init_cap_good_price_current_max);
   
    for (int i=0; i<n_capital_firms; i++) {
        //cout << "cap firm initializing #: "<< i << endl;
        float float_vals[] = {
            init_dividend_ratio_optimist(),  
            init_dividend_ratio_pessimist(),
            init_desired_inventory_factor(), 
            init_good_price_current()
        };
        int int_vals[]{
            int(init_total_assets()),
            int(init_employee_count_desired()),
            int(init_working_capital_inventory()),
            int(init_inventory()),
            int(init_wage_offer()),
            int(init_production_planned()),
        };

        
        pCapital_Firm_vector->push_back(new Capital_Firm_Agent(float_vals, int_vals));
        //cout << "Cons firm initialized! #" << i << endl;
        pCapital_Firm_vector->at(i)->Set_Public_Info_Board(pPublic_Board);
    }
    //cout << "Capital firms initialized" << endl;
}


void Post_Initial_Job_Offers_Cap(vector<Capital_Firm_Agent*> *pCapital_Firm_vector, int size)
{
    for (Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector) {
        firm_ptr->Post_Jobs();
    }
}


void Check_Initial_Job_Offers_Cap(vector<Capital_Firm_Agent*> *pCapital_Firm_vector, int size)
{  
    for (Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector) {
        firm_ptr->Check_For_New_Employees();
    }
}

// ----------------------- Households
void Initialize_Households(vector<Household_Agent*> *pHousehold_vector, Public_Info_Board* pPublic_Board, int size)
{   
    cout << "\n Initializing " << size << " households" << endl;
    
    //Set up Random Generators
    Normal_Dist_Generator init_c(init_c_mean, init_c_std, init_c_min, init_c_max);
    Normal_Dist_Generator init_s_optimist(init_s_optimist_mean, init_s_optimist_std, init_s_optimist_min, init_s_optimist_max);
    Normal_Dist_Generator init_s_pessimist(init_s_pessimist_mean, init_s_pessimist_std, init_s_pessimist_min, init_s_pessimist_max);
    Normal_Dist_Generator init_c_f(init_c_f_mean, init_c_f_std, init_c_f_min, init_c_f_max);
    Normal_Dist_Generator init_c_h(init_c_h_mean, init_c_h_std, init_c_h_min, init_c_h_max);
    Normal_Dist_Generator init_c_excess(init_c_excess_mean, init_c_excess_std, init_c_excess_min, init_c_excess_max);
    Normal_Dist_Generator init_p_majority(init_p_majority_mean, init_p_majority_std, init_p_majority_min, init_p_majority_max);
    Normal_Dist_Generator init_wealth(init_wealth_mean, init_wealth_std, init_wealth_min, init_wealth_max);
    Normal_Dist_Generator init_unemp_tolerance(init_unemp_tolerance_mean, init_unemp_tolerance_std, init_unemp_tolerance_min, init_unemp_tolerance_max);
    Normal_Dist_Generator init_res_wage(init_res_wage_mean, init_res_wage_std, init_res_wage_min, init_res_wage_max);

    for (int i=0; i<size; i++) {
        float propensities[] = { 
            init_c(), // consumption propensity
            init_s_optimist(), // saving_propensity_optimist 
            init_s_pessimist(), // saving_propensity_pessimist
            init_c_f(), // c_f
            init_c_h(), // c_h
            init_c_excess(), // c_excess_money
            init_p_majority(), // p_majority_op_adoption
         };

        int vals[] = {
            int(init_wealth()),
            int(init_unemp_tolerance()),
            int(init_res_wage())
        };


        pHousehold_vector->push_back(new Household_Agent(propensities, vals,pPublic_Board));
        //Household_array[i].Set_Public_Info_Board(pPublic_Board);
        //cout << "The c_h value is " << Household_array[i].Get_C_h() << endl;
    }
}


/* Loop through households and call seek jobs function
*/
void Initialize_Household_Jobs(vector<Household_Agent*> *pHousehold_vector,  int size)
{
    for (Household_Agent* household_ptr : *pHousehold_vector) {
        household_ptr->Seek_Jobs();}
}


/* Loop through all households and randomly set a total of n_firms of them to be firm owners
*/
void Initialize_Household_Firm_Owners(vector<Household_Agent*> *pHousehold_vector, vector<Consumer_Firm_Agent*>* pConsumer_Firm_vector,
 vector<Capital_Firm_Agent*> *pCapital_Firm_vector) {

    int temp = n_consumer_firms + n_capital_firms;  // Number of owners we need 


    // Create a local vector called firms that contains all firms
    vector<Firm_Agent*> firms_vector;
    for (Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector) {
        firms_vector.push_back(firm_ptr);}
    for (Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector) {
        firms_vector.push_back(firm_ptr); }


    // Shuffle the household vector
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(pHousehold_vector->begin(), pHousehold_vector->end(), g);

    // Set the first `temp` households as firm owners and decrement `temp` each time
    for (Household_Agent* household_ptr : *pHousehold_vector) {
        if (temp <= 0) {
        break; }
        household_ptr->Set_Firm_Owner(firms_vector[0]);  // Set the firm owner to the first firm in the shuffled firm vector

        firms_vector.erase(firms_vector.begin());  // Remove the first firm from the shuffled firm vector
        temp--;  // Decrement the number of households left to set as firm owners
    }
    cout << "Finished setting firm owners" << n_consumer_firms + n_firms - temp << " households are owners" << endl;
}







// ----------------------- Job market
/*Function to set up Job market at t=0
Needs pointers to agent arrays and public board
*/
void Initialize_Job_Market(vector<Household_Agent*> *pHousehold_vector,
    vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, vector<Capital_Firm_Agent*> *pCapital_Firm_vector,
    Public_Info_Board* pPublic_Info_Board){

    //cout << "Now initializing job market" << endl;

    cout << "Posting Jobs: Consumer Firms- Begin" << endl;
    Post_Initial_Job_Offers_Cons(pConsumer_Firm_vector, n_consumer_firms);
    cout << "Posting Jobs: Consumer Firms- End" << endl;
    cout << "Posting Jobs: Capital Firms- Begin" << endl;
    Post_Initial_Job_Offers_Cap(pCapital_Firm_vector, n_capital_firms); 
    cout << "Posting Jobs: Capital Firms- End" << endl;
    

    Job_Market* pJob_Market = pPublic_Info_Board->Get_Job_Market_Ptr();
    //cout << "Sorting Job Market - begin" <<endl;
    pPublic_Info_Board->Sort_Job_Market();
    //cout << "Sorting Job Market - end" <<endl;
    //pJob_Market->Print_Size(); 

    cout << "Household job initialization - begin" << endl;

    // Shuffle households
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(pHousehold_vector->begin(), pHousehold_vector->end(), g);

    Initialize_Household_Jobs(pHousehold_vector, n_households);
    cout << "Household job initialization - end" << endl;

    // All firms Check for their new employees
    cout << "Now Consumer firms are checking their job postings" << endl;
    Check_Initial_Job_Offers_Cons(pConsumer_Firm_vector, n_consumer_firms);
    cout << "Now Capital firms are checking their job postings" << endl;
    Check_Initial_Job_Offers_Cap(pCapital_Firm_vector, n_capital_firms);

    cout << " Job Market Initialization Now Complete" << endl;
    
}

// ---- Consumer and Capital goods market
// Function to set up Consumer Goods market at t=0
void Initialize_Cons_Cap_Goods_Markets(vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, vector<Capital_Firm_Agent*> *pCapital_Firm_vector,
    Consumer_Goods_Market* pConsumer_Goods_Market, Capital_Goods_Market* pCapital_Goods_Market,Public_Info_Board* pPublic_Info_Board){

    // Order of looping does not matter here
    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Send_Goods_To_Market();
        firm_ptr->Update_Average_Profits_T1();
        firm_ptr->Update_Average_Sales_T1();}
    for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Send_Goods_To_Market();
        firm_ptr->Update_Average_Profits_T1();
        firm_ptr->Update_Average_Sales_T1();}

    pConsumer_Goods_Market->Update_Price_Level();
    pCapital_Goods_Market->Update_Price_Level();

    pPublic_Info_Board->Initialize_Price_Level();

}

void Create_Sectors(std::vector<Consumer_Firm_Sector*> *pConsumer_Firm_Sector_vector,std::vector<std::pair<int, float>>* pFirm_Weighing_vector) {
    std::ifstream file("../InitializationData/Consumer_Firm_Sectors.csv"); // Open the file

    if (!file.is_open()) { // Check if file is open
        std::cout << "Error opening file" << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Get the first line (headers)

    int temp = 0; // keep track of sector counts

    while (std::getline(file, line)) { // Loop through the rest of the lines
        std::stringstream ss(line); // Create a stringstream from the line
        std::string sector_name;
        std::string consumption_weighing_str;
        std::string sector_id_str;
        std::string firm_weighing_str;

        if (std::getline(ss, sector_name, ',') // Parse the comma separated values into separate variables
            && std::getline(ss, consumption_weighing_str, ',')
            && std::getline(ss, sector_id_str, ',')
            && std::getline(ss, firm_weighing_str, ',')) {
            float consumption_weighing = std::stof(consumption_weighing_str); // Convert strings to float and int
            int sector_id = std::stoi(sector_id_str);
            float firm_weighing = std::stof(firm_weighing_str);

            Consumer_Firm_Sector *pSector = new Consumer_Firm_Sector(sector_name, consumption_weighing, sector_id); // Create new instance of Consumer_Firm_Sector struct
            pConsumer_Firm_Sector_vector->push_back(pSector); // Add it to the vector
            temp ++;
            // Push the pair of sector_id and firm_weighing to the vector
            std::pair<int, float> pair(sector_id, firm_weighing);
            pFirm_Weighing_vector->push_back(pair);
        }
    }

    file.close(); // Close the file

    const int n_sectors = temp; // Set the number of sectors as a global parameter
}


/* Function to allocate consumer firms to a sector based on sector weighings, which are given in the pFirm_Weighing_vector

*/
void Allocate_Firms_to_Sectors(vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector,
 vector<Consumer_Firm_Sector*> *pConsumer_Firm_Sector_vector,std::vector<std::pair<int, float>>* pFirm_Weighing_vector){

        
    std::srand(std::time(0)); // used for random generation
    int total_firms = n_consumer_firms;
    int total_allocation = 0; // keep track of how many firms we have allocated

    // Shuffle the consumer firm vector to ensure randomness
    std::shuffle(pConsumer_Firm_vector->begin(), pConsumer_Firm_vector->end(), std::default_random_engine(std::time(0)));


    // Assign sectors sequentially to the shuffled firms
    int start_index = 0;
    for (auto& weighing_pair : *pFirm_Weighing_vector) // Loop through the vector weighing
    { 
        // Calculate the number of firms to allocate to this sector - round the value up to ensure we allocate all firms
        int sector_id = weighing_pair.first;
        float sector_weighing = weighing_pair.second;
        int firms_to_allocate = max(1, static_cast<int>(round(total_firms * sector_weighing)));
        int allocation_counter = 0;
        cout << "Planning to allocate " << firms_to_allocate << " firms to sector #" << sector_id << endl;

        // Find the corresponding sector from the sector vector
        Consumer_Firm_Sector* target_sector = nullptr;
        for (Consumer_Firm_Sector* sector : *pConsumer_Firm_Sector_vector) {
            if (sector->sector_id == sector_id) {
                target_sector = sector;
                break;
            }
        }

        if (target_sector == nullptr) {
            // Sector not found, skip this iteration
            cout << "Error: Sector "<< sector_id << " not found " << endl;
            continue;
        }

        // Randomly allocate firms to the sector
        for (int i = 0; i < firms_to_allocate; ++i) {

            // Due to the rounding of int firms_to_allocate, we will try to allocate more firms than we have
            if (start_index >= pConsumer_Firm_vector->size()) {
                break;
            }

            Consumer_Firm_Agent* selected_firm = (*pConsumer_Firm_vector)[start_index];
            selected_firm->Assign_Sector(target_sector);
            start_index++;
            allocation_counter++;
            total_allocation++;
        }
        cout << " Allocated " << allocation_counter << " firms to sector " << sector_id << endl;
    }
    cout << "Allocated a total of " << total_allocation << " firms out of  " << n_consumer_firms << " to a sector" <<  endl;


    if (total_allocation != n_consumer_firms) {
        cout << "Problem: Not all firms have been allocated to a sector, allocating remaining firms to last sector " << endl;
        // Allocate remaining firms to the first sector
        for (int i = start_index; i < pConsumer_Firm_vector->size(); ++i) {
            Consumer_Firm_Agent* selected_firm = (*pConsumer_Firm_vector)[i];
            selected_firm->Assign_Sector((*pConsumer_Firm_Sector_vector)[0]);
            total_allocation ++;
        }
        cout << "Now allocated a total of " << total_allocation << " firms out of  " << n_consumer_firms << " to a sector" <<  endl;
    }
    

 }
