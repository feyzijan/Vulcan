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
    cout << "STEP 0.11: Initialize Households and Firms" << endl;
    Initialize_Households(pHousehold_vector, pPublic_Board, n_households); 
    Initialize_Consumer_Firms( pConsumer_Firm_vector, pPublic_Board,  n_consumer_firms);
    Initialize_Capital_Firms(pCapital_Firm_vector, pPublic_Board,n_capital_firms);


    //----------- STEP 0.12 Initialize Firm Owners
    cout << "STEP 0.12: Initialize Firm Owners" << endl;
    Initialize_Firm_Owners(pHousehold_vector,pConsumer_Firm_vector, pCapital_Firm_vector);


    //----------- STEP 0.13: Initialize job market
    cout << "STEP 0.13: Initialize job market" << endl;
    Initialize_Job_Market(pHousehold_vector,pConsumer_Firm_vector,pCapital_Firm_vector,pPublic_Board);
    cout << "Job market size: " << pJob_Market->Get_Size() << endl; 


    //----------- STEP 0.14: Initialize consumer firm sectors
    cout << "STEP 0.14: Initialize consumer firm sectors" << endl;
    Initialize_Consumer_Firm_Sectors(pConsumer_Firm_vector, pConsumer_Firm_Sector_vector,
        pPublic_Board, pConsumer_Goods_Market, pHousehold_vector);


    //----------- STEP 0.15: Initialize emission allowances - This must be done after employees and sectors are set
    cout << "STEP 0.15: Initialize emission allowances" << endl;
    for (auto it = pConsumer_Firm_vector->begin(); it != pConsumer_Firm_vector->end(); ++it){
        (*it)->Initialize_Emission_Allowances(); }


    //---------- STEP 0.16: Initialize Production - Must be done after job market matching
    cout << "STEP 0.16: Initialize Production based on Job Market matching" << endl;
    for (auto it = pConsumer_Firm_vector->begin(); it != pConsumer_Firm_vector->end(); ++it){
        (*it)->Initialize_Production(); }
    for (auto it = pCapital_Firm_vector->begin(); it != pCapital_Firm_vector->end(); ++it){
        (*it)->Initialize_Production(); }


    //----------- STEP 0.17: Send initial goods to markets and initialize price level
    cout << "Step 0.17: Send initial goods to markets and initialize price level" << endl;
    Initialize_Markets(pConsumer_Firm_vector,  pCapital_Firm_vector, pConsumer_Goods_Market,
    pCapital_Goods_Market,pPublic_Board, pConsumer_Firm_Sector_vector);
}



// ----------------------- Consumer firms

/* Initialize a fixed number of households given an array of suitable size allocated
*/
void Initialize_Consumer_Firms(vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, Public_Info_Board* pPublic_Board, int size)
{
    cout << "\nInitializing " << size << " consumer firms" << endl;

    Normal_Dist_Generator init_target_inv_factor(firm_cons_init_target_inv_factor_mean, firm_cons_init_target_inv_factor_std, firm_cons_init_target_inv_factor_min, firm_cons_init_target_inv_factor_max);
    Normal_Dist_Generator init_cash(firm_cons_init_cash_mean, firm_cons_init_cash_std, firm_cons_init_cash_min, firm_cons_init_cash_max);
    Normal_Dist_Generator init_worker_demand(firm_cons_init_worker_demand_mean, firm_cons_init_worker_demand_std, firm_cons_init_worker_demand_min, firm_cons_init_worker_demand_max);
    Normal_Dist_Generator init_inv_factor(firm_cons_init_inv_factor_mean, firm_cons_init_inv_factor_std, firm_cons_init_inv_factor_min, firm_cons_init_inv_factor_max);
    Normal_Dist_Generator init_wage_offer(firm_cons_init_wage_offer_mean, firm_cons_init_wage_offer_std, firm_cons_init_wage_offer_min, firm_cons_init_wage_offer_max);
    Normal_Dist_Generator init_cons_good_price(firm_cons_init_good_price_mean, firm_cons_init_good_price_std, firm_cons_init_good_price_min, firm_cons_init_good_price_max);
   
    int object_id = 0;
    for (int i=0; i<n_consumer_firms; i++) {
        //cout << " Cons firm initializing #" << i << endl;
        float init_values[] = {
            init_target_inv_factor(), 
            init_cons_good_price(),
            init_inv_factor(),
            init_cash(),
            init_worker_demand(),
            init_wage_offer(),
            static_cast<float>(object_id)
        };
        pConsumer_Firm_vector->push_back(new Consumer_Firm_Agent(init_values));
        //cout << "Cons firm initialized! #" << i << endl;
        pConsumer_Firm_vector->at(i)->Set_Public_Info_Board(pPublic_Board);  
    }
    object_id += 1;
    //cout << "Consumer Firms initialized" << endl;
}



