/**
 * BZOJ 1003
 * [ZJOI2006] 物流运输
 * by Abreto<m@abreto.net>.
 **/
#include <cstdio>
#include <vector>
#include <bitset>
#include <utility>
#include <cstring>
#include <queue>

using namespace std;
typedef long long int ll;
#define pb push_back
typedef pair<int,int> pii;
#define mp make_pair
#define fi first
#define se second

#define MAXN (1 << 7)
#define MAXV (1 << 5)

int n, m, K;
vector<pii> g[MAXV];
int broken[MAXV][MAXN];

bool is_available(int u, int l, int r)
{
    return (broken[u][r] == broken[u][l - 1]);
}
priority_queue< pii, vector<pii>, greater<pii> > q;
int d[MAXV];
bitset<MAXV> solid;
int sp(int l, int r)
{
    while (!q.empty()) q.pop();
    memset(d, 0x3f, sizeof d);
    solid.reset();
    q.push(mp(d[1] = 0, 1));
    while (!q.empty())
    {
        int u = q.top().se; q.pop();
        if (solid.test(u)) continue;
        solid.set(u);
        if (u == m) break;
        for (vector<pii>::iterator it = g[u].begin(); it != g[u].end(); it++)
        {
            pii e = *it;
            int v = e.fi, w = e.se;
            if (!is_available(v, l, r)) continue;
            if (d[u] + w < d[v])
                q.push(mp(d[v] = d[u] + w, v));
        }
    }
    return d[m];
}

ll f[MAXN][MAXN], dp[MAXN];

int main(void)
{
    int i, j, e;
    scanf("%d%d%d%d", &n, &m, &K, &e);
    while (e--)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[u].pb(mp(v, w));
        g[v].pb(mp(u, w));
    }
    scanf("%d", &i);
    while (i--)
    {
        int P, a, b;
        scanf("%d%d%d", &P, &a, &b);
        for (e = a; e <= b; e++) broken[P][e] = 1;
    }
    for (i = 1; i <= n; i++)
    {
        for (e = 1; e <= m; e++)
            broken[e][i] += broken[e][i - 1];
    }
    for (i = 1; i <= n; i++)
        for (e = i; e <= n; e++)
            f[i][e] = sp(i, e);
    for (i = 1; i <= n; i++)
    {
        dp[i] = f[1][i] * i;
        for (j = 1; j < i; j++)
            if (f[j + 1][i] != 0x3f3f3f3f)
                dp[i] = min(dp[i], dp[j] + f[j + 1][i] * (i - j) + K);
    }
    printf("%lld\n", dp[n]);
    return 0;
}
