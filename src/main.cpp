#include <iostream>
#include "Public_Info_Board.hpp"
#include "Household_Agent.hpp"

#include "Initialization_Parameters.hpp"
#include "Job.hpp"

using namespace std;

int main()
{


    cout << job_market_size << endl;


    //Public_Info_Board* pPublic_Info_Board = new Public_Info_Board();

    Household_Agent* Household_1 = new Household_Agent(1000, 10, false, false, 500, 0.4,0.2);

    Household_1->Print();


    Job* job_1 = new Job(nullptr,10,1);
    job_1->Print();



    
    

    cout << "Program end :-)\n";
    return 0;
}

