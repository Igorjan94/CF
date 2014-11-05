import java.util.*;
import java.io.*;
 
public class K2 {
 
    int[] dsu, rank;
    ArrayList<Integer>[] a;
    boolean[] isLeaf;
 
    int get(int v) {
        return dsu[v] == v ? v : (dsu[v] = get(dsu[v]));
    }
 
    void union(int u, int v) {
        u = get(u);
        v = get(v);
 
        if (u != v) {
            if (rank[u] == rank[v]) {
                ++rank[u];
            }
 
            if (rank[u] < rank[v]) {
                dsu[u] = v;
            } else {
                dsu[v] = u;
            }
        }
    }
 
    boolean addEdge(int v, int u) {
        if (get(v) != get(u)) {
            union(v, u);
            a[u].add(v);
            a[v].add(u);
            return true;
        }
        return false;
    }
 
    public void solve() {
        int t = in.nextInt();
        while (--t >= 0) {
            int n = in.nextInt();
            dsu = new int[n];
            rank = new int[n];
            a = new ArrayList[n];
            isLeaf = new boolean[n];
 
            int[][] d = new int[n][n];
            for (int i = 0; i < n; i++) {
                a[i] = new ArrayList<>();
                dsu[i] = i;
            }
 
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    d[i][j] = in.nextInt() - 1;
                }
            }
             
            for (int i = 0; i < n; ++i)
                isLeaf[d[i][n - 1]] = true;
             
            for (int i = 0; i < n; i++) {
                addEdge(i, d[i][1]);
            }
            int k = n - 1;
            for (int t1 = 0; t1 < n; ++t1) {
                for (int i = 0; i < n; ++i)
                    isLeaf[d[i][k]] = true;
                k--;
                for (int i = 0; i < n; ++i) 
                    if (!isLeaf[i])
                    {
                        for (int j = 0; j < n; ++j)
                            if (!isLeaf[d[i][j]])
                                addEdge(i, d[i][j]);
                    }
                boolean magic = true;
                for (int i = 0; i < n; ++i)
                    magic &= isLeaf[i];
                if (magic)
                    break;
            }
            for (int i = 0; i < n; ++i)
                for (int y : a[i])
                    if (y > i)
                        out.println("" + (i + 1) + " " + (y + 1));
            out.println();
 
        }
 
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
        new K2().run();
    }
}
 
 
/*
1
5
1 4 5 3 2
2 3 4 1 5
3 2 4 5 1
4 1 5 3 2
5 4 3 1 2
*/