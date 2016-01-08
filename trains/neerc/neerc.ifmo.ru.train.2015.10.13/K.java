import java.util.*;
import java.io.*;
import static java.lang.Math.*;
 
public class K {
    FastScanner in;
    PrintWriter out;
 
    final String inputName = null;
    final String outputName = null;
 
    public void solve() {
        int n = in.nextInt();
 
        int[] a = new int[n];
 
        for (int i = 0; i < n; i++) {
            a[i] = in.nextInt();
        }
 
        int k = 30;
        long[] c = new long[k];
 
        for (int i = 0; i < k; i++) {
            c[i] = in.nextLong();
        }
        int m = 1 << n;
 
        long[][] w = new long[n][n];
 
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int d = a[i] ^ a[j];
 
                for (int b = 0; b < k; b++) {
                    if (((1 << b) & d) > 0) {
                        w[i][j] += c[b];
                    }
                }
            }
        }
 
        long[][] dp = new long[n][m];
 
        for (int i = 0; i < n; i++) {
            for (int mask = 1; mask < m; mask++) {
                dp[i][mask] = Integer.MAX_VALUE;
            }
        }
 
        for (int i = 0; i < n; i++) {
            int mask = 1 << i;
 
            long cur = 0;
            for (int b = 0; b < k; b++) {
                if (((1 << b) & a[i]) > 0) {
                    cur += c[b];
                }
            }
 
            dp[i][mask] = cur;
 
        }
 
        for (int mask = 1; mask < m; mask++) {
            for (int i = 0; i < n; i++) {
                if (((1 << i) & mask) > 0) {
 
                    int free = mask ^ (1 << i);
 
                    for (int j = 0; j < n; j++) {
                        if (((1 << j) & free) > 0) {
                            dp[i][mask] = min(dp[i][mask], dp[j][free] + w[i][j]);
                        }
                    }
                }
            }
        }
 
        long ans = Integer.MAX_VALUE;
        for (int i = 0; i < n; i++) {
            ans = min(ans, dp[i][m - 1]);
        }
 
        out.println(ans);
 
    }
 
    public void run() {
        try {
 
            if (inputName == null) {
                in = new FastScanner(null);
            } else {
                in = new FastScanner(new File(inputName));
            }
 
            if (outputName == null) {
                out = new PrintWriter(System.out);
            } else {
                out = new PrintWriter(new File(outputName));
 
            }
 
            solve();
            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
 
    class FastScanner {
        BufferedReader br;
        StringTokenizer st;
 
        void close() throws IOException {
            br.close();
        }
 
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
        new K().run();
    }
}
