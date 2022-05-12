#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 1e3 + 10;
ll n,dist,cnt,sz[N],p[N],ans;
struct edge {
    ll u, v, d;
};
vector<edge> edges;
vector<pair<ll, ll>> q;

bool cmp(edge ax, edge ay) {
    return ax.d < ay.d;
}

ll get(ll a) {
    if(a ^ p[a]) {
        p[a] = get(p[a]);
    }
    return p[a];
}

void merge(ll x, ll y) {
    ll a = get(x), b = get(y);
    if(sz[a] > sz[b]) {
        swap(a, b);
    }
    p[b] = a, sz[a] += sz[b];
}

int main()
{
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);

    ll x,y;
    cin >> n ;
    for(int i = 0; i < n; i++) {
        cin >> x >> y;
        q.push_back({x, y});
        sz[i] = 1, p[i] = i;
    }


    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i; j++) {
            dist = (q[i].first - q[j].first) * (q[i].first - q[j].first) + (q[i].second - q[j].second) * (q[i].second - q[j].second);
            edges.push_back({i, j, dist});
            cnt++;
        }
    }

    sort(edges.begin(), edges.end(), cmp);

    for(int i = 0; i < cnt; i++) {
        if(get(edges[i].u) ^ get(edges[i].v)) {
            merge(edges[i].u, edges[i].v);
            ans = edges[i].d; ll t = get(edges[i].u);
            if(sz[t] == n) {
                break;
            }
        }
    }
    cout << ans << endl;
    return 0;
}