// return the max value
// to make it min change
// sign of number xd
// (don't forget to decrease the
// current value instead of increasing
// good luck)
 
vector < pair<long long, long long> > mas;
 
long double calc(pair<long long, long long> p1, pair<long long, long long> p2) {
  return (long double)(p1.second - p2.second) / (long double)(p2.first - p1.first);
}
 
void add(long long k, long long b) {
  while (sz(mas) >= 2) {
    int sz = sz(mas);
    auto cur = make_pair(k, b);
    auto lst1 = mas[sz - 1];
    auto lst2 = mas[sz - 2];
    ///
    if (calc(cur, lst1) < calc(lst1, lst2)) {
      mas.pop_back();
    } else {
      break;
    }
  }

  mas.emplace_back(k, b);
}

long long get(int x) {
  int ina = 0, inb = sz(mas) - 2, res = sz(mas) - 1;
  while (ina <= inb) {
    int mid = (ina + inb) / 2;
    if (x < calc(mas[mid], mas[mid + 1])) {
      res = mid;
      inb = mid - 1;
    } else {
      ina = mid + 1;
    }
  }
  return mas[res].first * 1ll * x + mas[res].second;
}