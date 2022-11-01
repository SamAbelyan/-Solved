struct fenwick {
  int n;
  vector<int> tr;

  void init(int m) {
    n = m, tr.assign(m + 1, 0);
  }

  void upd(int u, long long value) {
    while(u <= n) {
      tr[u] += value;
      u += u & (-u);
    }
  }
  
  long long qry(int u) {
    long long s = 0;
    while(u > 0) {
      s += tr[u];
      u -= u & (-u);
    }
    return s;
  }
  
  long long sum(int l, int r) {
    return qry(r) - qry(l - 1);
  }
};