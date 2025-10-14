#include <iostream>
#include <queue>
#include <unordered_set>
#include <omp.h>
#include <vector>
using namespace std;

const int dRow[] = {-1, 1, 0, 0};
const int dCol[] = {0, 0, -1, 1};
const string GOAL = "ABCDEFGHIJKLMNO#";

struct State {
    string board;
    int blankPos;
    int cost;
    State(string b, int pos, int c) : board(b), blankPos(pos), cost(c) {}
};

string swapBoardTiles(const string &currentBoard, int p1, int p2) {
    string newBoard = currentBoard;
    char tmp = newBoard[p1];
    newBoard[p1] = newBoard[p2];
    newBoard[p2] = tmp;
    return newBoard;
}

int bfsSubspace(const string &start) {
    queue<State> q;
    unordered_set<string> visited;
    int blankPos = start.find('#');
    q.push(State(start, blankPos, 0));
    visited.insert(start);

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        if (current.board == GOAL) return current.cost;

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
    return -1;
}
int bfsDomainDecomposition(string start) {
    int blankPos = start.find('#');
    int row = blankPos / 4;
    int col = blankPos % 4;
    vector<string> subdomains;
    for (int i = 0; i < 4; i++) {
        int newRow = row + dRow[i];
        int newCol = col + dCol[i];
        if (0 <= newRow && newRow < 4 && 0 <= newCol && newCol < 4) {
            int newPos = newRow * 4 + newCol;
            subdomains.push_back(swapBoardTiles(start, blankPos, newPos));
        }
    }

    int bestResult = -1;
    int numDomains = subdomains.size();

    #pragma omp parallel for num_threads(numDomains) shared(bestResult)
    for (int i = 0; i < numDomains; i++) {
        int localResult = bfsSubspace(subdomains[i]);

        #pragma omp critical
        {
            if (localResult != -1) {
                if (bestResult == -1 || localResult + 1 < bestResult)
                    bestResult = localResult + 1; 
            }
        }
    }

    return bestResult;
}

int main() {
    string start;
    cin >> start;

    double startTime = omp_get_wtime();
    int result = bfsDomainDecomposition(start);
    double endTime = omp_get_wtime();

    cout << "\nResultado: " << result << endl;
    cout << "Tiempo total: " << (endTime - startTime) << " segundos" << endl;
    return 0;
}
