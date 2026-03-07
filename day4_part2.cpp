#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

int inspectBlock(const std::vector<std::vector<char>>& block)
{
    int state = 0;   // 0=M, 1=A, 2=S

    // STATE 0: expecting A in the center
    if (state == 0) {
        if (block[1][1] == 'A') {
            // std::cout << "Center is A\n";
            state = 1;
        } else {
            return 0;
        }
    }

    // STATE 1: expecting M on top-left and bottom-left
    if (state == 1) {
        if ((block[0][0] == 'M' && block[2][0] == 'M') || (block[0][0] == 'M' && block[0][2] == 'M')|| (block[2][0] == 'M' && block[2][2] == 'M') || (block[0][2] == 'M' && block[2][2] == 'M')) {
            // std::cout << "Side is M\n";
            state = 2;
        } else {
            return 0;
        }
    }

    // STATE 2: expecting S on top-left and bottom-left
    if (state == 2) {
        if ((block[0][0] == 'S' && block[2][0] == 'S') || (block[0][0] == 'S' && block[0][2] == 'S')|| (block[2][0] == 'S' && block[2][2] == 'S') || (block[0][2] == 'S' && block[2][2] == 'S')) {
            return 1;   // success
        } else {
            return 0;
        }
    }

    return 0;
}

int totalXmas = 0;
int main() {
    // First, load the file as a matrix.
    std::ifstream file("day4_test.txt");
    std::vector<std::vector<char>> matrix;
    std::string line;

    while (std::getline(file, line)) {
        std::vector<char> row(line.begin(), line.end());
        matrix.push_back(row);
    }

    file.close();


    // Now, index the matrix
    int numRow = matrix.size();
    int numCol = matrix[0].size();

    std::cout << "numR = " << numRow << "\n";
    std::cout << "numC = " << numCol << "\n";
    std::vector<std::vector<std::vector<char>>> blocks;

    for (int r = 0; r <= matrix.size() - 3; ++r)
    {
        for (int c = 0; c <= matrix[0].size() - 3; ++c)
        {
            std::vector<std::vector<char>> block = {
                { matrix[r][c],     matrix[r][c+1],     matrix[r][c+2] },
                { matrix[r+1][c],   matrix[r+1][c+1],   matrix[r+1][c+2] },
                { matrix[r+2][c],   matrix[r+2][c+1],   matrix[r+2][c+2] }
            };
    
            blocks.push_back(block);
            // for (const auto& row : block) {
            //     for (char ch : row) {
            //         std::cout << ch << ' ';
            //     }
            //     std::cout << '\n';
            // }
            // std::cout << '\n';
            totalXmas+=inspectBlock(block);
        }
    }
    
    std::cout << "Total = " << totalXmas << '\n';
    return 0;
}