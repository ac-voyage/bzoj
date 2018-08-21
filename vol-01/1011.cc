/**
 * BZOJ 1011
 * [HNOI2008] 遥远的行星
 * by Abreto<m@abreto.net>.
 **/
#include <cstdio>

using namespace std;

const int maxn = 100100;
const double eps = 1e-8;
const int threshold = 1 << 7;

double M[maxn];
double s[maxn];

int main(void)
{
    int N;
    double a;
    scanf("%d%lf", &N, &a);
    for (int i = 1; i <= N; i++)
    {
        double ans = 0.;
        int j = (int)(a * i + eps);
        scanf("%lf", M + i);
        if (i < threshold)
        {
            for (int k = 1; k <= j; k++)
                ans += M[i] * M[k] / (1. * (i - k));
        } else {
            ans = s[j] * M[i] / (1. * (i - j / 2.));
        }
        s[i] = s[i - 1] + M[i];
        printf("%lf\n", ans);
    }
    return 0;
}
