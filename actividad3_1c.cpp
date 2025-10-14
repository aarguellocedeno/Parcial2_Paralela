#include <iostream>
#include <queue>
#include <unordered_map>
#include <tuple>
#include <omp.h>
#include <string>
using namespace std;

const string GOAL = "ABCDEFGHIJKLMNO#";

int manhattan(string board) {
    int total = 0;
    for (int i = 0; i < 16; i++) {
        char tile = board[i];
        if (tile != '#') {
            int goalIndex = GOAL.find(tile);
            int row1 = i / 4, col1 = i % 4;
            int row2 = goalIndex / 4, col2 = goalIndex % 4;
            total += abs(row1 - row2) + abs(col1 - col2);
        }
    }
    return total;
}

int aStarSearch(string start) {
    const int dRow[4] = {-1, 1, 0, 0}; // arriba, abajo
    const int dCol[4] = {0, 0, -1, 1}; // izq, der

    int inv = 0;
    for (int i = 0; i < 16; i++) {
        if (start[i] == '#') continue;
        for (int j = i + 1; j < 16; j++) {
            if (start[j] == '#') continue;
            if (start[i] > start[j]) inv++;
        }
    }
    int rowFromBottom = 4 - (start.find('#') / 4);
    if ((inv + rowFromBottom) % 2 == 0) return -1;
    
    priority_queue<tuple<int, int, string>, vector<tuple<int, int, string>>, greater<>> pq;
    unordered_map<string, int> dist;

    int h0 = manhattan(start);
    pq.push({h0, 0, start});
    dist[start] = 0;

    while (!pq.empty()) {
        tuple<int, int, string> top = pq.top();
        pq.pop();

        int f = get<0>(top);
        int g = get<1>(top);
        string s = get<2>(top);

        if (s == GOAL) return g;

        if (dist[s] == g) {
            int pos = s.find('#');
            int r = pos / 4;
            int c = pos % 4;

            #pragma omp parallel for
            for (int i = 0; i < 4; i++) {
                int nr = r + dRow[i];
                int nc = c + dCol[i];
                if (nr >= 0 && nr < 4 && nc >= 0 && nc < 4) {
                    int newPos = nr * 4 + nc;
                    string newBoard = s;
                    char temp = newBoard[pos];
                    newBoard[pos] = newBoard[newPos];
                    newBoard[newPos] = temp;

                    int newG = g + 1;
                    if (dist.count(newBoard) == 0 || newG < dist[newBoard]) {
                        dist[newBoard] = newG;
                        int newH = manhattan(newBoard);
                        pq.push({newG + newH, newG, newBoard});
                    }
                }
            }
        }
    }
    return -1;
}

int main() {
    string start;
    cin >> start;
    int result = aStarSearch(start);
    cout << result << endl;
    return 0;
}