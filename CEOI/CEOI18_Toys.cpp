#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
//#include "temp.cpp"
#include <cstdio>
using namespace std;
 
#pragma GCC optimize("Ofast")
 
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
long long dx[8] = {-1,0,1,0,1,-1,1,-1};
long long dy[8] = {0,1,0,-1,1,1,-1,-1};
 
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
 
// Random
mt19937 myrand(chrono::steady_clock::now().time_since_epoch().count());
 
// Indexed Set
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
long long n;
map<long long, set<long long>> memo;
 
set<long long> calc(long long x, vector<long long> &div) {
  if(memo.find(x) != memo.end()) {
    return memo[x];
  }
  memo[x].insert(x - 1);
 
  vector<long long> div2;
  for(auto i: div) {
    if(x % i == 0) {
      div2.push_back(i);
    }
  }
 
  for(auto i: div2) {
    if(x % i == 0) {
      set<long long> st = calc(x / i, div2);
      for(auto j: st) {
        memo[x].insert(j + i - 1);
      }
    } 
  }
 
  return memo[x];
}
 
void solve_() {
  cin >> n;
 
  if(n == 1) {
    printf("1\n0");
    return;
  }
 
  vector<long long> div;
  for(int i = 2; i * i <= n; i++) {
    if(n % i == 0) {
      div.push_back(i);
    } 
  }
  
  set<long long> st = calc(n, div);
 
  printf("%d\n", sz(st));
  for(auto i: st) {
    printf("%lld " , i );
  } printf("\n");
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