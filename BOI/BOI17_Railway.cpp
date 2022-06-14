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
 
#define sz(x) (int((x).size()))
#define len(x) (int)x.length()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define clr(x) (x).clear()
#define uniq(x) x.resize(unique(all(x)) - x.begin());
#define blt __builtin_popcount
 
#define pb push_back
#define popf pop_front
#define popb pop_back
 
void print(long long t) {cerr << t;}
void print(int t) {cerr << t;}
void print(string t) {cerr << t;}
void print(char t) {cerr << t;}
void print(double t) {cerr << t;}
void print(long double t) {cerr << t;}
void print(unsigned long long t) {cerr << t;}
 
template <class T, class V> void print(pair <T, V> p);
template <class T> void print(vector <T> v);
template <class T> void print(set <T> v);
template <class T, class V> void print(map <T, V> v);
template <class T> void print(multiset <T> v);
template <class T, class V> void print(T v[],V n) {cerr << "["; for(int i = 0; i < n; i++) {print(v[i]); cerr << " "; } cerr << "]";}
template <class T, class V> void print(pair <T, V> p) {cerr << "{"; print(p.first); cerr << ","; print(p.second); cerr << "}";}
template <class T> void print(vector <T> v) {cerr << "[ "; for (T i : v) {print(i); cerr << " ";} cerr << "]";}
template <class T> void print(set <T> v) {cerr << "[ "; for (T i : v) {print(i); cerr << " ";} cerr << "]";}
template <class T> void print(multiset <T> v) {cerr << "[ "; for (T i : v) {print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void print(map <T, V> v) {cerr << "[ "; for (auto i : v) {print(i); cerr << " ";} cerr << "]";}
 
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#define nl '\n'
 
// for grid problems
int dx[8] = {-1,0,1,0,1,-1,1,-1};
int dy[8] = {0,1,0,-1,1,1,-1,-1};
 
// lowest / (1 << 17) >= 1e5 / (1 << 18) >= 2e5 / (1 << 21) >= 1e6
void fastIO() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr); cout.tie(nullptr);
}
// file in/out
void setIO(string str = "") {
  fastIO();
 
  if (str != "") {
    freopen((str + ".in").c_str(), "r", stdin);
    freopen((str + ".out").c_str(), "w", stdout);
  }
}
// Indexed Set
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
const int N = 2e5 + 10, LOG = 22;
set<int> need_add[N], need_erase[N];
int n, m, k, up[N][LOG], depth[N];
map<pair<int, int>, int> mp;
vector<int> adj[N], answ;
 
void dfs(int node, int parent) {
  for(auto i: adj[node]) {
    if(i == parent) continue;
    up[i][0] = node;
    for(int j = 1; j < LOG; j++) {
      up[i][j] = up[up[i][j - 1]][j - 1];
    }
    depth[i] = depth[node] + 1;
    dfs(i, node);
  }
}
 
int lca(int a, int b) {
  if(a == b) {
    return a;
  }
 
  if(depth[a] < depth[b]) {
    swap(a, b);
  }
 
  int delta = depth[a] - depth[b];
 
  for(int i = 0; i < LOG; i++) {
    if(delta & (1 << i)) {
      a = up[a][i];
    }
  }
 
  if(a == b) {
    return a;
  }
 
  for(int i = LOG - 1; i >= 0; i--) {
    if(up[a][i] != up[b][i]) {
      a = up[a][i], b = up[b][i];
    }
  }
 
  return up[a][0];
}
 
void dfsAns(int node, int parent) {
  for(auto i: adj[node]) {
    if(i == parent) continue;
    dfsAns(i, node);
 
    if(sz(need_add[i]) > sz(need_add[node])) {
      need_add[i].swap(need_add[node]);
    }
 
    for(auto j: need_add[i]) {
      need_add[node].insert(j);
    }
  }
 
  for(auto i: need_erase[node]) {
    assert(need_add[node].find(i) != need_add[node].end());
    need_add[node].erase(i);
  }
 
  // parent/node
  int id = mp[{min(parent, node), max(parent, node)}];
  if(sz(need_add[node]) >= k) {
    answ.push_back(id);
  }
}
 
void solve_() {
  cin >> n >> m >> k;
 
  for(int i = 1; i <= n - 1; i++) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
    mp[{min(a, b), max(a, b)}] = i;
  }
 
  dfs(1, 0);
 
  for(int i = 1; i <= m; i++) {
    int cnt; cin >> cnt;
 
    int anc = -1;
    for(int j = 1; j <= cnt; j++) {
      int node; cin >> node;
 
      if(anc == -1) anc = node;
      else anc = lca(anc, node);
 
      need_add[node].insert(i);
    }
    
    need_erase[anc].insert(i);
  }
 
  dfsAns(1, 0);
 
  sort(all(answ));
 
  printf("%d\n", sz(answ));
  for(auto i: answ) {
    printf("%d ", i);
  } printf("\n");
}
 
int main() {
  setIO("");
 
  auto solve = [&](int test_case)-> void {
    while(test_case--) {
      solve_();
    }
  };
 
  int test_cases = 1;
  solve(test_cases);
 
  return 0;
}