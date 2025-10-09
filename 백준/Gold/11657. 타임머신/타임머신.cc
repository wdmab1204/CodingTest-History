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

    int N, M;
    cin >> N >> M;
    vector<long> map(N + 1, LONG_MAX);
    vector<edge> edges;

    for (int i = 0; i < M; i++) {
        int s, e, w;
        cin >> s >> e >> w;
        edges.emplace_back(s, e, w);
    }

    map[1] = 0;

    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < M; j++) {
            edge edge = edges[j];
            int start = edge.s;
            int end = edge.e;
            int time = edge.w;

            if (map[start] != LONG_MAX && map[end] > map[start] + time) {
                map[end] = map[start] + time;
            }
        }
    }

    bool nCycle = false;
    for (int j = 0; j < M; j++) {
        edge edge = edges[j];
        int start = edge.s;
        int end = edge.e;
        int time = edge.w;

        if (map[start] != LONG_MAX && map[end] > map[start] + time) {
            nCycle = true;
            break;
        }
    }

    if (nCycle)
        cout << -1 << endl;
    else {
        for (int i = 2; i <= N; i++) {
            if (map[i] == LONG_MAX)
                cout << -1 << endl;
            else
                cout << map[i] << endl;
        }
    }

    return 0;
}


