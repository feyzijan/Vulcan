#ifndef RANDOM_FUNCTIONS_HPP
#define RANDOM_FUNCTIONS_HPP

#include <iostream>
#include <vector>
#include <random>
#include <chrono>


// TODO: Add Random seeds based on time so they are truly random

int Uniform_Dist (int min, int max);

int Normal_Dist(int mean, int std, int min, int max);


class Normal_Dist_Generator {
    std::default_random_engine generator;
    std::normal_distribution<float> distribution;
    float min;
    float max;

public:
    Normal_Dist_Generator(float mean, float stddev, float min, float max):
        distribution(mean, stddev), min(min), max(max)
    {}

    float operator ()() {
        while (true) {
            float number = this->distribution(generator);
            if (number >= this->min && number <= this->max)
                return number;
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

    float operator ()() {
        while (true) {
            int number = this->distribution(generator);
            return number;
        }
    }
};

#endif