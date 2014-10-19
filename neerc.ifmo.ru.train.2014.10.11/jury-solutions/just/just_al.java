/*--------------------------------------------------------------*/
/* ACM ICPC 2008-2009, NEERC                                    */
/* Northern Subregional Contest                                 */
/* St Petersburg, November 1, 2008                              */
/*--------------------------------------------------------------*/
/* Problem J. Just Too Lucky                                    */
/*                                                              */
/* Original idea         Andrew Stankevich, Fedor Tsarev        */
/* Problem statement     Andrew Stankevich                      */
/* Testset               Andrew Stankevich                      */
/*--------------------------------------------------------------*/
/* Solution                                                     */
/*                                                              */
/* Author                Andrew Lopatin                         */
/*--------------------------------------------------------------*/
 
import java.util.*;
import java.io.*;

public class just_al {
  static final long MaxN = (long)1e12;

  static long rLong (String s, long a, long b) {
    long x = Long.parseLong (s);
    if (x < a || x > b) throw new RuntimeException (x + " is not within " + a + ".." + b);
    return x;
  };

  public static void main (String [] args) throws Exception {
    BufferedReader in = new BufferedReader (new FileReader ("just.in"));
    PrintWriter out = new PrintWriter ("just.out");
    long n = rLong (in.readLine (), 1, MaxN);

    String s = "" + n;

    int m = s.length ();
    long ans = 0;

    for (int j = 1; j <= 9 * m; j++) {
      long [][][] D = new long [m + 1][j][j + 1];
      int eq = 1, ek = 0, el = 0;
      for (int i = 0; i < m; i++) {
        for (int k = 0; k < j; k++)
          for (int l = 0; l <= j; l++) {
            int alim = Math.min (9, j - l);
            for (int a = 0, nk = (k * 10) % j; a <= alim; a++, nk++) {
              if (nk >= j) nk -= j;
              D[i + 1][nk][l + a] += D[i][k][l];
            };
          };
        int cd = s.charAt (i) - '0', alim = Math.min (cd - 1, j - el);
        for (int a = 0, nk = (ek * 10) % j; a <= alim; a++, nk++) {
          if (nk >= j) nk -= j;
          D[i + 1][nk][el + a] += eq;
        };
        if (el + cd > j) eq = 0; else {
          ek = (ek * 10 + cd) % j;
          el += cd;
        };
      };
      ans += D[m][0][j];
      if (eq > 0 && ek == 0 && el == j) ++ans;
    };

    out.println (ans);

    out.close ();
  };
};