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
const int N = 2e5 + 10;
int n, m, st[N], en[N], sz[N], timer = 1;
map<int, int> color[N];
vector<int> adj[N];

// bit
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
      u += u & (-u);
    }
  }

  long long qry(int u) {
    long long sum = 0;
    while(u > 0) {
      sum += tree[u];
      u -= u & (-u); // lsb
    }
    return sum;
  }

  long long sum(int l, int r) {
    return qry(r) - qry(l - 1);
  }

} ft, ftSub;

void dfs(int node, int parent) {
  st[node] = timer++;
  for(auto i: adj[node]) {
    if(i == parent) continue;
    dfs(i, node);
  }
  en[node] = timer++;
  sz[node] = (en[node] - st[node] + 1) / 2;
}

void solve_() {
  cin >> n >> m;
  for(int i = 1; i <= n - 1; i++) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  dfs(1, 0);
  ft.init(timer), ftSub.init(timer);

  while(m--) {
    int type; cin >> type;

    if(type == 1) {
      int node, col; cin >> node >> col;

      auto it = color[col].upper_bound(st[node]);
      if(it != color[col].begin() && en[prev(it)->second] > en[node]) {
        continue;
      }

      vector<int> need_to_erase;
      while(it != color[col].end() && en[it->second] < en[node]) {
        need_to_erase.push_back(it->second);
        it++;
      }

      color[col][st[node]] = node;
      for(auto i: need_to_erase) {
        color[col].erase(st[i]);
        ft.upd(st[i], -1);
        ft.upd(en[i], 1);


        ftSub.upd(st[i], -sz[i]);
      }

      ft.upd(st[node], 1);
      ft.upd(en[node], -1);

      ftSub.upd(st[node], sz[node]);
    } else {
      int node; cin >> node;

      long long answ = ft.sum(1, st[node] - 1) * sz[node] + ftSub.sum(st[node], en[node]);
      printf("%lld\n", answ);
    }
  }

}

int main() {
  setIO("snowcow");

  auto solve = [&](int test_case)-> void {
    while(test_case--) {
      solve_();
    }
  };

  int test_cases = 1;
  solve(test_cases);

  return 0;
}