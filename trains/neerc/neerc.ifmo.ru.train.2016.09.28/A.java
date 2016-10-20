import java.util.*;
import java.io.*;
 
public class A {
 
    final static String input = "input.txt";
    final static String output = "output.txt";
 
    public void run() {
        int n = nextInt(), m = 3;
 
        String[][] rnames = new String[n][m];
 
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                rnames[i][j] = next();
            }
        }
 
        int[] p = new int[n];
 
        for (int i = 0; i < n; i++) {
            p[i] = nextInt() - 1;
        }
 
        String[][] names = new String[n][];
        for (int i = 0; i < n; i++) {
            names[i] = rnames[p[i]];
        }
 
        String[] ans = new String[n];
 
        String cur = "";
 
        for (int i = 0; cur != null && i < n; i++) {
            Arrays.sort(names[i]);
 
            for (int j = 0; j < m; j++) {
                if (cur.compareTo(names[i][j]) < 0) {
                    ans[i] = names[i][j];
                    break;
                }
            }
            cur = ans[i];
        }
 
        if (cur == null) {
            out.println("IMPOSSIBLE");
            return;
        }
 
        for (int i = 0; i < n; i++) {
            out.println(ans[i]);
        }
 
    }
 
    int nextInt() {
        return Integer.parseInt(next());
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
 
    static PrintWriter out;
    static BufferedReader br;
    static StringTokenizer st;
 
    public static void main(String[] arg) throws IOException {
 
        if (input == null) {
            br = new BufferedReader(new InputStreamReader(System.in));
        } else {
            br = new BufferedReader(new FileReader(new File(input)));
        }
 
        if (output == null) {
            out = new PrintWriter(System.out);
        } else {
            out = new PrintWriter(new File(output));
        }
 
        new A().run();
        br.close();
        out.close();
 
    }
}
