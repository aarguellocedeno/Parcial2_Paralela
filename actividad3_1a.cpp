#include <omp.h>
#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;

/*
 *Possible movement directions 
 * Up, Down, Left, Right
 */
const int dRow[] = {-1, 1, 0, 0}; // UP, DOWN, LEFT, RIGHT
const int dCol[] = {0, 0, -1, 1};
const string MOVES[] = {"UP", "DOWN", "LEFT", "RIGHT"};
const string GOAL = "ABCDEFGHIJKLMNO#";

struct State{
      string board;
      int blankPos;
      int cost;
      State(string b, int pos, int c) :  board(b), blankPos(pos), cost(c) {}
};

// =============================================================================
// HELPER FUNCTIONS
// =============================================================================

string swapBoardTiles(const string &currentBoard, int position1, int position2) {
    string newBoard = currentBoard;
    char tmp = newBoard[position1];
    newBoard[position1] = newBoard[position2];
    newBoard[position2] = tmp;
    return newBoard;
}  


int bfs(string start){
    queue<State> q;
    unordered_set<string> visited;
    int blankPos = start.find('#'); 
    q.push(State(start, blankPos, 0));
    visited.insert(start);

    while (!q.empty()){
        State current = q.front();
        q.pop();
        if (current.board == GOAL) return current.cost;

        int row = current.blankPos / 4;
        int col = current.blankPos % 4;

        #pragma omp parallel for
        for (int i = 0; i < 4; i++){
            int newRow = row + dRow[i];
            int newCol = col + dCol[i];

            if (0 <= newRow && newRow < 4 && 0 <= newCol && newCol < 4){
                int newPos = newRow * 4 + newCol;
                string newBoard = swapBoardTiles(current.board, current.blankPos, newPos);

                #pragma omp critical
                if (visited.find(newBoard) == visited.end()){
                    q.push(State(newBoard, newPos, current.cost + 1));
                    visited.insert(newBoard);
                }
            }
        }
    }
    return -1;
}

int main(){
      string start;
      cin >> start;
      int result = bfs(start);
      cout << result << endl;
      return 0;
}