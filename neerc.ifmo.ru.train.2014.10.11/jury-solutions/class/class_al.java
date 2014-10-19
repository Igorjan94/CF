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
/* Author                Andrew Lopatin                         */
/*--------------------------------------------------------------*/
 
import java.util.*;
import java.io.*;

public class class_al {
  static final int MaxRC = 100;
  public static void main (String args []) throws Exception {
    Scanner in = new Scanner (new File ("class.in"));
    PrintWriter out = new PrintWriter ("class.out");
    int n = in.nextInt ();
    int r = in.nextInt ();
    int c = in.nextInt ();
    if (n < 1 || n > r * c || r < 1 || r > MaxRC || c < 1 || c > MaxRC)
      throw new Exception ("invalid combination of n = " + n +", r = " + r + " and c = " + c);
    if (in.hasNext ()) throw new Exception ("EOF expected");
    boolean [][] f = new boolean [r][c];
    f[0][0] = true;
    int p = 1; 
    --n;
    while (n > 0 && p < Math.min (r, c)) {
      f[p][0] = true;
      --n;
      if (n == 0) break;
      f[0][p] = true;
      ++p;
      --n;
    };
    out.println (p);
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++)
        if (f[i][j]) out.print ("#"); else {
          if (n == 0) out.print ("."); else {
            --n;
            out.print ("#");
          };
        };
      out.println ();
    };
    out.close ();
  };

};