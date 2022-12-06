#include <iostream>
#include "Public_Info_Board.hpp"
#include "Household_Agent.hpp"

#include "Initialization_Parameters.hpp"


using namespace std;

int main()
{


    cout << job_market_size << endl;


    //Public_Info_Board* pPublic_Info_Board = new Public_Info_Board();

    Household_Agent* Household_1 = new Household_Agent(1000, 10, false, false, 500, 0.4,0.2);

    Household_1->Print();


    
    

    std::cout << "Hello World :-)\n";
    return 0;
}

