#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
//#include "temp.cpp"
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
template <class T> void print(T v[],T n) {cerr << "["; for(int i = 0; i < n; i++) {cerr << v[i] << " ";} cerr << "]";}
template <class T, class V> void print(pair <T, V> p) {cerr << "{"; print(p.first); cerr << ","; print(p.second); cerr << "}";}
template <class T> void print(vector <T> v) {cerr << "[ "; for (T i : v) {print(i); cerr << " ";} cerr << "]";}
template <class T> void print(set <T> v) {cerr << "[ "; for (T i : v) {print(i); cerr << " ";} cerr << "]";}
template <class T> void print(multiset <T> v) {cerr << "[ "; for (T i : v) {print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void print(map <T, V> v) {cerr << "[ "; for (auto i : v) {print(i); cerr << " ";} cerr << "]";}

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#define nl '\n'

// lowest / (1 << 17) >= 1e5 / (1 << 18) >= 2e5
void fastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
}
// file in/out
void setIO(string str = "") {
    fastIO();

    if(str != "") {
        freopen((str + ".in").c_str(), "r", stdin);
        freopen((str + ".out").c_str(), "w", stdout);
    }
}
// Indexed Set
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct segTree {
    struct node {
        long long value, lazy, mini;
    };
    int size = 1;
    vector<node> tree;

    node combine(node a, node b) {
        node c;
        c.value = a.value + b.value;
        c.mini = min(a.mini, b.mini);
        c.lazy = 0;
        return c;
    }

    void build(vector<long long>& v, int x, int lx, int rx) {
        if(rx - lx == 1) {
//            cout << lx << ' ' << v.size() << endl;
            if(lx < v.size()) {
                tree[x] = {v[lx], 0LL, v[lx]};
//                cout << tree[x].value << " " << tree[x].lazy << " " << tree[x].mini << endl;
            } else {
                tree[x] = {0LL, 0LL, INT64_MAX};
//                cout << tree[x].value << " " << tree[x].lazy << " " << tree[x].mini << endl;
            }
        } else {
            int mid = (lx + rx) / 2;
            build(v, 2 * x + 1, lx, mid);
            build(v, 2 * x + 2, mid, rx);
            tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
        }
    }

    void init(int s, vector<long long>& v) {
        while(s > size) {
            size *= 2;
        }
        tree.resize(2 * size - 1);
        build(v, 0, 0, size);
    }

    void propagate(int x, int lx, int rx) {
        if(rx - lx == 1 || !tree[x].lazy) {
            tree[x].lazy = 0LL;
            return;
        }

        int mid = (lx + rx) / 2;

        tree[2 * x + 1].value += (mid - lx) * tree[x].lazy;
        tree[2 * x + 1].lazy += tree[x].lazy;
        tree[2 * x + 1].mini += tree[x].lazy;

        tree[2 * x + 2].value += (rx - mid) * tree[x].lazy;
        tree[2 * x + 2].lazy += tree[x].lazy;
        tree[2 * x + 2].mini += tree[x].lazy;

        tree[x].lazy = 0LL;
    }

    void upd(int l, int r, long long value, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if(lx >= r || rx <= l) {
            return;
        }

        if(lx >= l && rx <= r) {
            tree[x].value += (rx - lx) * value;
            tree[x].mini += value;
            tree[x].lazy = value;
            propagate(x, lx, rx);
            return;
        }

        int mid = (lx + rx) / 2;
        upd(l, r, value, 2 * x + 1, lx, mid);
        upd(l, r, value, 2 * x + 2, mid, rx);
        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void upd(int l, int r, long long value) {
        upd(l, r, value, 0, 0, size);
    }

    node qry(int l, int r, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if(lx >= r || rx <= l) {
            return {0, 0, INT64_MAX};
        }

        if(lx >= l && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        node s1 = qry(l, r, 2 * x + 1, lx, mid);
        node s2 = qry(l, r, 2 * x + 2, mid, rx);
//        cout << s1.value << " " << s1.lazy << " " << s1.mini << endl;
//        cout << s2.value << " " << s2.lazy << " " << s2.mini << endl;
//        cout << LLONG_MAX << endl;
        return combine(s1, s2);
    }

    node qry(int l, int r) {
        return qry(l, r, 0, 0, size);
    }



};

int n,m;
segTree seg;

int main () {
    setIO("haybales");

    cin >> n >> m;
    vector<long long> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }
    seg.init(n, v);

//    seg.prin();
    for(int i = 0; i < m; i++) {
        char ch; int l, r; cin >> ch >> l >> r;
        if(ch == 'M') {
            cout << seg.qry(l - 1, r).mini << endl;
        } else if(ch == 'P') {
            long long value; cin >> value;
            seg.upd(l - 1, r, value);
        } else {
            auto u = seg.qry(l - 1, r);
            cout << u.value << endl;
        }
    }

    return 0;
}
