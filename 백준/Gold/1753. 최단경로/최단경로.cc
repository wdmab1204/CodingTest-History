#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <iostream>
#include <queue>
#include <limits.h>

using namespace std;

typedef pair<int, int> edge;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);


    int V, E, S;
    cin >> V >> E >> S;

    vector<vector<edge>> adj(V + 1);
    vector<int> visited(V + 1, false);
    priority_queue<edge, vector<edge>, greater<edge>> pq;

    for (int i = 0; i < E; i++)
    {
        int s, d, w;
        cin >> s >> d >> w;
        adj[s].emplace_back(d, w);
    }

    pq.emplace(0, S);
    vector<int> map(V + 1, INT_MAX);
    map[S] = 0;

    while (!pq.empty()) {
        auto [curW, curV] = pq.top();
        pq.pop();

        if (visited[curV]) 
            continue;
        visited[curV] = true;

        for (auto [nextV, nextW] : adj[curV]) {
            if (map[nextV] > curW + nextW) {
                map[nextV] = curW + nextW;
                pq.emplace(map[nextV], nextV);
            }
        }
    }

    for (int i = 1; i <= V; i++) {
        if (visited[i])
            cout << map[i] << endl;
        else
            cout << "INF" << endl;
    }

    return 0;
}


