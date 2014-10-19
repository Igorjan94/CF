/*--------------------------------------------------------------*/
/* ACM ICPC 2008-2009, NEERC                                    */
/* Northern Subregional Contest                                 */
/* St Petersburg, November 1, 2008                              */
/*--------------------------------------------------------------*/
/* Problem D. Deposits                                          */
/*                                                              */
/* Original idea         Roman Satukov                          */
/* Problem statement     Andrew Stankevich                      */
/* Testset               Andrew Stankevich                      */
/*--------------------------------------------------------------*/
/* Solution                                                     */
/*                                                              */
/* Author                Andrew Lopatin                         */
/*--------------------------------------------------------------*/
 
import java.util.*;
import java.io.*;

public class deposits_al {
  static final int MaxV = (int)1e6;
  static final int MaxNM = (int)1e5;
  static int rInt (String s, int a, int b) {
    int x = Integer.parseInt (s);
    if (x < a || x > b) throw new RuntimeException (x + " is not within " + a + ".." + b);
    return x;
  };
  public static void main (String args []) throws Exception {
    BufferedReader in = new BufferedReader (new FileReader ("deposits.in"));
    PrintWriter out = new PrintWriter ("deposits.out");

    int n = rInt (in.readLine (), 1, MaxNM);
    StringTokenizer t = new StringTokenizer (in.readLine ());

    int [] a = new int [n];

    for (int i = 0; i < n; i++)
      a[i] = rInt (t.nextToken (), 1, MaxV);

    if (t.hasMoreTokens ()) throw new Exception ("EOL expected");

    int m = rInt (in.readLine (), 1, MaxNM);
    t = new StringTokenizer (in.readLine ());
    int [] b = new int [m];
    int [] f = new int [MaxV + 1];

    for (int i = 0; i < m; i++) {
      b[i] = rInt (t.nextToken (), 1, MaxV);
      ++f[b[i]];
    };

    if (t.hasMoreTokens ()) throw new Exception ("EOL expected");
    if (in.ready ()) throw new Exception ("EOF expected");

    for (int i = MaxV; i >= 1; i--) {
      for (int j = i + i; j <= MaxV; j += i)
        f[j] += f[i];
    };

    long ans = 0;
    for (int k = 0; k < n; k++)
      ans += f[a[k]];

    out.println (ans);

    out.close ();
  };
};