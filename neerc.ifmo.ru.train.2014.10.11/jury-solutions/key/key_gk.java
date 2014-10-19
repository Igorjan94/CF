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

public class key_gk implements Runnable {
    static Scanner in;
    static PrintWriter out;

    public void run() {
        int n = in.nextInt();
        int m = in.nextInt();

        int[] a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = in.nextInt();
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

        Thread t = new Thread(new key_gk());
        t.start();
        t.join();

        in.close();
        out.close();
    }
}
