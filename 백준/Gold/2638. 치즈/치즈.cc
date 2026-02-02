#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
using namespace std;

int N, M;
vector<vector<int>> arr;

int dirx[]{ 1,-1,0,0 };
int diry[]{ 0,0,1,-1 };

bool InArr(pair<int, int> p)
{
    return p.first >= 0 && p.first < N && p.second >= 0 && p.second < M;
}

vector<pair<int, int>> bfs(bool visited[101][101])
{
    pair<int, int> start = { N - 1, M - 1 };
    queue<pair<int, int>> q;
    q.push(start);

    int cheesemap[101][101] = { 0, };

    vector<pair<int, int>> result;

    while (!q.empty())
    {
        auto cur = q.front(); q.pop();
        visited[cur.first][cur.second];

        for (int i = 0; i < 4; i++)
        {
            pair<int, int> next = { cur.first + diry[i], cur.second + dirx[i] };
            if (InArr(next) == false)
                continue;

            if (arr[next.first][next.second] == 1)
                cheesemap[next.first][next.second] += 1;

            if (cheesemap[next.first][next.second] == 2)
                result.push_back(next);
        }

        for (int i = 0; i < 4; i++)
        {
            pair<int, int> next = { cur.first + diry[i], cur.second + dirx[i] };
            if (InArr(next) == false)
                continue;

            if (visited[next.first][next.second] == true)
                continue;

            if (arr[next.first][next.second] == 1)
                continue;

            q.push(next);
            visited[next.first][next.second] = true;
        }
    }

    return result;
}

bool HasCheese()
{
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < M; x++)
        {
            if (arr[y][x] == 1)
                return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    N += 1;
    M += 1;

    arr.resize(N, vector<int>(M, 0));

    int days = 0;
    for (int y = 0; y < N - 1; y++)
    {
        for (int x = 0; x < M - 1; x++)
        {
            cin >> arr[y][x];
        }
    }

    while (HasCheese())
    {
        bool visited[101][101] = { false, };
        auto result = bfs(visited);
        for (auto p : result)
        {
            arr[p.first][p.second] = 0;
        }
        days += 1;
    }

    cout << days;

    /*auto result = bfs();
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < M; x++)
        {

            bool f = false;
            for (auto p : result)
            {
                if (p.first == y && p.second == x)
                {
                    cout << "K" << " ";
                    f = true;
                    break;
                }
            }

            if (f)
                continue;

            if (arr[y][x] == 1)
                cout << "A" << " ";
            if (arr[y][x] == 0)
                cout << 0 << " ";
        }
        cout << endl;
    }*/

    return 0;
}
