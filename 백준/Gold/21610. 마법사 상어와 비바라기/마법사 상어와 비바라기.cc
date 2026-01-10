#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <queue>
using namespace std;

int N, M;
vector<vector<int>> arr;
vector<pair<int, int>> clouds;
vector<pair<int, int>> removedclouds;

bool IsInArr(int y, int x)
{
    return x >= 0 && x < N &&  y >= 0 && y < N;
}

void MoveCloud(int move, int dir)
{
    dir -= 1;
    //←, ↖, ↑, ↗, →, ↘, ↓, ↙
	int dy[] = {0, -1, -1, -1, 0, 1, 1, 1};
	int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};

    for (auto& cloud : clouds)
    {
        int ny = ((cloud.first + dy[dir] * move) % N + N) % N;
        int nx = ((cloud.second + dx[dir] * move) % N + N) % N;
        cloud.first = ny;
        cloud.second = nx;
    }
}

void AddWater()
{
    for (const auto cloud : clouds)
    {
        arr[cloud.first][cloud.second] += 1;
    }
}

void RemoveAllCloud()
{
    removedclouds = clouds;
    clouds.clear();
}

void DoWaterCopyBug()
{
    int dx[] = { 1,1,-1,-1 };
    int dy[] = { -1,1,1,-1 };

    for (const auto cloud : removedclouds)
    {
        int waterCount = 0;
        for (int i = 0; i < 4; i++)
        {
            int ny = cloud.first + dy[i];
            int nx = cloud.second + dx[i];
            if (IsInArr(nx, ny) == false)
                continue;

            if (arr [ny][nx] > 0)
                waterCount += 1;
        }

        arr[cloud.first][cloud.second] += waterCount;
    }
}

void CreateClouds()
{
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            pair<int, int> coord = pair<int, int>(y, x);
            if (find(removedclouds.begin(), removedclouds.end(), coord) != removedclouds.end())
                continue;

            if (arr[y][x] >= 2)
            {
                clouds.push_back(coord);
                arr[y][x] -= 2;
            }
                
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

	cin >> N >> M;

	arr.resize(N, vector<int>(N));
	clouds.push_back({ N - 1, 0 }); 
	clouds.push_back({ N - 1, 1 }); 
    clouds.push_back({ N - 2, 0 });
    clouds.push_back({ N - 2, 1 });

    for(int j=0; j<N; j++) {
        for(int i=0; i<N; i++) {
            cin >> arr[j][i];
        }
	}

    int move, dir;
    for (int k = 0; k < M; k++)
    {

        cin >> dir >> move;
        

        MoveCloud(move, dir);
        AddWater();
        RemoveAllCloud();
        DoWaterCopyBug();
        CreateClouds();

        /*for (int j = 0; j < N; j++)
        {
            for (int i = 0; i < N; i++)
            {
                cout << arr[j][i] << " ";
            }
            cout << endl;
        }
        cout << endl;*/
    }

    int totalWater = 0;
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            totalWater += arr[y][x];
        }
    }

    cout << totalWater;


    return 0;
}
