import java.io.*;
import java.util.*;
import java.math.BigInteger;
import java.util.Map.Entry;
import static java.lang.Math.*;
 
public class D {
 
    final static String task_name = "defense";
 
    void run() {
 
        int w = nextInt(), h = nextInt(), n = nextInt() + 2, ans = 0;
        int[] x = new int[n], y = new int[n];
        x[1] = w + 1;
        y[1] = h + 1;
 
        for (int i = 2; i < n; i++) {
            x[i] = nextInt();
            y[i] = nextInt();
        }
 
        Arrays.sort(x);
        Arrays.sort(y);
 
        for (int i = 1; i < n; i++) {
            int dx = x[i] - x[i - 1] - 1;
            for (int j = 1; dx > 0 && j < n; j++) {
                int dy = y[j] - y[j - 1] - 1;
                if (dx * dy > ans) {
                    ans = dx * dy;
                }
            }
        }
        out.println(ans);
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
 
        new D().run();
        out.close();
        in.close();
    }
}