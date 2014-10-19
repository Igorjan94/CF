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
/* Author                Andrew Lopatin                         */
/*--------------------------------------------------------------*/
 
import java.util.*;
import java.io.*;

public class key_al {
  static final int MaxMN = 30;
  static final int MaxV = (int)1e9;
  static int rInt (String s, int a, int b) {
    int x = Integer.parseInt (s);
    if (x < a || x > b) throw new RuntimeException (x + " is not within " + a + ".." + b);
    return x;
  };
  public static void main (String args []) throws Exception {
    BufferedReader in = new BufferedReader (new FileReader ("key.in"));
    PrintWriter out = new PrintWriter ("key.out");

    StringTokenizer t = new StringTokenizer (in.readLine ());
    int n = rInt (t.nextToken (), 0, MaxMN);
    int m = rInt (t.nextToken (), 1, MaxMN);
    if (t.hasMoreTokens ()) throw new Exception ("EOL expected");

    t = new StringTokenizer (in.readLine ());
    int [] a = new int [n];
    for (int i = 0; i < n; i++)
      a[i] = rInt (t.nextToken (), 1, MaxV);
    if (t.hasMoreTokens ()) throw new Exception ("EOL expected");
    if (in.ready ()) throw new Exception ("EOF expected");

    Arrays.sort (a);

    long msum = 1;
    int apos = 0, bcnt = 0;
    while (bcnt < m) {
      if (apos == n || msum < a[apos]) {
        out.print (msum + " ");
        ++bcnt;
        msum += msum;
      } else {
        msum += a[apos++];
      };
    };

    out.close ();
  };
};