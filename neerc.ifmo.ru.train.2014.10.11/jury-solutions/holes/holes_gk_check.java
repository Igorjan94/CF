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
/* Author                Georgiy Korneev                        */
/*--------------------------------------------------------------*/
 
import java.util.*;
import java.io.*;

public class holes_gk_check {

	static final int MAX_H = 510;
    static Scanner in;
    static PrintWriter out;

    public void run() {
        int h = in.nextInt();

        assert (0 <= h && h <= MAX_H);

        if (h == 0) {
            out.println(1);
        } else if (h == 1) {
            out.println(0);
        } else {
            if (h % 2 == 1) {
                out.print('4');
            }
            for (int i = 0; i < h / 2; i++) {
                out.print('8');
            }
            out.println();
        }
    }

    public static void main(String[] args) throws Exception {        
        in = new Scanner(new File("holes.in"));
        out = new PrintWriter("holes.out");

        new holes_gk_check().run();

        in.close();
        out.close();
    }
}
