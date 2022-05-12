#include <bits/stdc++.h>
using namespace std;

#define add push_back

typedef long long ll;
typedef double db;
typedef string str;

const int N = 2e3 + 10;
int n,m,c,dp[N][N],ans;
vector<int> adj[N];
int main()
{
    //ifstream cin("time.in");
    //ofstream cout("time.out");
    int x,y;
    cin >> n >> m >> c;
    vector<int> cost(n + 1);
    for(int i = 1; i <= n; i++)
        cin >> cost[i];

    for(int i = 0; i < m; i++)
    {
        cin >> x >> y;
        adj[x].add(y);
    }

    memset(dp, -1, sizeof(dp));
    dp[0][1] = 0;
    for(int i = 0; i < 1001; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(dp[i][j] != -1)
            {
                if(j == 1)
                    ans = max(ans, dp[i][j] - c * i * i);

                for(auto k: adj[j])
                    dp[i + 1][k] = max(dp[i + 1][k], dp[i][j] + cost[k]);
            }

        }
    }
    cout << ans << endl;
    return 0;
}