// Initialize emission allowances
void Initialize_Emission_Allowances(vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, Public_Info_Board* pPublic_Board){
    // loop through all the consumer firms and call the public board's function to set the allowances
    for (Consumer_Firm_Agent* cons_firm_ptr : *pConsumer_Firm_vector) {
        int n_employees = cons_firm_ptr->Get_Employee_Count();
        int sector_id = cons_firm_ptr->Get_Sector_ID();
        pPublic_Board->Distribute_Initial_Emission_Allowances(n_employees, sector_id);
    }
}


// ----------------------- Capital firms

void Initialize_Capital_Firms(vector<Capital_Firm_Agent*> *pCapital_Firm_vector, Public_Info_Board* pPublic_Board, int size)
{
    cout << "\nInitializing " << size << " capital firms" << endl;
    
    Normal_Dist_Generator init_target_inv_factor(firm_cons_init_target_inv_factor_mean, firm_cons_init_target_inv_factor_std, firm_cons_init_target_inv_factor_min, firm_cons_init_target_inv_factor_max);
    Normal_Dist_Generator init_cash(firm_cons_init_cash_mean, firm_cons_init_cash_std, firm_cons_init_cash_min, firm_cons_init_cash_max);
    Normal_Dist_Generator init_worker_demand(firm_cons_init_worker_demand_mean, firm_cons_init_worker_demand_std, firm_cons_init_worker_demand_min, firm_cons_init_worker_demand_max);
    Normal_Dist_Generator init_inv_factor(firm_cap_init_inv_factor_mean, firm_cap_init_inv_factor_std, firm_cap_init_inv_factor_min, firm_cap_init_inv_factor_max);
    Normal_Dist_Generator init_wage_offer(firm_cons_init_wage_offer_mean, firm_cons_init_wage_offer_std, firm_cons_init_wage_offer_min, firm_cons_init_wage_offer_max);
    Normal_Dist_Generator init_cap_good_price(firm_cap_init_good_price_mean, firm_cap_init_good_price_std, firm_cap_init_good_price_min, firm_cap_init_good_price_max);
   
    int object_id = 0;
    for (int i=0; i<n_capital_firms; i++) {
        //cout << "cap firm initializing #: "<< i << endl;
        float init_values[] = {
            init_target_inv_factor(), 
            init_cap_good_price(),
            init_inv_factor(),
            init_cash(),
            init_worker_demand(),
            init_wage_offer(),
            static_cast<float>(object_id)
        };
        pCapital_Firm_vector->push_back(new Capital_Firm_Agent(init_values));
        //cout << "Cons firm initialized! #" << i << endl;
        pCapital_Firm_vector->at(i)->Set_Public_Info_Board(pPublic_Board);
    }
    object_id += 1;
    //cout << "Capital firms initialized" << endl;
}

// ----------------------- Households
void Initialize_Households(vector<Household_Agent*> *pHousehold_vector, Public_Info_Board* pPublic_Board, int size)
{   
    cout << "\nInitializing " << size << " households" << endl;
    
    //Set up Random Generators
    Normal_Dist_Generator init_s_optimist(household_init_s_optimist_mean, household_init_s_optimist_std, household_init_s_optimist_min, household_init_s_optimist_max);
    Normal_Dist_Generator init_s_pessimist(household_init_s_pessimist_mean, household_init_s_pessimist_std, household_init_s_pessimist_min, household_init_s_pessimist_max);
    Normal_Dist_Generator init_c_f(household_init_c_f_mean, household_init_c_f_std, household_init_c_f_min, household_init_c_f_max);
    Normal_Dist_Generator init_c_excess(household_init_c_excess_mean, household_init_c_excess_std, household_init_c_excess_min, household_init_c_excess_max);
    
    Normal_Dist_Generator init_wealth(household_init_wealth_mean, household_init_wealth_std, household_init_wealth_min, household_init_wealth_max);
    Normal_Dist_Generator init_unemp_tolerance(household_init_unemp_tolerance_mean, household_init_unemp_tolerance_std, household_init_unemp_tolerance_min, household_init_unemp_tolerance_max);
    Normal_Dist_Generator init_res_wage(household_init_res_wage_mean, household_init_res_wage_std, household_init_res_wage_min, household_init_res_wage_max);

    int object_id = 1;
    for (int i=0; i<size; i++) {
        float propensities[] = { 
            init_s_optimist(), // saving_propensity_optimist 
            init_s_pessimist(), // saving_propensity_pessimist
            init_c_f(), // c_f
            init_c_excess(), // c_excess_money
         };

        int vals[] = {
            int(init_wealth()),
            int(init_unemp_tolerance()),
            int(init_res_wage())
        };
        pHousehold_vector->push_back(new Household_Agent(propensities, vals, object_id, pPublic_Board));
        object_id +=1;
    }
}


