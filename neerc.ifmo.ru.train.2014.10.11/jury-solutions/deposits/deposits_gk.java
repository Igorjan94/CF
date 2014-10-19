/*--------------------------------------------------------------*/
/* ACM ICPC 2008-2009, NEERC                                    */
/* Northern Subregional Contest                                 */
/* St Petersburg, November 1, 2008                              */
/*--------------------------------------------------------------*/
/* Problem D. Deposits                                          */
/*                                                              */
/* Original idea         Roman Satukov                          */
/* Problem statement     Andrew Stankevich                      */
/* Testset               Andrew Stankevich                      */
/*--------------------------------------------------------------*/
/* Solution                                                     */
/*                                                              */
/* Author                Georgiy Korneev                        */
/*--------------------------------------------------------------*/
 
import java.io.*;
import java.util.*;

public class deposits_gk {
    static StreamTokenizer tokenizer;
    static PrintWriter out;


    int nextInt() throws IOException {
        tokenizer.nextToken();
        return (int) tokenizer.nval;
    }

    public void run() throws IOException {
        int n = nextInt();
        int a[] = new int[n];
        for(int i = 0; i < n; i++) {
            a[i] = nextInt();
        }

        int m = nextInt();
        int b[] = new int[m];
        for(int i = 0; i < m; i++) {
            b[i] = nextInt();
        }

        Arrays.sort(a);
        Arrays.sort(b);
        int maxA = a[n - 1];
        int[] count = new int[maxA + 1];

        int j = 0;
        int ops = 0;
        while (j < m) {
            int c = 1;
            while (j + c < m && b[j] == b[j + c]) {
                c++;
            }
            int v = b[j];
            for (int i = v; i <= maxA; i += v) {
                count[i] += c;
                ops++;
            }
            j += c;
        }

        long result = 0;
        for (int i : a) {
            result += count[i];
        }
        out.println(result);
    }

    public static void main(String args[]) throws Exception {
        tokenizer = new StreamTokenizer(new FileReader("deposits.in"));
        out = new PrintWriter("deposits.out");
        (new deposits_gk()).run();
        out.close();
    }
}
