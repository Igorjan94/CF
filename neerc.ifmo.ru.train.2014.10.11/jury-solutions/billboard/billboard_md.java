/*--------------------------------------------------------------*/
/* ACM ICPC 2008-2009, NEERC                                    */
/* Northern Subregional Contest                                 */
/* St Petersburg, November 1, 2008                              */
/*--------------------------------------------------------------*/
/* Problem B. Billboard                                         */
/*                                                              */
/* Original idea         Georgiy Korneev                        */
/* Problem statement     Mikhail Dorkin                         */
/* Testset               Mikhail Dorkin                         */
/*--------------------------------------------------------------*/
/* Solution                                                     */
/*                                                              */
/* Author                Mikhail Dorkin                         */
/*--------------------------------------------------------------*/
 
import java.io.*;
import java.util.*;

public class billboard_md implements Runnable {
    private Scanner in;
    private PrintWriter out;
    
    private class SegmentsTree {
        int[] a;
        int two;
        
        public SegmentsTree(int[] data) {
            for (two = 1; two < data.length; two *= 2);
            a = new int[2 * two];
            for (int i = 0; i < data.length; i++) {
                a[two + i] = data[i];
            }
            for (int i = two - 1; i > 0; i--) {
                a[i] = Math.max(a[2 * i], a[2 * i + 1]);
            }
        }
        
        public int leftmostAtLeast(int value) {
            if (a[1] < value)
                return -1;
            int cur = 1;
            while (cur < two) {
                cur *= 2;
                if (a[cur] < value)
                    cur++;
            }
            return cur - two;
        }
        
        public int get(int index) {
            return a[two + index];
        }
        
        public void set(int index, int value) {
            int cur = two + index;
            a[cur] = value;
            while (cur > 1) {
                cur /= 2;
                a[cur] = Math.max(a[2 * cur], a[2 * cur + 1]);
            }
        }
    }

    public void solve() {
        int hei = in.nextInt();
        int wid = in.nextInt();
        int n = in.nextInt();
        int[] free = new int[Math.min(hei, n)];
        Arrays.fill(free, wid);
        SegmentsTree st = new SegmentsTree(free);
        for (int i = 0; i < n; i++) {
            int banner = in.nextInt();
            int pos = st.leftmostAtLeast(banner);
            if (pos == -1) {
                out.println(-1);
                continue;
            }
            out.println(pos + 1);
            st.set(pos, st.get(pos) - banner);
        }
    }
    
    @Override
    public void run() {
        try {
            in = new Scanner(new FileReader("billboard.in"));
            out = new PrintWriter(new File("billboard.out"));
            solve();
            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
    
    public static void main(String[] args) throws IOException {
        Locale.setDefault(Locale.US);
        new Thread(new billboard_md()).start();
    }
}
