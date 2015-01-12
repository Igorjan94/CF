import java.io.*;
import java.util.*;
import java.math.BigInteger;
import java.util.Map.Entry;
import static java.lang.Math.*;
 
public class I {
 
    final static String task_name = "ideal";
 
    void run() {
        String last = "";
        String line = "";
        while (!line.contains("------") || !last.contains("Time") || !last.contains("Team")) {
            last = line;
            line = nextLine();
        }
 
        String prob = last.split("=")[0];
        int m = 0, n = 0;
        int rs = prob.indexOf(" A ") + 1;
 
        while ((m + 'A' <= 'Z') && prob.contains(" " + (char) (m + 'A') + " ")) {
            ++m;
        }
 
        // System.out.println(m);
 
        boolean[][] s = new boolean[301][27];
        int[] r = new int[301], q = new int[301];
 
        while ((line = nextLine()) != null && line.length() > 3) {
            // System.out.println(line.substring(rs));
            StringTokenizer res = new StringTokenizer(line.substring(rs));
            for (int j = 0; j < m; j++) {
                s[n][j] = res.nextToken().contains("+");
            }
            res.nextToken();
            res.nextToken();
            r[n] = Integer.parseInt(res.nextToken());
            ++n;
        }
 
        double vainness = 0;
        double oversimplification = 0;
        double evenness = 0.0;
        double unsolvability = 0.0;
 
        double[] instability = new double[m];
 
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (s[i][j]) {
                    ++q[i];
                }
            }
            if (q[i] == 0) {
                vainness += 1.0 / n;
            }
            if (q[i] == m) {
                oversimplification += 1.0 / n;
            }
        }
 
        for (int i = 1; i < n; i++) {
            evenness += max(q[i - 1] - q[i] - 1, 0);
        }
 
        for (int j = 0; j < m; j++) {
            int low = -1;
            for (int i = 0; i < n; i++) {
                if (s[i][j]) {
                    low = i;
                }
            }
            if (low != -1) {
                for (int i = 0; i < low; i++) {
                    if (!s[i][j] && r[i] < r[low]) {
                        instability[j] += 1.0 / n;
                    }
                }
 
            } else {
                ++unsolvability;
            }
        }
 
        if (m > 0) {
            evenness /= m;
            unsolvability /= m;
        }
 
        double sum = 0;
 
        for (int j = 0; j < m; j++) {
            sum += instability[j] / m;
        }
 
        sum += 1.030 * vainness;
        sum += 3.141 * oversimplification;
        sum += 2.171 * evenness;
        sum += 1.414 * unsolvability;
 
        out.printf("Vainness = %.3f\n", vainness);
        out.printf("Oversimplification = %.3f\n", oversimplification);
        out.printf("Evenness = %.3f\n", evenness);
        out.printf("Unsolvability = %.3f\n", unsolvability);
        for (int j = 0; j < m; j++) {
            out.printf("Instability %d = %.3f\n", j + 1, instability[j]);
        }
 
        out.printf("Negidealness = %.3f\n", sum);
 
        // Oversimplification = 0.000
        // Evenness = 0.200
        // Unsolvability = 0.200
        // Instability 1 = 0.000
        // Instability 2 = 0.333
        // Instability 3 = 0.000
        // Instability 4 = 0.333
        // Instability 5 = 0.000
        // Negidealness = 1.022
 
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
 
        new I().run();
        out.close();
        in.close();
    }
}