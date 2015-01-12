import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.math.BigInteger;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.StringTokenizer;

public class D {
    FastScanner in;
    PrintWriter out;

    final String taskName = null;

    void mull(BigInteger[] a, int n) {

        while (n > 1) {
            int m = 0;

            for (int i = 1; i < n; i += 2) {
                a[m++] = a[i - 1].multiply(a[i]);
            }

            if (n % 2 == 1) {
                a[m++] = a[n - 1];
            }
            n = m;
        }
    }

    class Pair {
        int p, n;

        Pair(int p, int n) {
            this.p = p;
            this.n = n;
        }

    }

    List<Pair> fac(int n) {
        List<Pair> ans = new ArrayList<Pair>();

        if (n == 0) {
            ans.add(new Pair(0, 1));
            return ans;
        }

        if (n == 1) {
            return ans;
        }

        for (int d = 2; d * d <= n; d++) {
            int m = 0;
            while (n % d == 0) {
                ++m;
                n /= d;
            }
            if (m > 0) {
                ans.add(new Pair(d, m));
            }
        }

        if (n > 1) {
            ans.add(new Pair(n, 1));
        }
        return ans;
    }

    void mull(Map<Integer, Integer> map, List<Pair> n) {
        for (Pair pair : n) {
            Integer e = map.get(pair.p);
            if (e == null) {
                e = 0;
            }
            map.put(pair.p, e + pair.n);
        }
    }

    public void solve() {
        int n = in.nextInt();
        Map<Integer, Integer>[] a = new Map[n], b = new Map[n];

        for (int i = 0; i < n; i++) {
            a[i] = new HashMap<Integer, Integer>();
            b[i] = new HashMap<Integer, Integer>();

            int m = in.nextInt();
            List<Pair> p = fac(m - 1);
            List<Pair> q = fac(m - 0);

            mull(b[i], q);

            for (int j = 0; j < i; j++) {
                mull(a[j], p);
                mull(b[j], q);
            }
        }

        BigInteger[] p = new BigInteger[n * 1024], q = new BigInteger[n * 1024];

        for (int i = 0; i < n; i++) {
            if (a[i].containsKey(0)) {
                out.println("0/1");
            } else {
                int ps = 1, qs = 1;
                p[0] = q[0] = BigInteger.ONE;

                for (Entry<Integer, Integer> entry : a[i].entrySet()) {
                    Integer be = b[i].get(entry.getKey());
                    if (be == null) {
                        be = 0;
                    }

                    int ae = entry.getValue();

                    int m = Math.min(ae, be);

                    if (m != ae) {
                        p[ps++] = BigInteger.valueOf(entry.getKey())
                                .pow(ae - m);
                    }

                    if (m != be) {
                        b[i].put(entry.getKey(), be - m);
                    } else {
                        b[i].remove(entry.getKey());
                    }
                }

                for (Entry<Integer, Integer> entry : b[i].entrySet()) {
                    q[qs++] = BigInteger.valueOf(entry.getKey()).pow(
                            entry.getValue());
                }

                mull(p, ps);
                mull(q, qs);

                out.print(p[0]);
                out.print('/');
                out.print(q[0]);
                out.println();
            }
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
        new D().run();
    }
}
