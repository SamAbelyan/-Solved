#include <bits/stdc++.h>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
ll n,m,curr,ans = LLONG_MAX;
pair<ll, ll> a[N];
int main() {

    ifstream cin("hayfeast.in");
    ofstream cout("hayfeast.out");

    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }

    int l = 0; multiset<ll> mt;
    for(int r = 0; r < n; r++) {
        curr += a[r].first; mt.insert(a[r].second);
        if(curr - a[l].first >= m) {
            curr -= a[l].first;
            mt.erase(mt.find(a[l].second)), l++;
        }
        if(curr >= m) ans = min(ans, *mt.rbegin());
        // cout << l << " " << r << " " << curr << " " << *mt.rbegin()<< endl;
    }

    cout << ans << endl;
    return 0;
}