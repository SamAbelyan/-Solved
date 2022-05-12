#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e3 + 10;
ll n, arr[N], ans, p[N], sz[N];
struct edge {
    ll a,b,w;
};
vector<edge> edges;

bool cmp(edge x, edge y) {
    return x.w > y.w;
}

ll get(ll a) {
    if(a ^ p[a]) {
        a = get(p[a]);
    }
    return p[a];
}
ll merge(ll a, ll b) {
    ll x = get(a), y= get(b);
    if(x == y) return 0;
    if(sz[x] > sz[y]) {
        swap(x, y);
    }
    p[y] = x, sz[x] += sz[y];
    return sz[x];
}

int main() {
    freopen("superbull.in", "r", stdin);
    freopen("superbull.out", "w", stdout);
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> arr[i];
        sz[i] = 1, p[i] = i;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j < i; j++) {
            edges.push_back({i, j, arr[i] ^ arr[j]});
        }
    }

    sort(edges.begin(), edges.end(), cmp);

    for(auto i: edges) {
        ll k = merge(i.a, i.b);
        if(k) ans += i.w;
        if(k == n) {
            cout << ans << endl;
            return 0;
        }
    }

    return 0;
}