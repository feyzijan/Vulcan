# include <iostream>
#include <array>

using namespace std;

int main() {
    int past_data[10] = {0};

    past_data[0] = 2;
    past_data[1] = 3;

    cout << past_data[0] << endl;
    cout << ( past_data[1] == 0 )<< endl;

    int * pMyint = 0;

    cout << (pMyint == 0) << endl;


    bool my_sentiment = true;

    int my_int = 4;

    my_int +=my_sentiment;

    cout << my_int << endl;

    return 0;
}
