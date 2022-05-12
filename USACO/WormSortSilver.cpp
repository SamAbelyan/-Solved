#include <bits/stdc++.h>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
ll n,m,p[N],d[N],sz[N],ans;
struct edge {
    ll a,b,w;
};
vector<edge> edges;

bool cmp(edge x, edge y) {
    return x.w > y.w;
}

ll get(ll a) {
    if(a != p[a]) {
        p[a] = get(p[a]);
    }
    return p[a];
}

ll merge(ll a,ll b) {
    ll x = get(a), y = get(b);
    if(sz[x] > sz[y]) {
        swap(x, y);
    }
    p[y] = x, sz[x] += sz[y];
    return sz[x];
}


int main() {
    freopen("wormsort.in", "r", stdin);
    freopen("wormsort.out", "w", stdout);
    ll a,b,w;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> d[i];
        p[i] = i;
        sz[i] = 1;
    }

    for(int i = 0; i < m; i++) {
        cin >> a >> b >> w;
        edges.push_back({a,b,w});
    }

    sort(edges.begin(), edges.end(), cmp);

    ll curr = 0;
    for(int i = 1; i <= n; i++) {
        while(curr < m && get(i) ^ get(d[i])) {
//            cout << edges[curr].a << " " << edges[curr].b << endl;
            merge(edges[curr].a, edges[curr].b), ans = edges[curr].w;
            curr++;
        }
    }

    if(!ans) cout << -1 << endl;
    else cout << ans << endl;

    return 0;
}