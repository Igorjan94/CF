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
/* Author                Andrew Lopatin                         */
/*--------------------------------------------------------------*/
 
import java.util.*;
import java.io.*;

public class billboard_al {
  static final int MaxWH = (int)1e9;
  static final int MaxN = 200000;
  static final int TSize = 1 << 19, TShift = TSize >> 1;

  static int rInt (String s, int a, int b) {
    int x = Integer.parseInt (s);
    if (x < a || x > b) throw new RuntimeException (x + " is not within " + a + ".." + b);
    return x;
  };

  public static void main (String args []) throws Exception {
    BufferedReader in = new BufferedReader (new FileReader ("billboard.in"));
    PrintWriter out = new PrintWriter ("billboard.out");
    StringTokenizer t = new StringTokenizer (in.readLine ());
    int h = rInt (t.nextToken (), 1, MaxWH);
    int w = rInt (t.nextToken (), 1, MaxWH);
    int n = rInt (t.nextToken (), 1, MaxN);
    if (t.hasMoreTokens ()) throw new Exception ("EOL expected");

    int [] D = new int [TSize];

    for (int i = 0; i < Math.min (h, MaxN); i++)
      D[TShift + i] = w;

    for (int i = TShift - 1; i > 0; i--)
      D[i] = Math.max (D[2 * i], D[2 * i + 1]);

    for (int i = 0; i < n; i++) {
      int q = rInt (in.readLine (), 1, MaxWH);
      if (q > D[1]) out.println (-1); else {
        int x;
        for (x = 1; x < TShift; ) {
          x *= 2;
          if (q > D[x]) ++x;
        };
        out.println (x - TShift + 1);
        D[x] -= q;
        for (x >>= 1; x > 0; x >>= 1)
          D[x] = Math.max (D[2 * x], D[2 * x + 1]);
      };
    };
    if (in.ready ()) throw new Exception ("EOF expected");

    out.close ();
  };
};
