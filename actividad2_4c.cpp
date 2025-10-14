#include <iostream>
#include <queue>
#include <unordered_map>
#include <tuple>
#include <string>
using namespace std;

int manhattan(string board, string goal, int n) {
    int total = 0;
    for (int i = 0; i < board.size(); i++) {
        char tile = board[i];
        if (tile != '#') {
            int goalIndex = goal.find(tile);
            int row1 = i / n, col1 = i % n;
            int row2 = goalIndex / n, col2 = goalIndex % n;
            total += abs(row1 - row2) + abs(col1 - col2);
        }
    }
    return total;
}
bool esSoluble(string board, int n) {
    int inv = 0;
    for (int i = 0; i < board.size(); i++) {
        if (board[i] == '#') continue;
        for (int j = i + 1; j < board.size(); j++) {
            if (board[j] == '#') continue;
            if (board[i] > board[j]) inv++;
        }
    }
    int rowFromBottom = n - (board.find('#') / n);
    return ((inv + rowFromBottom) % 2 == 1);
}


int aStarSearch(string start, string goal, int n) {
    const int dRow[4] = {-1, 1, 0, 0};
    const int dCol[4] = { 0, 0, -1, 1};

    if (!esSoluble(start, n)) return -1;

    priority_queue<tuple<int, int, string>, vector<tuple<int, int, string>>, greater<>> pq;
    unordered_map<string, int> dist;

    int h0 = manhattan(start, goal, n);
    pq.push({h0, 0, start});
    dist[start] = 0;

    while (!pq.empty()) {
        tuple<int, int, string> top = pq.top();
        pq.pop();

        int f = get<0>(top);
        int g = get<1>(top);
        string s = get<2>(top);
        
        if (s == goal) return g;
        if (dist[s] == g) {
            int pos = s.find('#');
            int r = pos / n;
            int c = pos % n;

            for (int i = 0; i < 4; i++) {
                int nr = r + dRow[i];
                int nc = c + dCol[i];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                    int newPos = nr * n + nc;
                    string newBoard = s;
                    swap(newBoard[pos], newBoard[newPos]);

                    int newG = g + 1;
                    if (dist.count(newBoard) == 0 || newG < dist[newBoard]) {
                        dist[newBoard] = newG;
                        int newH = manhattan(newBoard, goal, n);
                        pq.push({newG + newH, newG, newBoard});
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

    int result = aStarSearch(start, goal, n);
    cout << result << endl;
    return 0;
}
