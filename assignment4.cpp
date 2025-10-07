// To Implement A* Algorithm for an application
#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <utility>
#include <algorithm>
#include <cstring>
#include <cfloat>
using namespace std;

// Size of the grid
#define ROW 9
#define COL 10

// Structure to hold the details of a cell
struct Cell {
    int parent_i, parent_j;
    double f, g, h;
    // f=g+h, g=cost from start to current, h=heuristic cost to goal
    Cell() {
        parent_i = parent_j = 0;
        f = g = h = FLT_MAX;
    }
};

// Check cell validity
bool isValid(int row, int col) {
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

// Check cell blocked/unblocked
bool isUnblocked(int grid[ROW][COL], int row, int col) {
    return grid[row][col] == 1; // 1 indicates unblocked
}

// Check destination
bool isDestination(int row, int col, pair<int, int> dest) {
    return (row == dest.first && col == dest.second);
}

// Calculate the heuristic value (Euclidean distance)
double calculateHValue(int row, int col, pair<int, int> dest) {
    return sqrt((row - dest.first) * (row - dest.first) +
                (col - dest.second) * (col - dest.second));
}

// Trace the path from destination to source
void tracePath(Cell cellDetails[ROW][COL], pair<int, int> dest) {
    cout << "The Path is:\n";
    vector<pair<int, int>> path;

    int row = dest.first;
    int col = dest.second;

    while (!(cellDetails[row][col].parent_i == row &&
             cellDetails[row][col].parent_j == col)) {
        path.push_back({row, col});
        //Follows parent pointers back to the start, then reverses the path
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }
    path.push_back({row, col});
    reverse(path.begin(), path.end());

    for (auto &p : path)
        cout << "-> (" << p.first << "," << p.second << ") ";
    cout << endl;
}

// A* Search Algorithm
void aStarSearch(int grid[ROW][COL], pair<int, int> src, pair<int, int> dest) {
    if (!isValid(src.first, src.second) || !isValid(dest.first, dest.second)) {
        cout << "Source or destination is invalid\n";
        return;
    }

    if (!isUnblocked(grid, src.first, src.second) || 
        !isUnblocked(grid, dest.first, dest.second)) {
        cout << "Source or destination is blocked\n";
        return;
    }

    if (isDestination(src.first, src.second, dest)) {
        cout << "We are already at the destination\n";
        return;
    }

    bool closedList[ROW][COL]; // Track visited cells
    memset(closedList, false, sizeof(closedList));

    Cell cellDetails[ROW][COL]; // Details of each cell

    int i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    set<pair<double, pair<int, int>>> openList;
    openList.insert({0.0, {i, j}});

    bool foundDest = false;

    while (!openList.empty()) { // Explores cells with lowest f values
        pair<double, pair<int, int>> p = *openList.begin();
        openList.erase(openList.begin());

        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1},
                                {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

        for (int d = 0; d < 8; d++) {
            int new_i = i + directions[d][0];
            int new_j = j + directions[d][1];

            if (isValid(new_i, new_j)) {
                if (isDestination(new_i, new_j, dest)) {
                    cellDetails[new_i][new_j].parent_i = i;
                    cellDetails[new_i][new_j].parent_j = j;
                    cout << "The destination cell is found\n";
                    tracePath(cellDetails, dest);
                    foundDest = true;
                    return;
                } 
                else if (!closedList[new_i][new_j] && isUnblocked(grid, new_i, new_j)) { // If not in closed list and unblocked
                    double gNew = cellDetails[i][j].g + 1.0; // New Cost
                    double hNew = calculateHValue(new_i, new_j, dest);
                    double fNew = gNew + hNew;

                    if (cellDetails[new_i][new_j].f == FLT_MAX || cellDetails[new_i][new_j].f > fNew) {
                        openList.insert({fNew, {new_i, new_j}});
                        cellDetails[new_i][new_j].f = fNew;
                        cellDetails[new_i][new_j].g = gNew;
                        cellDetails[new_i][new_j].h = hNew;
                        cellDetails[new_i][new_j].parent_i = i;
                        cellDetails[new_i][new_j].parent_j = j;
                    }
                }
            }
        }
    }

    if (!foundDest)
        cout << "Failed to find the destination cell\n";
}

int main() {
    int grid[ROW][COL] = {
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
        {0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
        {1, 0, 1, 1, 1, 1, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 1, 0, 0, 1}
    };

    pair<int, int> src = make_pair(8, 0);
    pair<int, int> dest = make_pair(0, 0);

    aStarSearch(grid, src, dest);

    return 0;
}