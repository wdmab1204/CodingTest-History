#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>
using namespace std;

vector<vector<int>> arr;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int ymax, xmax;
    cin >> ymax >> xmax;

    arr.resize(ymax, vector<int>(xmax, 0));
    
    for (int x = 0; x < xmax; x++) {
        int height;
        cin >> height;
        for (int y = 0; y < height; y++) {
            arr[y][x] = 1;
        }
    }

    int totalWater = 0;
    for (int y = 0; y < ymax; y++) {
        int meetBlack = false;
        int water = 0;
        for (int x = 0; x < xmax; x++) {
            if (arr[y][x] == 0) {
                water += 1;
            }
            else {
                if (meetBlack)
                    totalWater += water;
                water = 0;
                meetBlack = true;
            }
        }
    }

    cout << totalWater;

    return 0;
}
