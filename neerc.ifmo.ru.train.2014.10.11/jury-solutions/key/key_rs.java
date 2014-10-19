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
/* Author                Roman Satukov                          */
/*--------------------------------------------------------------*/
 
import java.io.*;
import java.util.*;

/**
 * @author Roman V Satyukov
 */
public class key_rs implements Runnable {
    private final String problemID = getClass().getName().split("_")[0].toLowerCase();
    private BufferedReader in;
    private PrintWriter out;
    
    private void check(boolean expr, String message) {
        if (!expr) {
            throw new AssertionError(message);
        }
    }
    
    private void solve() throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(st.nextToken());
        check((0 <= n) && (n <= 30), "n is not in [0..30]");
        int m = Integer.parseInt(st.nextToken());
        check((1 <= m) && (m <= 30), "m is not in [1..30]");
        int[] a = new int[n];
        if (n != 0) {
            st = new StringTokenizer(in.readLine());
            for (int i = 0; i < n; i++) {
                a[i] = Integer.parseInt(st.nextToken());
                check((1 <= a[i]) && (a[i] <= 1000000000), "some of a[i] is not in [1..1000,000,000]");
            }
        }
        Arrays.sort(a);
        long current = 0;
        int last = 0;
        for (int i = 0; i < m; i++) {
            while (last < n && a[last] <= current + 1) {
                current += a[last];
                last++;
            }
            if (i > 0) {
                out.print(" ");
            }
            out.print(current + 1);
            current = current + current + 1;
        }
        out.println();
    }
    
    public static void main(String[] args) {
        new Thread(new key_rs()).start();
    }

    public void run() {
        try {
            in = new BufferedReader(new FileReader(new File(problemID + ".in")));
            out = new PrintWriter(new File(problemID + ".out"));
            solve();
            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
}
