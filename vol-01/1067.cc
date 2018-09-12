/**
 * BZOJ 1067
 * [SCOI2007] 降雨量
 * by Abreto<m@abreto.net>.
 **/
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const int maxn = 50050;
const int maxblk = 1 << 9;

int n;
int blk_sz, blk_cnt;
int ys[maxn], rs[maxn];
int mr[maxblk];
inline int yid(int y)
{
    return lower_bound(ys, ys + n, y) - ys;
}
inline int blk_id(int x)
{
    return x / blk_sz;
}
inline int l_bound(int bid)
{
    return bid * blk_sz;
}
inline int r_bound(int bid)
{
    return (bid + 1) * blk_sz - 1;
}
void init(void)
{
    blk_sz = (int)(sqrt(n + 10));
    blk_cnt = (n + blk_sz - 1) / blk_sz;
    for (int i = 0; i < n; i++)
    {
        int bid = blk_id(i);
        mr[bid] = max(mr[bid], rs[i]);
    }
}
void add(int id, int y, int r)
{
    ys[id] = y;
    rs[id] = r;
}

/* 0 for true, 5 for false, 11 for maybe */
int answer(int y, int x)
{
    const static int TRUE = 0, FALSE = 5, MAYBE = 11;
    if (x < y) return FALSE;
    int l = yid(y), r = yid(x);
    int havey = (l < n) && (ys[l] == y), havex = (r < n) && (ys[r] == x);
    if ( !havey && !havex ) return MAYBE;
    int limit = 0x7f7f7f7f;
    if (havey) limit = min(limit, rs[l]);
    if (havex) limit = min(limit, rs[r]);
    if (havey && havex && rs[r] > rs[l]) return FALSE;
    if ( (l + havey) < r )
    {
        int lid = blk_id(l + havey), rid = blk_id(r);
        if (lid == rid)
        {
            for (int i = l + havey; i < r; i++)
                if (rs[i] >= limit) return FALSE;
        } else {
            int lblkr = r_bound(lid);
            for (int i = l + havey; i <= lblkr; i++)
                if (rs[i] >= limit) return FALSE;
            for (int i = lid + 1; i < rid; i++)
                if (mr[i] >= limit) return FALSE;
            int rblkl = l_bound(rid);
            for (int i = rblkl; i < r; i++)
                if (rs[i] >= limit) return FALSE;
        }
    }
    if (!havex || !havey) return MAYBE;
    if (r - l < x - y) return MAYBE;
    return TRUE;
}

int main(void)
{
    int i;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int yi, ri;
        scanf("%d%d", &yi, &ri);
        add(i, yi, ri);
    }
    init();
    scanf("%d", &i);
    while (i--)
    {
        int Y, X;
        scanf("%d%d", &Y, &X);
        printf("%s\n", "true\0false\0maybe" + answer(Y, X));
    }
    return 0;
}
