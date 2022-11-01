namespace Cnk {
  const long long mod = 1e9 + 7;
  const int N = 2e5 + 10, maxN = N - 2;
  long long fact[N], ifact[N];

  long long binPowByMod(long long a, long long b) {
    a %= mod;
    long long res = 1;
    while (b > 0) {
      if (b & 1)
        res = res * a % mod;
      a = a * a % mod;
      b >>= 1;
    }
    return res;
  }
  
  long long choose (long long a, long long b) {
    return (((fact[a] * ifact[b]) % mod ) * ifact[a - b] ) % mod;
  }

  void generate() {
    fact[0] = fact[1] = 1;
    for(int i = 2; i < N; i++) {
      fact[i] = (fact[i - 1] * i) % mod;
    }
  
    ifact[maxN] = binPowByMod(fact[maxN], mod - 2);
    for(int i = maxN; i >= 1; i--) {
      ifact[i - 1] = (ifact[i] * i) % mod;
    }
  }
}