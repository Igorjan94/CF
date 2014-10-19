/*--------------------------------------------------------------*/
/* ACM ICPC 2008-2009, NEERC                                    */
/* Northern Subregional Contest                                 */
/* St Petersburg, November 1, 2008                              */
/*--------------------------------------------------------------*/
/* Problem K. Key to Success                                    */
/*                                                              */
/* Original idea         Andrew Stankevich                      */
/* Problem statement     Andrew Stankevich                      */
/* Testset               Andrew Stankevich                      */
/*--------------------------------------------------------------*/
/* Solution                                                     */
/*                                                              */
/* Author                Andrew Stankevich                      */
/*--------------------------------------------------------------*/
 
import java.io.*;
import java.util.*;

public class key_as implements Runnable {

    public void solve() throws IOException {
        Scanner in = new Scanner(new File("key.in"));
        PrintWriter out = new PrintWriter(new File("key.out"));

        int n = in.nextInt();
        assert 0 <= n && n <= 30;
        int m = in.nextInt();
        assert 1 <= m && m <= 30;
        long[] a = new long[n];
        for (int i = 0; i < n; i++) {
            a[i] = in.nextLong();
            assert 1 <= a[i] && a[i] <= 1000000000;
        }
        Arrays.sort(a);

        ArrayList<Long> ans = new ArrayList<Long>();
        long cur = 1;
        int j = 0;
        for (int i = 0; i < m; i++) {
            while (j < n && a[j] <= cur) {
                cur += a[j];
                j++;
            }
            ans.add(cur);
            cur += cur;
        }

        for (long v : ans) {
            out.print(v + " ");
        }

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
        new Thread(new key_as()).start();
    }
}
