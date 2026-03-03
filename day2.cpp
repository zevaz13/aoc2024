#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm> // Required for std::sort()
#include <iterator>
#include <numeric>

int sign(int x) {
    return (x > 0) - (x < 0);
}

int main() {
    int safe = 0;
    // load the data from the file
    std::ifstream file("day2_test.txt");
    std::string line;

    int lineCount = 0;
    std::string tmp;
    while (std::getline(file, tmp)) {
        ++lineCount;
    }
    // reset file to beginning
    file.clear();
    file.seekg(0);

    for (int li =0; li<lineCount; li++){

        std::vector<int> numbers1;

        // parse the input into vectors for unsigned integers
        std::getline(file, line);
        std::stringstream ss(line);
    
        unsigned int num1;
    
        while (ss >> num1) {
                numbers1.push_back(num1);
            }
        
        // for (size_t i = 0; i < numbers1.size(); i++) {
        //     std::cout << numbers1[i] << " ";}
        // std::cout << "\n";
        std::vector<int> diffs;
        std::adjacent_difference(numbers1.begin(), numbers1.end(), std::back_inserter(diffs));
    
        // for (size_t i = 0; i < diffs.size(); i++) {
        //     std::cout << diffs[i] << " ";}
        // std::cout << "\n";
    
        std::vector<int> absDiff;
        absDiff.resize(diffs.size());
        
        std::transform(diffs.begin(), diffs.end(), absDiff.begin(),
                        [](int x) { return std::abs(x); });    // sort the arrays
    
        // for (size_t i = 1; i < absDiff.size(); i++) {
        //     std::cout << absDiff[i] << " ";}
        
        int firstSign = sign(diffs[1]);   // skip diffs[0], which is the artifact

        bool allSameSign = std::all_of(diffs.begin() + 1, diffs.end(),
                [firstSign](int x) {
                    return sign(x) == firstSign;
                });
        bool hasZero = std::any_of(absDiff.begin()+1, absDiff.end(),
            [](int x){ return x == 0; });
    
        bool hasGreaterThan3 = std::any_of(absDiff.begin()+1, absDiff.end(),
            [](int x){ return x > 3; });
    
        if (hasZero == 0 && hasGreaterThan3==0 && allSameSign ==1) {safe +=1;};
    }

    std::cout << "total = " << safe << "\n";
    // std::cout << "Part2. Total Similarity = " << totalSimilarity << "\n";
    return 0;
}