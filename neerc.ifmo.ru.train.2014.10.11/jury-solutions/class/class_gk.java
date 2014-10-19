/*--------------------------------------------------------------*/
/* ACM ICPC 2008-2009, NEERC                                    */
/* Northern Subregional Contest                                 */
/* St Petersburg, November 1, 2008                              */
/*--------------------------------------------------------------*/
/* Problem C. Class                                             */
/*                                                              */
/* Original idea         Georgiy Korneev                        */
/* Problem statement     Georgiy Korneev                        */
/* Testset               Georgiy Korneev                        */
/*--------------------------------------------------------------*/
/* Solution                                                     */
/*                                                              */
/* Author                Georgiy Korneev                        */
/*--------------------------------------------------------------*/
 
import java.util.*;
import java.io.*;

public class class_gk {
    static Scanner in;
    static PrintWriter out;

    boolean[][] ans;
    int n;

    private void occupy(int r, int c) {
        if (!ans[r][c] && n > 0) {
            ans[r][c] = true;
            n--;
        }
    }

    public void run() {
        n = in.nextInt();
        int r = in.nextInt();
        int c = in.nextInt();

        int target = Math.min((n + 1) / 2, Math.min(r, c));
        ans = new boolean[r][c];

        for (int i = 0; i < target; i++) {
            occupy(0, i);
            occupy(i, 0);
        }

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                occupy(i, j);
            }
        }

        out.println(target);
        for (boolean[] row : ans) {
            for (boolean desk : row) {
                out.print(desk ? '#' : '.');
            }
            out.println();
        }
    }

    public static void main(String[] args) throws Exception {        
        in = new Scanner(new File("class.in"));
        out = new PrintWriter("class.out");

        new class_gk().run();

        in.close();
        out.close();
    }
}
