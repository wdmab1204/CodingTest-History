#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <utility>
using namespace std;
int N, M, K;

struct OpDTO
{
    int r;
    int c;
    int s;
};

vector<OpDTO> v;
vector<vector<int>> arr;
vector<bool> visited;
int m = 10000;

void op(int r, int c, int s)
{
    int leftTop_y = r - s;
    int leftTop_x = c - s;
    int rightBtm_y = r + s;
    int rightBtm_x = c + s;

    while (rightBtm_x - leftTop_x > 1)
    {
        int tmp = arr[leftTop_y][leftTop_x];
        for (int x = leftTop_x + 1; x <= rightBtm_x; x++)
        {
            int tmp2 = arr[leftTop_y][x];
            arr[leftTop_y][x] = tmp;
            tmp = tmp2;
        }
        for (int y = leftTop_y + 1; y <= rightBtm_y; y++)
        {
            int tmp2 = arr[y][rightBtm_x];
            arr[y][rightBtm_x] = tmp;
            tmp = tmp2;
        }
        for (int x = rightBtm_x - 1; x >= leftTop_x; x--)
        {
            int tmp2 = arr[rightBtm_y][x];
            arr[rightBtm_y][x] = tmp;
            tmp = tmp2;
        }
        for (int y = rightBtm_y - 1; y >= leftTop_y; y--)
        {
            int tmp2 = arr[y][leftTop_x];
            arr[y][leftTop_x] = tmp;
            tmp = tmp2;
        }
        leftTop_y++;
        leftTop_x++;
        rightBtm_y--;
        rightBtm_x--;
    }
}
void rop(int r, int c, int s)
{
    int leftTop_y = r - s;
    int leftTop_x = c - s;
    int rightBtm_y = r + s;
    int rightBtm_x = c + s;

    while (rightBtm_x - leftTop_x > 1)
    {
        int tmp = arr[leftTop_y][leftTop_x];
        for (int y = leftTop_y + 1; y <= rightBtm_y; y++)
        {
            int tmp2 = arr[y][leftTop_x];
            arr[y][leftTop_x] = tmp;
            tmp = tmp2;
        }
        for (int x = leftTop_x + 1; x <= rightBtm_x; x++)
        {
            int tmp2 = arr[rightBtm_y][x];
            arr[rightBtm_y][x] = tmp;
            tmp = tmp2;
        }
        for (int y = rightBtm_y - 1; y >= leftTop_y; y--)
        {
            int tmp2 = arr[y][rightBtm_x];
            arr[y][rightBtm_x] = tmp;
            tmp = tmp2;
        }
        for (int x = rightBtm_x - 1; x >= leftTop_x; x--)
        {
            int tmp2 = arr[leftTop_y][x];
            arr[leftTop_y][x] = tmp;
            tmp = tmp2;
        }
        leftTop_y++;
        leftTop_x++;
        rightBtm_y--;
        rightBtm_x--;
    }
}
void GetMin()
{
    for (int y = 0; y < arr.size(); y++)
    {
        int total = 0;
        for (int x = 0; x < arr[0].size(); x++)
        {
            total += arr[y][x];
        }
        if (m > total)
            m = total;
    }
}

void DFS(int d)
{
    if (d == K)
    {
        GetMin();
        return;
    }

    for (int i = 0; i < K; i++)
    {
        if (visited[i]) continue;

        visited[i] = true;
        auto dto = v[i];

        op(dto.r, dto.c, dto.s);

        DFS(d + 1);

        rop(dto.r, dto.c, dto.s);
        visited[i] = false;
    }
}

void Print()
{
    for (int y = 0; y < arr.size(); y++)
    {
        for (int x = 0; x < arr[0].size(); x++)
        {
            cout << arr[y][x] << " ";
        }
        cout << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> K;
    arr.resize(N, vector<int>(M));
    visited.resize(K, false);
    v.resize(K);
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < M; x++)
        {
            cin >> arr[y][x];
        }
    }

    for (int k = 0; k < K; k++)
    {
        OpDTO dto;
        cin >> dto.r >> dto.c >> dto.s;
        dto.r -= 1;
        dto.c -= 1;
        v[k] = dto;
    }

    DFS(0);
    
    cout << m;
}
