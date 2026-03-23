#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <utility>
using namespace std;
struct Point
{
    int y;
    int x;

    bool operator==(const Point& other) const
    {
        return x == other.x && y == other.y;
    }
};

struct Student
{
    int num;
    vector<int> likes;
};

struct Cell
{
    int num;
    int like_cnt;
    int empty_cnt;
    int y;
    int x;
};

int N;
int score = 0;
int dirx[] = { 1,-1,0,0 };
int diry[] = { 0,0,1,-1 };
//unordered_map<int, Student> friends;
vector<Student> friends;
vector<vector<int>> arr;
vector<vector<Cell>> classes;

bool IsInArr(int y, int x)
{
    return y >= 0 && y < N && x >= 0 && x < N;
}

void Set(int v)
{
    classes.clear();
    vector<Cell> cells;
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            if (arr[y][x] != 0)
                continue;

            Point p = { y,x };
            Cell cell;
            cell.y = y;
            cell.x = x;
            cell.num = v;
            cell.like_cnt = 0;
            cell.empty_cnt = 0;

            for (int i = 0; i < 4; i++)
            {
                Point next = { p.y + diry[i], p.x + dirx[i] };
                if (IsInArr(next.y, next.x) == false)
                    continue;

                auto fri = friends[v].likes;
                for (int k = 0; k < 4; k++)
                {
                    if (fri[k] == arr[next.y][next.x])
                        cell.like_cnt += 1;
                }

                if (arr[next.y][next.x] == 0)
                    cell.empty_cnt += 1;
            }

            cells.push_back(cell);
        }
    }

    sort(cells.begin(), cells.end(), [](const Cell a, const Cell b)
        {
            if (a.like_cnt != b.like_cnt)
                return a.like_cnt > b.like_cnt;

            if (a.empty_cnt != b.empty_cnt)
                return a.empty_cnt > b.empty_cnt;

            if (a.y != b.y)
                return a.y < b.y;

            return a.x < b.x;
        });

    arr[cells[0].y][cells[0].x] = cells[0].num;
}

void Score()
{
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            int v = arr[y][x];
            Point p = { y,x };
            int cnt = 0;
            for (int i = 0; i < 4; i++)
            {
                auto fri = friends[v].likes;
                Point next = { p.y + diry[i], p.x + dirx[i] };

                if (IsInArr(next.y, next.x) == false)
                    continue;

                for (int k = 0; k < 4; k++)
                {
                    if (fri[k] == arr[next.y][next.x])
                        cnt += 1;
                }
            }

            if (cnt == 1)
                score += 1;
            else if (cnt == 2)
                score += 10;
            else if (cnt == 3)
                score += 100;
            else if (cnt == 4)
                score+=1000;
        }
    }
}

void Print()
{
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            cout << arr[y][x] << " ";
        }
        cout << endl;
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    int num;
    arr.resize(N, vector<int>(N, 0));
    vector<int> order(N * N);
    friends.resize(N * N + 1);
    for (int i = 0; i < N * N; i++)
    {
        vector<int> likes(4);
        cin >> num;
        for (int j = 0; j < 4; j++)
            cin >> likes[j];
        Student st = { num, likes };
        friends[num] = st;
        order[i] = num;
    }

    for (int i = 0; i < N * N; i++)
    {
        Set(order[i]);
    };

    Score();
    //Print();

    cout << score;
}
