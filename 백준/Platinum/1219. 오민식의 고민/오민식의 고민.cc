#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <iostream>
#include <queue>
#include <limits.h>

using namespace std;

struct edge {
    int s, e, w;
    edge(int s, int e, int w) : s(s), e(e), w(w){}
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int N, S, E, M;
    cin >> N >> S >> E >> M;
    vector<long> map(N, LONG_MIN);
    vector<int> city(N);
    vector<edge> edges;
    vector<vector<edge>> adj(N);

    for (int i = 0; i < M; i++) {
        int s, e, w;
        cin >> s >> e >> w;
        edges.emplace_back(s, e, -w);
        adj[s].emplace_back(s, e, -w);
    }

    //도시 도착하면 버는 돈
    for (int i = 0; i < N; i++) {
        cin >> city[i];
    }

    map[S] = city[S];

    
    for (int i = 0; i < N - 1; i++) {  
        for (int j = 0; j < M; j++) {
            int s = edges[j].s;
            int e = edges[j].e;
            int w = edges[j].w;

            if (map[s] != LONG_MIN && map[e] < map[s] + w + city[e]) {
                map[e] = map[s] + w + city[e];
            }
        }
    }

    


    if (map[E] == LONG_MIN) {
        cout << "gg" << endl;
        return 0;
    }

    queue<int> q;
    vector<int> visited(N, false);
    for (int j = 0; j < M; j++) {
        int s = edges[j].s;
        int e = edges[j].e;
        int w = edges[j].w;
        

        if (map[s] != LONG_MIN && map[e] < map[s] + w + city[e]) {
            //cout << "Gee" << endl;
            //return 0;
            q.push(s);
        }
    }

    while (!q.empty()) {
        int cur = q.front(); q.pop();

        if (cur == E) {
            cout << "Gee" << endl;
            return 0;
        }

        for (int i = 0; i < adj[cur].size(); i++) {
            int nei = adj[cur][i].e;
            if (visited[nei] == false) {
                visited[nei] = true;
                q.push(nei);
            }
        }
    }
    

    cout << map[E] << endl;

    return 0;
}


