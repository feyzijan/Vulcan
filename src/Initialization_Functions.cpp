#include "Initialization_Functions.hpp"

// General Initialization Function
void Initialize_Households_Firms_Jobs( vector<Household_Agent*> *pHousehold_vector, vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector,
 vector<Capital_Firm_Agent*> *pCapital_Firm_vector,  Public_Info_Board* pPublic_Board, Job_Market* pJob_Market,
Consumer_Goods_Market* pConsumer_Goods_Market, Capital_Goods_Market* pCapital_Goods_Market, Bank_Agent* pBank,
vector<Consumer_Firm_Sector*> *pConsumer_Firm_Sector_vector){
        
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

    //----------- STEP 0.14: Initialize consumer firm sectors
    int n_sectors =  Initialize_Consumer_Firm_Sectors(pConsumer_Firm_vector, pConsumer_Firm_Sector_vector,
     pPublic_Board, pConsumer_Goods_Market, pHousehold_vector);

    //----------- STEP 0.16: Send initial goods to markets and initialize price level
    cout << "Step 0.16: Send initial goods to markets and initialize price level" << endl;

    Initialize_Cons_Cap_Goods_Markets(pConsumer_Firm_vector,  pCapital_Firm_vector, pConsumer_Goods_Market,
    pCapital_Goods_Market,pPublic_Board, n_sectors);


}




// ----------------------- Consumer firms

