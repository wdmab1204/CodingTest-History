#include <iostream>
#include <vector>
using namespace std;



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;
    string input;
    vector<string> v;
    while(k--)
    {
        cin >> input;
        v.push_back(input);
    }

    if (v.size() == 1)
    {
        cout << v[0];
        return 0;
    }

    int len = v[0].size();

    string target = v[0];
    string result;
    for (int i = 0; i < len; i++)
    {
        bool same = true;
        
        for (int j = 1; j < v.size(); j++)
        {
            if (target[i] != v[j][i])
            {
                same = false;
                break;
            }
        }

        if (same)
            result.push_back(target[i]);
        else
            result.push_back('?');
    }
    cout << result;

    return 0;
}
