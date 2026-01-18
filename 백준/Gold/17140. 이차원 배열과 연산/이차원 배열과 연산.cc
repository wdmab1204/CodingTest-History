#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
using namespace std;

vector<vector<int>> arr(3, vector<int>(3));

struct Data
{
    int num;
    int count;
};

vector<vector<int>> Transpose(vector<vector<int>> tmp)
{
    int newY = tmp[0].size();
    int newX = tmp.size();
    vector<vector<int>> newArr = vector<vector<int>>(newY, vector<int>(newX));

    for (int y = 0; y < newY; y++)
    {
        for (int x = 0; x < newX; x++)
        {
            newArr[y][x] = tmp[x][y];
        }
    }

    return newArr;
}

void Operate(vector<vector<int>>& tmp)
{
    int maxLength = 0;
    for (int j = 0; j < tmp.size(); j++)
    {
        map<int, int> m;
        
        for (int i = 0; i < tmp[j].size(); i++)
        {
            if (tmp[j][i] == 0)
                continue;

            m[tmp[j][i]] += 1;
        }

        vector<Data> v;
        for (auto pair : m)
        {
            v.push_back({ pair.first, pair.second });
        }

        sort(v.begin(), v.end(), [](Data a, Data b)
            {
                if (a.count == b.count)
                    return a.num < b.num;

                return a.count < b.count;
            });

        vector<int> newList;

        for (int i = 0; i < v.size(); i++)
        {
            if (i >= 100)
                break;

            auto data = v[i];
            if (data.num == 0)
                continue;
            newList.push_back(data.num);
            newList.push_back(data.count);
        }

        tmp[j] = newList;

        if (maxLength < newList.size())
            maxLength = newList.size();
    }

    for (int j = 0; j < tmp.size(); j++)
    {
        tmp[j].resize(maxLength);
    }
}

void Print(vector<vector<int>> printArr)
{
    cout << endl;
    for (int y = 0; y < printArr.size(); y++)
    {
        for (int x = 0; x < printArr[y].size(); x++)
        {
            cout << printArr[y][x] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int r, c, k;
    cin >> r >> c >> k;
   

    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            cin >> arr[y][x];
        }
    }

    int sec = 0;
    while (r-1 >=arr.size() || c-1 >=arr[0].size() || arr[r - 1][c - 1] != k)
    {
        if (sec > 100)
            break;

        if (arr.size() >= arr[0].size())
        {
            Operate(arr);
        }
        else
        {
            arr = Transpose(arr);
            Operate(arr);
            arr = Transpose(arr);
        }
        sec += 1;
    }

    if (sec > 100)
        cout << -1;
    else
        cout << sec;

    return 0;
}
