#include <iostream>
#include <fstream>
#include <regex>
#include <string>

int main() {
    std::ifstream file("day3_test.txt");

    // Regex patterns
    std::regex eventPattern(R"(do\(\)|don't\(\)|mul\((\d{1,3}),(\d{1,3})\))"); // Find all the pinches events
    std::regex mulCapture(R"(mul\((\d{1,3}),(\d{1,3})\))"); // Now, lets find the important stuff

    long long totalSumPart2 = 0;
    long long totalSumPart1 = 0;
    bool isOn = true; // starts enabled at the very beginning. But not at the start of the lines...

    std::string line;
    while (std::getline(file, line)) {
        // Find all the events in a line.
        std::sregex_iterator it(line.begin(), line.end(), eventPattern);
        std::sregex_iterator end;

        for (; it != end; ++it) {
            std::string matchStr = it->str();

            if (matchStr == "do()") {
                isOn = true;
            } 
            else if (matchStr == "don't()") {
                isOn = false;
            } 
            else {
                // matchStr is a mul(x,y). So, we get here if the pattern found is the type mul(x,y), and the multiplication is enabled
                if (isOn) {
                    std::smatch m;
                    if (std::regex_match(matchStr, m, mulCapture)) {
                        int x = std::stoi(m[1]);
                        int y = std::stoi(m[2]);
                        totalSumPart2 += static_cast<long long>(x) * y;
                    }
                }
            }
        }
    }

    file.clear();
    file.seekg(0);

    std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))"); // regex to match the pattern

    int totalSum = 0;
    while (std::getline(file, line)) {
        auto begin = std::sregex_iterator(line.begin(), line.end(), pattern);
        auto end = std::sregex_iterator();
        std::cout << "Current Line = " << line << '\n';

        for (auto it = begin; it != end; ++it) {
            int x = std::stoi((*it)[1]);
            int y = std::stoi((*it)[2]);

            std::cout << "Found: x=" << x << ", y=" << y << " multi = " << x*y <<'\n';
            totalSum += x*y;
        }
    }
    std::cout << "Total sum PArt 1= " << totalSum << '\n';
    std::cout << "Total sum Part 2 = " << totalSumPart2 << std::endl;
    return 0;
}

