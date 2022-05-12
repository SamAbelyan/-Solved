#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#define nl '\n'

template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
typedef long long ll;

const int N = 2e5 + 10, MOD = 1e9 + 7;
long long n, a[N], l[N], r[N], ans;

int main() {
    freopen("bphoto.in", "r", stdin);
    freopen("bphoto.out", "w", stdout);

    cin >> n; Tree<pair<long long, long long>> bit_1, bit_2;

    for(int i = 0; i < n; i++) {
        cin >> a[i];
        l[i] = i - bit_1.order_of_key({a[i], MOD});
        bit_1.insert({a[i], i});
    }

    for(int i = n - 1; i >= 0; i--) {
        r[i] = bit_2.size() - bit_2.order_of_key({a[i], MOD});
        bit_2.insert({a[i], i});
    }

    for(int i = 0; i < n; i++) {
        if(min(l[i], r[i]) * 2 < max(r[i],l[i])) {
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}
