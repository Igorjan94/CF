/*--------------------------------------------------------------*/
/* ACM ICPC 2008-2009, NEERC                                    */
/* Northern Subregional Contest                                 */
/* St Petersburg, November 1, 2008                              */
/*--------------------------------------------------------------*/
/* Problem E. Enchanted Mirror                                  */
/*                                                              */
/* Original idea         Andrew Lopatin                         */
/* Problem statement     Andrew Lopatin                         */
/* Testset               Andrew Lopatin                         */
/*--------------------------------------------------------------*/
/* Solution                                                     */
/*                                                              */
/* Author                Andrew Lopatin                         */
/*--------------------------------------------------------------*/
 
import java.util.*;
import java.io.*;

public class enchanted_al {
  static final int MaxL = 100;

  static BufferedReader in;
  static int cnt [][] = new int [26][26];

  static String getLine () throws Exception {
    String r = in.readLine ();
    if (r.length () == 0 || r.length () > MaxL)
      throw new Exception ("Bad length: " + r.length ());
    for (int i = 0; i < r.length (); i++)
      if (r.charAt (i) < 'A' || r.charAt (i) > 'Z')
        throw new Exception ("Bad character: " + r.charAt (i));
    return r;
  };

  static int twoLines (int inc) throws Exception {
    String s1 = getLine ();
    String s2 = getLine ();
    int n = s1.length ();
    if (s2.length () != s1.length ())
      throw new Exception ("non-equal lengths " + s1.length () + " and " + s2.length ());
    for (int i = 0; i < n; i++)
      cnt[s1.charAt (i) - 'A'][s2.charAt (n - i - 1) - 'A'] += inc;
    return n;
  };

  public static void main (String args []) throws Exception {
    in = new BufferedReader (new FileReader ("enchanted.in"));
    PrintWriter out = new PrintWriter ("enchanted.out");

    int n1 = twoLines (1);
    int n2 = twoLines (-1);

    if (n1 != n2) throw new Exception ("non-equal lengths");
    if (in.ready ()) throw new Exception ("EOF expected");

    boolean res = true;

    for (int i = 0; i < 26; i++)
      for (int j = 0; j < 26; j++)
        if (cnt[i][j] != 0)
          res = false;

    out.println (res ? "Yes" : "No");
    out.close ();
  };
};
