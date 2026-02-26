#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>
using namespace std;

vector<vector<int>> arr;
vector<pair<int, int>> zeroList;

vector<int> GetHorizontal(pair<int, int> pos)
{
    vector<int> list;
    for (int y = 0; y < 9; y++)
    {
        if (arr[y][pos.second] == 0)
            continue;
        list.push_back(arr[y][pos.second]);
    }
    return list;
}

bool IsValid(pair<int,int> pos, int n)
{
    vector<int> list;
    for (int x = 0; x < 9; x++)
        if (arr[pos.first][x] == n) return false;
    for (int y = 0; y < 9; y++)
        if (arr[y][pos.second] == n) return false;

    int xmin = pos.second / 3 * 3;
    int ymin = pos.first / 3 * 3;

    for (int y = ymin; y < ymin + 3; y++)
    {
        for (int x = xmin; x < xmin + 3; x++)
        {
            if (arr[y][x] == n)
                return false;
        }
    }

    return true;
}

bool DFS(int i)
{
    if (i == zeroList.size())
        return true;

    auto curPos = zeroList[i];
    for (int k = 1; k <= 9; k++)
    {
        if (IsValid(curPos, k))
        {
            arr[curPos.first][curPos.second] = k;
            if (DFS(i + 1))
                return true;
            arr[curPos.first][curPos.second] = 0;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string input;
    arr.resize(9, vector<int>(9));

    for (int j = 0; j < 9; j++)
    {
        cin >> input;
        for (int i = 0; i < 9; i++)
        {
            arr[j][i] = input[i] - '0';
            if (arr[j][i] == 0)
                zeroList.push_back({ j,i });
        }
    }

    DFS(0);

    for (int j = 0; j < 9; j++)
    {
        for (int i = 0; i < 9; i++)
        {
            cout << arr[j][i];
        }
        cout << endl;
    }

    return 0;
}
