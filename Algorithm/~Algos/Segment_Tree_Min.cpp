#include <bits/stdc++.h>
using namespace std;

struct segTreeMin {
  vector<long long> mTree;
  int size;
 
  void init(long long n) {
    size = 1;
    while(size < n)  {
      size *= 2;
    }
    mTree.assign(2 * size - 1, INT64_MAX);
  }
 
  void upd(int u, long long v, int x, int lx, int rx) { // set value at pos u
    if(rx - lx == 1) {
      mTree[x] = v;
      return;
    }
 
    int m = (lx + rx) / 2;
    if(u < m) {
      upd(u, v, 2 * x + 1, lx, m);
    }else {
      upd(u, v, 2 * x + 2, m, rx);
    }
    mTree[x] = min(mTree[2 * x + 1], mTree[2 * x + 2]);
  }
 
  void upd(int u, long long v) {
    upd(u, v, 0, 0, size);
  }
 
  long long qry (int l, int r, int x, int lx, int rx) { // range queries
    if(l >= rx || lx >= r) {
      return INT64_MAX;
    }
    if(lx >= l && r >= rx) {
      return mTree[x];
    }
 
    int m = (rx + lx) / 2;
    long long s1 = qry(l, r, 2 * x + 1, lx, m);
    long long s2 = qry(l, r, 2 * x + 2, m, rx);
    return min(s1, s2);
  }
 
  long long qry(int l, int r) {
    return qry(l, r, 0, 0, size);
  }
};