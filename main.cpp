#include <bits/stdc++.h>
using namespace std;

const int ROWS = 10;
const int COLS = 10;

vector<vector<char>> grid(ROWS, vector<char>(COLS, '.'));
pair<int, int> start;
vector<pair<int, int>> targets;

bool USE_RANDOM_GRID = true;  

void generateRandomGrid() {
    srand(time(0));

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if ((rand() % 100) < 20)
                grid[i][j] = '#';
        }
    }

    while (true) {
        int x = rand() % ROWS;
        int y = rand() % COLS;
        if (grid[x][y] == '.') {
            grid[x][y] = 'S';
            start = {x, y};
            break;
        }
    }

    int numTargets = 1 + rand() % 3;
    while (targets.size() < numTargets) {
        int x = rand() % ROWS;
        int y = rand() % COLS;
        if (grid[x][y] == '.') {
            grid[x][y] = 'T';
            targets.push_back({x, y});
        }
    }
}

void readGrid() {
    cout << "Enter 10x10 grid (S = Start, T = Target, # = Obstacle, . = Free):\n";
    for (int i = 0; i < ROWS; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = row[j];
            if (grid[i][j] == 'S') start = {i, j};
            else if (grid[i][j] == 'T') targets.push_back({i, j});
        }
    }
}

void printGrid() {
    cout << "\n--- Grid Loaded ---\n";
    for (auto row : grid) {
        for (auto ch : row) cout << ch << ' ';
        cout << '\n';
    }
}

struct Node {
    int x, y, cost;
    bool operator>(const Node &other) const {
        return cost > other.cost;
    }
};

bool isValid(int x, int y) {
    return x >= 0 && x < ROWS && y >= 0 && y < COLS && grid[x][y] != '#';
}

pair<int, vector<pair<int, int>>> dijkstra(pair<int, int> src, pair<int, int> dest) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    vector<vector<int>> dist(ROWS, vector<int>(COLS, INT_MAX));
    vector<vector<bool>> visited(ROWS, vector<bool>(COLS, false));
    vector<vector<pair<int, int>>> parent(ROWS, vector<pair<int, int>>(COLS, {-1, -1}));

    pq.push({src.first, src.second, 0});
    dist[src.first][src.second] = 0;

    vector<pair<int, int>> dirs = {{-1,0},{1,0},{0,-1},{0,1}};
    while (!pq.empty()) {
        Node curr = pq.top(); pq.pop();

        if (visited[curr.x][curr.y]) continue;
        visited[curr.x][curr.y] = true;

        if (curr.x == dest.first && curr.y == dest.second) {
            vector<pair<int, int>> path;
            pair<int, int> p = dest;
            while (p != make_pair(-1, -1)) {
                path.push_back(p);
                p = parent[p.first][p.second];
            }
            reverse(path.begin(), path.end());
            return {curr.cost, path};
        }

        for (auto d : dirs) {
            int nx = curr.x + d.first;
            int ny = curr.y + d.second;

            if (isValid(nx, ny)) {
                int newCost = curr.cost + 1;
                if (newCost < dist[nx][ny]) {
                    dist[nx][ny] = newCost;
                    parent[nx][ny] = {curr.x, curr.y};
                    pq.push({nx, ny, newCost});
                }
            }
        }
    }

    return {-1, {}};
}

int main() {
    if (USE_RANDOM_GRID)
        generateRandomGrid();
    else
        readGrid();

    printGrid();

    ofstream fout("path_data.txt");
    fout << ROWS << " " << COLS << "\n";
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            fout << grid[i][j];
        }
        fout << "\n";
    }

    fout << start.first << " " << start.second << "\n";
    fout << targets.size() << "\n";

    for (auto target : targets) {
        pair<int, vector<pair<int, int>>> result = dijkstra(start, target);
        int cost = result.first;
        vector<pair<int, int>> path = result.second;

        fout << target.first << " " << target.second << " " << cost << "\n";
        fout << path.size() << "\n";
        for (auto p : path)
            fout << p.first << " " << p.second << "\n";

        cout << "\nShortest path to target at (" << target.first << "," << target.second << ") = ";
        if (cost != -1)
            cout << cost << " steps.\n";
        else
            cout << "NOT reachable.\n";
    }

    fout.close();
    return 0;
}
