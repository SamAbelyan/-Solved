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
const int N = 3e2 + 10;
long long n, m, dp[N][N][2];
vector<long long> coord;

long long solve(int l, int r, int pos, long long cnt) {
  if(cnt == 0) {
    return 0;
  }

  if(dp[l][r][pos] != -1) {
    return dp[l][r][pos];
  }

  long long answ = 1e9, curr;

  // pos == 0 -> l
  // pos == 1 -> r

  if(!pos) {
    curr = coord[l];
  } else {
    curr = coord[r];
  }

  if(l > 0) {
    answ = min(answ, cnt * abs(curr - coord[l - 1]) + solve(l - 1, r, 0, cnt - 1));
  } 

  if(r < n) {
    answ = min(answ, cnt * abs(curr - coord[r + 1]) + solve(l, r + 1, 1, cnt - 1));
  }

  return dp[l][r][pos] = answ;
}

void solve_() {
  cin >> n >> m;

  coord.resize(n + 1);
  for(int i = 1; i <= n; i++) {
    cin >> coord[i];
  }

  coord[0] = 0;
  sort(all(coord));

  auto it = lower_bound(all(coord), 0) - coord.begin();

  long long answ = 0;
  // ~N^3
  for(int i = 1; i <= n; i++) {
    memset(dp, -1, sizeof(dp));
    answ = max(answ, i * m - solve(it, it, 0, i));
  }

  printf("%lld\n", answ);
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