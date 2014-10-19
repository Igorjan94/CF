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
/* Author                Georgiy Korneev                        */
/*--------------------------------------------------------------*/
 
import java.util.*;
import java.io.*;

public class enchanted_gk_check {
    static Scanner in;
    static PrintWriter out;
    static int MAX_LENGTH = 100;

    String reverse(String s) {
        return new StringBuilder(s).reverse().toString();
    }

    List<String> build(String s1, String s2) {
        s2 = reverse(s2);
        List<String> result = new ArrayList<String>();
        for (int i = 0; i < s1.length(); i++) {
            result.add(s1.charAt(i) + "" + s2.charAt(i));
        }
        Collections.sort(result);
        return result;
    }

    public void run() {
        String s1 = in.next();
        String s2 = in.next();
        String t1 = in.next();
        String t2 = in.next();

        assert 1 <= s1.length() && s1.length() <= MAX_LENGTH;
        assert s1.length() == s2.length();
        assert s1.length() == t1.length();
        assert s1.length() == t2.length();

        assert s1.matches("[A-Z]+");
        assert s2.matches("[A-Z]+");
        assert t1.matches("[A-Z]+");
        assert t2.matches("[A-Z]+");

        boolean result = build(s1, s2).equals(build(t1, t2));
        out.println(result ? "Yes" : "No");
    }

    public static void main(String[] args) throws Exception {        
        in = new Scanner(new File("enchanted.in"));
        out = new PrintWriter("enchanted.out");

        new enchanted_gk_check().run();

        in.close();
        out.close();
    }
}
