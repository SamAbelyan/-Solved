#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
// #include "temp.cpp"
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
#define clr(x) x.clear()
#define uniq(x) x.resize(unique(all(x)) - x.begin());
#define blt __builtin_popcount

#define pb push_back
#define pf push_front
#define popf pop_front
#define popb pop_back

void print(long long t) {cerr << t;}
void print(int t) {cerr << t;}
void print(string t) {cerr << t;}
void print(char t) {cerr << t;}
void print(double t) {cerr << t;}
void print(long double t) {cerr << t;}
void print(unsigned long long t) {cerr << t;}

template <class T> void print(set <T> v);
template <class T> void print(vector <T> v);
template <class T> void print(multiset <T> v);
template <class T, class V> void print(map <T, V> v);
template <class T, class V> void print(pair <T, V> p);
template <class T, class V> void print(T v[],V n) {cerr << "["; for(int i = 0; i < n; i++) {print(v[i]); cerr << " "; } cerr << "]";}
template <class T, class V> void print(pair <T, V> p) {cerr << "{"; print(p.first); cerr << ","; print(p.second); cerr << "}";}
template <class T> void print(vector <T> v) {cerr << "[ "; for (T i : v) {print(i); cerr << " ";} cerr << "]";}
template <class T> void print(deque<T> v) {cerr << "[ "; for (T i : v) {print(i); cerr << " ";} cerr << "]";}
template <class T> void print(set <T> v) {cerr << "[ "; for (T i : v) {print(i); cerr << " ";} cerr << "]";}
template <class T> void print(multiset <T> v) {cerr << "[ "; for (T i : v) {print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void print(map <T, V> v) {cerr << "[ "; for (auto i : v) {print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void print(unordered_map<T, V> v) {cerr << "[ "; for (auto i : v) {print(i); cerr << " ";} cerr << "]";}

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

  if (str != "" && str != "input") {
    freopen((str + ".in").c_str(), "r", stdin);
    freopen((str + ".out").c_str(), "w", stdout);
  }

  if(str == "input") {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
  }
}
// Indexed Set
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
const int N = 5e4 + 10;
int n, k, sz[N], top[N], id[N], it = 1;
int p[N], depth[N];
vector<int> adj[N];

struct segTree {
  struct node {
    long long value, lazy, maxi;
  };
  vector<node> tree;
  int size = 1;

  void init(int n) {
    while(size < n) {
      size *= 2;
    }
    tree.assign(2 * size - 1, {0, 0, 0});
  }

  void propagate(int x, int lx, int rx) {
    if(rx - lx == 1 || !tree[x].lazy) {
      tree[x].lazy = 0;
      return;
    }

    int mid = (lx + rx) / 2;
    tree[2 * x + 1].value += (mid - lx) * tree[x].lazy;
    tree[2 * x + 1].maxi += tree[x].lazy;
    tree[2 * x + 1].lazy += tree[x].lazy;

    tree[2 * x + 2].value += (rx - mid) * tree[x].lazy;
    tree[2 * x + 2].maxi += tree[x].lazy;
    tree[2 * x + 2].lazy += tree[x].lazy;

    tree[x].lazy = 0;
  }

  void upd(int l, int r, long long value, int x, int lx, int rx) {
    propagate(x, lx, rx);
    if(lx >= r || rx <= l) {
      return;
    }

    if(lx >= l && rx <= r) {
      tree[x].value += (rx - lx) * value;
      tree[x].lazy  += value;
      tree[x].maxi  += value;
      return;
    }

    int mid = (lx + rx) / 2;
    upd(l, r, value, 2 * x + 1, lx, mid);
    upd(l, r, value, 2 * x + 2, mid, rx);

    tree[x].value = tree[2 * x + 1].value + tree[2 * x + 2].value;
    tree[x].maxi = max(tree[2 * x + 1].maxi, tree[2 * x + 2].maxi);
  }

  void upd(int l, int r, long long value) {
    upd(l, r, value, 0, 0, size);
  }

  long long qry(int l, int r, int x, int lx, int rx) {
    propagate(x, lx, rx);
    if(lx >= r || rx <= l) {
      return 0;
    }

    if(lx >= l && rx <= r) {
      return tree[x].maxi;
    }

    int mid = (lx + rx) / 2;
    long long s1 = qry(l, r, 2 * x + 1, lx, mid);
    long long s2 = qry(l, r, 2 * x + 2, mid, rx);
    return max(s1, s2);
  }

  long long qry(int l, int r) {
    return qry(l, r, 0, 0, size);
  }

};
segTree seg;

int dfs_sz(int node, int parent) {
  sz[node] = 1, p[node] = parent;
  for(auto u: adj[node]) {
    if(u == parent) continue;
    depth[u] = depth[node] + 1;
    sz[node] += dfs_sz(u, node);
  }
  return sz[node];
}

void hld(int node, int parent, int tp) {
  id[node] = it++, top[node] = tp;

  int heavy_size = -1, heavy_child = -1;
  for(auto u: adj[node]) {
    if(u == parent) continue;
    if(sz[u] > heavy_size) {
      heavy_size = sz[u];
      heavy_child = u;
    }
  }

  if(heavy_child == -1) return;
  hld(heavy_child, node, tp);

  for(auto u: adj[node]) {
    if(u == parent || u == heavy_child) continue;
    hld(u, node, u);
  }
}

void path(int x, int y) {
  while(top[x] != top[y]) {
    if(depth[top[x]] < depth[top[y]]) {
      swap(x, y);
    }

    seg.upd(id[top[x]], id[x] + 1, 1);
    x = p[top[x]];
  }

  if(depth[x] > depth[y]) {
    swap(x, y);
  }
  seg.upd(id[x], id[y] + 1, 1);
}

void solve_() {
  cin >> n >> k, seg.init(n + 1);

  for(int i = 1; i <= n - 1; i++) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  dfs_sz(1, 0);
  hld(1, 0, 1);

  while(k--) {
    int a, b; cin >> a >> b;
    path(a, b);
  }

  long long answ = 0;
  for(int i = 1; i <= n; i++) {
    answ = max(answ, seg.qry(i, i + 1));
  }

  printf("%lld\n", answ);
}

int main() {
  setIO("maxflow");

  auto solve = [&](int test_case)-> void {
    while(test_case--) {
      solve_();
    }
  };

  int test_cases = 1;
  solve(test_cases);

  return 0;
}