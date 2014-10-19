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
/* Author                Roman Satukov                          */
/*--------------------------------------------------------------*/
 
import java.io.*;
import java.util.*;

public class ground_rs implements Runnable {
    private final String problemID = getClass().getName().split("_")[0].toLowerCase();
    private static final double eps = 1e-9;
    private BufferedReader in;
    private PrintWriter out;
    private boolean[][] hilbert;
    private double tanAlpha;
    private int alpha;
    private long answer1, answer2, answer3;
    
    private static final int[] dx = { 1, 0, -1, 0 };
    private static final int[] dy = { 0, 1, 0, -1 };
    
    private void check(boolean expr, String message) {
        if (!expr) {
            throw new AssertionError(message);
        }
    }
    
    private void buildHilbert(int order, int x, int y, int d, boolean top) {
        if (order == 1) {
            hilbert[x][y] = top; 
            return;
        }
        int dd = (d + 1) % 4;
        int size = 1 << (order - 1);
        buildHilbert(order - 1, x, y, d, top);
        buildHilbert(order - 1, x + dx[d] * size, y + dy[d] * size, d, top);
        buildHilbert(order - 1, x + dx[d] * (size - 2) + dx[dd] * size, y + dy[d] * (size - 2) + dy[dd] * size, (d + 1) % 4, !top);
        buildHilbert(order - 1, x + dx[d] * size + dx[dd] * (size + size - 2), y + dy[d] * size + dy[dd] * (size + size - 2), (d + 3) % 4, !top);
        if (top) {
            int xx = x + dx[dd] * (size - 1);
            int yy = y + dy[dd] * (size - 1);
            for (int i = 0; i < size + size - 1; i++) {
                hilbert[xx][yy] = true;
                xx += dx[d];
                yy += dy[d];
            }
            xx = x + dx[d] * (size - 1) + dx[dd] * (size - 1);
            yy = y + dy[d] * (size - 1) + dy[dd] * (size - 1);
            for (int i = size - 1; i < size + size - 1; i++) {
                hilbert[xx][yy] = true;
                xx += dx[dd];
                yy += dy[dd];
            }
        } else {
            int xx = x + dx[d] * (size - 1);
            int yy = y + dy[d] * (size - 1);
            for (int i = 0; i < size - 1; i++) {
                hilbert[xx][yy] = true;
                xx += dx[dd];
                yy += dy[dd];
            }
        }
    }

    // depth = u + tanAlpha * v
    private void calcTriangle(int u, int v, int sign) {
        double depth = u + tanAlpha * v;
        if (depth < eps) {
            return;
        }
        answer1 += sign * v * v;
        answer2 += sign * 2 * u * v;
        answer3 += sign * u * u;
    }
    
    private void calcVolume(int u, int v) {
        calcTriangle(u, v, +1);
        calcTriangle(u - 1, v, -1);
        calcTriangle(u, v - 1, -1);
    }

    // depth = u + tanAlpha * v
    private void process(int x, int y, int d, int u, int v) {
        if (x < 0 || y < 0 || x >= hilbert.length || y >= hilbert.length || !hilbert[x][y]) {
            return;
        }
        double depth = u + tanAlpha * v;
        if (depth > 1 + tanAlpha) {
            depth = 1 + tanAlpha;
            u = v = 1;
        }
        if (depth < eps) {
            return;
        }
        calcVolume(u, v);
        for (int dir = 0; dir < 4; dir++) {
            if (dir == d) {
                continue;
            }
//            process(x + dx[dir], y + dy[dir], (dir + 2) % 4, depth + dx[dir] * tanAlpha - dy[dir]);
            process(x + dx[dir], y + dy[dir], (dir + 2) % 4, u - dy[dir], v + dx[dir]);
        }
    }

    private void solve() throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(st.nextToken());
        alpha = Integer.parseInt(st.nextToken());
        check((1 <= n) && (n <= 12), "n is not in [1..12]");
        check((0 <= alpha) && (alpha <= 89), "alpha is not in [0..89]");
        tanAlpha = Math.tan(alpha * Math.PI / 180.0);
        
        hilbert = new boolean[(1 << n) - 1][(1 << n) - 1];
        buildHilbert(n, 0, 0, 0, true);
        int top = (1 << n) - 2;
        for (int i = 0; i <= top; i++) {
            if (hilbert[i][top]) {
                process(i, top, 1, 1, 0);
            }
        }
        double volume;
        if (alpha == 0) {
             volume = (answer1 * tanAlpha + answer2) / 2;
        } else {
             volume = (answer1 * tanAlpha + answer2 + answer3 / tanAlpha) / 2;
        }
        out.println(volume);
    }

    public void run() {
        try {
            in = new BufferedReader(new FileReader(new File(problemID + ".in")));
            out = new PrintWriter(new File(problemID + ".out"));
            solve();
            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
    
    public static void main(String[] args) {
        new Thread(new ground_rs()).start();
    }
}
