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
const int N = 3e5 + 10;
int n, k, dp[N];
string s;

multiset<int> dp_values{0};
multiset<int> dp_prefix[N];

void solve_() {
  cin >> n >> k >> s;

  vector<int> p(n + 1);

  for(int i = 0; i < n; i++) {
    if(s[i] == 'G') {
      p[i + 1] = p[i] - 1;
    } else {
      p[i + 1] = p[i] + 1;
    }
  }

  dp_prefix[0].insert(0);

  // dp[i] = dp[j] + C(ij)
  // C(ij) is 0/1

  for(int i = 1; i <= n; i++) {
    int min_dp = *dp_values.begin();

    if(*dp_prefix[min_dp].begin() >= p[i]) {
      min_dp++;
    }

    dp[i] = min_dp;
    dp_values.insert(dp[i]);
    dp_prefix[dp[i]].insert(p[i]);

    if(i >= k) {
      dp_values.erase(dp_values.find(dp[i - k]));
      dp_prefix[dp[i - k]].erase(dp_prefix[dp[i - k]].find(p[i - k]));
    }
  }

  printf("%d\n", dp[n]);
}

int main() {
  setIO("redistricting");

  auto solve = [&](int test_case)-> void {
    while(test_case--) {
      solve_();
    }
  };

  int test_cases = 1;
  solve(test_cases);

  return 0;
}