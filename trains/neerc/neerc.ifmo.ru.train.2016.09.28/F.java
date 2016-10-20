import java.util.*;
import java.io.*;
 
import static java.lang.Math.*;
 
public class F {
 
    final static String input = "input.txt";
    final static String output = "output.txt";
 
    double solve(double n, double m) {
 
        if (n == 0) {
            return 1;
        }
 
        if (m == 0) {
            return 0;
        }
 
        return (m) * (2 * n + 1) / (n + m);
    }
 
    double chk(int n, int m) {
        double cnt = 0;
        double fails = 0;
        int k = n + m;
 
        for (int mask = (1 << k) - 1; mask >= 0; mask--) {
            boolean last = true;
 
            int x = 0, y = 0;
 
            int f = 0;
            for (int i = 0; i < k; i++) {
 
                if ((mask & (1 << i)) > 0) {
 
                    if (!last) {
                        ++f;
                    }
 
                    last = true;
                    ++x;
                } else {
 
                    if (last) {
                        ++f;
                    }
 
                    last = false;
                    ++y;
                }
            }
 
            if (x == n && y == m) {
                fails += f;
                cnt += 1;
            }
 
        }
 
        return fails / cnt;
    }
 
    long cnt(int n, int m) {
        long cnt = 0;
        int k = n + m;
 
        for (int mask = (1 << k) - 1; mask >= 0; mask--) {
            boolean last = true;
 
            int x = 0, y = 0;
 
            int f = 0;
            for (int i = 0; i < k; i++) {
 
                if ((mask & (1 << i)) > 0) {
 
                    if (!last) {
                        ++f;
                    }
 
                    last = true;
                    ++x;
                } else {
 
                    if (last) {
                        ++f;
                    }
 
                    last = false;
                    ++y;
                }
            }
 
            if (x == n && y == m) {
                cnt += 1;
            }
 
        }
 
        return cnt;
    }
 
    void test() {
        for (int n = 0; n <= 10; n++) {
            for (int m = 0; m <= 10; m++) {
                if ((n | m) == 0) {
                    System.out.printf("%.4f %.4f     ", 0., 0.);
                } else {
                    // System.out.printf("%6d ", solve(n, m) / (2 * n + 1));
                    System.out.printf("%.4f %.4f     ", chk(n, m), solve(n, m));
                }
            }
            System.out.println();
        }
 
    }
 
    public void run() {
        int t = nextInt(), s = nextInt();
        int m = s - 2 * t;
        int n = t - m;
        out.printf(Locale.ENGLISH, "%.9f", solve(m, n));
    }
 
    int nextInt() {
        return Integer.parseInt(next());
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
 
    static PrintWriter out;
    static BufferedReader br;
    static StringTokenizer st;
 
    public static void main(String[] arg) throws IOException {
 
        if (input == null) {
            br = new BufferedReader(new InputStreamReader(System.in));
        } else {
            br = new BufferedReader(new FileReader(new File(input)));
        }
 
        if (output == null) {
            out = new PrintWriter(System.out);
        } else {
            out = new PrintWriter(new File(output));
        }
 
        new F().run();
        br.close();
        out.close();
 
    }
}