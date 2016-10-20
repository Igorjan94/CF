import java.util.*;
import java.io.*;
 
import static java.lang.Math.*;
 
public class G {
 
    final static String input = "input.txt";
    final static String output = "output.txt";
 
    int[] zip(int[] array) {
        int[] sorted = array.clone();
        Arrays.sort(sorted);
        int m = 1, n = array.length;
 
        for (int i = 1; i < n; i++) {
            if (sorted[i - 1] != sorted[i]) {
                ++m;
            }
        }
 
        int[] zip = new int[m];
 
        zip[0] = sorted[0];
 
        for (int i = 1, j = 1; i < n; i++) {
            if (sorted[i - 1] != sorted[i]) {
                zip[j++] = sorted[i];
            }
        }
 
        return zip;
    }
 
    public void run() {
        int n = nextInt();
        int[] px = new int[n];
        int[] py = new int[n];
 
        int[] val = new int[n];
 
        for (int i = 0; i < n; i++) {
            px[i] = nextInt();
            py[i] = nextInt();
            val[i] = nextInt();
        }
 
        int[] vx = zip(px);
        int[] vy = zip(py);
 
        int m = vx.length, k = vy.length;
 
        int[] rx = new int[n], ry = new int[n];
 
        long[][] qsum = new long[m + 1][k + 1];
        long[][] sum = new long[m + 1][k + 1];
 
        for (int i = 0; i < n; i++) {
            rx[i] = Arrays.binarySearch(vx, px[i]);
            ry[i] = Arrays.binarySearch(vy, py[i]);
            qsum[rx[i] + 1][ry[i] + 1] += val[i];
        }
 
        for (int x = 1; x <= m; x++) {
            for (int y = 1; y <= k; y++) {
                sum[x][y] = qsum[x][y] + sum[x - 1][y] + sum[x][y - 1] - sum[x - 1][y - 1];
            }
        }
 
        int lt = -1, rt = -1, up = -1, dw = -1;
        long ans = Long.MIN_VALUE;
 
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
 
                int ax = max(rx[i], rx[j]) + 1;
                int ay = max(ry[i], ry[j]) + 1;
 
                int bx = min(rx[i], rx[j]) + 1;
                int by = min(ry[i], ry[j]) + 1;
 
                long cur = sum[ax][ay] - sum[bx - 1][ay] - sum[ax][by - 1] + sum[bx - 1][by - 1];
 
//              System.out.println(bx + " " + by);
//              System.out.println(ax + " " + ay);
//              System.out.println(cur);
//              System.out.println();
 
                if (cur > ans) {
                    ans = cur;
                    lt = vx[bx - 1];
                    dw = vy[by - 1];
 
                    rt = vx[ax - 1];
                    up = vy[ay - 1];
                }
 
            }
        }
 
        out.println(lt + " " + rt);
        out.println(dw + " " + up);
 
    }
 
    int nextInt() {
        return Integer.parseInt(next());
    }
 
    String nextLine() {
        try {
            return br.readLine();
        } catch (IOException e) {
            return null;
        }
    }
 
    String next() {
        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(nextLine());
        }
        return st.nextToken();
    }
 
    static PrintWriter out;
    static BufferedReader br;
    static StringTokenizer st;
 
    public static void main(String[] arg) throws IOException {
 
        if (input == null) {
            br = new BufferedReader(new InputStreamReader(System.in));
        } else {
            br = new BufferedReader(new FileReader(new File(input)));
        }
 
        if (output == null) {
            out = new PrintWriter(System.out);
        } else {
            out = new PrintWriter(new File(output));
        }
 
        new G().run();
        br.close();
        out.close();
 
    }
}