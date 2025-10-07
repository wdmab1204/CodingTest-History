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


    int V, E, K;
    cin >> V >> E >> K;

    vector<vector<edge>> adj(V + 1);
    vector<priority_queue<int>> map(V + 1);
    priority_queue<edge, vector<edge>, greater<edge>> pq;

    for (int i = 0; i < E; i++) {
        int s, d, w;
        cin >> s >> d >> w;
        adj[s].emplace_back(w, d);
    }

    pq.emplace(0, 1);
    map[1].push(0);
    while (!pq.empty()) {
        auto [curW, curV] = pq.top();
        pq.pop();

        for (int i = 0; i < adj[curV].size(); i++) {
            auto [nextW, nextV] = adj[curV][i];
            if (map[nextV].size() < K) {
                map[nextV].push(curW + nextW);
                pq.emplace(curW + nextW, nextV);
            }
            else if (map[nextV].top() > curW + nextW) {
                map[nextV].pop();
                map[nextV].push(curW + nextW);
                pq.emplace(curW + nextW, nextV);
            }
        }
    }

    for (int i = 1; i <= V; i++) {
        if (map[i].size() == K)
            cout << map[i].top() << endl;
        else
            cout << -1 << endl;
    }

    return 0;
}


