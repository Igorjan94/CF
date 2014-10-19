import java.util.*;
import java.io.*;
 
public class F {
    FastScanner in;
    PrintWriter out;
 
    final String taskName = "obs";
 
    class Edge implements Comparable<Edge> {
        int f, t, d;
 
        public Edge(int f, int t, int d) {
            this.f = f;
            this.t = t;
            this.d = d;
        }
 
        @Override
        public int compareTo(Edge e) {
            return Integer.compare(d, e.d);
        }
 
    }
 
    int[] dsu, rank;
 
    int get(int v) {
        return dsu[v] == v ? v : (dsu[v] = get(dsu[v]));
    }
 
    void union(int u, int v) {
        u = get(u);
        v = get(v);
 
        if (rank[u] == rank[v]) {
            ++rank[u];
        }
 
        if (rank[u] < rank[v]) {
            dsu[u] = v;
        } else {
            dsu[v] = u;
 
        }
 
    }
 
    ArrayList<Edge>[] g;
 
    void dfs(int v, int p, int d, int[] ans) {
        ans[v] = d;
        for (Edge e : g[v]) {
            if (e.f == v && e.t != p) {
                dfs(e.t, v, Math.max(d, e.d), ans);
            }
 
            if (e.t == v && e.f != p) {
                dfs(e.f, v, Math.max(d, e.d), ans);
            }
        }
 
    }
 
    public void solve() {
        int n = in.nextInt(), m = in.nextInt();
 
        g = new ArrayList[n];
        dsu = new int[n];
        rank = new int[n];
 
        for (int i = 0; i < n; i++) {
            dsu[i] = i;
            g[i] = new ArrayList<Edge>();
        }
 
        Edge[] edge = new Edge[m];
 
        for (int i = 0; i < m; i++) {
            edge[i] = new Edge(in.nextInt() - 1, in.nextInt() - 1, in.nextInt());
        }
 
        Arrays.sort(edge);
 
        for (Edge e : edge) {
            if (get(e.f) != get(e.t)) {
                union(e.f, e.t);
                g[e.f].add(e);
                g[e.t].add(e);
            }
        }
 
        int[] ans = new int[n];
        long sum = 0;
 
        for (int i = 0; i < n; i++) {
            dfs(i, -1, 0, ans);
            for (int j = 0; j < n; j++) {
                sum += ans[j];
            }
        }
        out.println(sum);
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
 
        String nextLine() {
            try {
                return br.readLine();
            } catch (IOException e) {
                return null;
            }
        }
 
        boolean hasNext() {
            while (st == null || !st.hasMoreTokens()) {
                String line = nextLine();
                if (line == null) {
                    return false;
                }
                st = new StringTokenizer(line);
            }
            return true;
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