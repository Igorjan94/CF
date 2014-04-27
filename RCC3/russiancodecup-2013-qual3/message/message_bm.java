import java.io.*;
import java.util.*;

public class message_bm {
    FastScanner in;
    PrintWriter out;

    int mod = (int) 1e9 + 7;

    void solve() {
        int n = in.nextInt();
        for (int i = 0; i < n; i++) {
            String s = in.next();

            int ans = 1;
            for (int j = 0; j < s.length(); j++) {
                if (s.charAt(j) == '?')
                    ans = (ans * 2) % mod;
            }
            int norm = 1;
            for (int j = 0; j < s.length() / 2; j++) {
                char c1 = s.charAt(j);
                char c2 = s.charAt(j + s.length() / 2);
                if (c1 == '?' && c2 == '?') {
                    norm = (norm * 2) % mod;
                } else {
                    if (c1 != c2 && c1 != '?' && c2 != '?')
                        norm = 0;
                }
            }
            ans = (ans - norm + mod) % mod;
            out.println(ans);
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
        new message_bm().runIO();
    }
}