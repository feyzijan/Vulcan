#include <string>
#include <fstream>
#include <vector>
#include <utility> // std::pair

void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<int>>> dataset);
