#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <iterator>
using namespace std;

struct PairHash
{
    size_t operator()(const std::pair<int, int>& p) const noexcept
    {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};

int N, M;
vector<vector<int>> arr;
unordered_set<pair<int, int>, PairHash> visited;
int dx[] = { 1,-1,0,0 };
int dy[] = { 0,0,1,-1 };

bool IsInArr(pair<int, int> pos)
{
    return pos.first >= 0 && pos.first < N && pos.second >= 0 && pos.second < M;
}

vector<pair<int, int>> BFS(pair<int,int> pos, unordered_set<pair<int, int>, PairHash>& visited)
{
    queue<pair<int, int>> q;
    vector<pair<int, int>> list;
    q.push(pos);
    visited.insert(pos);

    while (!q.empty())
    {
        auto cur = q.front(); q.pop();
        

        for (int i = 0; i < 4; i++)
        {
            int ny = cur.first + dy[i];
            int nx = cur.second + dx[i];
            pair<int, int> next = { ny,nx };

            if (IsInArr(next) == false)
                continue;

            if (arr[next.first][next.second] == 1)
            {
                list.push_back(next);
                continue;
            }

            if (visited.find(next) == visited.end())
            {
                q.push(next);
                visited.insert(next);
            }
        }
    }

    return list;
}

void RemoveCheeses(vector<pair<int, int>> removeCheeses)
{
    for (auto r_pos : removeCheeses)
    {
        arr[r_pos.first][r_pos.second] = 0;
    }
}

vector<pair<int, int>> GetOutsideCheeses()
{
    visited.clear();
    vector<pair<int, int>> latestCheeses;
    latestCheeses = (BFS({ 0,0 }, visited));

    return latestCheeses;
}

bool HasCheese()
{
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < M; x++)
        {
            if (arr[y][x] == 1)
            {
                return true;
            }
        }
    }

    return false;
}

int GetCheeseCount()
{
    int cheeseCount = 0;
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < M; x++)
        {
            if (arr[y][x] == 1)
            {
                cheeseCount += 1;
            }
        }
    }

    return cheeseCount;
}

void Print(vector<pair<int, int>> c)
{
    cout << endl;
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < M; x++)
        {
            if (arr[y][x] == 0)
                cout << 0<<" ";
            else if (find(c.begin(), c.end(), std::make_pair(y, x)) != c.end())
                cout << 'c'<<" ";
            else
                cout << 1<<" ";
        }

        cout << endl;
    }
    cout << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    arr.resize(N, vector<int>(M, 0));

    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < M; x++)
        {
            cin >> arr[y][x];
        }
    }

    int hours = 0;
    pair<int, int> startPos;
    vector<pair<int, int>> removeCheeselist;
    int cheeseCount = 0, latestCheeseCount = 0;
    
    while (cheeseCount = GetCheeseCount())
    {
        removeCheeselist = GetOutsideCheeses();
        //Print(removeCheeselist);
        latestCheeseCount = cheeseCount;
        RemoveCheeses(removeCheeselist);
        hours += 1;
    }

    cout << hours << endl;
    cout << latestCheeseCount << endl;

    return 0;
}