/* Initialize a fixed number of households given an array of suitable size allocated
*/
void Initialize_Consumer_Firms(vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, Public_Info_Board* pPublic_Board, int size)
{
    cout << "\n Initializing " << size << " consumer firms" << endl;

    Normal_Dist_Generator init_dividend_ratio_optimist(firm_cons_init_dividend_ratio_optimist_mean, firm_cons_init_dividend_ratio_optimist_std, firm_cons_init_dividend_ratio_optimist_min, firm_cons_init_dividend_ratio_optimist_max);
    Normal_Dist_Generator init_dividend_ratio_pessimist(firm_cons_init_dividend_ratio_pessimist_mean, firm_cons_init_dividend_ratio_pessimist_std, firm_cons_init_dividend_ratio_pessimist_min, firm_cons_init_dividend_ratio_pessimist_max);
    Normal_Dist_Generator init_desired_inventory_factor(firm_cons_init_desired_inventory_factor_mean, firm_cons_init_desired_inventory_factor_std, firm_cons_init_desired_inventory_factor_min, firm_cons_init_desired_inventory_factor_max);
    Normal_Dist_Generator init_total_assets(firm_cons_init_total_assets_mean, firm_cons_init_total_assets_std, firm_cons_init_total_assets_min, firm_cons_init_total_assets_max);
    Normal_Dist_Generator init_employee_count_desired(firm_cons_init_employee_count_desired_mean, firm_cons_init_employee_count_desired_std, firm_cons_init_employee_count_desired_min, firm_cons_init_employee_count_desired_max);
    Normal_Dist_Generator init_working_capital_inventory(firm_cons_init_working_capital_inventory_mean, firm_cons_init_working_capital_inventory_std, firm_cons_init_working_capital_inventory_min, firm_cons_init_working_capital_inventory_max);
    Normal_Dist_Generator init_inventory(firm_cons_init_inventory_mean, firm_cons_init_inventory_std, firm_cons_init_inventory_min, firm_cons_init_inventory_max);
    Normal_Dist_Generator init_wage_offer(firm_cons_init_wage_offer_mean, firm_cons_init_wage_offer_std, firm_cons_init_wage_offer_min, firm_cons_init_wage_offer_max);
    Normal_Dist_Generator init_production_planned(firm_cons_init_production_planned_mean, firm_cons_init_production_planned_std, firm_cons_init_production_planned_min, firm_cons_init_production_planned_max);
    Normal_Dist_Generator init_good_price_current(firm_cons_init_good_price_current_mean, firm_cons_init_good_price_current_std, firm_cons_init_good_price_current_min, firm_cons_init_good_price_current_max);
   
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
    Normal_Dist_Generator init_dividend_ratio_optimist(firm_cons_init_dividend_ratio_optimist_mean, firm_cons_init_dividend_ratio_optimist_std, firm_cons_init_dividend_ratio_optimist_min, firm_cons_init_dividend_ratio_optimist_max);
    Normal_Dist_Generator init_dividend_ratio_pessimist(firm_cons_init_dividend_ratio_pessimist_mean, firm_cons_init_dividend_ratio_pessimist_std, firm_cons_init_dividend_ratio_pessimist_min, firm_cons_init_dividend_ratio_pessimist_max);
    Normal_Dist_Generator init_desired_inventory_factor(firm_cons_init_desired_inventory_factor_mean, firm_cons_init_desired_inventory_factor_std, firm_cons_init_desired_inventory_factor_min, firm_cons_init_desired_inventory_factor_max);
    
    Normal_Dist_Generator init_total_assets(firm_cons_init_total_assets_mean, firm_cons_init_total_assets_std, firm_cons_init_total_assets_min, firm_cons_init_total_assets_max);
    Normal_Dist_Generator init_employee_count_desired(firm_cons_init_employee_count_desired_mean, firm_cons_init_employee_count_desired_std, firm_cons_init_employee_count_desired_min, firm_cons_init_employee_count_desired_max);
    Normal_Dist_Generator init_working_capital_inventory(firm_cons_init_working_capital_inventory_mean, firm_cons_init_working_capital_inventory_std, firm_cons_init_working_capital_inventory_min, firm_cons_init_working_capital_inventory_max);
    
    Normal_Dist_Generator init_inventory(firm_cap_init_inventory_mean, firm_cap_init_inventory_std, firm_cap_init_inventory_min, firm_cap_init_inventory_max);
    Normal_Dist_Generator init_wage_offer(firm_cons_init_wage_offer_mean, firm_cons_init_wage_offer_std, firm_cons_init_wage_offer_min, firm_cons_init_wage_offer_max);
    Normal_Dist_Generator init_production_planned(firm_cap_init_production_planned_mean, firm_cap_init_production_planned_std, firm_cap_init_production_planned_min, firm_cap_init_production_planned_max);
    Normal_Dist_Generator init_good_price_current(firm_cap_init_good_price_current_mean, firm_cap_init_good_price_current_std, firm_cap_init_good_price_current_min, firm_cap_init_good_price_current_max);
   
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
    Normal_Dist_Generator init_c(household_init_c_mean, household_init_c_std, household_init_c_min, household_init_c_max);
    Normal_Dist_Generator init_s_optimist(household_init_s_optimist_mean, household_init_s_optimist_std, household_init_s_optimist_min, household_init_s_optimist_max);
    Normal_Dist_Generator init_s_pessimist(household_init_s_pessimist_mean, household_init_s_pessimist_std, household_init_s_pessimist_min, household_init_s_pessimist_max);
    Normal_Dist_Generator init_c_f(household_init_c_f_mean, household_init_c_f_std, household_init_c_f_min, household_init_c_f_max);
    Normal_Dist_Generator init_c_h(household_init_c_h_mean, household_init_c_h_std, household_init_c_h_min, household_init_c_h_max);
    Normal_Dist_Generator init_c_excess(household_init_c_excess_mean, household_init_c_excess_std, household_init_c_excess_min, household_init_c_excess_max);
    Normal_Dist_Generator init_p_majority(household_init_p_majority_mean, household_init_p_majority_std, household_init_p_majority_min, household_init_p_majority_max);
    Normal_Dist_Generator init_wealth(household_init_wealth_mean, household_init_wealth_std, household_init_wealth_min, household_init_wealth_max);
    Normal_Dist_Generator init_unemp_tolerance(household_init_unemp_tolerance_mean, household_init_unemp_tolerance_std, household_init_unemp_tolerance_min, household_init_unemp_tolerance_max);
    Normal_Dist_Generator init_res_wage(household_init_res_wage_mean, household_init_res_wage_std, household_init_res_wage_min, household_init_res_wage_max);

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


// ----------------------- Job market ------------------------------//

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
    Consumer_Goods_Market* pConsumer_Goods_Market, Capital_Goods_Market* pCapital_Goods_Market,Public_Info_Board* pPublic_Info_Board, int n_sectors){

    // Order of looping does not matter here
    for(Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector){
        firm_ptr->Send_Goods_To_Market();
        firm_ptr->Update_Average_Profits_T1();
        firm_ptr->Update_Average_Sales_T1();}
    for(Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector){
        firm_ptr->Send_Goods_To_Market();
        firm_ptr->Update_Average_Profits_T1();
        firm_ptr->Update_Average_Sales_T1();}


    // Set up the consumer goods market's sector lists
    pConsumer_Goods_Market->Divide_Goods_Into_Sectors(n_sectors);
    // Sort each sector by price
    pConsumer_Goods_Market->Sort_Cons_Goods_By_Sector_By_Price();
    // Update the price levels in each sector
    pConsumer_Goods_Market->Update_Price_Level_by_Sector();
    pCapital_Goods_Market->Update_Price_Level();

    // Initialize the price levels in public board with these sectors
    pPublic_Info_Board->Initialize_Price_Levels();

}


