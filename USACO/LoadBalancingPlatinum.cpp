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
const int N = 1e5 + 10;
int n, left_points, right_points;

struct fenwick_additional {
  int size;
  vector<long long> tree;
  vector<long long> indi;

  void init() {
    sort(all(indi));
    uniq(indi)
    tree.assign(sz(indi) + 4, 0);
    size = sz(tree);
  }

  void add(int u) {
    indi.push_back(u);
  }

  int get(int u) {
    // assert(lower_bound(all(indi), u) != indi.end());
    auto it = lower_bound(all(indi), u); 
    if(it != indi.end()) {
      u = it - indi.begin() + 1;
    } else {
      u = size - 1;
    }

    // dbg(u)
    return u;
  }

  void upd(int u, long long v, bool flag = false) {
    if(!flag) {
      u = get(u);
    } else {
      u = min(u, size - 1);
    }

    while(u < size) {
      tree[u] += v;
      u += u & (-u);
    }
  }

  long long qry(int u,bool flag = false) {
    if(!flag) {
      u = get(u);
    } else {
      u = min(u, size - 1);
    }

    long long sum = 0;
    while(u > 0) {
      sum += tree[u];
      u -= u & (-u); // lsb
    }
    return sum;
  }

  long long sum(int l, int r) {
    l = get(l), r = get(r);
    if(l > r) {
      return 0;
    }
    return qry(r) - qry(l - 1);
  }

} left_side, right_side;

bool check(int mid) {
  // we have left_side and right_side already computed
  // need to check we can reach maximum mid


  int ina = 0, inb = N;
  while(ina <= inb) {
    int m = (ina + inb) / 2;

    int bottomLeft = left_side.qry(m, true);
    int topLeft = left_points - bottomLeft;
    int bottomRight = right_side.qry(m, true);  
    int topRight = right_points - bottomRight;

    if(bottomLeft <= mid && topRight <= mid && bottomRight <= mid && topLeft <= mid) {
        return true;
    }

    if(max(topLeft, topRight) > mid) {
      ina = m + 1;
    } else {
      inb = m - 1;
    }
  }

  return false;
}

void solve_() {
  cin >> n;

  vector<pair<int, int>> coords;
  for(int i = 1; i <= n; i++) {
    int a, b; cin >> a >> b;
    coords.push_back({a, b});
  }

  sort(all(coords));

  for(int i = 0; i < n; i++) {
    right_side.add(coords[i].second);
    left_side.add(coords[i].second);
    right_points++;
  }

  left_side.init();
  right_side.init();

  for(int i = 0; i < n; i++) {
    right_side.upd(coords[i].second, 1);
  }

  int best = n;
  // init BIT 
  for(int i = 0; i < n; i++) {
    int j = i;
    while(j < n && coords[j].first == coords[i].first) {
      right_side.upd(coords[j].second, -1);
      left_side.upd(coords[j].second, 1);
      left_points++, right_points--;
      j++;
    }
    
    int ina = 1, inb = n, answ = n;
    while(ina <= inb) {
      int mid = (ina + inb) / 2;
      if(check(mid)) {
        answ = mid;
        inb = mid - 1;
      } else {
        ina = mid + 1;
      }
    }

    best = min(best, answ);

    i = j - 1;
  }

  printf("%d\n", best);
}

int main () {
  setIO("balancing");

  auto solve = [&](int test_case)-> void {
    while(test_case--) {
      solve_();
    }
  };

  int test_cases = 1;
  solve(test_cases);

  return 0;
}