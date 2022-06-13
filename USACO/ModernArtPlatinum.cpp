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
const int N = 1e3 + 10, M = N * N;
int n, A[N][N], p[N][N];
int t[M], d[M], r[M], l[M];
bool bad[M];

void solve_() {
  cin >> n;

  set<int> st;

  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= n; j++) {
      cin >> A[i][j];
      
      if(!A[i][j]) continue;
      
       st.insert(A[i][j]);
      if(!t[A[i][j]]) {
        t[A[i][j]] = i;
        d[A[i][j]] = i;
        r[A[i][j]] = j;
        l[A[i][j]] = j;
      }

      d[A[i][j]] = i;
      r[A[i][j]] = max(r[A[i][j]], j);
      l[A[i][j]] = min(l[A[i][j]], j);
    }
  }

  if(sz(st) == 1) {
    printf("%d\n", n * n - 1);
    return;
  }

  for(int i = 1; i <= n * n; i++) {
    if(st.find(i) == st.end()) continue;

    p[t[i]][l[i]]++;
    p[d[i] + 1][l[i]]--;
    p[t[i]][r[i] + 1]--;
    p[d[i] + 1][r[i] + 1]++;
  }

  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= n; j++) {
      p[i][j] += p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1];
      if(p[i][j] > 1) {
        bad[A[i][j]] = true;
      }
    }
  }

  int answ = 0;
  for(int i = 1; i <= n * n; i++) {
    if(!bad[i]) {
      ++answ;
    }
  }

  printf("%d\n", answ);
}

int main() {
  setIO("art");

  auto solve = [&](int test_case)-> void {
    while(test_case--) {
      solve_();
    }
  };

  int test_cases = 1;
  solve(test_cases);

  return 0;
}