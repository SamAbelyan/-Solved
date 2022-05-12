#include <bits/stdc++.h>
using namespace std;

#define nline endl

const int N = 1e5 + 10;
int n,m,k, arr[N], inDegree[N], ans[N];
vector<int> adj[N], topSort;
vector<pair<int, int>> edge[N];
int main()
{
    ifstream cin("timeline.in");
    ofstream cout("timeline.out");
    int a,b,c;
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++)
        cin >> arr[i];

    for(int i = 0; i < k; i++)
    {
        cin >> a >> b >> c;
        adj[a].push_back(b);
        edge[b].push_back(make_pair(a, c));
        inDegree[b]++;
    }

    queue<int> q;
    for(int i = 1; i <= n; i++)
        if(!inDegree[i])
            q.push(i);

    while(!q.empty())
    {
        int a = q.front();
        topSort.push_back(a);
        q.pop();
        for(auto i: adj[a])
        {
            inDegree[i]--;
            if(!inDegree[i])
                q.push(i);
        }
    }

    for(auto i: topSort)
    {
        ans[i] = arr[i];
        for(auto j: edge[i])
        {
            ans[i] = max(ans[i], ans[j.first] + j.second);
            // cout << i << " " << ans[j.first] << " " << j.second << endl;
        }
    }

    for(int i = 1; i <= n; i++)
        cout << ans[i] << nline;

    return 0;
}