
import java.io.*;
import java.util.*;
 
public class B {
    int n;
    String[] a, b;
 
    int get(String f, String t) {
        if (f.equals(t)) {
            return 0;
        }
 
        int min = 16;
        for (int i = 0; i < n; i++) {
            if (f.contains(a[i])) {
                String s = f.replace(a[i], b[i]);
                if (s.length() <= t.length()) {
                    min = Math.min(min, get(s, t));
                }
            }
        }
 
        return min + 1;
    }
 
    void run() {
        while (true) {
            n = nextInt();
            if (n == 0) {
                return;
            }
 
            a = new String[n];
            b = new String[n];
 
            for (int i = 0; i < n; i++) {
                a[i] = next();
                b[i] = next();
            }
            int ans = get(next(), next());
            out.println(ans > 10 ? -1 : ans);
        }
    }
 
    static StringTokenizer stringTokenizer;
    static BufferedReader bufferedReader;
    static PrintWriter out;
 
    int nextInt() {
        return Integer.parseInt(next());
    }
 
    String next() {
        while (stringTokenizer == null || !stringTokenizer.hasMoreTokens()) {
            stringTokenizer = new StringTokenizer(nextLine());
        }
        return stringTokenizer.nextToken();
    }
 
    String nextLine() {
        try {
            return bufferedReader.readLine();
        } catch (IOException e) {
            return "";
        }
    }
 
    public static void main(String[] args) throws IOException {
        bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        out = new PrintWriter(System.out);
        new B().run();
        bufferedReader.close();
        out.close();
    }
}