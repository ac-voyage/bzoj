/**
 * BZOJ 1009
 * [HNOI2008] GT考试
 * by Abreto<m@abreto.net>.
 **/
#include <cstdio>

using namespace std;

int k;
inline void add(int &dest, int delta)
{
    dest += delta;
    if (dest < 0) dest += k;
    if (dest >= k) dest -= k;
}
inline void mul(int &dest, int times)
{
    dest *= times;
    dest -= dest / k * k;
}
inline int rmul(int a, int b)
{
    int z = a * b;
    return z - z / k * k;
}

int M;

#define MATSZ (1 << 5)
/* dest = b * dest */
void matmul(int dest[MATSZ][MATSZ], int b[MATSZ][MATSZ])
{
    int tmp[MATSZ][MATSZ] = {{0}};
    for (int i = 0; i < M; i++)
        for (int j = 0; j < M; j++)
            for (int l = 0; l < M; l++)
                add(tmp[i][j], rmul(b[i][l], dest[l][j]));
    for (int i = 0; i < M; i++)
        for (int j = 0; j < M; j++)
            dest[i][j] = tmp[i][j];
}

char A[MATSZ];
int f[MATSZ];
int trans[MATSZ][MATSZ];

void calc_transMAT(void)
{
    int i, j;
    f[1] = j = 0;
    for (i = 2; i <= M; i++)
    {
        while (j  && A[i] != A[j + 1]) j = f[j];
        if (A[i] == A[j + 1]) j++;
        f[i] = j;
    }
    for (i = 0; i < M; i++)
        for (j = '0'; j <= '9'; j++)
        {
            int l = i;
            while (l && A[l + 1] != j) l = f[l];
            if (A[l + 1] == j) l++;
            /* i -> l is possible */
            if (l < M) add(trans[l][i], 1);
        }
}

int dp[MATSZ][MATSZ];

int main(void)
{
    int n;
    scanf("%d%d%d", &n, &M, &k);
    scanf("%s", A + 1);
    calc_transMAT();
    dp[0][0] = 1;
    while (n)
    {
        if (1 & n) matmul(dp, trans);
        matmul(trans, trans);
        n >>= 1;
    }
    int ans = 0;
    for (int i = 0; i < M; i++)
        add(ans, dp[i][0]);
    printf("%d\n", ans);
    return 0;
}
