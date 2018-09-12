/**
 * BZOJ 1015
 * [JSOI2008] 星球大战starwar
 * by Abreto<m@abreto.net>.
 **/
#include <cstdio>
#include <vector>
#include <bitset>
#include <set>
#include <algorithm>

using namespace std;
typedef vector<int> vi;
typedef vi::iterator vii;
#define pb push_back
typedef set<int> si;
typedef si::iterator sii;
#define ins insert

#define MAXM    (200020)
#define MAXN    (MAXM << 1)

int N, M, k;
vi g[MAXN];
bitset<MAXN> vis;
bitset<MAXN> des;
int att[MAXN];
int ans[MAXN];

struct disjoint
{
    int f[MAXN];
    disjoint(void)
    {
        for (int i = 0; i < MAXN; i++) f[i] = i;
    }
    int find(int x)
    {
        return (x == f[x]) ? (x) : (f[x] = find(f[x]));
    }
    void uni(int x, int y)
    {
        int fx = find(x), fy = find(y);
        f[fx] = fy;
    }
}dj;

void dfs(int u, int root)
{
    vis.set(u);
    dj.uni(u, root);
    for (vii v = g[u].begin(); v != g[u].end(); v++)
        if ( (!des.test(*v)) && (!vis.test(*v)) )
            dfs(*v, root);
}

int main(void)
{
    int i;
    scanf("%d%d", &N, &M);
    for (i = 0; i < M; i++)
    {
        static int x, y;
        scanf("%d%d", &x, &y);
        g[x].pb(y);
        g[y].pb(x);
    }
    scanf("%d", &k);
    for (i = 0; i < k; i++)
    {
        scanf("%d", att + i);
        des.set(att[i]);
    }
    int tot = 0;
    for (i = 0; i < N; i++)
    {
        if (!des.test(i) && !vis.test(i))
        {
            tot++;
            dfs(i, i);
        }
    }
    ans[k] = tot;
    for (i = k - 1; i >= 0; i--)
    {
        si neibor;
        int u = att[i];
        for (vii v = g[u].begin(); v != g[u].end(); v++)
        {
            if (!des.test(*v))
            {
                neibor.ins(dj.find(*v));
            }
        }
        tot -= (((int)(neibor.size())) - 1);
        for (sii v = neibor.begin(); v != neibor.end(); v++)
            dj.uni(u, *v);
        des.reset(u);
        ans[i] = tot;
    }
    for (i = 0; i <= k; i++)
        printf("%d\n", ans[i]);
    return 0;
}
