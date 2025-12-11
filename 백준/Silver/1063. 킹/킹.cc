#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>
using namespace std;

vector<vector<int>> arr(8, vector<int>(8, 0));
unordered_map<string, pair<int, int>> dict;
pair<int, int> player, stone;

bool IsValidCoord(pair<int, int> pawn) {
    return pawn.first >= 0 && pawn.first < 8 && pawn.second >= 0 && pawn.second < 8;
}

bool PawnCompare(pair<int, int> pawn1, pair<int, int> pawn2) {
    return pawn1.first == pawn2.first && pawn1.second == pawn2.second;
}

pair<int, int> ConvertCoord(string cmd) {
    char prefix = cmd[0];
    char suffix = cmd[1];

    int y = 8 - (suffix - '0');
    int x = prefix - 'A';

    return pair<int, int>(x, y);
}

string ConvertCoord(pair<int, int> pawn) {
    int x = pawn.first;
    int y = pawn.second;

    char prefix = x + 'A';
    char suffix = 8 + '0' - y;

    string result;
    result.push_back(prefix);
    result.push_back(suffix);
    return result;
}

pair<int,int> Move(pair<int,int> pawn, string cmd) {
    pawn.first += dict[cmd].first;
    pawn.second += dict[cmd].second;
    return pawn;
}

void Logic(string cmd) {
    auto nextPlayerPos = Move(player, cmd);
    if (IsValidCoord(nextPlayerPos) == false)
        return;

    if (PawnCompare(nextPlayerPos, stone)) {
        auto nextStonePos = Move(stone, cmd);
        if (IsValidCoord(nextStonePos) == false)
            return;
        else
            stone = nextStonePos;
    }
    player = nextPlayerPos;
}

void Print() {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            pair<int, int> coord = pair<int, int>(x, y);
            if (PawnCompare(player, coord))
                cout << "* ";
            else if (PawnCompare(stone, coord))
                cout << "- ";
            else
                cout << ". ";
        }
        cout << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    dict["R"] = pair<int, int>(1, 0);
    dict["L"] = pair<int, int>(-1, 0);
    dict["B"] = pair<int, int>(0, +1);
    dict["T"] = pair<int, int>(0, -1);
    dict["RT"] = pair<int, int>(1, -1);
    dict["LT"] = pair<int, int>(-1, -1);
    dict["RB"] = pair<int, int>(1, 1);
    dict["LB"] = pair<int, int>(-1, 1);

    string playercmd, stonecmd, cmdInput;
    int cmdCount;
    cin >> playercmd >> stonecmd >> cmdCount;

    player = ConvertCoord(playercmd);
    stone = ConvertCoord(stonecmd);

    while (cmdCount-- > 0) {
        cin >> cmdInput;
        Logic(cmdInput);
        //Print();
    }

    cout << ConvertCoord(player) << endl;
    cout << ConvertCoord(stone);

    return 0;
}
