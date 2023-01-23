#include "Random_Functions.hpp"



int Uniform_Dist (int min, int max)
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::default_random_engine generator(seed);
  std::uniform_int_distribution<int> distribution (min,max);
  return distribution(generator);
}



int Normal_Dist(int mean, int std, int min, int max)
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::default_random_engine generator(seed);
  std::normal_distribution<double> distribution;
  return int(distribution(generator));

}