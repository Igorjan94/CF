/*--------------------------------------------------------------*/
/* ACM ICPC 2008-2009, NEERC                                    */
/* Northern Subregional Contest                                 */
/* St Petersburg, November 1, 2008                              */
/*--------------------------------------------------------------*/
/* Problem D. Deposits                                          */
/*                                                              */
/* Original idea         Roman Satukov                          */
/* Problem statement     Andrew Stankevich                      */
/* Testset               Andrew Stankevich                      */
/*--------------------------------------------------------------*/
/* Solution                                                     */
/*                                                              */
/* Author                Andrew Stankevich                      */
/*--------------------------------------------------------------*/
 
import java.io.*;
import java.util.*;

public class deposits_as implements Runnable {

    BufferedReader in;
    StringTokenizer st;

    int nextInt() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(in.readLine());
        }
        return Integer.parseInt(st.nextToken());
    }

    final int MAX = 1000000;

    public void solve() throws IOException {
        in = new BufferedReader(new FileReader("deposits.in"));
        PrintWriter out = new PrintWriter(new File("deposits.out"));

        int n = nextInt();
        assert 1 <= n && n <= 100000;
        int[] a = new int[n];
        int[] ca = new int[MAX + 1];
        for (int i = 0; i < n; i++) {
            a[i] = nextInt();
            assert 1 <= a[i] && a[i] <= MAX;
            ca[a[i]] ++;
        }
        int m = nextInt();
        assert 1 <= m && m <= 100000;
        int[] b = new int[m];
        int[] cb = new int[MAX + 1];
        for (int i = 0; i < m; i++) {
            b[i] = nextInt();
            assert 1 <= b[i] && b[i] <= MAX;
            cb[b[i]]++;
        }

        long r = 0;
        for (int i = 1; i <= MAX; i++) {
            for (int j = i; j <= MAX; j += i) {
                r += 1L * ca[j] * cb[i];
            }
        }

        out.println(r);

        in.close();
        out.close();
    }

    public void run() {
        try {
            solve();
        } catch (IOException e) {
            System.exit(64);
        }
    }

    public static void main(String[] arg) throws IOException {
        new Thread(new deposits_as()).start();
    }
}
