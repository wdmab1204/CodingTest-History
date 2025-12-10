#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

char arr[12][6];

bool IsValidCoord(int x, int y) {
    return x >= 0 && x < 6 && y >= 0 && y < 12;
}

vector<pair<int, int>> GetGroup(int x, int y, char c, int visited[12][6]) {
    queue<pair<int, int>> q;
    q.emplace(x, y);
    visited[y][x] = 1;
    int xdir[4] = { 1,-1,0,0 };
    int ydir[4] = { 0,0,1,-1 };

    vector<pair<int, int>> groupList;

    while (q.empty() == false) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        groupList.emplace_back(x, y);

        for (int i = 0; i < 4; i++) {
            int nx = x + xdir[i];
            int ny = y + ydir[i];
            if (IsValidCoord(nx, ny) == false)
                continue;
            if (visited[ny][nx] == 1)
                continue;
            if (arr[ny][nx] != c)
                continue;

            visited[ny][nx] = 1;
            q.emplace(nx, ny);
        }
    }

    return groupList;
}

vector<pair<int, int>> FindGroup() {
    int visited[12][6] = { 0, };
    bool findGroup = true;
    vector<pair<int, int>> groupListContainer;
    for (int y = 0; y < 12; y++) {
        for (int x = 0; x < 6; x++) {
            if (arr[y][x] == '.')
                continue;

            auto groupList = GetGroup(x, y, arr[y][x], visited);
            if (groupList.size() >= 4) {
                groupListContainer.insert(groupListContainer.end(), groupList.begin(), groupList.end());
            }
        }
    }


    return groupListContainer;
}

void RemoveGroupList(vector<pair<int, int>> groupList) {
    for (auto pos : groupList) {
        arr[pos.second][pos.first] = '.';
    }
}

void Print() {
    cout << "==============" << endl;
    for (int j = 0; j < 12; j++) {
        for (int i = 0; i < 6; i++) {
            cout << arr[j][i] << " ";
        }
        cout << endl;
    }
}

void DownShift() {
    for (int y = 11; y >= 0; y--) {
        for (int x = 0; x < 6; x++) {
            if (arr[y][x] != '.') {
                int beforeY = y;
                int currentY = y + 1;
                while (IsValidCoord(x, currentY)) {
                    if (arr[currentY][x] != '.')
                        break;

                    arr[currentY][x] = arr[beforeY][x];
                    arr[beforeY][x] = '.';
                    beforeY = currentY;
                    currentY += 1;
                }
            }
        }
    }
}



int main() {
    for (int j = 0; j < 12; j++) {
        for (int i = 0; i < 6; i++) {
            cin >> arr[j][i];
        }
    }

    int result = 0;
    bool findGroup = true;
    do {
        auto groupList = FindGroup();
        if (groupList.empty())
            findGroup = false;
        else {
            RemoveGroupList(groupList);
            DownShift();
            //Print();
            result += 1;
        }
    } while (findGroup == true);

    cout << result;

    return 0;
}
