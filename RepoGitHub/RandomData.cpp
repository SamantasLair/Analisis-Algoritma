#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>

void my_algorithm() {
  // Simulate some work done by the algorithm
  for (int i = 0; i < 1000000; i++) {
    ; // Empty loop to simulate work
  }
}

int main() {
    int n = 90000;
        srand(time(nullptr));
        std::ofstream outfile("dataUntukSorting.csv", std::ios::app);
        if (!outfile.is_open()) {
        std::cerr << "Error opening output file!" << std::endl;
        return 1;
        }
    for (int i = 0; i < n; i++) {
        int random_number = rand() % 10000 + 1;
        outfile << random_number << std::endl;
    }
        outfile.close();
    return 0;
}
