#include <iostream>
#include <vector>
#include <random>
#include <chrono>


int Uniform_Dist (int min, int max);

int Normal_Dist(int mean, int std, int min, int max);


class Normal_Dist_Generator {
    std::default_random_engine generator;
    std::normal_distribution<double> distribution;
    double min;
    double max;


public:
    Normal_Dist_Generator(double mean, double stddev, double min, double max):
        distribution(mean, stddev), min(min), max(max)
    {}

    double operator ()() {
        while (true) {
            double number = this->distribution(generator);
            if (number >= this->min && number <= this->max)
                return int(number);
        }
    }
};


/* Returns generator of uniform dist
*/
class Uniform_Dist_Generator {
    int min;
    int max;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;
    


public:
    Uniform_Dist_Generator(int min, int max):
        distribution(min,max)
     {}

    double operator ()() {
        while (true) {
            int number = this->distribution(generator);
            return number;
        }
    }
};