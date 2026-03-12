#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>

int sign(int x) {
    return (x > 0) - (x < 0);
}

// -------------------------
// Part 1 safety check
// -------------------------
bool isSafe(const std::vector<int>& v) {
    if (v.size() < 2) return true;

    std::vector<int> diffs;
    std::adjacent_difference(v.begin(), v.end(), std::back_inserter(diffs));

    std::vector<int> absDiff(diffs.size());
    std::transform(diffs.begin(), diffs.end(), absDiff.begin(),
                   [](int x){ return std::abs(x); });

    int firstSign = sign(diffs[1]);  // skip diffs[0]

    bool allSameSign = std::all_of(diffs.begin() + 1, diffs.end(),
        [firstSign](int x){
            return sign(x) == firstSign;
        });

    bool hasZero = std::any_of(absDiff.begin() + 1, absDiff.end(),
        [](int x){ return x == 0; });

    bool hasGreaterThan3 = std::any_of(absDiff.begin() + 1, absDiff.end(),
        [](int x){ return x > 3; });

    return (!hasZero && !hasGreaterThan3 && allSameSign);
}

// -------------------------
// Part 2 safety check
// -------------------------
bool isSafeWithDampener(const std::vector<int>& v) {
    if (isSafe(v)) return true;

    // Try removing each element once
    for (size_t i = 0; i < v.size(); i++) {
        std::vector<int> tmp;
        tmp.reserve(v.size() - 1);

        for (size_t j = 0; j < v.size(); j++) {
            if (j != i) tmp.push_back(v[j]);
        }

        if (isSafe(tmp)) return true;
    }

    return false;
}

// -------------------------
// Main
// -------------------------
int main() {
    std::ifstream file("day2_test.txt");
    std::string line;

    int safe = 0;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<int> numbers;

        int x;
        while (ss >> x) {
            numbers.push_back(x);
        }

        if (isSafeWithDampener(numbers)) {
            safe++;
        }
    }

    std::cout << "Part 2 total safe = " << safe << "\n";
    return 0;
}