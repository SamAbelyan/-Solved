#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

const long long N = 1e3 + 10, inf = 1e18;
long long n, m, network[N][N], parent[N];
vector<int> adj[N];
 
// Edmonds Karp Algorithm
pair<bool, long long> bfs() {   
  vector<bool> used(n + 1);
  memset(parent, 0, sizeof(parent));
  queue<pair<long long, long long>> q;
 
  q.push({1, inf}), used[1] = true;
  while(!q.empty()) {
    auto u = q.front();
    q.pop();
    for(auto i: adj[u.first]) {
      if(used[i] || !network[u.first][i]) continue;
      used[i] = true; parent[i] = u.first;
      long long newFlow = min(u.second, network[u.first][i]);
      if(i == n) {
        return {true, newFlow};
      }
      q.push({i, newFlow});
    }
  }
 
  return {false, inf};
}
 
long long maxFlow() {
  long long maxflow = 0;
  while(true) {
    auto currFlow = bfs();
    if(!currFlow.first) {
      return maxflow;
    }
    maxflow += currFlow.second; long long curr = n;
    while(curr != 0) {
      network[parent[curr]][curr] -= currFlow.second;
      network[curr][parent[curr]] += currFlow.second;
      curr = parent[curr];
    }
  }
}

int main() {
  cin >> n >> m;
  for(int i = 0; i < m; i++) {
    int a, b, c; cin >> a >> b >> c;
    network[a][b] += c;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
 
  cout << maxFlow() << endl;
  return 0;
}