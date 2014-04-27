
import java.io.*;
import java.util.*;

public class K {

    final static String task_name = "stdin";

    void run() throws IOException {
        int n = nextInt();
        int[] d = new int[n];
        for (int i = 0; i < n; i++) {
            d[i] = nextInt();
        }
        ArrayList<String> ans = new ArrayList<String>(n);

        for (int r, x, y, l = 0; l < n;) {
            r = l;
            while (r < n) {
                if (d[r] <= r - l) {
                    r--;
                    break;
                }
                r++;
            }
            x = r - l + 1;

            y = n;
            r = l;
            while (y > 0 && r < n) {
                y = Math.min(y - 1, d[r] - 1);
                if (y <= 0) {
                    break;
                }
                r++;
            }

            y = r - l + 1;

            if (l + x >= n) {
                x = n - l;
            }
            if (l + y >= n) {
                y = n - l;
            }

            // pw.println(x + " " + y);

            if (x > y) {
                ans.add((l + 1) + " " + (l + x));
                l += x;
            } else {
                ans.add((l + y) + " " + (l + 1));
                l += y;
            }
        }

        pw.println(ans.size());
        for (String s : ans) {
            pw.println(s);
        }

    }

    String next() throws IOException {
        while (st == null || !st.hasMoreTokens())
            st = new StringTokenizer(br.readLine());
        return st.nextToken();
    }

    int nextInt() throws IOException {
        return Integer.parseInt(next());
    }

    String nextLine() throws IOException {
        return br.readLine();
    }

    static PrintWriter pw;
    static BufferedReader br;
    static StringTokenizer st;

    public static void main(String[] args) throws IOException {
        long timeout = System.currentTimeMillis();
        // br = new BufferedReader(new FileReader(new File(task_name + ".in")));
        // pw = new PrintWriter(new FileWriter(new File(task_name + ".out")));
        // while (br.ready())
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);
        new K().run();
        // System.out.println(System.currentTimeMillis() - timeout);
        br.close();
        pw.close();
    }
}
