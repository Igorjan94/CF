import java.util.*;
import java.io.*;
 
public class B {
    FastScanner in;
    PrintWriter out;
 
    final String taskName = "anc";
 
    double q(int n, int k) {
        double ans = 0;
 
        int m = 100000;
 
        for (int i = 0; i < m; i++) {
            double w = Math.PI / m;
            double x = Math.PI * i / m;
            double h = Math.pow(Math.cos(x), n) * Math.cos((n - 2 * k) * x);
            ans += w * h;
        }
 
        return ans * (1 << n) / Math.PI;
    }
 
    public void solve() {
        int n = in.nextInt(), k = in.nextInt(), m = Math.max(n, k) + 1;
 
        long mod = 1L << in.nextInt();
 
        if (k > n) {
            out.println(0);
            return;
        }
 
        int[] s = new int[m];
        int[][] p = new int[m][16];
        int[][] e = new int[m][16];
 
        for (int i = 2; i < m; i++) {
            if (s[i] == 0) {
 
                long curP = i;
                int curE = 1;
                while (curP < m) {
                    long d = 1;
                    while (d * curP < m) {
                        if (d % i != 0) {
                            int j = (int) (d * curP);
                            p[j][s[j]] = i;
                            e[j][s[j]] = curE;
                            ++s[j];
                        }
                        ++d;
                    }
 
                    ++curE;
                    curP *= i;
                }
            }
 
        }
 
        int[] a = new int[m];
 
        for (int i = 2; i <= n; i++) {
            for (int j = 0; j < s[i]; j++) {
                a[p[i][j]] += e[i][j];
            }
        }
 
        for (int i = 2; i <= k; i++) {
            for (int j = 0; j < s[i]; j++) {
                a[p[i][j]] -= e[i][j];
            }
        }
 
        for (int i = 2; i <= (n - k); i++) {
            for (int j = 0; j < s[i]; j++) {
                a[p[i][j]] -= e[i][j];
            }
        }
 
        long ans = 1 % mod;
        for (int i = 0; i < m; i++) {
            while (a[i] > 0) {
                ans = (ans * i) % mod;
                --a[i];
            }
 
        }
 
        out.println(ans);
 
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
 
        long nextLong() {
            return Long.parseLong(next());
        }
 
        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }
 
        int nextInt() {
            return Integer.parseInt(next());
        }
    }
 
    public static void main(String[] arg) {
        new B().run();
    }
}