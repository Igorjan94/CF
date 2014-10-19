/*--------------------------------------------------------------*/
/* ACM ICPC 2008-2009, NEERC                                    */
/* Northern Subregional Contest                                 */
/* St Petersburg, November 1, 2008                              */
/*--------------------------------------------------------------*/
/* Problem I. Important Wires                                   */
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

public class important_al {
  static final int MaxN = 10;
  static final int MaxL = 1000;
  static int rInt (String s, int a, int b) {
    int x = Integer.parseInt (s);
    if (x < a || x > b) throw new RuntimeException (x + " is not within " + a + ".." + b);
    return x;
  };

  static int p;
  static String s;
  static String curLex;


  static String nextLex () {
    String res = curLex;
    while (s.charAt (p) == ' ') ++p;
    switch (s.charAt (p)) {
      case '@': curLex = "@"; break;
      case '=': if (!s.substring (p, p + 2).equals ("=>")) throw new RuntimeException ("=> expected");
                curLex = "=>"; p += 2; break;
      case '<': if (!s.substring (p, p + 3).equals ("<=>")) throw new RuntimeException ("<=> expected");
                curLex = "<=>"; p += 3; break;
      default : curLex = "" + s.charAt (p++); break;
    };
    return res;
  };


  static void checkTerm () {
    String l = curLex;
    if (l.equals ("(")) {
      checkExpr ();
      l = nextLex ();
      if (!l.equals (")")) throw new RuntimeException (") expected");
    } else
    if (l.equals ("~")) {
      nextLex ();
      checkTerm ();
    } else
    if (l.length () == 1 && l.charAt (0) >= 'a' && l.charAt (0) <= 'z') {
      nextLex ();
      return;
    } else throw new RuntimeException ("unexpected lexem " + l);
  };


  static void checkExpr () {
    String l;
    do {
      nextLex ();
      checkTerm ();
      l = curLex;
    } while (l.equals ("&") || l.equals ("|") || l.equals ("=>") || l.equals ("<=>"));
  };


  static char checkFormula (String f) {
    char r = f.charAt (0);
    f = f.substring (1).trim ();
    if (!f.substring (0, 2).equals (":=")) throw new RuntimeException (":= expected");
    p = 0;
    s = f.substring (2).trim () + '@';
    curLex = "";
    checkExpr ();
    if (p != s.length () - 1) throw new RuntimeException ("formula in the input is invalid");
    return r;
  };

  public static void main (String args []) throws Exception {
    BufferedReader in = new BufferedReader (new FileReader ("important.in"));
    PrintWriter out = new PrintWriter ("important.out");

    int n = rInt (in.readLine (), 1, MaxN);

    boolean [] t = new boolean [26];

    for (int i = 0; i < n; i++) {
      String s = in.readLine ();
      if (s.length () > MaxL) throw new Exception ("String is too long");
      char f = checkFormula (s.trim ());
      t[f - 'A'] = true;
    };


    out.println ("Yes");

    boolean flag = false;
    for (int i = 0; i < 26; i++)
      if (t[i]) {
        if (flag) out.print (" | ");
        String let = "" + (char)(i + 'A');
        out.print (let + " | ~" + let);
        flag = true;
      };

    out.close ();
  };
};