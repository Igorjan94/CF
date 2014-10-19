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
/* Author                Georgiy Korneev                        */
/*--------------------------------------------------------------*/
 
import java.util.*;
import java.io.*;

public class important_gk {
    static Scanner in;
    static PrintWriter out;

    public void run() {
    	out.println("Yes");

        int n = in.nextInt();
        in.nextLine();
        for (int i = 0; i < n; i++) {
            String line = in.nextLine().trim();
            char function = line.charAt(0);
            if (i > 0) {
                out.print('&');
            }
            out.format("(%1$s|~%1$s)", function);
        }
    }

    public static void main(String[] args) throws Exception {        
        in = new Scanner(new File("important.in"));
        out = new PrintWriter("important.out");

        new important_gk().run();

        in.close();
        out.close();
    }
}
