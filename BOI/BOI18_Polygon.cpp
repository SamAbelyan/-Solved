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
const int N = 1e5 + 10;
int n, it = 1, ci = 1, answ, kent;
unordered_map<string, int> mp;
vector<int> adj[N];
int used[N], p[N], in[N];
bool happy[N];
 
void dfsCycle(int node, int parent) {
  used[node] = 1, p[node] = parent;
  for(auto i: adj[node]) {
    if(i == parent) continue;
 
    if(used[i] == 1) {
      int curr = node, cnt = 1;
 
      while(curr != i) {
        curr = p[curr];
        cnt++;
      }
      
      answ += cnt / 2;
      if(cnt & 1) {
        kent++;
      }
    } else if(!used[i]) {
      dfsCycle(i, node);
    }
  }
 
  used[node] = 2;
}
 
void solve_() {
  cin >> n, mp.reserve(2 * n);
 
  if(n & 1) {
    printf("-1\n");
    return;
  }
 
  for(int i = 1; i <= n; i++) {
    string a, b; cin >> a >> b;
 
    int ida, idb;
 
    if(mp.find(a) == mp.end()) {
      mp[a] = it++;
      ida = it - 1;
    } else {
      ida = mp[a];
    }
 
    if(mp.find(b) == mp.end()) {
      mp[b] = it++;
      idb = it - 1;
    } else {
      idb = mp[b];
    }
 
    adj[ida].push_back(idb);
    p[ida] = idb;
    in[idb]++;
 
    if(ida != idb && p[idb] == ida) {
      happy[ida] = happy[idb] = true;
    }
  }
 
  assert(it == n + 1);
 
  queue<int> q;
  for(int i = 1; i <= n; i++) {
    if(!in[i]) {
      q.push(i);
    }
  }
 
  while(!q.empty()) {
    auto u = q.front();
    q.pop();
 
    if(happy[p[u]]) {
      happy[u] = true;
      kent++;
      continue;
    }
 
    happy[u] = happy[p[u]] = true;
    answ++;
 
    in[p[p[u]]]--;
    if (!in[p[p[u]]]) {
      q.push(p[p[u]]);
    }
  }
 
  for(int i = 1; i <= n; i++) {
    if(!happy[i]) {
      // cycles
      dfsCycle(i, 0);
    }
  }
 
  assert(kent % 2 == 0);
  answ += kent;
 
  printf("%d\n", answ);
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