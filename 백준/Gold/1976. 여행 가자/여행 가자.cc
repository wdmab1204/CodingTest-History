#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <iostream>

using namespace std;

vector<int> parent;

int Find(int a) {
    if (parent[a] == a)
        return a;

    return parent[a] = Find(parent[a]);
}


void Union(int a, int b) {
    int v1 = Find(a);
    int v2 = Find(b);

    if (v1 != v2)
        parent[v2] = v1;
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;

    cin >> n >> m;
    
    parent.resize(n + 1);
    for (int i = 1; i <= n; i++)
        parent[i] = i;

    int dosi[201][201];

    for (int j = 1; j <= n; j++) {
        for (int i = 1; i <= n; i++) {
            cin >> dosi[j][i];

            if (dosi[j][i] == 1)
                Union(j, i);
        }
    }

    vector<int> route(m);
    for (int i = 0; i < m; i++) {
        cin >> route[i];
    }

    int p = Find(route[0]);
    for (int i = 1; i < m; i++) {
        if (Find(route[i]) != p) {
            cout << "NO";
            return 0;
        }
    }

    cout << "YES";
   

    return 0;
}


