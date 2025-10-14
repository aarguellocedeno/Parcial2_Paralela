#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

const string GOAL = "ABCDEFGHIJKLMNO#";

int misplacedTiles(const string& board) {
    int h = 0;
    for (int i = 0; i < 16; i++) {
        if (board[i] != '#' && board[i] != GOAL[i]) h++;
    }
    return h;
}

pair<int, int> aStarSearch(string start) {
    const int dRow[4] = {-1, 1, 0, 0}; 
    const int dCol[4] = {0, 0, -1, 1};

    int inversions = 0;
    for (int i = 0; i < 16; i++) {
        if (start[i] == '#') continue;
        for (int j = i + 1; j < 16; j++) {
            if (start[j] == '#') continue;
            if (start[i] > start[j]) inversions++;
        }
    }
    int blankRow = 4 - (start.find('#') / 4);
    int total = inversions + blankRow;
    if (total % 2 == 0) return {-1, 0}; 

    
    priority_queue<tuple<int, int, string>, vector<tuple<int, int, string>>, greater<>> pq;
    unordered_map<string, int> dist;

    int h0 = misplacedTiles(start);
    pq.push({h0, 0, start});
    dist[start] = 0;

    int expanded = 0;

    while (!pq.empty()) {
        tuple<int, int, string> top = pq.top();
        pq.pop();

        int f = get<0>(top);
        int g = get<1>(top);
        string s = get<2>(top);
        expanded++;

        if (s == GOAL) return {g, expanded};

        if (dist[s] >= g) {
            int pos = s.find('#');
            int r = pos / 4;
            int c = pos % 4;

            for (int i = 0; i < 4; i++) {
                int nr = r + dRow[i];
                int nc = c + dCol[i];
                if (nr >= 0 && nr < 4 && nc >= 0 && nc < 4) {
                    int newPos = nr * 4 + nc;
                    string newBoard = s;
                    swap(newBoard[pos], newBoard[newPos]);

                    int ng = g + 1;
                    if (!dist.count(newBoard) || ng < dist[newBoard]) {
                        dist[newBoard] = ng;
                        int nh = misplacedTiles(newBoard);
                        pq.push({ng + nh, ng, newBoard});
                    }
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
        pair<int, int> result = aStarSearch(line);
        cout << "Puzzle #" << id++ << ": " << line << endl;
        cout << "  Costo de solución: " << result.first << endl;
        cout << "  Nodos expandidos:  " << result.second << endl;
        cout << "--------------------------------------" << endl;
    }

    return 0;
}
