/**
 * BZOJ 1004
 * [HNOI2008] Cards
 * by Abreto<m@abreto.net>.
 **/
#include <cstdio>
#include <bitset>
#include <cstring>

using namespace std;
typedef long long int ll;

ll p;
void add(ll &dest, ll delta) { dest = (dest + delta) % p; }
void mul(ll &dest, ll times) { dest = (dest * times) % p; }
ll qow(ll a, ll x)
{
    ll ret = 1ll;
    while (x)
    {
        if (1 & x) mul(ret, a);
        mul(a, a);
        x >>= 1;
    }
    return ret;
}

#define MAXC (1 << 5)
#define MAXN (1 << 7)

int n;
int sr, sb, sg;
int m;
int to[MAXN];

bitset<MAXN> vis;
int ncir;
int sz[MAXN];
ll f[MAXC][MAXC][MAXC];
ll count(void)
{
    ncir = 0;
    memset(sz, 0, sizeof sz); memset(f, 0, sizeof f);
    vis.reset();
    for (int i = 1; i <= n; i++)
    {
        if (vis.test(i)) continue;
        int v = i;
        while (!vis.test(v))
        {
            sz[ncir]++;
            vis.set(v);
            v = to[v];
        }
        ncir++;
    }
    f[0][0][0] = 1ll;
    for (int c = 0; c < ncir; c++)
    {
        for (int i = sr; i >= 0; i--)
            for (int j = sb; j >= 0; j--)
                for (int k = sg; k >= 0; k--)
                {
                    if (i >= sz[c]) add(f[i][j][k], f[i - sz[c]][j][k]);
                    if (j >= sz[c]) add(f[i][j][k], f[i][j - sz[c]][k]);
                    if (k >= sz[c]) add(f[i][j][k], f[i][j][k - sz[c]]);
                }
    }
    return f[sr][sb][sg];
}

int main(void)
{
    int i, j;
    ll ans = 0ll;
    scanf("%d%d%d%d%lld", &sr, &sb, &sg, &m, &p);
    n = sr + sb + sg;
    for (i = 0; i < m; i++)
    {
        for (j = 1; j <= n; j++)
            scanf("%d", to + j);
        add(ans, count());
    }
    for (i = 1; i <= n; i++) to[i] = i; add(ans, count());
    mul(ans, qow(m + 1, p - 2));
    printf("%lld\n", ans);
    return 0;
}
