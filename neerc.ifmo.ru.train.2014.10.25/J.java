import java.util.*;
import java.util.Map.Entry;
import java.io.*;
import java.math.BigInteger;
 
public class J {
    FastScanner in;
    PrintWriter out;
    final String taskName = null;
 
    class Pair {
        int n, r;
 
        Pair(int r) {
            this.n = 1;
            this.r = r;
        }
    }
 
    long p = 31;
 
    Pair ans(char[] str, long[] pow, long[] h, int n, int m, int s) {
        Map<Long, Pair> q = new HashMap<Long, Pair>(n);
 
        for (int r = m - 1; r < n; r++) {
            int l = r - m + 1;
 
            long sum = h[r];
            if (l > 0) {
                sum -= h[l - 1];
            }
 
            sum = (sum * pow[n - l]);
 
            Pair cur = q.get(sum);
 
            if (cur == null) {
                q.put(sum, new Pair(l));
            } else {
                ++cur.n;
                cur.r = l;
            }
 
            // System.out.println(new String(str).substring(l, r + 1) + " " +
            // sum);
 
        }
 
        Pair ans = null;
 
        for (Entry<Long, Pair> e : q.entrySet()) {
            if (e.getValue().n >= s && (ans == null || e.getValue().r > ans.r)) {
                ans = e.getValue();
            }
        }
 
        return ans;
    }
 
    public void solve() {
        int m;
        while ((m = in.nextInt()) != 0) {
            char[] str = in.nextLine().toCharArray();
            int n = str.length;
 
            long[] pow = new long[n + 1];
            pow[0] = p;
            for (int i = 1; i <= n; i++) {
                pow[i] = (pow[i - 1] * p) ;
            }
 
            long[] h = new long[n];
 
            h[0] = (p * (str[0] - 'a' + 1)) ;
 
            for (int i = 1; i < n; i++) {
                h[i] = (pow[i] * (str[i] - 'a' + 1) + h[i - 1]) ;
            }
 
            // out.println(Arrays.toString(pow));
            // out.println(Arrays.toString(h));
 
            int l = 1, r = n;
 
            while (r - l > 1) {
                int c = (r + l) / 2;
                Pair ans = ans(str, pow, h, n, c, m);
                if (ans == null || ans.n < m) {
                    r = c;
                } else {
                    l = c;
                }
            }
 
            Pair y = ans(str, pow, h, n, r, m);
 
            if (y == null || y.n < m) {
                r = l;
                y = ans(str, pow, h, n, r, m);
            }
 
            if (y == null || y.n < m) {
                out.println("none");
            } else {
                out.println(r + " " + y.r);
            }
 
        }
    }
 
    public void run() {
        try {
            if (taskName == null) {
                in = new FastScanner(null);
                out = new PrintWriter(System.out);
 
            } else {
                in = new FastScanner(new File(taskName + ".in"));
                out = new PrintWriter(new File(taskName + ".out"));
 
            }
 
            solve();
 
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
 
    class FastScanner {
        BufferedReader br;
        StringTokenizer st;
 
        FastScanner(File f) {
            try {
                if (f == null) {
                    br = new BufferedReader(new InputStreamReader(System.in));
                } else {
                    br = new BufferedReader(new FileReader(f));
                }
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }
 
        String nextLine() {
            try {
                return br.readLine();
            } catch (IOException e) {
                return null;
            }
        }
 
        long nextLong() {
            return Long.parseLong(next());
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
        new J().run();
    }
}
