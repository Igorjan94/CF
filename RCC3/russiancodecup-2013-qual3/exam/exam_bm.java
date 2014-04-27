import java.io.*;
import java.util.*;

public class exam_bm {
    FastScanner in;
    PrintWriter out;

    int s(String s) {
        String[] tmp = s.split(":");
        return Integer.parseInt(tmp[0]) * 60 * 60 + Integer.parseInt(tmp[1])
                * 60 + Integer.parseInt(tmp[2]);
    }

    void solve() {
        int n = in.nextInt();
        for (int i = 0; i < n; i++) {
            int t1 = s(in.next());
            int t2 = s(in.next());
            if (t2 <= t1)
                t2 += 60 * 60 * 24;
            t1 += in.nextInt() * 60;
            if (t1 <= t2) {
                out.println("Perfect");
            } else {
                if (t1 - 60 * 60 <= t2) {
                    out.println("Test");
                } else {
                    out.println("Fail");
                }
            }
        }
    }

    void run() {
        try {
            in = new FastScanner(new File("object.in"));
            out = new PrintWriter(new File("object.out"));

            solve();

            out.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    void runIO() {

        in = new FastScanner(System.in);
        out = new PrintWriter(System.out);

        solve();

        out.close();
    }

    class FastScanner {
        BufferedReader br;
        StringTokenizer st;

        public FastScanner(File f) {
            try {
                br = new BufferedReader(new FileReader(f));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }

        public FastScanner(InputStream f) {
            br = new BufferedReader(new InputStreamReader(f));
        }

        String next() {
            while (st == null || !st.hasMoreTokens()) {
                String s = null;
                try {
                    s = br.readLine();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                if (s == null)
                    return null;
                st = new StringTokenizer(s);
            }
            return st.nextToken();
        }

        boolean hasMoreTokens() {
            while (st == null || !st.hasMoreTokens()) {
                String s = null;
                try {
                    s = br.readLine();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                if (s == null)
                    return false;
                st = new StringTokenizer(s);
            }
            return true;
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        long nextLong() {
            return Long.parseLong(next());
        }
    }

    public static void main(String[] args) {
        new exam_bm().runIO();
    }
}