// ----------------------- Consumer Sectors ------------------------------//
int Initialize_Consumer_Firm_Sectors(vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, vector<Consumer_Firm_Sector*> *pConsumer_Firm_Sector_vector,
Public_Info_Board* pPublic_Info_Board, Consumer_Goods_Market* pConsumer_Goods_Market,
vector<Household_Agent*> *pHousehold_vector){
    // Create the sectors
    int n_sectors = Create_Sectors(pConsumer_Firm_Sector_vector);
    // Assign firms to sectors
    Allocate_Firms_to_Sectors(pConsumer_Firm_vector, pConsumer_Firm_Sector_vector);
    // Set up sectors in the public board
    pPublic_Info_Board->Set_Consumer_Sectors(pConsumer_Firm_Sector_vector, n_sectors);
    
    // Notify Households
    for (Household_Agent* pHousehold : *pHousehold_vector){
        pHousehold->Initialize_Sector_Weights(pConsumer_Firm_Sector_vector);
    }
 
    return n_sectors;

}

int Create_Sectors(std::vector<Consumer_Firm_Sector*> *pConsumer_Firm_Sector_vector) {
    std::ifstream file("../InitializationData/Consumer_Firm_Sectors.csv"); // Open the file

    if (!file.is_open()) { // Check if file is open
        std::cout << "Error opening file" << std::endl;
        return 0;
    }

    string line;
    std::getline(file, line); // Get the first line (headers)

    int temp = 0; // keep track of sector counts

    while (std::getline(file, line)) { // Loop through the rest of the lines
        stringstream ss(line); // Create a stringstream from the line
        string sector_name;
        string sector_id_str;
        string consumption_weighing_str;
        string firm_weighing_str;
        string inv_depr_rate_str;
        string output_per_machine_str;
        string workers_per_machine_str;
        string good_unit_cost_str;
        string max_production_climbdown_str;

        // Parse the comma separated values into separate variables
        if (std::getline(ss, sector_name, ',') && std::getline(ss, sector_id_str, ',') && std::getline(ss, consumption_weighing_str, ',')
            && std::getline(ss, firm_weighing_str, ',') && std::getline(ss, inv_depr_rate_str, ',')
            && std::getline(ss, output_per_machine_str, ',') && std::getline(ss, workers_per_machine_str, ',')
            && std::getline(ss, good_unit_cost_str, ',') && std::getline(ss, max_production_climbdown_str, ',')) {
            // Convert strings to float and int
            int sector_id = std::stoi(sector_id_str);
            float consumption_weighing = std::stof(consumption_weighing_str); 
            float firm_weighing = std::stof(firm_weighing_str);
            float inv_depr_rate = std::stof(inv_depr_rate_str);
            int output_per_machine = std::stoi(output_per_machine_str);
            int workers_per_machine = std::stoi(workers_per_machine_str);
            float good_unit_cost = std::stof(good_unit_cost_str);
            float max_production_climbdown = std::stof(max_production_climbdown_str);

            // Create new instance of Consumer_Firm_Sector struct
            Consumer_Firm_Sector *pSector = new Consumer_Firm_Sector(sector_name, sector_id, consumption_weighing, firm_weighing,
                inv_depr_rate, output_per_machine, workers_per_machine, good_unit_cost, max_production_climbdown); 
            pConsumer_Firm_Sector_vector->push_back(pSector); // Add it to the vector
            temp ++;
        }
    }

    file.close(); // Close the file

    const int n_sectors = temp; // Set the number of sectors as a global parameter
    return temp;
}


/* Function to allocate consumer firms to a sector based on sector weighings

*/
void Allocate_Firms_to_Sectors(vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector,
 vector<Consumer_Firm_Sector*> *pConsumer_Firm_Sector_vector){

        
    std::srand(std::time(0)); // used for random generation
    int total_firms = n_consumer_firms;
    int total_allocation = 0; // keep track of how many firms we have allocated

    // Shuffle the consumer firm vector to ensure randomness
    std::shuffle(pConsumer_Firm_vector->begin(), pConsumer_Firm_vector->end(), std::default_random_engine(std::time(0)));
    
    // Create a vector of pairs of sector_id and sector_weighing ****************
    vector<pair<int, float>> vec_Sector_Weights;
    for (Consumer_Firm_Sector* sector : *pConsumer_Firm_Sector_vector) {
        vec_Sector_Weights.push_back(make_pair(sector->sector_id, sector->firm_weighing));
    }

    // Assign sectors sequentially to the shuffled firms
    int start_index = 0;
    for (auto& weighing_pair : vec_Sector_Weights) // Loop through the vector weighing
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
