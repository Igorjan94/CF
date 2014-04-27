import java.io.*;
import java.util.*;

public class L {

    final static String task_name = "stdin";

    void run() throws IOException {
        int n = nextInt();
        long d = nextInt(), a = nextInt(), b = nextInt(), s = 0, m, cur, last = nextInt(), k = 0;
        boolean q = false;

        while (--n > 0) {
            //pw.println(d + " " + s);
            cur = nextInt();
            if (cur > last) {
                if (q) {
                    ++k;
                } else {
                    k = 1;
                    q = true;
                }

                m = Math.min(d / cur, a * k);
                d -= m * cur;
                s += m;

            } else if (cur < last) {

                if (q) {
                    k = 1;
                    q = false;
                } else {
                    ++k;
                }

                m = Math.min(s, b * k);
                d += m * cur;
                s -= m;
            }
            last = cur;
        }
        pw.println(d + " " + s);
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
        new L().run();
        // System.out.println(System.currentTimeMillis() - timeout);
        br.close();
        pw.close();
    }
}
