#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_set>
using namespace std;

int N, K;
vector<int> belts;
vector<int> robots;

int Calc(int value) {
    return value % (N*2);
}

void DecreaseDurability(int index) {
    belts[index] -= 1;
}

int GetDurability(int index) {
    return belts[index];
}

void SetRobot() {
    robots.push_back(0);
    DecreaseDurability(0);
}


bool CanPlaceRobot(int index) {
    if (GetDurability(index) <= 0)
        return false;
    for (int i = 0; i < robots.size(); i++) {
        if (robots[i] == index)
            return false;
    }
    return true;
}

bool IsRobotDestination(int index) {
    return index == N - 1;
}

void RemoveRobot(int robot) {
    for (int i = 0; i < robots.size(); i++) {
        if (robots[i] == robot)
        {
            robots.erase(robots.begin() + i);
            return;
        }
    }
}

void MoveRobot(int robotIndex) {
    int newRobotPos = Calc(robots[robotIndex] + 1);
    robots[robotIndex] = newRobotPos;
}

void CheckAndMovingRobots() {
    vector<int> removes;
    for (int i = 0; i < robots.size(); i++) {
        if (robots[i] == 0)
            continue;

        if (CanPlaceRobot(Calc(robots[i] + 1)) == false)
            continue;

        MoveRobot(i);

        DecreaseDurability(robots[i]);

        if (IsRobotDestination(robots[i])) {
            removes.push_back(robots[i]);
        }
    }

    for (auto robot : removes)
        RemoveRobot(robot);
}

vector<int> MovingCommand(vector<int> v) {
    if (v.size() == 0)
        return v;

    int back = v[v.size() - 1];
    for (int i = v.size() - 1; i > 0; i--) {
        v[i] = v[i - 1];
    }
    v[0] = back;
    return v;
}

void MovingBeltAndRobot() {
    belts = MovingCommand(belts);
    vector<int> removes;

    for (int i = 0; i < robots.size(); i++) {
        robots[i] = Calc(robots[i] + 1);
        if (IsRobotDestination(robots[i])) {
            removes.push_back(robots[i]);
        }
    }

    for (auto robot : removes)
        RemoveRobot(robot);
}

int GetZeroDurabilityCount() {
    int cnt = 0;
    for (int i = 0; i < belts.size(); i++) {
        if (belts[i] == 0)
            cnt++;
    }
    return cnt;
}

int GetRobot(int index) {
    for (int i = 0; i < robots.size(); i++) {
        if (index == robots[i])
            return 1;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> K;

    belts.resize(N * 2, 0);

    for (int i = 0; i < N * 2; i++) {
        cin >> belts[i];
    }
    
    int step = 1;
    while (true) {
        //cout << "Step: " << step << endl;

        MovingBeltAndRobot();
        /*cout << "MovingBeltAndRobot" << endl;
        for (int i = 0; i < N* 2; i++) {
            cout << "(" << belts[i] << ", " << GetRobot(i) << ")" << endl;
        }
        cout << endl;*/

        CheckAndMovingRobots();
        /*cout << "CheckAndMovingRobot" << endl;
        for (int i = 0; i < N * 2; i++) {
            cout << "(" << belts[i] << ", " << GetRobot(i) << ")" << endl;
        }
        cout << endl;*/

        if (CanPlaceRobot(0)) {
            SetRobot();
        }
        /*cout << "SetRobot" << endl;
        for (int i = 0; i < N * 2; i++) {
            cout << "(" << belts[i] << ", " << GetRobot(i) << ")" << endl;
        }
        cout << endl;*/

        if (GetZeroDurabilityCount() >= K)
            break;

        step += 1;
        //int t;
        //cin >> t;
    }

    cout << step;


    return 0;
}
