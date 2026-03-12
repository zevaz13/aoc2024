#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

struct ParsedData {
    std::vector<int> middle;
    std::vector<int> used;
};

struct ParsedDatacond {
    std::vector<int> start;
    std::vector<int> ending;
};


ParsedData loadFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    ParsedData result;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<int> values;

        result.used.push_back(0);   // one "used" entry per line

        while (std::getline(ss, token, ',')) {
            values.push_back(std::stoi(token));
        }

        int mid = values.size() / 2;
        result.middle.push_back(values[mid]);
    }
    file.close();
    return result;
}

ParsedDatacond loadFileCond(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    ParsedDatacond result;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int a, b;
        char bar;

        if (ss >> a >> bar >> b) {   // bar should be '|'
            result.start.push_back(a);
            result.ending.push_back(b);
        }
    }

    return result;
}

std::unordered_map<int,int> buildPosMap(const std::vector<int>& pages) {
    std::unordered_map<int,int> pos;
    for (int i = 0; i < (int)pages.size(); ++i) {
        pos[pages[i]] = i;
    }
    return pos;
}

bool isValidUpdate(const std::vector<int>& pages, const ParsedDatacond& cond) {
    auto pos = buildPosMap(pages);

    for (int i = 0; i < cond.start.size(); ++i) {
        int a = cond.start[i];
        int b = cond.ending[i];

        // If either page is missing from this update, ignore the rule
        if (!pos.count(a) || !pos.count(b))
            continue;

        // Rule violated: a must appear before b
        if (pos[a] > pos[b])
            return false;
    }

    return true;
}

int sumResult = 0;
int cntr  = 0;
int main() {
    // load vectors for the result and conditions
    ParsedData data = loadFile("day5_test2.txt");
    ParsedDatacond conditions = loadFileCond("day5_test1.txt");

    // Example update
    std::ifstream file("day5_test2.txt");
    std::string line;
    while (std::getline(file, line)) {

        // Parse this line into a vector<int> update
        std::stringstream ss(line);
        std::string token;
        std::vector<int> update;
    
        while (std::getline(ss, token, ',')) {
            update.push_back(std::stoi(token));
        }
    
        // Now call your rule checker
        bool ok = isValidUpdate(update, conditions);
    
        if (ok) {
            data.used[cntr] = 1;
        } else {
        }
    
        // for (int x : update) std::cout << x << " ";
        // std::cout << "\n";
        cntr++;
    }
    
    for (int i = 0; i < data.used.size(); ++i){
        sumResult+= data.used[i] * data.middle[i];
    }
    std::cout << "Final sum = " << sumResult <<"\n";
    return 0;
}