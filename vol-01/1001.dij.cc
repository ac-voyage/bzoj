/**
 * BZOJ
 * [BeiJing2006] 狼抓兔子
 * by Abreto<m@abreto.net>.
 **/
#include <cstdio>
#include <queue>
#include <bitset>
#include <cstring>
#include <cassert>
#include <functional>

using namespace std;
typedef long long int ll;

#define MAXV 2000200
#define MAXE 6000600
struct edge
{
    int v;
    ll w;
    edge *n;
    edge(int vv = 0, ll ww = 0ll, edge *nn = NULL) : v(vv), w(ww), n(nn) { }
}E[MAXE];
int ne;
edge *front[MAXV];
void add_edge(int u, int v, ll w)
{
    assert(v >= 0);
    E[ne] = edge(v, w, u[front]);
    u[front] = E + ne;
    ne ++;
}

typedef pair<ll,int> pli;
#define mp make_pair
#define fi first
#define se second

ll d[MAXV];
bitset<MAXV> solid;
ll sp(int s, int t)
{
    priority_queue< pli, vector<pli>, greater<pli> > q;

    memset(d, 0x7f, sizeof d);

    q.push(mp(0ll, s));
    d[s] = 0ll;

    while ( !q.empty() )
    {
        pli cur = q.top(); q.pop();
        int u = cur.se;
        if (solid.test(u)) continue;
        solid.set(u);
        for (edge *e = u[front]; e; e = e->n)
        {
            int v = e->v; ll w = e->w;
            if ( d[v] > d[u] + w )
            {
                d[v] = d[u] + w;
                q.push(mp(d[v], v));
            }
        }
    }

    return d[t];
}

#define s (0)
#define t (MAXV-1)

#define lb(x)   (2*(x) - 1)
#define ru(x)   (2*(x))

int main(void)
{
    int N, M;
    ll w;
    scanf("%d%d", &N, &M);
    assert(N > 1 || M > 1);
    /* - */
    /* first line */
    for (int i = 1; i < M; i++)
    {
        scanf("%lld", &w);
        if (1 == N)
        {
            add_edge(s, t, w);
            add_edge(t, s, w);
        } else {
            add_edge(s, ru(i), w);
            add_edge(ru(i), s, w);
        }
    }
    for (int i = 1; i < N - 1; i++)
    {
        int up = 1 + (i - 1) * (M - 1);
        int down = up + M - 1;
        for (int j = 1; j < M; j++)
        {
            scanf("%lld", &w);
            add_edge(lb(up), ru(down), w);
            add_edge(ru(down), lb(up), w);
            up ++; down ++;
        }
    }
    /* last line */
    if (N > 1)
    {
        int block = 1 + (N - 2) * (M - 1);
        for (int i = 1; i < M; i++)
        {
            scanf("%lld", &w);
            add_edge(lb(block), t, w);
            add_edge(t, lb(block), w);
            block ++;
        }
    }
    /* | */
    for (int i = 1; i < N; i++)
    {
        if (1 == M)
        {
            scanf("%lld", &w);
            add_edge(s, t, w);
            add_edge(t, s, w);
        } else {
            int block = 1 + (i - 1) * (M - 1);
            scanf("%lld", &w);
            add_edge(t, lb(block), w); add_edge(lb(block), t, w);
            for (int j = 1; j < M - 1; j++)
            {
                scanf("%lld", &w);
                add_edge(ru(block), lb(block + 1), w);
                add_edge(lb(block + 1), ru(block), w);
                block ++;
            }
            scanf("%lld", &w);
            add_edge(ru(block), s, w);
            add_edge(s, ru(block), w);
        }
    }
    /* \ */
    for (int i = 1; i < N; i++)
    {
        int blk = 1 + (i - 1) * (M - 1);
        for (int j = 1; j < M; j++)
        {
            scanf("%lld", &w);
            add_edge(lb(blk), ru(blk), w);
            add_edge(ru(blk), lb(blk), w);
            blk ++;
        }
    }
    /* --- */
    printf("%lld\n", sp(s, t));
    return 0;
}
