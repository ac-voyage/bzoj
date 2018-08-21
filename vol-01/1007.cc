/**
 * BZOJ 1007
 * [HNOI2008] 水平可见直线
 * by Abreto<m@abreto.net>.
 **/
#include <cassert>
#include <cstdio>
#include <algorithm>

using namespace std;
typedef long long int ll;

#define maxn 50000
#define maxa 500000

int n;
int b[(maxa + 10) << 1];
int id[(maxa + 10) << 1];
int ans[maxn + 10];

bool under(int p, int i, int j)
{
    ll ki = i - maxa, kj = j - maxa, kp = p - maxa;
    ll left = ki * b[j] - kj * b[i];
    ll rig1 = kp * (b[j] - b[i]);
    ll rig2 = 1ll * b[p] * (ki - kj);
    return left >= (rig1 + rig2);
}

int top;
int stk[maxn + 10];

int main(void)
{
    int i;
    for (i = 0; i <= (maxa << 1); i++) b[i] = - maxa - 1;
    scanf("%d", &n); // assert(0 < n && n < 50000);
    for (i = 0; i < n; i++)
    {
        int ai, bi;
        scanf("%d%d", &ai, &bi);
        // assert(-500000 <= ai && ai <= 500000);
        // assert(-500000 <= bi && bi <= 500000);
        if (bi > b[maxa + ai])
        {
            b[maxa + ai] = bi;
            id[maxa + ai] = i + 1;
        }
    }
    for (i = 0; i <= (maxa << 1); i++)
        if (b[i] >= (-maxa))
        {
            while ((top > 1) && under(stk[top - 1], i, stk[top - 2])) top--;
            stk[top++] = i;
        }
    for (i = 0; i < top; i++) ans[id[stk[i]]] = 1;
    for (i = 1; i <= n; i++)
        if (ans[i]) printf("%d ", i);
    puts("");
    return 0;
}
