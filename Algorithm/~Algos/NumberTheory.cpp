long long binPowByMod(long long a, long long b) {
	long long  res = 1;
	while (b != 0) {
    if (b & 1)
      res = res * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return res;
}


const int M = 1e6 + 10;
int lp[M];

void linear_sieve() {
	vector<int> pr;
	for (int i = 2; i < M; ++i) {
    if (lp[i] == 0) {
			lp[i] = i;
			pr.push_back(i);
    }

    for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] < M; ++j) {
			lp[i * pr[j]] = pr[j];
    }
	}
}