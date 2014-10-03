import java.util.*;
import java.io.*;
import java.math.BigInteger;

public class H {
    FastScanner in;
    PrintWriter out;

    final String taskName = null;

    ArrayList<Integer>[] g;

    int[] ans, color;

    int okU, okV;

    int dfsLoop(int v, int p) {

        if (color[v] == 2) {
            return -1;
        }
        color[v] = 1;

        for (int u : g[v]) {
            if (u == p) {
                continue;
            }
            // System.err.println(v + " " + u + " " + color[u]);

            if (color[u] == 1) {
                okU = u;
                okV = v;
                ans[u] = v;
                color[v] = 2;
                return u;
            }

            int l = dfsLoop(u, v);
            if (l != -1) {
                color[v] = 2;
                return l;
            }
        }

        color[v] = 2;
        return -1;
    }

    void dfsDir(int v) {
        if (color[v] == 3) {
            return;
        }

        color[v] = 3;
        for (int u : g[v]) {
            if (okV == v && okU == u) {
                continue;
            }

            if (okV == u && okU == v) {
                continue;
            }

            if (ans[u] == -1) {
                ans[u] = v;
            }
            dfsDir(u);
        }
    }

    public void solve() {
        int n = in.nextInt(), m = in.nextInt();

        g = new ArrayList[n];
        ans = new int[n];
        Arrays.fill(ans, -1);
        color = new int[n];

        for (int i = 0; i < n; i++) {
            g[i] = new ArrayList<>();
        }

        for (int i = 0; i < m; i++) {
            int u = in.nextInt() - 1, v = in.nextInt() - 1;
            g[u].add(v);
            g[v].add(u);
        }

        if (m < n) {
            out.println("NIE");
            return;
        }

        for (int i = 0; i < n; i++) {
            if (ans[i] == -1) {
                int v = dfsLoop(i, -1);

                if (v == -1) {
                    out.println("NIE");
                    return;
                }
                dfsDir(v);
            }
        }

        out.println("TAK");
        for (int i = 0; i < n; i++) {
            out.println(ans[i] + 1);
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
        new H().run();
    }
}
