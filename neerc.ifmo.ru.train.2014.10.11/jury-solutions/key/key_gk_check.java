/*--------------------------------------------------------------*/
/* ACM ICPC 2008-2009, NEERC                                    */
/* Northern Subregional Contest                                 */
/* St Petersburg, November 1, 2008                              */
/*--------------------------------------------------------------*/
/* Problem K. Key to Success                                    */
/*                                                              */
/* Original idea         Andrew Stankevich                      */
/* Problem statement     Andrew Stankevich                      */
/* Testset               Andrew Stankevich                      */
/*--------------------------------------------------------------*/
/* Solution                                                     */
/*                                                              */
/* Author                Georgiy Korneev                        */
/*--------------------------------------------------------------*/
 
import java.util.*;
import java.io.*;

public class key_gk_check {
    static final int MAX_N = 30;
    static final int MAX_A = 1000000000;

    static Scanner in;
    static PrintWriter out;

    public void run() {
        int n = in.nextInt();
        assert 0 <= n && n <= MAX_N;

        int m = in.nextInt();
        assert 1 <= m && m <= MAX_N;

        int[] a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = in.nextInt();
            assert 0 <= a[i] && a[i] <= MAX_A;
        }
        Arrays.sort(a);

        long bound = 1;
        int j = 0;
        for (int i = 0; i < m; i++) {
            while (j < n && a[j] <= bound) {
                bound += (long) a[j];
                j++;
            }
            out.println(bound);
            bound *= 2;
        }
    }

    public static void main(String[] args) throws Exception {        
        in = new Scanner(new File("key.in"));
        out = new PrintWriter("key.out");

        new key_gk_check().run();

        in.close();
        out.close();
    }
}
