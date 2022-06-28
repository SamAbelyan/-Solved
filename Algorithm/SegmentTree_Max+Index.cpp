// segment Tree Max
// Range Queries
struct segTree {
  vector<pair<long long, int>> mTree;
  int size;

  void init(long long n) {
    size = 1;
    while(size < n)  {
      size *= 2;
    }
    mTree.assign(2 * size - 1, {0, 0});
  }

  pair<ll, ll> combine(pair<ll, ll> a, pair<ll, ll> b) {
    if(a.first > b.first) {
      return a;
    } else {
      return b;
    }
  }

  void upd(int u, long long v, int x, int lx, int rx) { // set value at pos u
    if(rx - lx == 1) {
      mTree[x] = {v, lx};
      return;
    }

    int m = (lx + rx) / 2;
    if(u < m) {
      upd(u, v, 2 * x + 1, lx, m);
    }else {
      upd(u, v, 2 * x + 2, m, rx);
    }
    mTree[x] = combine(mTree[2 * x + 1], mTree[2 * x + 2]);
  }

  void upd(int u, long long v) {
    upd(u, v, 0, 0, size);
  }

  pair<ll, ll> qry (int l, int r, int x, int lx, int rx) { // range queries
    if(l >= rx || lx >= r) {
      return {INT64_MIN, -1};
    }
    if(lx >= l && r >= rx) {
      return mTree[x];
    }

    int m = (rx + lx) / 2;
    auto s1 = qry(l, r, 2 * x + 1, lx, m);
    auto s2 = qry(l, r, 2 * x + 2, m, rx);
    return combine(s1, s2);
  }

  ll qry(int l, int r) {
    return qry(l, r, 0, 0, size).second;
  }
};

segTree seg_max;