/* Function to initialize the firm owners for each firm
Loop through all households and randomly set a total of n_firms of them to be firm owners
*/
void Initialize_Firm_Owners(vector<Household_Agent*> *pHousehold_vector, vector<Consumer_Firm_Agent*>* pConsumer_Firm_vector,
 vector<Capital_Firm_Agent*> *pCapital_Firm_vector) {

    int temp = n_consumer_firms + n_capital_firms;  // Number of owners we need 

    // Create a local vector that contains all firms
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
            break; 
        } 
        else {
            household_ptr->Set_Firm_Owner(firms_vector[0]);  // Set the firm owner to the first firm in the shuffled firm vector
            firms_vector.erase(firms_vector.begin());  // Remove the first firm from the shuffled firm vector
            temp--;  // Decrement the number of households left to set as firm owners
        }
    }
    cout << "Finished setting firm owners" << n_consumer_firms + n_capital_firms - temp << " households are owners" << endl;
}


// ----------------------- Job market ------------------------------//

/* Function to set up Job market at t=0
Needs pointers to agent arrays and public board
*/
void Initialize_Job_Market(vector<Household_Agent*> *pHousehold_vector,
    vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, vector<Capital_Firm_Agent*> *pCapital_Firm_vector,
    Public_Info_Board* pPublic_Info_Board){

    cout << "Now initializing job market" << endl;

    cout << "Posting Jobs: Consumer Firms- Begin" << endl;
    for (Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector) {firm_ptr->Post_Jobs();}
    cout << "Posting Jobs: Consumer Firms- End" << endl;
    cout << "Posting Jobs: Capital Firms- Begin" << endl;
    for (Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector) {firm_ptr->Post_Jobs();}
    cout << "Posting Jobs: Capital Firms- End" << endl;
    
    pPublic_Info_Board->Sort_Job_Market();

    cout << "Household job initialization - begin" << endl;

    // Shuffle households
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(pHousehold_vector->begin(), pHousehold_vector->end(), g);

    for (Household_Agent* household_ptr : *pHousehold_vector) {
        household_ptr->Seek_Jobs();
        household_ptr->Update_Public_Board_On_Employment();
        
        }

    cout << "Household job initialization - end" << endl;

    // All firms Check for their new employees
    cout << "Now Consumer firms are checking their job postings" << endl;
    for (Consumer_Firm_Agent* firm_ptr : *pConsumer_Firm_vector) {firm_ptr->Check_For_New_Employees();}
    cout << "Now Capital firms are checking their job postings" << endl;
    for (Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector) {firm_ptr->Check_For_New_Employees();}
    cout << " Job Market Initialization Now Complete" << endl;
}


/* Function to initialize consumer and capital markets 
*/
void Initialize_Markets(vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, vector<Capital_Firm_Agent*> *pCapital_Firm_vector,
    Consumer_Goods_Market* pConsumer_Goods_Market, Capital_Goods_Market* pCapital_Goods_Market,Public_Info_Board* pPublic_Info_Board,
    vector<Consumer_Firm_Sector*> *pConsumer_Firm_Sector_vector){

    // Set up the consumer goods market's sector lists and sort each sector by price
    pConsumer_Goods_Market->Divide_Goods_Into_Sectors(pConsumer_Firm_Sector_vector);
    pConsumer_Goods_Market->Sort_Cons_Goods_By_Sector_By_Price();

    // Set up the emission baskets in the consumer good market, and sort each by emission adjusted
    pConsumer_Goods_Market->Divide_Goods_Into_Emission_Adjusted_Price_Levels(); 
    pConsumer_Goods_Market->Sort_Cons_Goods_By_Sector_By_Price_and_Emissions();

    // Update the price levels in each sector
    pConsumer_Goods_Market->Update_Price_Level();
    pCapital_Goods_Market->Update_Price_Level();

    // Initialize the price levels in public board with these sectors
    pPublic_Info_Board->Initialize_Price_Levels();
}


// ----------------------- Consumer Sectors ------------------------------//

