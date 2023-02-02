#include "Initialization_Functions.hpp"


/*Function to set up Job market at t=0
Needs pointers to agent arrays and public board
*/
void Initialize_Job_Market(Consumer_Firm_Agent* Cons_Firm_array,
Capital_Firm_Agent* Cap_Firm_array, Household_Agent* Household_array,
Public_Info_Board* pPublic_Info_Board){

    //cout << "Now initializing job market" << endl;

    cout << "Posting Jobs: Consumer Firms- Begin" << endl;
    Post_Initial_Job_Offers_Cons(Cons_Firm_array, n_consumer_firms);
    cout << "Posting Jobs: Consumer Firms- End" << endl;
    cout << "Posting Jobs: Capital Firms- Begin" << endl;
    Post_Initial_Job_Offers_Cap(Cap_Firm_array, n_capital_firms); 
    cout << "Posting Jobs: Capital Firms- End" << endl;
    

    Job_Market* pJob_Market = pPublic_Info_Board->Get_Job_Market_Ptr();
    //cout << "Sorting Job Market - begin" <<endl;
    pPublic_Info_Board->Sort_Job_Market();
    //cout << "Sorting Job Market - end" <<endl;
    //pJob_Market->Print_Size(); 

    cout << "Household job initialization - begin" << endl;
    Initialize_Household_Jobs(Household_array, n_households);
    cout << "Household job initialization - end" << endl;

    // All firms Check for their new employees
    cout << "Now Consumer firms are checking their job postings" << endl;
    Check_Initial_Job_Offers_Cons(Cons_Firm_array, n_consumer_firms);
    cout << "Now Capital firms are checking their job postings" << endl;
    Check_Initial_Job_Offers_Cap(Cap_Firm_array, n_capital_firms);

    cout << " Job Market Initialization Now Complete" << endl;
    
}