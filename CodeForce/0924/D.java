import java.io.*;
import java.util.*;
import java.math.BigInteger;
import java.util.Map.Entry;

import static java.lang.Math.*;

public class D extends PrintWriter {

    long gcd(long a, long b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    class Q implements Comparable<Q> {
        final long n, d;

        @Override
        public String toString() {
            // return n + "/" + d;
            return String.format(Locale.ENGLISH, "%.3f", 1.0 * n / d);
        }

        public Q(long n, long d) {

            if (d < 0) {
                d *= -1;
                n *= -1;
            }

            long g = gcd(abs(n), abs(d));

            this.n = n / g;
            this.d = d / g;
        }

        @Override
        public int hashCode() {
            return ((int) (d ^ (d >>> 32))) * 31 + ((int) (n ^ (n >>> 32)));
        }

        @Override
        public boolean equals(Object obj) {
            if (this == obj)
                return true;
            if (obj == null)
                return false;
            return eq(this, (Q) obj);
        }

        @Override
        public int compareTo(Q q) {
            return Long.compare(n * q.d, d * q.n);
        }
    }

    boolean eq(Q a, Q b) {
        return (a.n == b.n) && (a.d == b.d);
    }

    void add(int[] ft, int i, int value) {
        for (; i < ft.length; i |= i + 1) {
            ft[i] += value;
        }
    }

    int sum(int[] ft, int i) {
        int res = 0;
        for (; i >= 0; i = (i & (i + 1)) - 1) {
            res += ft[i];
        }
        return res;
    }

    void run() {

        int n = nextInt();
        int w = nextInt();

        Q[] l = new Q[n];
        Q[] r = new Q[n];

        for (int i = 0; i < n; i++) {
            int x = nextInt();
            int v = nextInt();

            l[i] = new Q(x, v - w);
            r[i] = new Q(x, v + w);

          //  println(l[i] + " " + r[i]);
        }

        int m = 0;

        Q[] c = r.clone();
        Arrays.sort(c);

        int[] v = new int[n];

        for (int i = 1; i < n; i++) {
            if (!eq(c[i - 1], c[i])) {
                ++m;
            }
            v[i] = m;
        }
        ++m;

        int[] ft = new int[m];

        int[] cr = new int[n];

        for (int i = 0; i < n; i++) {
            cr[i] = v[Arrays.binarySearch(c, r[i])];
        }

        for (int i = 0; i < n; i++) {
            add(ft, cr[i], +1);
        }

        long ans = 0;

        Integer[] order = new Integer[n];

        for (int i = 0; i < n; i++) {
            order[i] = i;
        }

        Arrays.sort(order, new Comparator<Integer>() {
            @Override
            public int compare(Integer i, Integer j) {
                int cmp = l[i].compareTo(l[j]);
                if (cmp == 0)
                    return r[j].compareTo(r[i]);
                else
                    return cmp;
            }
        });

        for (int i : order) {
            int t = cr[i];
            add(ft, t, -1);

            long s = sum(ft, t);

          //  println(i + " " + s);

            ans += s;
        }

        println(ans);

    }

    boolean skip() {
        while (hasNext()) {
            next();
        }
        return true;
    }

    int[][] nextMatrix(int n, int m) {
        int[][] matrix = new int[n][m];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                matrix[i][j] = nextInt();
        return matrix;
    }

    String next() {
        while (!tokenizer.hasMoreTokens())
            tokenizer = new StringTokenizer(nextLine());
        return tokenizer.nextToken();
    }

    boolean hasNext() {
        while (!tokenizer.hasMoreTokens()) {
            String line = nextLine();
            if (line == null) {
                return false;
            }
            tokenizer = new StringTokenizer(line);
        }
        return true;
    }

    int[] nextArray(int n) {
        int[] array = new int[n];
        for (int i = 0; i < n; i++) {
            array[i] = nextInt();
        }
        return array;
    }

    int nextInt() {
        return Integer.parseInt(next());
    }

    long nextLong() {
        return Long.parseLong(next());
    }

    double nextDouble() {
        return Double.parseDouble(next());
    }

    String nextLine() {
        try {
            return reader.readLine();
        } catch (IOException err) {
            return null;
        }
    }

    public D(OutputStream outputStream) {
        super(outputStream);
    }

    static BufferedReader reader;
    static StringTokenizer tokenizer = new StringTokenizer("");
    static Random rnd = new Random();
    static boolean OJ;

    public static void main(String[] args) throws IOException {
        OJ = System.getProperty("ONLINE_JUDGE") != null;
        D solution = new D(System.out);
        if (OJ) {
            reader = new BufferedReader(new InputStreamReader(System.in));
            solution.run();
        } else {
            reader = new BufferedReader(new FileReader(new File(D.class.getName() + ".txt")));
            long timeout = System.currentTimeMillis();
            while (solution.hasNext()) {
                solution.run();
                solution.println();
                solution.println("----------------------------------");
            }
            solution.println("time: " + (System.currentTimeMillis() - timeout));
        }
        solution.close();
        reader.close();
    }
}
