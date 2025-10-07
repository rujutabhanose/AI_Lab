// Implement DFS, BFS for 8-puzzle problem
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

const vector<int> goal = {1, 2, 3, 4, 5, 6, 7, 8, 0};

void printState(const vector<int>& state) {
    for (int i = 0; i < 9; ++i) {
        cout << state[i] << " ";
        if (i % 3 == 2) cout << endl;
    }
    cout << endl;
}

bool isSolvable(const vector<int>& state) {
    int inv = 0;
    for (int i = 0; i < 9; ++i) {
        if (state[i] == 0) continue;
        for (int j = i + 1; j < 9; ++j) {
            if (state[j] != 0 && state[i] > state[j]) inv++;
        }
    }
    return inv % 2 == 0; //even inversions
}

vector<vector<int>> getMoves(const vector<int>& state) {
    vector<vector<int>> nextStates;
    int zeroIndex = find(state.begin(), state.end(), 0) - state.begin(); //index of empty tile

    vector<int> deltas = {-3, 3, -1, 1};

    for (int delta : deltas) {
        int newIndex = zeroIndex + delta;

        if (newIndex < 0 || newIndex >= 9) continue;
        if ((delta == -1 && zeroIndex % 3 == 0) || (delta == 1 && zeroIndex % 3 == 2)) continue;

        vector<int> newState = state;
        swap(newState[zeroIndex], newState[newIndex]);
        nextStates.push_back(newState);
    }

    return nextStates;
}

//BFS
vector<vector<vector<int>>> solveByBFS(const vector<int>& start) {
    queue<vector<int>> q;
    set<vector<int>> visited;
    map<vector<int>, vector<int>> parent;

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        vector<int> current = q.front();
        q.pop();

        if (current == goal) {
            vector<vector<int>> path;
            while (current != start) {
                path.push_back(current);
                current = parent[current];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return {path};
        }

        for (auto& next : getMoves(current)) {
            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                q.push(next);
                parent[next] = current;
            }
        }
    }

    return {};
}

//DFS
vector<vector<int>> solveByDFS(const vector<int>& start) {
    stack<vector<int>> stk;
    set<vector<int>> visited;
    map<vector<int>, vector<int>> parent;

    stk.push(start);

    while (!stk.empty()) {
        vector<int> current = stk.top();
        stk.pop();

        if (visited.count(current)) continue;
        visited.insert(current);

        if (current == goal) {
            vector<vector<int>> path;
            while (current != start) {
                path.push_back(current);
                current = parent[current];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        for (auto& next : getMoves(current)) {
            if (visited.find(next) == visited.end()) {
                parent[next] = current;
                stk.push(next);
            }
        }
    }

    return {};
}

int main() {
    vector<int> state1 = {1, 2, 3, 4, 5, 6, 0, 7, 8};
    vector<int> state2 = {8, 1, 2, 0, 4, 3, 7, 6, 5};

    cout << "State1 solvable? " << (isSolvable(state1) ? "Yes" : "No") << endl;
    cout << "State2 solvable? " << (isSolvable(state2) ? "Yes" : "No") << endl;

    cout << "\nTesting BFS on state1:" << endl;
    if (isSolvable(state1)) {
        cout << "Solvable!" << endl;
        auto paths = solveByBFS(state1);
        if (!paths.empty()) {
            cout << "Steps to goal: " << paths[0].size() - 1 << endl;
            for (auto& step : paths[0]) {
                printState(step);
            }
        } else {
            cout << "No solution found." << endl;
        }
    } else {
        cout << "No solution." << endl;
    }

    cout << "\nTesting DFS on state2:" << endl;
    if (isSolvable(state2)) {
        cout << "Solvable!" << endl;
        auto path = solveByDFS(state2);
        if (!path.empty()) {
            cout << "Steps to goal: " << path.size() - 1 << endl;
            for (auto& step : path) {
                printState(step);
            }
        } else {
            cout << "DFS did not find a solution." << endl;
        }
    } else {
        cout << "No solution." << endl;
    }

    return 0;
}