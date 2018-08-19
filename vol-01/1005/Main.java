/**
 * BZOJ
 * [HNOI2008] 明明的烦恼
 * by Abreto<m@abreto.net>.
 **/
import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
    static BigInteger[] f = new BigInteger[1024];
    public static void init() {
        f[0] = BigInteger.valueOf(1);
        for (int i = 1; i < 1024; i++)
            f[i] = f[i-1].multiply(BigInteger.valueOf(i));
    }

    static int n = 0;
    static int[] d = new int[1024];
    static int s = 0, c = 0;

    public static void solve() {
        Scanner cin = new Scanner(System.in);
        n = cin.nextInt();
        if (1 == n)
        {
            d[0] = cin.nextInt();
            System.out.println( (1 == d[0] * d[0]) ? 1 : 0 );
            return;
        }
        if (2 == n)
        {
            d[0] = cin.nextInt(); d[1] = cin.nextInt();
            if ( (1 == d[0] * d[0]) && (1 == d[1] * d[1]) )
                System.out.println(1);
            else
                System.out.println(0);
            return;
        }
        for (int i = 0; i < n; i++)
        {
            d[i] = cin.nextInt();
            if (0 == d[i] || d[i] > n - 1)
            {
                System.out.println(0);
                return;
            }
            if (-1 == d[i]) continue;
            s += d[i] - 1;
            c++;
        }
        if (n - 2 < s)
        {
            System.out.println(0);
            return;
        }
        BigInteger ans = f[n - 2].divide(f[n - 2 - s]);
        for (int i = 0; i < n; i++)
            if (-1 != d[i])
                ans = ans.divide(f[d[i] - 1]);
        for (int i = 0; i < n - 2 - s; i++)
            ans = ans.multiply(BigInteger.valueOf(n - c));
        System.out.println(ans);
    }

    public static void main(String[] args) throws Exception {
        init();
        solve();
    }
}
