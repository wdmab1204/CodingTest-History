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
    cin >> V >> E;

    vector<vector<edge>> adj(V + 1);
    vector<int> visited(V + 1, false);
    vector<int> map(V + 1, INT_MAX);
    priority_queue<edge, vector<edge>, greater<edge>> pq;

    for (int i = 0; i < E; i++) {
        int s, d, w;
        cin >> s >> d >> w;
        adj[s].emplace_back(w, d);
    }

    int source, destination;
    cin >> source >> destination;

    map[source] = 0;
    pq.emplace(0, source);
    while (!pq.empty()) {
        auto [curW, curV] = pq.top();
        pq.pop();

        if (visited[curV])
            continue;
        visited[curV] = true;

        for (int i = 0; i < adj[curV].size(); i++) {
            auto [nextW, nextV] = adj[curV][i];
            if (map[nextV] > map[curV] + nextW) {
                map[nextV] = map[curV] + nextW;
                pq.emplace(map[nextV], nextV);
            }
        }
    }

    cout << map[destination];

    return 0;
}


