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
const int N = 1e5 + 10, K = 1e2 + 10, inf = 2e9;
int dp[N][K][2], n, k, pos[N];

bool cmp(pair<int, int> a, pair<int, int> b) {
  if(a.first < b.first) {
    return true;
  }
  
  if(a.first == b.first) {
    return a.second > b.second;
  }

  return false;
}

void solve_() {
  cin >> n >> k;
  vector<pair<int, int>> c(n + 1), a;

  for(int i = 1; i <= n; i++) {
    cin >> c[i].first >> c[i].second;
  }

  sort(all(c), cmp);

  int prevR = 0;
  vector<int> ri{0};
  a.push_back({0, 0});
  for(int i = 1; i <= n; i++) {
    int r = c[i].second;

    if(prevR >= r) {
      k--, k = max(0, k);
      continue;
    }

    a.push_back(c[i]);
    ri.push_back(c[i].second);
    prevR = r;
  }

  n = sz(a);
  for(int i = 2; i < n; i++) {
    int it = lower_bound(all(ri), a[i].first) - ri.begin();
    assert(it >= 1 && it <= i);
    pos[i] = it;
  }

  dp[1][1][0] = 0;
  dp[1][0][1] = a[1].second - a[1].first;

  for(int i = 2; i < n; i++) {
    for(int j = 0; j <= min(i, k); j++) {
      if(i == j) {
        dp[i][j][0] = 0;
        continue;
      }

      if(!j) {
        dp[i][j][1] = dp[i - 1][j][1] + a[i].second - max(a[i].first, a[i - 1].second);
        continue;
      }
      
      //
      dp[i][j][0] = max(dp[i - 1][j - 1][0], dp[i - 1][j - 1][1]);

      //
      int cnt = i - pos[i] - 1; // intervsl (:)
      if(cnt >= 0) {
        dp[i][j][1] = dp[pos[i]][max(0, j - cnt)][1] + a[i].second - a[pos[i]].second;
        dp[i][j][1] = max(dp[i][j][1], dp[pos[i]][max(1, j - cnt)][0] + a[i].second - a[i].first);  
      } else {
        dp[i][j][1] = max(dp[i - 1][j][0], dp[i - 1][j][1]);  
        dp[i][j][1] += a[i].second - max(a[i].first, a[i - 1].second);
      }
      
    }
  }

  printf("%d\n", max(dp[n - 1][k][1], dp[n - 1][k][0]));
}

int main () {
  setIO("lifeguards");

  auto solve = [&](int test_case)-> void {
    while(test_case--) {
      solve_();
    }
  };

  int test_cases = 1;
  solve(test_cases);

  return 0;
}