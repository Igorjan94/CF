import java.util.*;
import java.io.*;
import java.math.BigInteger;
 
import static java.lang.Math.*;
 
public class C {
    FastScanner in;
    PrintWriter out;
 
    final String inputName = null;
    final String outputName = null;
    final static Random rnd = new Random();
 
    public void solve() {
        char[] str = in.next().toLowerCase().toCharArray();
        char[] p = { 'p', 'e', 'r' };
        int n = str.length;
        int ans = 0;
 
        for (int i = 0; i < n; i++) {
            if (str[i] != p[i % 3]) {
                ++ans;
            }
        }
 
        out.println(ans);
 
    }
 
    public void run() {
        try {
 
            if (inputName == null) {
                in = new FastScanner(null);
            } else {
                in = new FastScanner(new File(inputName));
            }
 
            if (outputName == null) {
                out = new PrintWriter(System.out);
            } else {
                out = new PrintWriter(new File(outputName));
 
            }
 
            solve();
            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
 
    class FastScanner {
        BufferedReader br;
        StringTokenizer st;
 
        void close() throws IOException {
            br.close();
        }
 
        FastScanner(File f) {
            try {
                if (f == null) {
                    br = new BufferedReader(new InputStreamReader(System.in));
                } else {
                    br = new BufferedReader(new FileReader(f));
                }
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }
 
        long nextLong() {
            return Long.parseLong(next());
        }
 
        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }
 
        int nextInt() {
            return Integer.parseInt(next());
        }
    }
 
    public static void main(String[] arg) {
        new C().run();
    }
}
