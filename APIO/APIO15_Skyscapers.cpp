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
const int N = 3e4 + 10;
vector<pair<int, int>> A;
vector<int> adj[N];
bool vis[N][N];
int n, m, dest;
 
void solve_() {
  cin >> n >> m;
  for(int i = 1; i <= m; i++) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);  
    A.push_back({a, b});
 
    if(i == 2) {
      dest = a;
    }
  }
 
  queue<pair<pair<int, int>, int>> q;
 
  q.push({A[0], 0});
  vis[A[0].second][A[0].first] = true;
  while(!q.empty()) {
    auto u = q.front();
    q.pop();
 
    if(u.first.first == dest) {
      printf("%d\n", u.second);
      return;
    }
 
    // 
    int x = u.first.first, l = u.first.second;
    if(x + l < n && !vis[l][x + l]) {
      vis[l][x + l] = true;
      q.push({{x + l, l}, u.second + 1});
    }
 
    if(x - l >= 0 && !vis[l][x - l]) {
      vis[l][x - l] = true;
      q.push({{x - l, l}, u.second + 1});
    }
 
    //
    for(auto i: adj[x]) {
      l = i;
      if(x + l < n && !vis[l][x + l]) {
        vis[l][x + l] = true;
        q.push({{x + l, l}, u.second + 1});
      }
 
      if(x - l >= 0 && !vis[l][x - l]) {
        vis[l][x - l] = true;
        q.push({{x - l, l}, u.second + 1});
      }
    }
  }
 
  printf("-1\n");
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