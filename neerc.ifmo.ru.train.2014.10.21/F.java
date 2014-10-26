import java.io.*;
import java.util.*;
import java.math.BigInteger;
import java.util.Map.Entry;
import static java.lang.Math.*;
 
public class F {
 
    final static String task_name = "frames";
 
    class Rect {
        long d, u, l, r;
 
        Rect(long x1, long y1, long x2, long y2) {
            l = min(x1, x2);
            r = max(x1, x2);
            d = min(y1, y2);
            u = max(y1, y2);
        }
 
        Rect move(long x, long y) {
            return new Rect(l + x, d + y, r + x, u + y);
        }
 
        long square() {
            return (u - d) * (r - l);
        }
 
        Rect intersect(Rect t) {
            Rect s = this;
 
            if (s.isEmpty() || t.isEmpty() || s.r <= t.l || t.r <= s.l || s.u <= t.d || t.u <= s.d) {
                return new Rect(0, 0, 0, 0);
            }
 
            return new Rect(max(s.l, t.l), max(s.d, t.d), min(s.r, t.r), min(s.u, t.u));
 
        }
 
        boolean isEmpty() {
            return l == r || u == d;
        }
    }
 
    void run() {
        long[][][] x = new long[2][2][4];
        long[][][] y = new long[2][2][4];
 
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                x[i][j][0] = x[i][j][3] = nextInt();
                y[i][j][0] = y[i][j][1] = nextInt();
                x[i][j][1] = x[i][j][2] = nextInt();
                y[i][j][3] = y[i][j][2] = nextInt();
            }
        }
 
        long ans = 0;
        long mx = 0, my = 0;
 
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int h = 0; h < 2; h++) {
                    for (int k = 0; k < 2; k++) {
                        for (int u = 0; u < 4; u++) {
                            for (int v = 0; v < 4; v++) {
                                for (int dx = -50; dx <= 50; dx++) {
                                    for (int dy = -50; dy <= 50; dy++) {
                                        long vx = x[i][j][u] - x[h][k][v] + dx;
                                        long vy = y[i][j][u] - y[h][k][v] + dy;
 
                                        Rect so = new Rect(x[0][0][0], y[0][0][0], x[0][0][2], y[0][0][2]);
                                        Rect si = new Rect(x[0][1][0], y[0][1][0], x[0][1][2], y[0][1][2]);
 
                                        Rect to = new Rect(x[1][0][0], y[1][0][0], x[1][0][2], y[1][0][2]).move(vx, vy);
                                        Rect ti = new Rect(x[1][1][0], y[1][1][0], x[1][1][2], y[1][1][2]).move(vx, vy);
 
                                        Rect a = so.intersect(to);
 
                                        Rect asi = a.intersect(si);
                                        Rect ati = a.intersect(ti);
                                        Rect asti = asi.intersect(ti);
 
                                        long sq = a.square() - asi.square() - ati.square() + asti.square();
                                        if (sq > ans) {
                                            ans = sq;
                                            mx = vx;
                                            my = vy;
                                        }
                                    }
                                }
 
                            }
                        }
 
                    }
                }
            }
        }
        out.println(ans);
        out.println(mx + " " + my);
 
    }
 
    int[][] nextMatrix(int n, int m) {
        int[][] matrix = new int[n][m];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                matrix[i][j] = nextInt();
        return matrix;
    }
 
    String next() {
        while (!st.hasMoreTokens())
            st = new StringTokenizer(nextLine());
        return st.nextToken();
    }
 
    boolean hasNext() {
        while (!st.hasMoreTokens()) {
            String line = nextLine();
            if (line == null) {
                return false;
            }
            st = new StringTokenizer(line);
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
            return in.readLine();
        } catch (IOException err) {
            return null;
        }
    }
 
    static PrintWriter out;
    static BufferedReader in;
    static StringTokenizer st = new StringTokenizer("");
    static Random rnd = new Random();
 
    public static void main(String[] args) throws IOException {
        if (task_name == null) {
            in = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);
        } else {
            in = new BufferedReader(new FileReader(new File(task_name + ".in")));
            out = new PrintWriter(new FileWriter(new File(task_name + ".out")));
        }
 
        new F().run();
        out.close();
        in.close();
    }
}