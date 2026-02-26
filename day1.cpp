#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm> // Required for std::sort()
#include <iterator>


int main() {

    // load the data from the file
    std::ifstream file("day1_test.txt");
    std::string line;

    std::vector<int> numbers1;
    std::vector<int> numbers2;

    // parse the input into vectors for unsigned integers
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        unsigned int num1, num2;

        if (ss >> num1 >> num2) {
            numbers1.push_back(num1);
            numbers2.push_back(num2);
        }
    }

    // Print results
    // std::cout << "Column 1:\n";
    // for (unsigned int num : numbers1) {
    //     std::cout << num << " ";
    // }

    // std::cout << "\n\nColumn 2:\n";
    // for (unsigned int num : numbers2) {
    //     std::cout << num << " ";
    // }

    // sort the arrays
    std::sort(numbers1.begin(), numbers1.end()); 
    std::sort(numbers2.begin(), numbers2.end()); 


    //std::cout << "Differences:\n";
    int totalFinal = 0;
    int totalSimilarity = 0;
    
    for (size_t i = 0; i < numbers1.size(); i++) {
        //std::cout << numbers1[i] - numbers2[i] << " ";
        totalFinal+= std::abs(numbers1[i] - numbers2[i]);
        int Ni = numbers1[i];
        int similarityNi = std::count(std::begin(numbers2), std::end(numbers2), Ni);
        totalSimilarity += similarityNi*Ni;

    }
    std::cout << "total = " << totalFinal << "\n";
    std::cout << "Part2. Total Similarity = " << totalSimilarity << "\n";
    return 0;
}