#include "Random_Functions.hpp"



int Uniform_Dist_Int (int min, int max)
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::default_random_engine generator(seed);
  std::uniform_int_distribution<int> distribution (min,max);
  return distribution(generator);
}

float Uniform_Dist_Float (float min, float max)
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::default_random_engine generator(seed);
  std::uniform_real_distribution<float> distribution (min,max);
  return distribution(generator);
}



float Normal_Dist(float mean, float std)
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::default_random_engine generator(seed);
  std::normal_distribution<double> distribution(mean,std);
  return float(distribution(generator));
}