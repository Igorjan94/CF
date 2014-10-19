/*--------------------------------------------------------------*/
/* ACM ICPC 2008-2009, NEERC                                    */
/* Northern Subregional Contest                                 */
/* St Petersburg, November 1, 2008                              */
/*--------------------------------------------------------------*/
/* Problem A. Access Control                                    */
/*                                                              */
/* Original idea         Nick Durov                             */
/* Problem statement     Andrew Stankevich                      */
/* Testset               Georgiy Korneev                        */
/*--------------------------------------------------------------*/
/* Solution                                                     */
/*                                                              */
/* Author                Andrew Lopatin                         */
/*--------------------------------------------------------------*/
 
import java.util.*;
import java.io.*;

public class access_al {
  static final int MaxN = (int)1e5;
  static final int MaxM = (int)1e5;
  static int rInt (String s, int a, int b) {
    int x = Integer.parseInt (s);
    if (x < a || x > b) throw new RuntimeException (x + " is not within " + a + ".." + b);
    return x;
  };

  static int parseIp (String ip) {
    StringTokenizer t = new StringTokenizer (ip, ".");
    int ad = 0;
    for (int i = 0; i < 4; i++)
      ad = (ad << 8) + rInt (t.nextToken (), 0, 255);
    if (t.hasMoreTokens ()) throw new RuntimeException ("invalid ip: " + ip);
    return ad;
  };

  public static void main (String args []) throws Exception {
    BufferedReader in = new BufferedReader (new FileReader ("access.in"));
    PrintWriter out = new PrintWriter ("access.out");
    int n = rInt (in.readLine (), 0, MaxN);
    int [][][] T = new int [3][2][32 * n + 2];
    int tc = 2;
    for (int i = 0; i < n; i++) {
      StringTokenizer t = new StringTokenizer (in.readLine ());
      String td = t.nextToken ();
      if (!td.equals ("allow") && !td.equals ("deny"))
        throw new Exception ("allow or deny expected instead of " + td);
      if (!t.nextToken ().equals ("from")) throw new Exception ("from expected");
      String ip = t.nextToken ();
      if (t.hasMoreTokens ()) throw new Exception ("EOL expected");
      int mp = ip.indexOf ('/'), ad, ms;
      if (mp >= 0) {
        ad = parseIp (ip.substring (0, mp));
        ms = rInt (ip.substring (mp + 1), 0, 32);
      } else {
        ad = parseIp (ip);
        ms = 32;
      };
      int j, x;
      for (j = 0, x = 1; j < ms && T[2][0][x] == 0; j++, ad <<= 1) {
        int cb = (ad < 0) ? 1 : 0;
        if (T[cb][0][x] == 0) {
          T[cb][0][x] = tc++;
          T[cb][1][x] = i;
        };
        x = T[cb][0][x];
      };
      if (T[2][0][x] == 0) {
        T[2][0][x] = td.equals ("allow") ? 2 : 1;
        T[2][1][x] = i;
      };
    };
    int m = rInt (in.readLine (), 1, MaxM);
    for (int i = 0; i < m; i++) {
      int ad = parseIp (in.readLine ());
      int cdo = 0, cdr = n;
      int j, x;
      for (j = 0, x = 1; j < 32; j++, ad <<= 1) {
        if (T[2][0][x] > 0 && T[2][1][x] < cdr) {
          cdr = T[2][1][x];
          cdo = T[2][0][x];
        };
        int cb = (ad < 0) ? 1 : 0;
        x = T[cb][0][x];
      };
      if (T[2][0][x] > 0 && T[2][1][x] < cdr) {
        cdr = T[2][1][x];
        cdo = T[2][0][x];
      };
      if (cdo == 1) out.print ("D"); else out.print ("A");
    };
    if (in.ready ()) throw new Exception ("EOF expected");

    out.close ();
  };
};