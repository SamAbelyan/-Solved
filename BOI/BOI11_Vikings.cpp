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

template <class T> void print(set <T> v);
template <class T> void print(vector <T> v);
template <class T> void print(multiset <T> v);
template <class T, class V> void print(map <T, V> v);
template <class T, class V> void print(pair <T, V> p);
template <class T, class V> void print(T v[],V n) {cerr << "["; for(int i = 0; i < n; i++) {print(v[i]); cerr << " "; } cerr << "]";}
template <class T, class V> void print(pair <T, V> p) {cerr << "{"; print(p.first); cerr << ","; print(p.second); cerr << "}";}
template <class T> void print(vector <T> v) {cerr << "[ "; for (T i : v) {print(i); cerr << " ";} cerr << "]";}
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
const int N = 7e2 + 10, inf = 1e8;
int n, m, xi, yi, si, sj;
int timer[N][N];
bool used[N][N];
char a[N][N];

int go(int x, int y, int time) {
  for(int i = 0; i < 4; i++) {
    int nx = x + dx[i];
    int ny = y + dy[i];

    while(nx >= 1 && nx <= n && ny >= 1 && ny <= m && a[nx][ny] != 'I') {
      timer[nx][ny] = min(timer[nx][ny], time);
      nx += dx[i], ny += dy[i];
    }
  }
}

void solve_() {
  cin >> n >> m;
  
  queue<pair<pair<int, int>, int>> q;

  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      timer[i][j] = inf;
    }
  }

  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      cin >> a[i][j];
    
      if(a[i][j] == 'V') {
        xi = i, yi = j;
        used[i][j] = true;
        timer[i][j] = 1;
        q.push({{i, j}, 1});
      } else if(a[i][j] == 'Y') {
        si = i, sj = j;
      }
    }
  }

  while(!q.empty()) {
    auto u = q.front();
    q.pop();
    go(u.first.first, u.first.second, u.second);

    int x = u.first.first, y = u.first.second;
    for(int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];

      if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && a[nx][ny] != 'I' && !used[nx][ny]) {
        used[nx][ny] = true;
        q.push({{nx, ny}, u.second + 1});
      }
    }
  }

  used[si][sj] = true;
  q.push({{si, sj}, 1});
  memset(used, false, sizeof(used));
  while(!q.empty()) {
    auto u = q.front();
    q.pop();

    int x = u.first.first, y = u.first.second;
    for(int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];

      if(nx >= 1 && ny <= n && ny >= 1 && ny <= m && a[nx][ny] != 'I' && timer[nx][ny] > u.second + 1 && !used[nx][ny]) {
        used[nx][ny] = true;
        if(a[nx][ny] == 'T') {
          printf("YES\n");
          return;
        }
        q.push({{nx, ny}, u.second + 1});
      }
    }
  }

  printf("NO\n");
}

int main() {
  setIO();

  auto solve = [&](int test_case)-> void {
    while(test_case--) {
      solve_();
    }
  };

  int test_cases = 1;
  solve(test_cases);

  return 0;
}