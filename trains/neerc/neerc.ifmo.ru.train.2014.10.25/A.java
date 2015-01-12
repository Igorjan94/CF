import java.util.*;
import java.io.*;
import static java.lang.Math.*;
 
public class A {
    FastScanner in;
    PrintWriter out;
 
    final String taskName = null;
 
    double dist(double dx, double dy) {
        return sqrt(dx * dx + dy * dy);
    }
 
    public void solve() {
 
        int n, m = 1000;
        while ((n = in.nextInt()) != 0) {
 
            double[] x = new double[n], y = new double[n];
            double l = Double.MAX_VALUE, r = Double.MIN_VALUE;
            for (int i = 0; i < n; i++) {
                x[i] = in.nextDouble();
                y[i] = in.nextDouble();
 
                l = min(l, x[i]);
                r = max(r, x[i]);
            }
 
            while (r - l > 1e-7) {
                double ll = l + (r - l) / 3;
                double rr = r - (r - l) / 3;
 
                double fl = 0, fr = 0;
                for (int i = 0; i < n; i++) {
                    fl = max(fl, dist(x[i] - ll, y[i]));
                    fr = max(fr, dist(x[i] - rr, y[i]));
                }
 
                if (fl < fr) {
                    r = rr;
                } else {
                    l = ll;
                }
            }
 
            double ans = 0, p = (r + l) / 2;
            for (int i = 0; i < n; i++) {
                ans = max(ans, dist(x[i] - p, y[i]));
            }
 
            out.println(p + " " + ans);
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
 
        long nextLong() {
            return Long.parseLong(next());
        }
 
        double nextDouble() {
            return Double.parseDouble(next());
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
        new A().run();
    }
}