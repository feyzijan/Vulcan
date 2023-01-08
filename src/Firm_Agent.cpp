#include "Firm_Agent.hpp"






void Firm_Agent::Print(){
    
}









void Firm_Agent::Update_Price()
{
    //int current_price = GetPrice();
    //n_uniform = uniform_dist(0,0.5);
    float n_uniform = 1; //Update this to be from uniform dist

    if (Inventory_Above_Desire())
    {
        good_price_current *= (1 + n_uniform);
    } else{
        good_price_current *= (1 - n_uniform);
    }


}

void Firm_Agent::Adjust_Wage_Offers()
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





/* Function that sets desired production for next timestep

*/
void Firm_Agent::Plan_Production()
{
    int n_uniform = 1; //Update this to be from uniform dist

    if (Inventory_Above_Desire())
    {
        production_planned = production_current *  (1 + n_uniform);
    } else {
        good_price_current = production_current *  (1 - n_uniform);
    }

}




/* Function to check sales in the preceeding period,
Update inventory, sales figure, etc.

*/
void Firm_Agent::Check_Sales()
{
    production_past = production_current; // The then current production is now past
    production_current = 0; // initialize current prod to zero
    quantity_sold = production_past -  goods_on_market->Get_Quantity(); // determine how much has been sold
    inventory += goods_on_market->Get_Quantity(); // determine how much is in inventory

    good_price_past = good_price_current;// The then current price is now past
    good_price_current = 0; // initialize current price to zero

    revenue_sales =  quantity_sold * good_price_past;

}




/* Function to pay liabilities and seek loans or go bankrupt if necessary

*/

void Firm_Agent::Pay_Liabilities(){
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
    employee_count = 0;

    for (int i = 0; i++; i<sizeof(employee_list))
    {
        if (employee_list[i] != NULL){
            labor_wage_bill += employee_list[i]->Get_Wage();
            employee_count += 1;
        }
    }

    total_liabilities = labor_wage_bill + debt_principal_payments + debt_interest_payments;

    int money_on_hand = revenue_sales + cash_on_hand < total_liabilities; 
    if (money_on_hand  < 0)
    {
        new_loan_issuance = Seek_Loans(); // implement this method, have it update new_loan_issuance
    }

    money_on_hand += new_loan_issuance;

    if (money_on_hand  < 0)
    {
       bankrupt = true;

    } else {
        dividend_payments = money_on_hand * dividend_ratio;
    }


}

