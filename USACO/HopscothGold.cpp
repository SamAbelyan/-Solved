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
#define ld long double
#define ll long long

void print(long long t) {cerr << t;}
void print(int t) {cerr << t;}
void print(string t) {cerr << t;}
void print(char t) {cerr << t;}
void print(double t) {cerr << t;}
void print(unsigned long long t) {cerr << t;}
void print(long double t) {cerr << t;}

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
const long long mod = 1e9 + 7;
const int N = 751;
int a[N][N], n, m, k;
int c[N * N];
long long dp[N][N];

// bit
struct fenwick_additional {
  int size;
  vector<long long> tree;
  vector<long long> indi;

  void init() {
    sort(all(indi));
    uniq(indi)
    tree.assign(sz(indi) + 2, 0);
    size = sz(tree);
  }

  void add(int u) {
    indi.push_back(u);
  }

  int get(int u) {
    assert(lower_bound(all(indi), u) != indi.end());
    u = lower_bound(all(indi), u) - indi.begin() + 1;
    return u;
  }

  void upd(int u, long long v) {
    u = get(u);
    while(u <= size) {
      tree[u] += v;
      if(tree[u] >= mod) {
        tree[u] -= mod;
      }
      u += u & (-u);
    }
  }

  long long qry(int u) {
    u = get(u);
    long long sum = 0;
    while(u > 0) {
      sum += tree[u];
      if(sum >= mod) {
        sum -= mod;
      }
      u -= u & (-u); // lsb
    }
    return sum;
  }

  long long sum(int l, int r) {
    l = get(l), r = get(r);
    if(l > r) {
      return 0;
    }
    return qry(r) - qry(l - 1);
  }

} color[N * N];

struct fenwick {
  int size;
  vector<long long> tree;

  void init(int size_) {
    tree.assign(size_ + 2, 0);
    size = size_;
  }

  void upd(int u, long long v) {
    while(u <= size) {
      tree[u] += v;
      if(tree[u] >= mod) {
        tree[u] -= mod;
      }
      u += u & (-u);
    }
  }

  long long qry(int u) {
    long long sum = 0;
    while(u > 0) {
      sum += tree[u];
      if(sum >= mod) {
        sum -= mod;
      }
      u -= u & (-u); // lsb
    }
    return sum;
  }

  long long sum(int l, int r) {
    return qry(r) - qry(l - 1);
  }

} column;


void solve_() {
  cin >> n >> m >> k;

  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      cin >> a[i][j];
      c[a[i][j]]++;
    }
  }

  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      color[a[i][j]].add(j - 1);
      color[a[i][j]].add(j);
    }
  }

  for(int i = 1; i <= n * m; i++) {
    color[i].init();
  }

  column.init(m);

  dp[1][1] = 1;
  column.upd(1, 1);
  color[a[1][1]].upd(1, 1);

  for(int i = 2; i <= n; i++) {
    for(int j = m; j >= 2; j--) {
      dp[i][j] = column.qry(j - 1) - color[a[i][j]].qry(j - 1);
      
      if(dp[i][j] <= 0) {
        dp[i][j] += mod;
      }

      column.upd(j, dp[i][j]);
      color[a[i][j]].upd(j, dp[i][j]);
    }
  }
  printf("%lld\n", dp[n][m]);
}

int main () {
  setIO("hopscotch");

  auto solve = [&](int test_case)-> void {
    while(test_case--) {
      solve_();
    }
  };

  int test_cases = 1;
  solve(test_cases);

  return 0;
}