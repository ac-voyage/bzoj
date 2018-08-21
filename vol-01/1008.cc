/**
 * BZOJ 1008
 * [HNOI2008] 越狱
 * by Abreto<m@abreto.net>.
 **/
#include <cstdio>

using namespace std;

typedef long long int ll;
const ll p = 100003ll;

void add(ll &dest, ll delta)
{
    dest += delta;
    if (dest < 0) dest += p;
    if (dest >= p) dest -= p;
}
void mul(ll &dest, ll times)
{
    dest *= times;
    dest -= dest / p * p;
}
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

int main(void)
{
    ll M, N;
    scanf("%lld%lld", &M, &N);
    ll ans = qow(M, N);
    ll notans = qow(M - 1, N - 1);
    mul(notans, M);
    add(ans, p - notans);
    printf("%lld\n", ans);
    return 0;
}
