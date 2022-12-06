#include "Public_Info_Board.hpp"


Job_Offer* Public_Info_Board::Get_Top_Job() {
    Job_Offer * job_pointer = new Job_Offer();
    return job_pointer;
    
}




void Public_Info_Board::Remove_Top_Job_Offer(){
    std::cout << "Top job offer taken" <<std::endl;
}