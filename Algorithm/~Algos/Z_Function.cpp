void z_func(string s, int len) {
  int l = 0, r = 0;
  for(int i = 1; i < len; i++) {
    z[i] = 0;
    if(i <= r) {
      z[i] = min(r - i + 1, z[i - l]);
      }
    while(z[i] + i < len && s[z[i] + i] == s[z[i]]) {
      z[i]++;
    }
 
    if(z[i] + i - 1 > r) {
      r = z[i] + i - 1, l = i;
    }
  }
}