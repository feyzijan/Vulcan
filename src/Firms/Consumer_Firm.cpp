#include "Consumer_Firm.hpp"
#include <iostream>

int main(){
    return 0;
}




// Constructor
Consumer_Firm_Agent::Consumer_Firm_Agent()
{
    loan_book = {NULL}; // sett all elements to null

}





//Copy constructor
Consumer_Firm_Agent::Consumer_Firm_Agent(Consumer_Firm_Agent&)
{

}



// Destructor
Consumer_Firm_Agent::~Consumer_Firm_Agent()
{

} 


/* Function to check sales in the preceeding period,
Update inventory, sales figure, etc.

*/
void Consumer_Firm_Agent::Check_Sales()
{
    production_past = production_current; // The then current production is now past
    production_current = 0; // initialize current prod to zero
    quantity_sold = production_past - int goods_on_market->GetQuantity(); // determine how much has been sold
    consumer_goods_inventory += int goods_on_market->GetQuantity(); // determine how much is in inventory

    good_price_past = good_price_current;// The then current price is now past
    good_price_current = 0; // initialize current price to zero

    revenue_current =  quantity_sold * good_price_past;

}

/* Function to pay liabilities and seek loans or go bankrupt if necessary

*/

void Consumer_Firm_Agent::Pay_Liabilities(){
    //Initialize debt payments to zero
    debt_principal_payments, debt_interest_payments = 0;
    
    //Sum up all needed debt repayments
    for (int i = 0; i++; i<sizeof(loan_book))
    {
        if (loan_book[i] != NULL){
            debt_principal_payments += loan_book[i]->Calculate_Principal_Repayment();
            debt_interest_payments += loan_book[i]->Calculate_Interest_Repayment();
        }
    }

    //Sum up wage bill
    labor_wage_bill = 0;
    worker_count_actual = 0;

    for (int i = 0; i++; i<sizeof(employee_list))
    {
        if (employee_list[i] != NULL){
            labor_wage_bill += employee_list[i]->GetWage();
            worker_count_actual += 1;
        }
    }

    total_liabilities = labor_wage_bill + debt_principal_payments + debt_interest_payments;

    int money_on_hand = revenue_current + cash_savings < total_liabilties; 
    if (money_on_hand  < 0)
    {
        new_loan_issuance = Seek_Loans(money_on_hand); // implement this method, have it update new_loan_issuance
    }

    money_on_hand += new_loan_issuance;

    if (money_on_hand  < 0)
    {
       bankrupt = True;

    } else {
        dividend_payments = money_on_hand * dividend_ratio;
    }


}








/* Function that sets desired production for next timestep

*/
void Consumer_Firm_Agent::Plan_Production()
{
    int n_uniform = 1; //Update this to be from uniform dist

    if (Inventory_Above_Desire())
    {
        planned_production = current_production *  (1 + n_uniform);
    } else {
        good_price = current_production *  (1 - n_uniform);
    }

}


void Consumer_Firm_Agent::Update_Price()
{
    //int current_price = GetPrice();
    //n_uniform = uniform_dist(0,0.5);
    float n_uniform = 1; //Update this to be from uniform dist

    if (Inventory_Above_Desire())
    {
        good_price *= (1 + n_uniform);
    } else{
        good_price *= (1 - n_uniform);
    }


}

void Consumer_Firm_Agent::Adjust_Wage_Offers()
{
    float w_stoc; // a stochastic cutoff value for labor
    float n_uniform; // value drawn from uniform dist

    if (w_current - w_target >= w_current)
    {
        wage_offer*= (1+n_uniform);
    } else{
        wage_offer*= (1-n_uniform);
    }


}
