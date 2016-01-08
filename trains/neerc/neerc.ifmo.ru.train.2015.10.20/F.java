import java.util.*;
import java.io.*;
 
import static java.lang.Math.*;
 
public class F {
    FastScanner in;
    PrintWriter out;
 
    final String inputName = null;
    final String outputName = null;
    final static Random rnd = new Random();
 
    public void solve() {
        int f = in.nextInt();
        boolean ok = true;
 
        for (int i = 0; i < f; i++) {
            int t = in.nextInt(), n = in.nextInt();
            boolean[] x = new boolean[t + 1], y = x.clone(), z;
 
            Arrays.fill(x, true);
 
            for (int j = 0; j < n; j++) {
                Arrays.fill(y, false);
                int l = in.nextInt(), r = in.nextInt();
                int d = r - l;
 
                for (int u = 0; u <= t; u++) {
                    if (x[u]) {
                        {
                            int v = u + d;
                            if (0 <= v && v <= t) {
                                y[v] = true;
                            }
                        }
                        {
                            int v = u - d;
                            if (0 <= v && v <= t) {
                                y[v] = true;
                            }
                        }
                    }
                }
 
 
                z = x;
                x = y;
                y = z;
 
            }
 
            boolean cur = false;
 
            for (boolean val : x) {
                cur |= val;
            }
            ok &= cur;
        }
 
        out.println(ok ? "possible" : "impossible");
 
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
        new F().run();
    }
}
