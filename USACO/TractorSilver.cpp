#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include <cstdio>
using namespace std;
const int N = 5e2 + 10;
int n, bd[N][N], mid,cnt,sz[N * N], p[N * N];
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};
//map<pair<int, int>, pair<int, int> > p;
//map<pair<int, int>, int> sz;
struct edge {
    pair<int, int> a,b;
    int d;
};

vector<edge> edges;

bool cmp(edge x, edge y) {
    return x.d < y.d;
}

int get(int a) {
    if(a != p[a]) {
        p[a] = get(p[a]);
    }
    return p[a];
}

int merge(int a,int b) {
    int x = get(a), y = get(b);
    if(sz[x] > sz[y]) {
        swap(x, y);
    }
    p[y] = x, sz[x] += sz[y];
    return sz[x];
}


int main() {
    freopen("tractor.in", "r", stdin);
    freopen("tractor.out", "w", stdout);
    cin >> n;
    mid = n * n / 2;
    if(n & 1) mid++;
//    cout << mid << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> bd[i][j];
            p[i * n + j] = i * n + j, sz[i * n + j] = 1;
        }
    }


    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < 2; k++) {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if(nx >= 0 && nx < n && ny >= 0 && ny < n) {
                    edges.push_back({{i, j}, {nx, ny}, abs(bd[nx][ny] - bd[i][j])});
                    cnt++;
                }
            }
        }
    }

    sort(edges.begin(), edges.end(), cmp);

    for(int i = 0; i < cnt; i++) {
        if(get(edges[i].a.first * n + edges[i].a.second) != get(edges[i].b.first * n + edges[i].b.second)) {

            int t = merge(edges[i].a.first * n + edges[i].a.second , edges[i].b.first * n + edges[i].b.second);
            if(t >= mid) {
                cout << edges[i].d << endl;
                return 0;
            }
        }
    }

    return 0;
}
