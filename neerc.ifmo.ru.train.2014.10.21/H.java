import java.io.*;
import java.util.*;
import java.math.BigInteger;
import java.util.Map.Entry;
import static java.lang.Math.*;
 
public class H {
 
    final static String task_name = "horrible";
 
    void run() {
        int n = nextInt();
        if (n == 1) {
            out.println("1");
            out.println("1 0");
            return;
        }
 
 
        ArrayList<String> ans = new ArrayList<String>(n * n);
 
        ans.add("2 -1");
        ans.add("1 0");
 
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (j != i - 1 && i != j) {
                    ans.add(j + " " + (i - 1));
                    ans.add(j + " -" + i);
                }
            }
            ans.add(i + " " + (i - 1));
            ans.add((i - 1) + " -" + i);
            ans.add(i + " 0");
        }
        ans.add("1 " + n);
 
        out.println(ans.size());
        for (String str : ans) {
            out.println(str);
 
        }
 
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
 
        new H().run();
        out.close();
        in.close();
    }
}