/* Function to initialize consumer firm sectors
*/
void Initialize_Consumer_Firm_Sectors(vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, vector<Consumer_Firm_Sector*> *pConsumer_Firm_Sector_vector,
Public_Info_Board* pPublic_Info_Board, Consumer_Goods_Market* pConsumer_Goods_Market,
vector<Household_Agent*> *pHousehold_vector){
    cout << "Initializing Consumer Firm Sectors" << endl;
    // Create the sectors
    Create_Sectors(pConsumer_Firm_Sector_vector);
    // Assign firms to sectors
    Allocate_Firms_to_Sectors(pConsumer_Firm_vector, pConsumer_Firm_Sector_vector);
    // Set up sectors in the public board
    pPublic_Info_Board->Initialize_Consumer_Sectors(pConsumer_Firm_Sector_vector);
    
    // Notify Households
    for (Household_Agent* pHousehold : *pHousehold_vector){
        pHousehold->Initialize_Sector_Weights(pConsumer_Firm_Sector_vector);
        pHousehold->Initialize_Sector_Emission_Sensitivities(pConsumer_Firm_Sector_vector);
    }
 
    cout << "There are " << sector_count << " consumer sectors in this simulation" << endl;
}


/* Function to create sectors and add them to the given vector
 * Returns the number of sectors created
*/
void Create_Sectors(vector<Consumer_Firm_Sector*> *pConsumer_Firm_Sector_vector) {
    std::ifstream file("../InitializationData/Consumer_Firm_Sectors.csv"); // Open the file

    if (!file.is_open()) { // Check if file is open
        std::cout << "ERROR opening file in Create_Sectors()" << std::endl;
    }

    string line;
    std::getline(file, line); // Get the first line (headers)

    int temp = 0; // keep track of sector counts

    while (std::getline(file, line)) { // Loop through the rest of the lines
        stringstream ss(line); // Create a stringstream from the line
        string sector_name;
        string sector_id_str;
        string weighing_str;
        string inv_depr_rate_str;
        string output_per_machine_str;
        string good_unit_cost_str;
        string emission_per_unit_str;
        string emission_sensitivity_mean_str;
        string emission_allowance_str;

        // Parse the comma separated values into separate variables
        if (std::getline(ss, sector_name, ',') && std::getline(ss, sector_id_str, ',') && std::getline(ss, weighing_str, ',')
            && std::getline(ss, inv_depr_rate_str, ',') && std::getline(ss, output_per_machine_str, ',') 
            && std::getline(ss, good_unit_cost_str, ',') 
            && std::getline(ss, emission_per_unit_str, ',')
            && std::getline(ss, emission_sensitivity_mean_str, ',') && std::getline(ss, emission_allowance_str, ',')) {
            // Convert strings to float and int
            int sector_id = std::stoi(sector_id_str);
            float weighing = std::stof(weighing_str); 
            float inv_depr_rate = std::stof(inv_depr_rate_str);
            int output_per_machine = std::stoi(output_per_machine_str);
            float good_unit_cost = std::stof(good_unit_cost_str);
            float emission_per_unit = std::stof(emission_per_unit_str);
            float emission_sensitivity_mean = std::stof(emission_sensitivity_mean_str);
            int emission_allowance = std::stoul(emission_allowance_str);
    
            // Create new instance of Consumer_Firm_Sector struct
            Consumer_Firm_Sector *pSector = new Consumer_Firm_Sector(sector_name, sector_id, weighing, inv_depr_rate, output_per_machine,
            good_unit_cost, emission_per_unit, emission_sensitivity_mean, emission_allowance); 
            pConsumer_Firm_Sector_vector->push_back(pSector); // Add it to the vector
            temp ++;
        }
    }

    file.close(); // Close the file

    cout << "Create sectors function has created " << temp << " consumer sectors" << endl;
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
        vec_Sector_Weights.push_back(make_pair(sector->sector_id, sector->weighing));
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
        cout << "Planning to allocate " << firms_to_allocate << " firms to sector # " << sector_id << endl;

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
            cout << "ERROR: in Allocate_Firms_to_Sectors: Sector "<< sector_id << " not found " << endl;
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
        cout << "Not all firms have been allocated to a sector, allocating remaining firms to last sector " << endl;
        // Allocate remaining firms to the first sector
        for (int i = start_index; i < pConsumer_Firm_vector->size(); ++i) {
            Consumer_Firm_Agent* selected_firm = (*pConsumer_Firm_vector)[i];
            selected_firm->Assign_Sector((*pConsumer_Firm_Sector_vector)[0]);
            total_allocation ++;
        }
        cout << "Now allocated a total of " << total_allocation << " firms out of  " << n_consumer_firms << " to a sector" <<  endl;
    }
 }