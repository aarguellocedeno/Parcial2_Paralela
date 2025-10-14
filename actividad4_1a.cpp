#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <string>
using namespace std;

const string GOAL = "ABCDEFGHIJKLMNO#";
const int dRow[] = {-1, 1, 0, 0};
const int dCol[] = {0, 0, -1, 1};

struct State {
    string board;
    int blankPos;
    int cost;
    State(string b, int pos, int c) : board(b), blankPos(pos), cost(c) {}
};

string swapBoardTiles(const string &currentBoard, int position1, int position2) {
    string newBoard = currentBoard;
    char tmp = newBoard[position1];
    newBoard[position1] = newBoard[position2];
    newBoard[position2] = tmp;
    return newBoard;
}


pair<int, int> bfs(string start) {
    queue<State> q;
    unordered_set<string> visited;

    int blankPos = start.find('#');
    q.push(State(start, blankPos, 0));
    visited.insert(start);

    int expanded = 0;

    while (!q.empty()) {
        State current = q.front();
        q.pop();
        expanded++;

        if (current.board == GOAL) return {current.cost, expanded};

        int row = current.blankPos / 4;
        int col = current.blankPos % 4;

        for (int i = 0; i < 4; i++) {
            int newRow = row + dRow[i];
            int newCol = col + dCol[i];
            if (0 <= newRow && newRow < 4 && 0 <= newCol && newCol < 4) {
                int newPos = newRow * 4 + newCol;
                string newBoard = swapBoardTiles(current.board, current.blankPos, newPos);
                if (visited.find(newBoard) == visited.end()) {
                    q.push(State(newBoard, newPos, current.cost + 1));
                    visited.insert(newBoard);
                }
            }
        }
    }

    return {-1, expanded}; 
}

int main() {
    ifstream file("puzzles.txt");
    string line;
    int id = 1;

    while (getline(file, line)) {
        pair<int, int> result = bfs(line);
        cout << "Puzzle #" << id++ << ": " << line << endl;
        cout << "  Costo de solución: " << result.first << endl;
        cout << "  Nodos expandidos:  " << result.second << endl;
        cout << "--------------------------------------" << endl;
    }

    return 0;
}
