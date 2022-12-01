# include <iostream>
#include <array>

using namespace std;

int main() {
    int past_data[10] = {0};

    past_data[0] = 2;
    past_data[1] = 3;

    cout << past_data[0] << endl;
    cout << ( past_data[1] == 0 )<< endl;

    return 0;
}
