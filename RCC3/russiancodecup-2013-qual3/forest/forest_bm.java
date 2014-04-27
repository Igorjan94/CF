import java.io.*;
import java.util.*;

public class forest_bm {
    FastScanner in;
    PrintWriter out;

    int magic = 3;
    
    int[] getInteresting(int w) {
        TreeSet<Integer> res = new TreeSet<>();
        for (int i = 0; i < magic; i++)
            if (i < w)
                res.add(i);
        for (int i = w - magic; i <= w; i++)
            if (i >= 0)
                res.add(i);
        int[] result = new int[res.size()];
        int it = 0;
        for (int x : res) {
            result[it++] = x;
        }
        return result;
    }
    
    int[] dx = {-1, 0, 0, 1};
    int[] dy = {0, -1, 1, 0};

    int neCount(int x, int y, int n, int m) {
        int res = 0;
        for (int i= 0; i < dx.length; i++)
            if (x + dx[i] >= 0 && x + dx[i] < n)
                if (y + dy[i] >= 0 && y + dy[i] < m)
                    res++;
        return res;
    }
    
    long getAnsw(int x, int y, int n, int m) {
        long ans = 12 * 12 * 12 * 12;
        long tmp = ans;
        for (int i= 0; i < dx.length; i++)
            if (x + dx[i] >= 0 && x + dx[i] < n)
                if (y + dy[i] >= 0 && y + dy[i] < m) {
                    int cnt = neCount(x + dx[i], y + dy[i], n, m);
                    ans /= cnt;
                    ans *= (cnt - 1);
                }
        return tmp - ans;
    }

    long vv = 20736;
    
    long gcd(long x, long y) {
        return x == 0 ? y : gcd(y % x, x);
    }
    
    void solve() {
        int testN = in.nextInt();
        for (int test = 0; test < testN; test++) {
            int n = in.nextInt();
            int m = in.nextInt();
            int[] xx = getInteresting(n);
            int[] yy = getInteresting(m);
            long answ = 0;
            for (int i = 0; i < xx.length - 1; i++)
                for (int j = 0; j < yy.length - 1; j++) {
                    long s = (xx[i + 1] - xx[i]) * 1L * (yy[j + 1] - yy[j]);
                    answ += s * getAnsw(xx[i], yy[j], n, m);
                }
            long answ2 = vv;
            long g = gcd(answ, answ2);
            answ /= g;
            answ2 /= g;
            out.print(answ);
            if (answ2 == 1) {
                out.println();
            } else {
                out.println("/" + answ2);
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
        new forest_bm().runIO();
    }
}