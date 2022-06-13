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
const int N = 2e5 + 10;
int n;

void solve_() {
  cin >> n;
  
  // vector<long long> coord;
  vector<pair<long long, long long>> coords;

  for(int i = 1; i <= n; i++) {
    int a, b; cin >> a >> b;
    // coord.push_back(a);
    // coord.push_back(b);

    coords.push_back({a, b});
  }

  // sort(all(coord));
  // uniq(coord);

  // for(auto &i: coords) {
    // int lstfirst = i.first, lstsecond = i.second;
    // i.first = lower_bound(all(coord), i.first) - coord.begin() + 1;
    // i.second = lower_bound(all(coord), i.second) - coord.begin() + 1;
    
    // compress[i.first] = lstfirst;
    // compress[i.second] = lstsecond;
  // }

  sort(all(coords));

  vector<pair<long long, long long>> prefY(n);
  for(int i = 0; i < n; i++) {
    if(!i) {
      prefY[i].first = coords[i].second;
      prefY[i].second = coords[i].second;
    } else {
      prefY[i].first = min(prefY[i - 1].first, coords[i].second);
      prefY[i].second = max(prefY[i - 1].second, coords[i].second);
    }
  }

  vector<pair<long long, long long>> sufY(n);
  for(int i = n - 1; i >= 0; i--) {
    if(i == n - 1) {
      sufY[i].first = coords[i].second;
      sufY[i].second = coords[i].second;
    } else {
      sufY[i].first = min(sufY[i + 1].first, coords[i].second);
      sufY[i].second = max(sufY[i + 1].second, coords[i].second);
    }
  }

  // left -> right
  // int li = prefX[n - 1].second, ri = prefX[1].second;

  long long start = coords[n - 1].first - coords[0].first;
  start *= (prefY[n - 1].second - prefY[n - 1].first);

  // prefY -> first -> min;
  // prefY -> second -> max;

  long long answ = start;
  for(int i = 0; i < n - 1; i++) {
    long long newArea1 = (prefY[i].second - prefY[i].first) * (coords[i].first - coords[0].first);
    long long newArea2 = (sufY[i + 1].second - sufY[i + 1].first) * (coords[n - 1].first - coords[i + 1].first);
    
    answ = min(answ, newArea1 + newArea2);
  }


  // by y
  for(int i = 0; i < coords.size(); i++) {
    swap(coords[i].first, coords[i].second);
  }

  sort(all(coords));

  for(int i = 0; i < n; i++) {
    if(!i) {
      prefY[i].first = coords[i].second;
      prefY[i].second = coords[i].second;
    } else {
      prefY[i].first = min(prefY[i - 1].first, coords[i].second);
      prefY[i].second = max(prefY[i - 1].second, coords[i].second);
    }
  }

  for(int i = n - 1; i >= 0; i--) {
    if(i == n - 1) {
      sufY[i].first = coords[i].second;
      sufY[i].second = coords[i].second;
    } else {
      sufY[i].first = min(sufY[i + 1].first, coords[i].second);
      sufY[i].second = max(sufY[i + 1].second, coords[i].second);
    }
  }

  for(int i = 0; i < n - 1; i++) {
    long long newArea1 = (prefY[i].second - prefY[i].first) * (coords[i].first - coords[0].first);
    long long newArea2 = (sufY[i + 1].second - sufY[i + 1].first) * (coords[n - 1].first - coords[i + 1].first);
    
    answ = min(answ, newArea1 + newArea2);
  }

  printf("%lld\n", start  - answ);
}

int main() {
  setIO("split");

  auto solve = [&](int test_case)-> void {
    while(test_case--) {
      solve_();
    }
  };

  int test_cases = 1;
  solve(test_cases);

  return 0;
}