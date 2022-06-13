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
const int inf = 1e5;

int a[9][9];
int dp[10][10][1 << 9][1 << 3][2]; // cost

int solve(int r, int c, int maskCol, int maskT, int row) {
  if(r == 9) {
    // check if cols are even
    if(maskCol) {
      return inf;
    }
    return 0;
  }

  if(c == 9) {
    // check if row is even
    if(row) {
      return inf;
    }

    // check if 3x3's are even
    if(r % 3 == 2 && maskT) {
      return inf;
    }

    // go to the next row
    return solve(r + 1, 0, maskCol, maskT, 0);
  }

  if(dp[r][c][maskCol][maskT][row] != -1) {
    return dp[r][c][maskCol][maskT][row];
  }

  int answ = inf;
  if(a[r][c] == 1) {
    answ = solve(r, c + 1, maskCol ^ (1 << c), maskT ^ (1 << (c / 3)), !row);
    answ = min(answ, 1 + solve(r, c + 1, maskCol, maskT, row));
  } else {
    answ = 1 + solve(r, c + 1, maskCol ^ (1 << c), maskT ^ (1 << (c / 3)), !row);
    answ = min(answ, solve(r, c + 1, maskCol, maskT, row));
  }

  return dp[r][c][maskCol][maskT][row] = answ;
}

void solve_() {
  for(int i = 0; i < 9; i++) {
    for(int j = 0; j < 9; j++) {
      char ch; cin >> ch;
      a[i][j] = (ch == '1');
    }
  }

  memset(dp, -1, sizeof(dp));

  cout << solve(0, 0, 0, 0, 0) << endl;
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