#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;

struct Group
{
    bool success;
    int totalValue;
    vector<pair<int, int>> posList;
};

int N, L, R;
vector<vector<int>> arr;
bool visited[51][51] = { false, };
int dirx[]={ 1,-1,0,0 };
int diry[]={ 0,0,1,-1 };


Group BFS(pair<int, int> start)
{
    queue<pair<int, int>> q;
    q.push(start);
    visited[start.first][start.second] = true;
    bool isFinded = false;
    Group group;
    group.totalValue = 0;
    
    while (q.empty() == false)
    {
        auto cur = q.front(); q.pop();

        group.posList.push_back(cur);
        group.totalValue += arr[cur.first][cur.second];

        

        for (int i = 0; i < 4; i++)
        {
            pair<int, int> next = { cur.first + diry[i], cur.second + dirx[i] };
            if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= N)
                continue;

            if (visited[next.first][next.second] == true)
                continue;

            int diff = abs(arr[cur.first][cur.second] - arr[next.first][next.second]);
            if (diff < L || diff > R)
                continue;

            q.push(next);
            visited[next.first][next.second] = true;
            isFinded = true;
        }
    }

    group.success = isFinded;

    return group;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> L >> R;

    arr.resize(N, vector<int>(N));

    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            cin >> arr[y][x];
        }
    }

    int days = 0;

    while (true)
    {
        memset(visited, false, sizeof(visited));
        vector<Group> groupList;
        for (int y = 0; y < N; y++)
        {
            for (int x = 0; x < N; x++)
            {
                if (visited[y][x] == 1)
                    continue;

                Group group = BFS({ y,x });
                if (group.success == false)
                    continue;

                groupList.push_back(group);
            }
        }

        if (groupList.size() == 0)
            break;

        for (auto group : groupList)
        {
            int unitValue = group.totalValue / group.posList.size();
            for (auto pos : group.posList)
            {
                arr[pos.first][pos.second] = unitValue;
            }
        }

        days++;
    }

    /*cout << endl;
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            cout << arr[y][x] << " ";
        }
        cout << endl;
    }*/

    cout << days;

    

    return 0;
}
