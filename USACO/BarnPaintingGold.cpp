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
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
const int N = 1e5 + 10, MOD = 1e9 + 7;
long long n, q, dp[N][3], color[N];
vector<long long> adj[N];

void dfs(int node, int parent) {
    if(color[node]) {
        dp[node][color[node] - 1] = 1;
    } else {
        dp[node][0] = 1, dp[node][1] = 1, dp[node][2] = 1;
    }
    for(auto i: adj[node]) {
        if(i ^ parent) {
            dfs(i, node);
            (dp[node][0] *= (dp[i][1] + dp[i][2])) %= MOD;
            (dp[node][1] *= (dp[i][0] + dp[i][2])) %= MOD;
            (dp[node][2] *= (dp[i][0] + dp[i][1])) %= MOD;
        }
    }
}

int main() {
//    setIO("barnpainting");
    fastIO();
    cin >> n >> q;

    for(int i = 0; i < n - 1; i++) {
        int a,b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for(int i = 0; i < q; i++) {
        int a,b; cin >> a >> b;
        color[a] = b;
    }

    dfs(1, 0);

    cout << ( dp[1][0] + dp[1][1] + dp[1][2] ) % MOD << nl;
    return 0;
}