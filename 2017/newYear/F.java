import java.util.*;
import java.io.*;

public class F {
    FastScanner in;
    PrintWriter out;
    ArrayList<Integer>[] g;
    ArrayList<Integer>[] ans;
    int color[];

    public void dfs() {
        int n = g.length;
        int k = in.nextInt();
        ans = new ArrayList[k];
        Queue<Integer> q = new LinkedList<Integer>();
        for (int i = 0; i < k; ++i) {
            ans[i] = new ArrayList<Integer>();
            int x = in.nextInt(); --x;
            q.add(x);
            color[x] = i;
            ans[i].add(x);
        }
        while (!q.isEmpty()) {
            int u = q.poll();
            for (int v : g[u])
                if (color[v] == -1) {
                    color[v] = color[u];
                    ans[color[u]].add(v);
                    q.add(v);
                }
        }
        for (int i = 0; i < k; ++i) {
            out.println(ans[i].size());
            for (int j = 0; j < ans[i].size(); ++j)
                out.print("" + (ans[i].get(j) + 1) + " ");
            out.println();
        }
    }

    public void solve() throws IOException {
        int n = in.nextInt();
        int m = in.nextInt();
        g = new ArrayList[n];
        color = new int[n];
        for (int i = 0; i < n; ++i) {
            g[i] = new ArrayList<Integer>();
            color[i] = -1;
        }

        for (int i = 0; i < m; ++i) {
            int from = in.nextInt(); --from;
            int to   = in.nextInt(); --to;
            g[from].add(to);
            if (from != to)
                g[to].add(from);
        }
        dfs();
    }

    public void run() {
        try {
            in = new FastScanner(new File("input.txt"));
            out = new PrintWriter(new File("output.txt"));

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
                br = new BufferedReader(new FileReader(f));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
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
