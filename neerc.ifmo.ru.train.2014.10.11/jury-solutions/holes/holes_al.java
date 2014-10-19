/*--------------------------------------------------------------*/
/* ACM ICPC 2008-2009, NEERC                                    */
/* Northern Subregional Contest                                 */
/* St Petersburg, November 1, 2008                              */
/*--------------------------------------------------------------*/
/* Problem H. Holes                                             */
/*                                                              */
/* Original idea         Jury                                   */
/* Problem statement     Dmitry Shtukenberg                     */
/* Testset               Dmitry Shtukenberg                     */
/*--------------------------------------------------------------*/
/* Solution                                                     */
/*                                                              */
/* Author                Andrew Lopatin                         */
/*--------------------------------------------------------------*/
 
import java.util.*;
import java.io.*;

public class holes_al {
  static final int MaxN = 510;
  static int rInt (String s, int a, int b) {
    int x = Integer.parseInt (s);
    if (x < a || x > b) throw new RuntimeException (x + " is not within " + a + ".." + b);
    return x;
  };
  public static void main (String args []) throws Exception {
    Scanner in = new Scanner (new File ("holes.in"));
    PrintWriter out = new PrintWriter ("holes.out");
    int n = rInt (in.next (), 0, MaxN);
    if (in.hasNext ()) throw new Exception ("EOF expected");
    if (n == 0) out.println (1); else 
    if (n == 1) out.println (0); else {
      if (n % 2 == 1) {
        out.print (4);
        --n;
      };
      for (int i = 0; i < (n >> 1); i++)
        out.print (8);
      out.println ();
    };

    out.close ();
  };
};