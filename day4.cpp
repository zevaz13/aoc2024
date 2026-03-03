#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

enum class Move { W, NW, N, NE, E, SE, S, SW };
struct Delta { int dr, dc; };

static const std::unordered_map<Move, Delta> deltas = {
    {Move::W,  { 0, -1}},
    {Move::N,  {-1,  0}},
    {Move::E,  { 0,  1}},
    {Move::S,  { 1,  0}},
    {Move::NW, {-1, -1}},
    {Move::NE, {-1,  1}},
    {Move::SE, { 1,  1}},
    {Move::SW, { 1, -1}}
};

std::vector<Move> allowedMoves(int r, int c, int numR, int numC) {
    bool W = (c > 2);
    bool N = (r > 2);
    bool E = (c < numR - 3);
    bool S = (r < numC - 3);

    std::vector<Move> moves;

    if (W) moves.push_back(Move::W);
    if (N) moves.push_back(Move::N);
    if (E) moves.push_back(Move::E);
    if (S) moves.push_back(Move::S);

    if (W && N) moves.push_back(Move::NW);
    if (N && E) moves.push_back(Move::NE);
    if (S && E) moves.push_back(Move::SE);
    if (S && W) moves.push_back(Move::SW);

    return moves;
}

int checkMovement(const std::vector<std::vector<char>>& matrix,
    int r, int c, Move mv)
{
auto [dr, dc] = deltas.at(mv);

int state = 0;   // 0=M, 1=A, 2=S

for (int step = 1; step <= 3; ++step) {
int rr = r + dr * step;
int cc = c + dc * step;

if (rr < 0 || rr >= matrix.size()) return 0;
if (cc < 0 || cc >= matrix[0].size()) return 0;

char ch = matrix[rr][cc];
// std::cout << "step " << step << " → (" << rr << "," << cc
//     << ") = " << ch << "\n";

switch (state) {
case 0: // expecting M
  if (ch == 'M') state = 1;
  else return 0;
  break;

case 1: // expecting A
  if (ch == 'A') state = 2;
  else return 0;
  break;

case 2: // expecting S
  if (ch == 'S') return 1;   // success
  else return 0;
}
}

return 0; // did not reach S
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

    // For one line (row), find those elements that have an 'X'
    for (int r = 0; r< matrix.size();++r){
        for (int c = 0; c < matrix[0].size(); ++c) {
            if (matrix[r][c] == 'X') {
                //std::cout << "X found in c = " << c <<  "\n";
                auto moves = allowedMoves(r, c, numRow, numCol);
                for (Move mv : moves) {
                    //std::cout << "New Pattern: \n"; 
                    totalXmas+=checkMovement(matrix, r, c, mv);
                }
            }            
        }
    }
    
    std::cout << "Total = " << totalXmas << '\n';
    return 0;
}