#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

int aStarSearch(string start, int n, string goal) {
    const int dRow[4] = {-1, 1, 0, 0}; // direcciones: arriba, abajo
    const int dCol[4] = { 0, 0, -1, 1}; // izquierda, derecha

    int inversions = 0;
    int size = n * n;

    for (int i = 0; i < size; i++) {
        if (start[i] == '#') continue;
        for (int j = i + 1; j < size; j++) {
            if (start[j] == '#') continue;
            if (start[i] > start[j]) inversions++;
        }
    }

    int blankRow = n - (start.find('#') / n);
    int total = inversions + blankRow;
    if (total % 2 == 0) return -1;

    int h = 0;
    for (int i = 0; i < size; i++) {
        if (start[i] != '#' && start[i] != goal[i]) h++;
    }

    priority_queue<tuple<int, int, string>, vector<tuple<int, int, string>>, greater<tuple<int, int, string>>> pq;
    pq.push(make_tuple(h, 0, start));

    unordered_map<string, int> dist;
    dist[start] = 0;

    while (!pq.empty()) {
        tuple<int, int, string> top = pq.top();
        pq.pop();

        int f = get<0>(top);
        int g = get<1>(top);
        string s = get<2>(top);

        if (s == goal) {
            return g;
        }

        if (dist[s] >= g) {
            int pos = s.find('#');
            int r = pos / n;
            int c = pos % n;

            for (int i = 0; i < 4; i++) {
                int nr = r + dRow[i];
                int nc = c + dCol[i];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                    int newPos = nr * n + nc;
                    string newBoard = s;
                    char temp = newBoard[pos];
                    newBoard[pos] = newBoard[newPos];
                    newBoard[newPos] = temp;

                    if (dist.count(newBoard) == 0 || dist[newBoard] > g + 1) {
                        dist[newBoard] = g + 1;
                        int h2 = 0;
                        for (int j = 0; j < size; j++) {
                            if (newBoard[j] != '#' && newBoard[j] != goal[j]) h2++;
                        }
                        pq.push(make_tuple(g + 1 + h2, g + 1, newBoard));
                    }
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

    int result = aStarSearch(start, n, goal);
    cout << result << endl;
    return 0;
}
