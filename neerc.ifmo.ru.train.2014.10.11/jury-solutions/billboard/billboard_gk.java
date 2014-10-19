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
/* Author                Georgiy Korneev                        */
/*--------------------------------------------------------------*/
 
import java.util.*;
import java.io.*;

public class billboard_gk {
    static Scanner in;
    static PrintWriter out;

    public void run() {
        int height = in.nextInt();
        int width = in.nextInt();
        int n = in.nextInt();

        height = Math.min(height, n);
        int m = 1;
        while (m < height) {
            m *= 2;
        }

        int[] tree = new int[2 * m];
        for (int i = 0; i < height; i++) {
            tree[m + i] = width;
        }
        for (int i = tree.length / 2 - 1; i > 0; i--) {
            tree[i] = tree[i * 2];
        }

        for (int i = 0; i < n; i++) {
            int w = in.nextInt();
            if (tree[1] >= w) {
                int p = 1;
                while (p < m) {
                    assert (tree[p] >= w);
                    p *= 2;
                    if (tree[p] < w) {
                        p++;
                    }
                }
                out.println(p - m + 1);
                tree[p] -= w;
                while (p > 1) {
                    p /= 2;                    
                    tree[p] = Math.max(tree[2 * p], tree[2 * p + 1]);
                }
            } else {
                out.println(-1);
            }
        }
    }

    public static void main(String[] args) throws Exception {        
        in = new Scanner(new File("billboard.in"));
        out = new PrintWriter("billboard.out");

        new billboard_gk().run();

        in.close();
        out.close();
    }
}
