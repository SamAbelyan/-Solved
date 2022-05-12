#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, x, cnt;
bool vis[N], on_stack[N];
vector<int> adj[N], nodes;

void dfs(int u) {
    vis[u] = true;
    on_stack[u] = true;
    for(auto i: adj[u]) {
        if(on_stack[i])
            nodes.push_back(i);
        else if(!vis[i])
            dfs(i);
    }
    on_stack[u] = false;
}

int main()
{
    ifstream cin("shuffle.in");
    ofstream cout("shuffle.out");
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> x;
        adj[i].push_back(x);
    }

    for(int i = 1; i <= n; i++) {
        if(!vis[i])
            dfs(i);
    }

    for(int i =0 ; i < nodes.size(); i++) {
        int u = nodes[i], x = u;
        u = adj[u][0], cnt++;
        while(u ^ x) {
            u = adj[u][0];
            cnt++;
        }
    }
    cout << cnt << endl;
    return 0;
}
