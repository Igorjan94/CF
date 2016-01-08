import java.util.*;
import java.io.*;
 
import static java.lang.Math.*;
 
public class E {
    FastScanner in;
    PrintWriter out;
 
    final String inputName = null;
    final String outputName = null;
    final static Random rnd = new Random();
 
    long[] mul(long[] x, long[] y) {
        long[] z = new long[x.length + y.length + 1];
 
        for (int i = 0; i < x.length; i++) {
            for (int j = 0; j < y.length; j++) {
                int k = i + j;
                z[k] += x[i] * y[j];
            }
        }
 
        return z;
    }
 
    long gcd(long a, long b) {
        return b == 0 ? a : gcd(b, a % b);
    }
 
    public void solve() {
        String p = in.next();
        int n = in.nextInt(), m = in.nextInt();
        long[] u = new long[] { 1 }, v = new long[] { 1 };
 
        if (p.equals("inf")) {
            for (int i = 0; i < n; i++) {
                int a = in.nextInt(), b = in.nextInt();
                u = mul(u, new long[] { b, a });
            }
 
            for (int i = 0; i < m; i++) {
                int a = in.nextInt(), b = in.nextInt();
                v = mul(v, new long[] { b, a });
            }
 
            for (int i = u.length - 1; i >= -1; i--) {
                if (i == -1 || u[i] != 0) {
                    for (int j = v.length - 1; j >= -1; j--) {
                        if (j == -1 || v[j] != 0) {
                            long a = (i == -1) ? 0 : u[i];
                            long b = (j == -1) ? 0 : v[j];
 
                            if (i < j) {
                                out.println("0/1");
                            } else if (i > j) {
                                if ((a < 0) ^ (b < 0)) {
                                    out.print('-');
                                }
                                out.println("inf");
                            } else {
                                if ((a < 0) ^ (b < 0)) {
                                    out.print('-');
                                }
 
                                a = Math.abs(u[i]);
                                b = Math.abs(v[j]);
 
                                long g = gcd(a, b);
 
                                out.println((a / g) + "/" + (b / g));
                            }
 
                            return;
                        }
                    }
                }
            }
 
        } else {
            long q = Long.parseLong(p);
 
            for (int i = 0; i < n; i++) {
                int a = in.nextInt(), b = in.nextInt();
                u = mul(u, new long[] { b + a * q, a });
            }
 
            for (int i = 0; i < m; i++) {
                int a = in.nextInt(), b = in.nextInt();
                v = mul(v, new long[] { b + a * q, a });
            }
 
            for (int i = 0; i <= u.length; i++) {
                if (i == u.length || u[i] != 0) {
                    for (int j = 0; j <= v.length; j++) {
                        if (j == v.length || v[j] != 0) {
                            long a = (i == u.length) ? 0 : u[i];
                            long b = (j == v.length) ? 0 : v[j];
 
                            if (i > j) {
                                out.println("0/1");
                            } else if (i < j) {
                                if ((a < 0) ^ (b < 0)) {
                                    out.print('-');
                                }
                                out.println("inf");
                            } else {
                                if ((a < 0) ^ (b < 0)) {
                                    out.print('-');
                                }
 
                                a = Math.abs(u[i]);
                                b = Math.abs(v[j]);
 
                                long g = gcd(a, b);
 
                                out.println((a / g) + "/" + (b / g));
                            }
 
                            return;
                        }
                    }
                }
            }
 
        }
 
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
        new E().run();
    }
}
