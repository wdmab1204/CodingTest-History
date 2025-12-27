#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <queue>
using namespace std;

struct PathResult {
public:
    pair<int, int> pos;
    int pathLength;
    bool success;
};

vector<vector<int>> arr;
pair<int, int> sharkPos;
int sharkLevel = 2, N, shakrEatCount = 0;

bool IsValidPos(int x, int y) {
    if (x < 0 || x >= N || y < 0 || y >= N)
        return false;

    if (arr[y][x] > sharkLevel)
        return false;

    return true;
}

PathResult BFS(pair<int,int> dest) {
    int visited[20][20] = { 0, };
    queue<pair<int, int>> q;
    int dirx[] = { 1,-1,0,0 };
    int diry[] = { 0,0,1,-1 };

    q.push(sharkPos);
    visited[sharkPos.first][sharkPos.second] = 1;

    bool success = false;
    while (q.empty() == false) {
        auto pos = q.front(); q.pop();
        if (pos == dest)
        {
            success = true;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nextX = pos.second + dirx[i];
            int nextY = pos.first + diry[i];

            if (IsValidPos(nextX, nextY) == false)
                continue;

            if (visited[nextY][nextX] != 0)
                continue;

            q.push(pair<int, int>(nextY, nextX));
            visited[nextY][nextX] = visited[pos.first][pos.second] + 1;
        }
    }

    PathResult pathResult;
    pathResult.pos = dest;
    pathResult.success = success;
    pathResult.pathLength = visited[dest.first][dest.second] - 1;
    return pathResult;
}

vector<PathResult> GetEatableFish() {

    vector<PathResult> v;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            if (y == sharkPos.first && x == sharkPos.second)
                continue;

            if (arr[y][x] == 0)
                continue;

            if (arr[y][x] >= sharkLevel)
                continue;

            PathResult pathResult = BFS(pair<int, int>(y, x));
            if (pathResult.success)
                v.push_back(pathResult);
        }
    }

    sort(v.begin(), v.end(), [](PathResult a, PathResult b) {
        if (a.pathLength != b.pathLength)
            return a.pathLength < b.pathLength;

        if (a.pos.first != b.pos.first)
            return a.pos.first < b.pos.first;

        return a.pos.second < b.pos.second;
        });

    return v;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    int input;
    arr.resize(N, vector<int>(N));
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            cin >> input;
            if (input == 9)
                sharkPos = pair<int, int>(y, x);
            else
                arr[y][x] = input;
        }
    }

    int secs = 0;
    while (true) {
        vector<PathResult> pathResult = GetEatableFish();
        if (pathResult.size() == 0) {
            break;
        }

        auto target = pathResult[0];
        //cout << "(" << target.pos.first << ", " << target.pos.second << ")" << endl;

        //Move
        sharkPos = target.pos;

        //Eat
        shakrEatCount += 1;
        arr[target.pos.first][target.pos.second] = 0;

        //SharkLevelUp
        if (shakrEatCount >= sharkLevel)
        {
            sharkLevel += 1;
            shakrEatCount = 0;
        }

        secs += target.pathLength;
    }

    cout << secs;

    return 0;
}
