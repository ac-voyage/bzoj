/**
 * BZOJ 1012
 * [JSOI2008] 最大数maxnumber
 * by Abreto<m@abreto.net>.
 **/
#include <cstdio>

using namespace std;

typedef long long int ll;

const int maxn = 200200;

int main(void)
{
    static int r;
    static ll q[maxn];
    int M; ll D;
    ll t = 0;
    scanf("%d%lld", &M, &D);
    while (M--)
    {
        char op[4]; ll operand;
        scanf("%s%lld", op, &operand);
        if ('Q' == op[0])
        {
            printf("%lld\n", t = q[r - operand]);
        } else {
            operand = (operand + t) % D;
            q[r++] = operand;
            /* 最坏是 O(n^2) 的，水过去了 */
            for (int i = r - 2; i >= 0 && q[i] < q[i+1]; i--)
                q[i] = q[i + 1];
        }
    }
    return 0;
}
