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
template <class T> void print(vector <T> v) {cerr << "[ "; for (T i : v) {print(i); cerr << " ";} cerr << "]" << endl;;}
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
template <class T> using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T> void print(indexed_set <T> v) {cerr << "[ "; for (T i : v) {print(i); cerr << " ";} cerr << "]";}
 
#include "robots.h"
 
 
int putaway(int A, int B, int T, int X[], int Y[], int W[], int S[]) {
  // A -> weak
  // B -> small
  vector<pair<int, int>> toys;
  vector<int> weak, small;
  for(int i = 0; i < T; i++) {
    toys.push_back({W[i], S[i]});
  } sort(all(toys));
 
  for(int i = 0; i < A; i++) {
    weak.push_back(X[i]);
  } sort(all(weak));
 
  for(int i = 0; i < B; i++) {
    small.push_back(Y[i]);
  } sort(all(small));
 

  auto check = [&](int mid)->bool {
    vector<bool> mark(T);
    int sz = T;
    
    // check weak
    if(!weak.empty()) {
      int it = 0;
      priority_queue<pair<int, int>> q;
      for(int i = 0; i < T; i++) {
        int j = i, cnt = 0;
        while(j < T && toys[j].first < weak[it]) {
          q.push({toys[j].second, j});
          j++;
        }
 
        while(!q.empty() && cnt < mid) {
          auto it = q.top();
          q.pop();
          mark[it.second] = true;
          sz--, cnt++;
        }
 
        //
        it++;
        if(it == sz(weak)) {
          break;
        }
        i = j - 1;
      }
 
      for(int i = it; i < sz(weak); i++) {
        int cnt = 0;
        while(!q.empty() && cnt < mid) {
          auto it = q.top();
          q.pop();
          mark[it.second] = true;
          sz--, cnt++;
        }
      }
    }
   
    if((long long)sz > (long long)(sz(small) * 1ll * mid)) {
      return false;
    }

    // create new array  
    vector<pair<int, int>> new_array;
    for(int i = 0; i < T; i++) {
      if(!mark[i]) {
        new_array.push_back({toys[i].second, i});
      }
    }
 
    // check small
    if(!small.empty()) {
      int it = 0;
      sort(all(new_array));
 
      for(int i = 0; i < sz(new_array); i++) {
        int j = i, cnt = 0;
        while(j < sz(new_array) && cnt < mid && new_array[j].first < small[it]) {
          sz--;
          j++, cnt++;
        }
 
        //
        it++;
        if(it == sz(small)) {
          break;
        }
        i = j - 1;
      }
    }
 
    if(sz) {
      return false;
    }
 
    return true;
  };
 
  int ina = 1, inb = T, answ = -1;
  while(ina <= inb) {
    int mid = (ina + inb) / 2;
    if(check(mid)) {
      answ = mid;
      inb = mid - 1;
    } else {
      ina = mid + 1;
    }
  }
 
  return answ;
}