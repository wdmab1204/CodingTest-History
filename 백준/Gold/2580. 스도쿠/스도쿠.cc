#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>
#include <unordered_set>
using namespace std;
typedef pair<int, int> Point;

int arr[9][9];
bool used[10];
vector<Point> zeroList;

void GetValidNums(Point p)
{
    memset(used, false, sizeof(used));

    for (int x = 0; x < 9; x++)
    {
        if (arr[p.first][x] != 0)
            used[arr[p.first][x]] = true;
    }

    for (int y = 0; y < 9; y++)
    {
        if (arr[y][p.second] != 0)
            used[arr[y][p.second]] = true;
    }

    int ymin = p.first / 3 * 3;
    int xmin = p.second/ 3 * 3;
    for (int y = ymin; y < ymin+3; y++)
    {
        for (int x = xmin; x < xmin + 3; x++)
        {
            if (arr[y][x] != 0)
                used[arr[y][x]] = true;
        }
    }
}

bool DFS(int k)
{
    
    if (k == zeroList.size())
        return true;

    bool used[10] = { false };

    Point p = zeroList[k];

    for (int x = 0; x < 9; x++)
        used[arr[p.first][x]] = true;

    for (int y = 0; y < 9; y++)
        used[arr[y][p.second]] = true;

    int ymin = p.first / 3 * 3;
    int xmin = p.second / 3 * 3;

    for (int y = ymin; y < ymin + 3; y++)
        for (int x = xmin; x < xmin + 3; x++)
            used[arr[y][x]] = true;

    for (int i = 1; i <= 9; i++)
    {
        if (used[i] == false)
        {
            arr[p.first][p.second] = i;
            if (DFS(k + 1))
                return true;
            arr[p.first][p.second] = 0;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            cin >> arr[y][x];
            if (arr[y][x] == 0)
                zeroList.push_back({ y,x });
        }
    }

    DFS(0);

    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            cout << arr[y][x] << " ";
        }
        cout << endl;
    }


    return 0;
}
