#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

#ifndef ONLINE_JUDGE
#define dbg(x) cerr << #x <<" "; print(x); cerr << endl;
#else
#define dbg(x)
#endif

void print(long long t) {cerr << t;}
void print(int t) {cerr << t;}
void print(string t) {cerr << t;}
void print(char t) {cerr << t;}
void print(double t) {cerr << t;}
void print(unsigned long long t) {cerr << t;}

template <class T, class V> void print(pair <T, V> p);
template <class T> void print(vector <T> v);
template <class T> void print(set <T> v);
template <class T, class V> void print(map <T, V> v);
template <class T> void print(multiset <T> v);
template <class T, class V> void print(pair <T, V> p) {cerr << "{"; print(p.first); cerr << ","; print(p.second); cerr << "}";}
template <class T> void print(vector <T> v) {cerr << "[ "; for (T i : v) {print(i); cerr << " ";} cerr << "]";}
template <class T> void print(set <T> v) {cerr << "[ "; for (T i : v) {print(i); cerr << " ";} cerr << "]";}
template <class T> void print(multiset <T> v) {cerr << "[ "; for (T i : v) {print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void print(map <T, V> v) {cerr << "[ "; for (auto i : v) {print(i); cerr << " ";} cerr << "]";}

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#define nl '\n'

void fastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
}
void setIO(string str) {
    fastIO();

    freopen((str + ".in").c_str(), "r", stdin);
    freopen((str + ".out").c_str(), "w", stdout);
}
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update> ;
const int N = 1e5 + 10;
long long n,q, values[N], tout[N], timer = 1, tin[N], ft[2 * N], euler[2 * N], timer2, tin2[N];
vector<int> adj[N];

void upd(long long u, long long value) {
    while(u <= timer2) {
        ft[u] ^= value;
        u += u & (-u);
    }
}
long long qry(long long u) {
    long long ans = 0;
    while(u >= 1) {
        ans ^= ft[u];
        u -= u & (-u);
    }
    return ans;
}

struct segTreeLca {
    vector<long long> tree;
    int size = 1;

    static long long combine(long long x,long long y) {
        return  tin2[x] < tin2[y] ? x : y;
    }

    void init(long long s) {
        while(size < s) {
            size *= 2;
        }
        tree.assign(2 * size - 1, 0 );
    }

    void upd(long long u,long long value, int x, int lx, int rx) {
        if(rx - lx == 1) {
            tree[x] = value;
            return;
        }

        int mid = (lx + rx) / 2;
        if(u < mid) {
            upd(u, value, 2 * x + 1, lx, mid);
        } else {
            upd(u, value, 2 * x + 2, mid, rx);
        }

        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void upd(long long u, long long value) {
        upd(u, value, 0, 0, size);
    }

    long long qry(int l, int r, int x, int lx, int rx) {
        if(lx >= r || rx <= l) {
            return 0;
        }

        if(lx >= l && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        long long s1 = qry(l, r, 2 * x + 1, lx, mid);
        long long s2 = qry(l, r, 2 * x + 2, mid, rx);
        return combine(s1, s2);
    }

    long long qry(int l, int r) {
        return qry(l, r, 0, 0, size);
    }

};

segTreeLca segL;

void dfs(int node, int parent) {
    tin[node] = timer++, tin2[node] = timer2;
    euler[timer2++] = node;
    for(auto i: adj[node]) {
        if(i ^ parent) {
            dfs(i, node);
            euler[timer2++] = node;
        }
    }
    tout[node] = timer++;
}

int lca(int a, int b) {
    a = tin2[a], b = tin2[b];
    return segL.qry( min(a, b), max(a, b) + 1 );
}

int main() {
//    setIO("cowland");
    cin >> n >> q;

    for(int i = 1; i <= n; i++) {
        cin >> values[i];
    }

    for(int i = 0; i < n - 1; i++) {
        int a,b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0), tin2[0] = INT32_MAX;

    for(int i = 1; i <= n; i++) {
        upd(tin[i], values[i]);
        upd(tout[i], values[i]);
    }

    segL.init(timer + 1);
    for(int i = 0; i < timer; i++) {
        segL.upd(i, euler[i]);
    }

    for(int i = 0; i < q; i++) {
        int type, a,b; cin >> type >> a >> b; type--;
        if(type) {
            cout << (qry(tin[a]) ^ qry(tin[b]) ^ values[lca(a, b)]) << nl;
        } else {
            upd(tin[a], (values[a] ^ b) );
            upd(tout[a], (values[a] ^ b) );
            values[a] = b;
        }
    }

    return 0;
}