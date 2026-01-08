#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <queue>
using namespace std;

int N, W, L;

vector<int> bridge;
queue<int> cacheTrucks;

bool EmptyTruck()
{
    return cacheTrucks.size() == 0;
}

void ShiftLeft()
{
    for (int i = 0; i < W - 1; i++)
    {
        bridge[i] = bridge[i + 1];
    }

    bridge[W - 1] = 0;
}

int GetBridgeTotalWeight()
{
    int totalWeight = 0;
    for (int i = 0; i < W; i++)
        totalWeight += bridge[i];
    return totalWeight;
}

void TryPushTruck()
{
    if (cacheTrucks.empty())
        return;

    int totalWeight = GetBridgeTotalWeight();
    int truck = cacheTrucks.front();
    if (totalWeight + truck <= L)
    {
        cacheTrucks.pop();
        bridge[W - 1] = truck;
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> W >> L;
    bridge.resize(W, 0);

    for (int i = 0; i < N; i++)
    {
        int input;
        cin >> input;
        cacheTrucks.push(input);
    }

    int hours = 0;
    while (EmptyTruck() == false || GetBridgeTotalWeight() > 0)
    {
        ShiftLeft();
        TryPushTruck();
        hours++;
    }
    cout << hours;

    return 0;
}
