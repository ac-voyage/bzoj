/**
 * BZOJ 1013
 * [JSOI2008] 球形空间产生器sphere
 * by Abreto<m@abreto.net>.
 **/
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const int maxn = 16;
typedef double acfloat;
const acfloat eps = 1e-8;

int n;
acfloat first[maxn], cur[maxn];
acfloat A[maxn][maxn]; /* [A b] for Ax = b */
acfloat ans[maxn];

void gauss(void)
{
    int i, j, k, l;
    i = 0;
    for (j = 0; i < n && j < n; j++)
    {
        for (k = i; k < n; k++) if (fabs(A[k][j]) > eps) break;
        if (k != i) for (l = 0; l <= n; l++) swap(A[i][l], A[k][l]);
        acfloat r = A[i][i];
        for (k = 0; k <= n; k++) A[i][k] /= r;
        for (k = 0; k < n; k++)
        {
            if (k == i) continue;
            acfloat o = A[k][i];
            for (l = 0; l <= n; l++) A[k][l] -= A[i][l] * o;
        }
        i++;
    }
    for (i = n - 1; i >= 0; i--) ans[i] = A[i][n];
}

inline acfloat sq(acfloat x) { return x * x; }

int main(void)
{
    int i, j;
    scanf("%d", &n);
    for (i = 0; i < n; i++) scanf("%lf", first + i);
    for (i = 0; i < n; i++)
    {
        acfloat xj;
        A[i][n] = 0.;
        for (j = 0; j < n; j++)
        {
            scanf("%lf", &xj);
            A[i][j] = 2. * (xj - first[j]);
            A[i][n] += sq(xj) - sq(first[j]);
        }
    }
    gauss();
    for (i = 0; i < n; i++)
        printf("%s%.3lf", i ? " " : "", ans[i]);
    puts("");
    return 0;
}
