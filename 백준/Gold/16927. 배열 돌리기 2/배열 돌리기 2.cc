#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>
#include <unordered_set>
#include <utility>
using namespace std;
typedef pair<int, int> Point;

int N, M, R;

vector<vector<int>> arr;

void Rotate(Point p, int n, int m, int r)
{
    int t = (n * 2) + ((m - 2) * 2);
    if (r >= t)
        r = r % t;

    for (int k = 0; k < r; k++)
    {
        int cache = arr[p.first][p.second];
        int cache2;
        for (int y = p.first + 1; y < p.first + n; y++)
        {
            cache2 = arr[y][p.second];
            arr[y][p.second] = cache;
            cache = cache2;
        }
        for (int x = p.second + 1; x < p.second + m; x++)
        {
            cache2 = arr[p.first + n - 1][x];
            arr[p.first + n - 1][x] = cache;
            cache = cache2;
        }
        for (int y = p.first + n - 2; y >= p.first; y--)
        {
            cache2 = arr[y][p.second + m - 1];
            arr[y][p.second + m - 1] = cache;
            cache = cache2;
        }
        for (int x = p.second + m - 2; x >= p.second; x--)
        {
            cache2 = arr[p.first][x];
            arr[p.first][x] = cache;
            cache = cache2;
        }
    }
}

void Print()
{
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < M; x++)
        {
            cout << arr[y][x] << " ";
        }
        cout << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> R;
    arr.resize(N, vector<int>(M));
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < M; x++)
        {
            cin >> arr[y][x];
        }
    }

    Point p = { 0,0 };
    int n = N;
    int m = M;

    int c = min(N, M) / 2;
    for (int i = 0; i < c; i++)
    {
        Rotate(p, n, m, R);
        p = { p.first + 1, p.second + 1 };
        n -= 2;
        m -= 2;
    }

    
    Print();
}
