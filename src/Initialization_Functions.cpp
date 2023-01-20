#include "Initialization_Functions.hpp"



void Initialize_Job_Market(Consumer_Firm_Agent* Cons_Firm_array,
Capital_Firm_Agent* Cap_Firm_array, Household_Agent* Household_array,
Public_Info_Board* pPublic_Info_Board){

    Post_Initial_Job_Offers_Cons(Cons_Firm_array, n_consumer_firms);
    Post_Initial_Job_Offers_Cap(Cap_Firm_array, n_capital_firms); 
    
    cout << "Posting jobs complete" << endl;
 
    Job_Market* pJob_Market = pPublic_Info_Board->Get_Job_Market_Ptr();
    pPublic_Info_Board->Sort_Job_Market();
    pJob_Market->Sort_Jobs_by_Wage();
    pJob_Market->Print_Size(); //debugging

    // All households try to find a job
    Initialize_Household_Jobs(Household_array, n_households);

    cout << " Households have got the jobs" << endl;

    // All firms Check for their new employees
    Check_Initial_Job_Offers_Cons(Cons_Firm_array, n_consumer_firms);
    Check_Initial_Job_Offers_Cap(Cap_Firm_array, n_capital_firms);

    cout << " Firms have registered their employees" << endl;

    pJob_Market->Print_Size(); //debugging

    cout << " Job Market Initialization Now Complete" << endl;
    
}