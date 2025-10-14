#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <vector>
#include <tuple>
#include <omp.h>
using namespace std;

const string GOAL = "ABCDEFGHIJKLMNO#";

int aStarSearch(string start) {
    const int dRow[4] = {-1, 1, 0, 0}; // direcciones: arriba, abajo
    const int dCol[4] = { 0, 0, -1, 1}; // izquierda, derecha

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
    if (total % 2 == 0) return -1; 

    int h = 0;
    for (int i = 0; i < 16; i++) {
        if (start[i] != '#' && start[i] != GOAL[i]) h++;
    }

    priority_queue<tuple<int, int, string>, vector<tuple<int, int, string>>, greater<>> pq;
    pq.push({h, 0, start});

    unordered_map<string, int> dist;
    dist[start] = 0;

    while (!pq.empty()) {
        tuple<int, int, string> top = pq.top();
        pq.pop();

        int f = get<0>(top);
        int g = get<1>(top);
        string s = get<2>(top);

        if (s == GOAL) {
            return g;
        }

        if (dist[s] >= g) {
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

                    if (dist.count(newBoard) == 0 || dist[newBoard] > g + 1) {
                        dist[newBoard] = g + 1;
                        int h2 = 0;
                        for (int j = 0; j < 16; j++) {
                            if (newBoard[j] != '#' && newBoard[j] != GOAL[j]) h2++;
                        }
                        pq.push({g + 1 + h2, g + 1, newBoard});
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
