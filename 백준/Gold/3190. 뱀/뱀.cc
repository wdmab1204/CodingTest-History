#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_set>
using namespace std;

//vector<vector<int>> arr;
vector<pair<int, int>> snake;
vector<pair<int, int>> apples;
pair<int, int> dir = pair<int, int>(0, 1);
int mapSize;

pair<int, int> GetHeadPos() {
    return snake[0];
}

bool IsInflictSnakeBody(pair<int,int> head) {
    for (int i = 1; i < snake.size(); i++) {
        if (head == snake[i])
            return true;
    }
    return false;
}

bool IsInflictWall(pair<int,int> head) {
    bool inarr = head.first >= 0 && head.first < mapSize && head.second >= 0 && head.second < mapSize;
    return inarr == false;
}

bool CheckInflict() {
    auto head = GetHeadPos();
    if (IsInflictWall(head))
        return true;

    if (IsInflictSnakeBody(head))
        return true;

    return false;
}

bool TryEatApple(pair<int,int> head) {
    for (auto it = apples.begin(); it != apples.end(); ++it) {
        if (*it == head) {
            apples.erase(it);
            return true;
        }
    }
    return false;
}

void OneMove() {
    auto head = GetHeadPos();
    head.first += dir.first;
    head.second += dir.second;
    snake.insert(snake.begin(), head);
}

void TurnSnake(char c) {
    pair<int, int> newdir;
    if (c == 'D') {
        newdir.first = dir.second;
        newdir.second = -dir.first;

    }
    else {
        newdir.first = -dir.second;
        newdir.second = dir.first;
    }

    dir = newdir;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int input, input2;
    snake.push_back(pair<int, int>(0, 0));

    cin >> input;
    mapSize = input;

    cin >> input;
    int appleCount = input;

    while (appleCount-- > 0) {
        cin >> input >> input2;
        apples.push_back(pair<int, int>(input - 1, input2 - 1));
    }

    cin >> input;
    int cmdCount = input;
    char cInput;
    vector<int> moveCmds;
    vector<char> dirCmds;
    while (cmdCount-- > 0) {
        cin >> input;
        cin >> cInput;

        moveCmds.push_back(input);
        dirCmds.push_back(cInput);
    }
    
    int secs = 1;
    int i = 0;
    while (true) {
        OneMove();
        if (CheckInflict()) { 
            cout << secs;
            return 0;
        }
        if (TryEatApple(GetHeadPos()) == false) {
            snake.pop_back();
        }

        if (i < moveCmds.size()) {
            if (secs == moveCmds[i]) {
                auto head = GetHeadPos();
                //cout << head.second << ", " << head.first << endl;
                TurnSnake(dirCmds[i]);
                i++;
            }
        }
        
        secs += 1;
        
    }
    cout << -1;
    return 0;
}
