import java.util.*;
import java.util.Map.Entry;
import java.io.*;
 
public class I {
    FastScanner in;
    PrintWriter out;
 
    final String taskName = null;
 
    class Pair {
        int p, n;
 
        Pair(int p, int n) {
            this.p = p;
            this.n = n;
        }
 
        @Override
        public String toString() {
            return "<" + p + " " + n + ">";
        }
    }
 
    int m = 500003;
    ArrayList<Integer>[] g = new ArrayList[m];
    int[] size = new int[m];
 
    void dfs(int v) {
        size[v] = 0;
        for (int u : g[v]) {
            dfs(u);
            size[v] += (size[u] + 1);
        }
    }
 
    void mull(Map<Integer, Integer> map, List<Pair> n) {
        for (Pair pair : n) {
            pair
            Integer e = map.get(pair.p);
            if (e == null) {
                e = 0;
            }
            map.put(pair.p, e + pair.n);
        }
    }
 
    public void solve() {
        ArrayList<Pair>[] fac = new ArrayList[m];
 
        for (int i = 0; i < m; i++) {
            g[i] = new ArrayList<Integer>(32);
            fac[i] = new ArrayList<Pair>(32);
        }
        boolean[] p = new boolean[m];
 
        Arrays.fill(p, true);
        p[0] = p[1] = false;
        for (int i = 2; i < m; i++) {
            if (p[i]) {
                for (int j = i * 2; j < m; j += i) {
                    p[j] = false;
                }
            }
        }
 
        for (int i = 2; i < m; i++) {
            if (p[i]) {
                fac[i].add(new Pair(i, 1));
                {
                    long n = ((long) i) * i;
                    int e = 2;
                    while (n < m) {
                        fac[(int) n].add(new Pair(i, e));
                        e++;
                        n *= i;
                    }
                }
 
                int e = 1;
                long n = i;
                while (n < m) {
                    long k = 2;
                    while (n * k < m) {
                        if (k % i != 0) {
                            fac[(int) (n * k)].add(new Pair(i, e));
                        }
                        ++k;
                    }
                    ++e;
                    n *= i;
                }
            }
        }
 
        // for (int i = 2; i < 20; i++) {
        // System.out.print(i + "     :       ");
        // for (Pair pair : fac[i]) {
        // System.out.print(pair + " ");
        // }
        // System.out.println();
        // }
 
        int[] a = new int[m];
        int t = in.nextInt();
        while (--t >= 0) {
            int n = in.nextInt();
 
            long mod = in.nextInt();
 
            for (int i = 0; i <= n; i++) {
                a[i] = 0;
            }
 
            for (int i = 0; i < n; i++) {
                g[i].clear();
            }
 
            for (int i = 1; i < n; i++) {
                int j = in.nextInt() - 1;
                g[j].add(i);
            }
             
            dfs(0);
 
            for (int i = 2; i < n; i++) {
                for (Pair pair : fac[i]) {
                    a[pair.p] += pair.n;
                }
            }
 
            for (int i = 1; i < n; i++) {
                for (Pair pair : fac[size[i] + 1]) {
                    a[pair.p] -= pair.n;
                }
            }
 
            long ans = 1;
 
            for (int i = 2; i <= n; i++) {
                long q = 1;
                for (int j = a[i]; j > 0; j--) {
                    q = (q * i) % mod;
                }
                ans = (ans * q) % mod;
            }
 
            out.println(ans);
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
        new I().run();
    }
}
