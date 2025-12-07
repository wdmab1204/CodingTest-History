#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int presentCnt, studentCnt, input;
    cin >> presentCnt >> studentCnt;

    priority_queue<int, vector<int>> presentQ;
    vector<int> studentV;

    for (int i = 0; i < presentCnt; i++) {
        cin >> input;
        presentQ.push(input);
    }
    for (int i = 0; i < studentCnt; i++) {
        cin >> input;
        studentV.push_back(input);
    }

    for (int i = 0; i < studentCnt; i++)
    {
        int student = studentV[i];
        int present = presentQ.top(); presentQ.pop();
        
        if (student > present) {
            cout << 0;
            return 0;
        }
        if (present - student > 0)
            presentQ.push(present - student);
    }

    cout << 1;

    return 0;
}
