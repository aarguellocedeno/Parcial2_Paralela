#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;

const int dRow[] = {-1, 1, 0, 0}; // UP, DOWN, LEFT, RIGHT
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

int bfs(string start, string goal, int n) {
    queue<State> q;
    unordered_set<string> visited;
    int blankPos = start.find('#'); 
    q.push(State(start, blankPos, 0));
    visited.insert(start);

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        if (current.board == goal) return current.cost;

        int row = current.blankPos / n;
        int col = current.blankPos % n;

        for (int i = 0; i < 4; i++) {
            int newRow = row + dRow[i];
            int newCol = col + dCol[i];

            if (0 <= newRow && newRow < n && 0 <= newCol && newCol < n) {
                int newPos = newRow * n + newCol;
                string newBoard = swapBoardTiles(current.board, current.blankPos, newPos);

                if (visited.find(newBoard) == visited.end()) {
                    q.push(State(newBoard, newPos, current.cost + 1));
                    visited.insert(newBoard);
                }
            }
        }
    }

    return -1;
}

int main() {
    int n;
    string start;

    cin >> n >> start;
    
    string goal = "";
    for (int i = 0; i < n * n - 1; i++) {
        goal += (char)('A' + i);
    }
    goal += '#';

    int result = bfs(start, goal, n);
    cout << result << endl;
    return 0;
}
