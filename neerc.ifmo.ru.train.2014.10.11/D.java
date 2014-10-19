import java.util.*;
import java.io.*;
 
public class D {
 
    final static String taskName = "deposits";
 
    public void solve() {
        int k = 1000001;
 
        long[] a = new long[k], b = new long[k];
 
        int n = in.nextInt();
        while (--n >= 0) {
            ++a[in.nextInt()];
        }
        int m = in.nextInt();
        while (--m >= 0) {
            ++b[in.nextInt()];
        }
 
        long ans = 0;
 
        for (int i = 1; i < k; i++) {
            for (int j = i; j < k; j += i) {
                ans += b[i] * a[j];
 
            }
        }
 
        out.println(ans);
    }
 
    public void run() {
        try {
            in = new FastScanner(new File(taskName + ".in"));
            out = new PrintWriter(new File(taskName + ".out"));
 
            solve();
 
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
 
    FastScanner in;
    PrintWriter out;
 
    class FastScanner {
        BufferedReader br;
        StringTokenizer st;
 
        FastScanner(File f) {
            try {
                br = new BufferedReader(new FileReader(f));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
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
        new D().run();
    }
}