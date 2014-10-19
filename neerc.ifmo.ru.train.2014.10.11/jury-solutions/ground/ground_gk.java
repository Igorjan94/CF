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
/* Author                Georgiy Korneev                        */
/*--------------------------------------------------------------*/
 
import java.util.*;
import java.io.*;

public class ground_gk implements Runnable {
    static Scanner in;
    static PrintWriter out;
    static final double EPS = 1e-10;
    
    boolean[][] hole;
    int size;
    double result;
    double maxh;
    double cos;
    double sin;
    int alpha;

    double part(double h, double base) {
        double dh = h - base;
        return dh > 0 ? dh * dh : 0;
    }

    void flood(int x, int y, double h) {
        if (x < 0 || x >= size || y < 0 || y >= size || !hole[x][y]) {
            return;
        }
        hole[x][y] = false;
        if (h < EPS) {
            return;
        }
        h = Math.min(h, maxh);

        result += alpha == 0 ? 1 : part(h, 0) - part(h, cos) - part(h, sin);
        
        flood(x - 1, y, h + sin);
        flood(x + 1, y, h - sin);
        flood(x, y - 1, h - cos);
        flood(x, y + 1, h + cos);
    }

    public void run() {
        int n = in.nextInt();
        alpha = in.nextInt();
        double angle = alpha * Math.PI / 180;

        hole = new boolean[0][0];
        size = 0;

        for (int i = 0; i < n; i++) {
            boolean[][] next = new boolean[2 * size + 1][2 * size + 1];

            for (int x = 0; x < size; x++) {
                for (int y = 0; y < size; y++) {
                    next[x][size + y + 1] = hole[x][y];
                    next[x + size + 1][y + size + 1] = hole[x][y];
                    next[x][y] = !hole[y][x];
                    next[x + size + 1][y] = !hole[y][size - x - 1];
                    next[size][y] = true;
                }
            }
            for (int x = 0; x < next.length; x++) {
                next[x][size] = true;
            }
            hole = next;
            size = 2 * size + 1;
        }

        cos = Math.cos(angle);
        sin = Math.sin(angle);
        maxh = Math.sqrt(2) * Math.cos(Math.PI / 4 - angle);
        double toph = cos;

        for (int x = 0; x < size; x++) {
            flood(x, 0, toph);
        }
        out.println(alpha == 0 ? result : result / cos / sin / 2);
    }

    public static void main(String[] args) throws Exception {        
        in = new Scanner(new File("ground.in"));
        out = new PrintWriter("ground.out");

        Thread t = new Thread(new ground_gk());
        t.start();
        t.join();

        in.close();
        out.close();
    }
}
