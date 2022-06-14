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
const int N = 55, M = 18;
int n, m, it = 0, dist[N][N], iid[N][N];
char a[N][N];
bool used[N][N];
vector<pair<int, int>> adj[N];

int dp[1 << M][M];

void bfsIsland(int sx, int sy) {
  used[sx][sy] = true;
  queue<pair<int, int>> q;
  q.push({sx, sy});

  while(!q.empty()) {
    auto u = q.front();
    q.pop();

    iid[u.first][u.second] = it;
    adj[it].push_back({u.first, u.second});

    int x = u.first, y = u.second;
    for(int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];

      if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && a[nx][ny] == 'X' && !used[nx][ny]) {  
        used[nx][ny] = true;
        q.push({nx, ny});
      }
    }
  }

  it++;
}

void bfsDist(int id) {
  memset(used, false, sizeof(used));
  priority_queue<pair<int, pair<int, int>>> q;
  for(auto i: adj[id]) {
    q.push({0, i});
    used[i.first][i.second] = true;
  }

  for(int i = 0; i < it; i++) {
    dist[id][i] = -1;
  }

  dist[id][id] = 0;
  while(!q.empty()) {
    auto u = q.top();
    q.pop();
    int x = u.second.first, y = u.second.second;
    u.first = abs(u.first);
    for(int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];

      if(nx >= 1 && nx <= n && ny >= 1 && ny <= m) {
        if(a[nx][ny] == 'S' && !used[nx][ny]) {
          used[nx][ny] = true;
          q.push({-(u.first + 1), {nx, ny}});
        } else if(a[nx][ny] == 'X' && (dist[id][iid[nx][ny]] == -1 || dist[id][iid[nx][ny]] > u.first)) {
          dist[id][iid[nx][ny]] = u.first;
        }
        if(!used[nx][ny] && a[nx][ny] == 'X') {
          used[nx][ny] = true;
          q.push({-(u.first), {nx, ny}});
        }
      }
    }
  }

}

void solve_() {
  cin >> n >> m;

  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      cin >> a[i][j];
    }
  }

  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      if(!used[i][j] && a[i][j] == 'X') {
        bfsIsland(i, j);
      }
    }
  }

  for(int i = 0; i < it; i++) {
    bfsDist(i);
  } 
  
  memset(dp, -1, sizeof(dp));
  for(int i = 0; i < it; i++) {
    dp[1 << i][i] = 0;
  }

  for(int mask = 1; mask < (1 << it); mask++) {
    int cnt = blt(mask);
    if(cnt <= 1) {
      continue;
    }

    for(int i = 0; i < it; i++) {
      if(!(mask & (1 << i))) continue;
      for(int j = 0; j < it; j++) {
        if(!(mask & (1 << j)) || i == j) continue;

        if(dp[mask][j] == -1) {
          dp[mask][j] = dp[mask ^ (1 << j)][i] + dist[i][j]; 
        } else {
          dp[mask][j] = min(dp[mask][j], dp[mask ^ (1 << j)][i] + dist[i][j]);
        }
      }
    }
  }

  int answ = 1e9;
  for(int i = 0; i < it; i++) {
    if(dp[(1 << it) - 1][i] == -1) continue;
    answ = min(answ, dp[(1 << it) - 1][i]);
  }

  printf("%d\n", answ);
}

int main() {
  setIO("island");

  auto solve = [&](int test_case)-> void {
    while(test_case--) {
      solve_();
    }
  };

  int test_cases = 1;
  solve(test_cases);

  return 0;
}