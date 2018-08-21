/**
 * BZOJ 1010
 * [HNOI2008] 玩具装箱toy
 * by Abreto<m@abreto.net>.
 **/
#include <cstdio>
#include <cmath>

using namespace std;

typedef long double ll;

const int maxn = 50050;

ll k[maxn], b[maxn];
inline ll g(int i, ll x)
{
    return k[i] * x + b[i];
}
/* if i is above s & j */
bool above(int s, int i, int j)
{
    ll l = (b[i] - b[s]) * (k[s] - k[j]);
    ll r = (b[j] - b[s]) * (k[s] - k[i]);
    return (l >= r);
}

int N;
ll L;
ll s[maxn];
ll f[maxn], dp[maxn];
int ql, qr, q[maxn];

inline void calc(int i)
{
    ll t = f[i] + L;
    k[i] = -2ll * t;
    b[i] = dp[i] + t * t;
}

int main(void)
{
    int i;
    scanf("%d%Lf", &N, &L); L++;
    for (i = 1; i <= N; i++)
    {
        scanf("%Lf", s + i);
        s[i] += s[i-1];
        f[i] = i + s[i];
    }
    ql = qr = dp[0] = 0;
    calc(0); q[qr++] = 0;
    for (i = 1; i <= N; i++)
    {
        while (ql + 1 < qr && g(q[ql], f[i]) >= g(q[ql + 1], f[i])) ql++;
        dp[i] = g(q[ql], f[i]) + f[i] * f[i];
        calc(i);
        while (ql + 1 < qr && above(q[qr - 2], q[qr - 1], i)) qr--;
        q[qr++] = i;
    }
    printf("%lld\n", (long long)round(dp[N]));
    return 0;
}
