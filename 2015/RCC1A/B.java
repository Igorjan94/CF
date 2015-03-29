import java.util.*;
import java.io.*;
import java.math.*;

public class Template {
    FastScanner in;
    PrintWriter out;

    public void solve() throws IOException {
        BigInteger x = new BigInteger(in.next());
        BigInteger y = new BigInteger(in.next());
        BigInteger z = new BigInteger(in.next());
        System.out.println(x.multiply(y).equals(z) ? "Infinity" : "Finite");       
    }

    public void run() {
        try {
            in = new FastScanner();
            int i = in.nextInt();
            while (i --> 0)
                solve();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    class FastScanner {
        BufferedReader br;
        StringTokenizer st;

        FastScanner() {
            try {
                br = new BufferedReader(new InputStreamReader(System.in));
            } catch (Exception e) {
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
        new Template().run();
    }
}
