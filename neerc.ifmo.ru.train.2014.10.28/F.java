import java.util.*;
import java.io.*;
 
public class F {
 
    long sum(long[] p, int l, int r) {
        if (r >= p.length) {
            r = p.length - 1;
        }
 
        long ans = p[r];
        if (l > 0) {
            ans -= p[l - 1];
        }
        return ans;
 
    }
 
    public void solve() {
        int n = in.nextInt(), k = in.nextInt();
 
        long[] p = new long[n];
        p[0] = in.nextInt();
        for (int i = 1; i < n; i++) {
            p[i] = p[i - 1] + in.nextInt();
        }
 
        if (k * 2 >= n) {
            out.println(p[n - 1]);
            return;
        }
 
        long[] m = new long[n];
 
        long q = 0;
 
        for (int i = n - 1; i >= 0; i--) {
            q = Math.max(q, sum(p, i, i + k - 1));
            m[i] = q;
        }
 
        long ans = 0;
 
        for (int i = 0; i < n; i++) {
            long cur = sum(p, i, i + k - 1);
            if (i + k < n) {
                cur += m[i + k];
            }
            ans = Math.max(ans, cur);
        }
 
        out.println(ans);
    }
 
    FastScanner in;
    PrintWriter out;
 
    public void run() {
        in = new FastScanner();
        out = new PrintWriter(System.out);
 
        solve();
 
        out.close();
    }
 
    class FastScanner {
        BufferedReader br;
        StringTokenizer st;
 
        FastScanner() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }
 
        String nextLine() {
            try {
                return br.readLine();
            } catch (IOException e) {
                return null;
            }
        }
 
        String next() {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(nextLine());
            }
            return st.nextToken();
        }
 
        int nextInt() {
            return Integer.parseInt(next());
        }
    }
 
    public static void main(String[] arg) {
        new F().run();
    }
}