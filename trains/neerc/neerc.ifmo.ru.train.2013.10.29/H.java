import java.io.*;
import java.util.*;

public class H {

    final static String task_name = "stdin";

    void run() throws IOException {
        int h = nextInt();
        char[] q = next().toCharArray();
        int m = q.length + 1;
        int[] ans = new int[m];
        int l = 1;
        int d = 0;

        for (int i = 1, c = 1; i < m; i++) {
            if (q[i - 1] == '>') {
                if (d == -1) {
                    ++c;
                } else {
                    c = 2;
                    d = -1;
                }
            } else if (q[i - 1] == '<') {
                if (d == 1) {
                    ++c;
                } else {
                    c = 2;
                    d = 1;
                }
            }
            if (c > l) {
                l = c;
            }
        }

        if (l > h) {
            pw.println(-1);
            return;
        }

        d = 0;
        for (int i = 1; i < m && d == 0; i++) {
            if (q[i - 1] == '>') {
                d = -1;
            } else if (q[i - 1] == '<') {
                d = 1;
            }

        }

        if (d == 0) {
            Arrays.fill(ans, 1);
        } else {
            ans[0] = (d == 1) ? 1 : l;
            int x = 1;
            while (x < m) {
                int y, z;
                for (y = x; y < m; y++) {
                    if (d == 1 && q[y - 1] == '>') {
                        break;
                    }
                    if (d == -1 && q[y - 1] == '<') {
                        break;
                    }
                }

                --y;

                for (z = x; z <= y; z++) {
                    if (q[z - 1] != '=') {
                        break;
                    }
                }

                //pw.println(d + " " + x + " " + z + " " + y);

                if (d == 1) {
                    ans[y] = l;
                    for (int i = y - 1; i >= z; i--) {
                        if (q[i] != '=') {
                            ans[i] = ans[i + 1] - 1;
                        } else {
                            ans[i] = ans[i + 1];
                        }
                    }
                    for (int i = x; i < z; i++) {
                        if (q[i - 1] != '=') {
                            ans[i] = ans[i - 1] + 1;
                        } else {
                            ans[i] = ans[i - 1];
                        }
                    }

                    d = -1;
                } else {

                    ans[y] = 1;
                    for (int i = y - 1; i >= z; i--) {
                        if (q[i] != '=') {
                            ans[i] = ans[i + 1] + 1;
                        } else {
                            ans[i] = ans[i + 1];
                        }
                    }
                    for (int i = x; i < z; i++) {
                        if (q[i - 1] != '=') {
                            ans[i] = ans[i - 1] - 1;
                        } else {
                            ans[i] = ans[i - 1];
                        }
                    }

                    d = 1;
                }

                x = y + 1;
            }

        }

        for (int a : ans) {
            pw.print((char) (a + 96));
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
        new H().run();
        // System.out.println(System.currentTimeMillis() - timeout);
        br.close();
        pw.close();
    }
}
