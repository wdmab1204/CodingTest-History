#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>
using namespace std;

typedef pair<int, int> Point;

Point cleaner;
int dirtyCount;
vector<vector<int>> arr;
int dir;
int diry[] = { -1,0,1,0 };
int dirx[] = { 0,1,0,-1 };
int N, M;

bool IsInArr(Point p)
{
    if (p.first < 0 || p.first >= N || p.second < 0 || p.second >= M)
        return false;

    if (arr[p.first][p.second] == 1)
        return false;

    return true;
}

bool IsCleanAround()
{
    for (int i = 0; i < 4; i++)
    {
        Point next = { cleaner.first + diry[i], cleaner.second + dirx[i] };

        if (IsInArr(next))
        {
            if (arr[next.first][next.second] == 0)
                return false;
        }
    }

    return true;
}

bool TryMoveBack()
{
    int reverseDir = (dir + 2) % 4;
    Point back = { cleaner.first + diry[reverseDir], cleaner.second + dirx[reverseDir] };
    if (IsInArr(back) == false)
        return false;

    cleaner = back;
    return true;
}

void Rotate_CCW_Dir()
{
    dir = (dir + 3) % 4;
}

void MoveForward()
{
    Point forward = { cleaner.first + diry[dir], cleaner.second + dirx[dir] };
    cleaner = forward;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    cin >> cleaner.first >> cleaner.second >> dir;

    arr.resize(N, vector<int>(M));
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < M; x++)
        {
            cin >> arr[y][x];
            if (arr[y][x] == 0)
                dirtyCount += 1;
        }
    }


    int cleanCount = 0;
    while (dirtyCount > 0)
    {
        if (arr[cleaner.first][cleaner.second] == 0)
        {
            arr[cleaner.first][cleaner.second] = 2;
            dirtyCount -= 1;
            cleanCount += 1;
        }

        if (IsCleanAround())
        {
            if (TryMoveBack())
                continue;
            else
                break;
        }

        for (int i = 0; i < 4; i++)
        {
            Rotate_CCW_Dir();
            Point next = { cleaner.first + diry[dir], cleaner.second + dirx[dir] };
            if (IsInArr(next) && arr[next.first][next.second] == 0)
            {
                MoveForward();
                break;
            }
        }
    }

    cout << cleanCount;

    return 0;
}
