import java.util.*;
import java.io.*;
 
public class K {
 
    final static String taskName = "key";
 
    long min(List<Long> cur) {
        long f = 0, t = 0;
 
        Collections.sort(cur);
 
        for (long l : cur) {
            long nf = l + f;
            long nt = l + t;
 
            if (t + 1 < nf) {
                return t + 1;
            }
            t = nt;
 
        }
 
        return t + 1;
    }
 
    public void solve() {
        int n = in.nextInt(), m = in.nextInt();
        List<Long> cur = new ArrayList<Long>(n + m);
        List<Long> ans = new ArrayList<Long>(m);
        while (--n >= 0) {
            cur.add((long) in.nextInt());
        }
 
        while (--m >= 0) {
            long a = min(cur);
            cur.add(a);
            ans.add(a);
        }
 
        for (long l : ans) {
            out.print(l + " ");
        }
 
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
        new K().run();
    }
}