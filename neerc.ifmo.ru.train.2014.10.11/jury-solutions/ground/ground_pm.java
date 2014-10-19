/*--------------------------------------------------------------*/
/* ACM ICPC 2008-2009, NEERC                                    */
/* Northern Subregional Contest                                 */
/* St Petersburg, November 1, 2008                              */
/*--------------------------------------------------------------*/
/* Problem G. Ground Works                                      */
/*                                                              */
/* Original idea         Iskander Akishev                       */
/* Problem statement     Pavel Mavrin                           */
/* Testset               Pavel Mavrin                           */
/*--------------------------------------------------------------*/
/* Solution                                                     */
/*                                                              */
/* Author                Pavel Mavrin                           */
/*--------------------------------------------------------------*/
 
import java.util.*;
import java.io.*;

public class ground_pm {
    static Scanner in;
    static PrintWriter out;

    int n;
    int a;
    double ha;
    double hb;
    double hc;

    boolean[][] b;

    private static final double EPS = 1e-10;

    private boolean[][] build(int n) {
        if (n == 1) {
            boolean[][] res = new boolean[1][1];
            res[0][0] = true;
            return res;
        } else {
            boolean[][] r = build(n - 1);
            int k = r.length;
            boolean[][] res = new boolean[2 * k + 1][2 * k + 1];
            for (int i = 0; i < k; i++) {
                for (int j = 0; j < k; j++) {
                    res[i][j] = !r[j][i];
                }
            }
            for (int i = 0; i < k; i++) {
                for (int j = 0; j < k; j++) {
                    res[i + k + 1][j] = !r[j][k - i - 1];
                }
            }
            for (int i = 0; i < k; i++) {
                for (int j = 0; j < k; j++) {
                    res[i][j + k + 1] = r[i][j];
                }
            }
            for (int i = 0; i < k; i++) {
                for (int j = 0; j < k; j++) {
                    res[i + k + 1][j + k + 1] = r[i][j];
                }
            }
            for (int i = 0; i < k; i++) res[k][i] = true;
            for (int i = 0; i < 2 * k + 1; i++) res[i][k] = true;
            return res;
        }
    }

    private double fill(int x, int y, int p, double h) {
        if (x < 0 || x >= b.length || y < 0 || y >= b.length || !b[x][y] || h <= EPS) return 0;
        if (h > hc) h = hc;

        double res;
        if (ha == 0) {
            res = 1;
        } else {
            res = h * h / (ha * hb);
            if (h > ha) res -= (h - ha) * (h - ha) / (ha * hb);
            if (h > hb) res -= (h - hb) * (h - hb) / (ha * hb);
            res *= 0.5;
        }

        if (p != 2) res += fill(x - 1, y, 1, h + ha);
        if (p != 1) res += fill(x + 1, y, 2, h - ha);
        if (p != 4) res += fill(x, y - 1, 3, h - hb);
        if (p != 3) res += fill(x, y + 1, 4, h + hb);
        return res;
    }

    public void run() {
        n = in.nextInt();
        a = in.nextInt();
        double alpha = (a * Math.PI / 180);
        ha = Math.sin(alpha);
        hb = Math.cos(alpha);
        hc = Math.cos(Math.PI / 4 - alpha) * Math.sqrt(2);

        //System.out.println("" + ha + " " + hb + " " + hc);
        
        b = build(n);

        //for (int i = 0; i < b.length; i++) {
        //    for (int j = 0; j < b.length; j++) {
        //        System.out.print(b[j][i] ? "." : "#");
        //    }
        //    System.out.println();
        //}

        double res = 0;

        for (int i = 0; i < b.length; i++) {
            if (b[i][0]) {
                res += fill(i, 0, 0, hb);
            }
        }

        out.println(res);
    }

    public static void main(String[] args) throws Exception {        
        in = new Scanner(new File("ground.in"));
        out = new PrintWriter("ground.out");

        new ground_pm().run();

        in.close();
        out.close();
    }
}
