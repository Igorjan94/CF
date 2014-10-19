/*--------------------------------------------------------------*/
/* ACM ICPC 2008-2009, NEERC                                    */
/* Northern Subregional Contest                                 */
/* St Petersburg, November 1, 2008                              */
/*--------------------------------------------------------------*/
/* Problem J. Just Too Lucky                                    */
/*                                                              */
/* Original idea         Andrew Stankevich, Fedor Tsarev        */
/* Problem statement     Andrew Stankevich                      */
/* Testset               Andrew Stankevich                      */
/*--------------------------------------------------------------*/
/* Solution                                                     */
/*                                                              */
/* Author                Georgiy Korneev                        */
/*--------------------------------------------------------------*/
 
import java.util.*;
import java.io.*;

public class just_gk implements Runnable {
    static Scanner in;
    static PrintWriter out;
     
    public void run() {
        long n = in.nextLong();
        int[] digits = new int[String.valueOf(n).length() + 1];

        boolean full = true;
        for (int i = 1; i < digits.length; i++) {
            digits[i] = (int) (n % 10);
            full &= digits[i] == 0 || digits[i] == 1 && i == digits.length - 1;
            n /= 10;
        }

        if (full) {
            Arrays.fill(digits, 9);
        }
        int cdigits = digits.length - (full ? 1 : 0);
        int maxSum = (cdigits - 1) * 9;

        long[][] free = new long[maxSum + 1][maxSum + 1];
        long[][] capped = new long[maxSum + 1][maxSum + 1];
        long[][] nfree = new long[maxSum + 1][maxSum + 1];
        long[][] ncapped = new long[maxSum + 1][maxSum + 1];

        int maxDivisor = 0;
        long result = 0;
        for (int divisor = 1; divisor <= maxSum; divisor++) {
            //long[][] free = new long[maxSum + 1][maxSum + 1];
            //long[][] capped = new long[maxSum + 1][maxSum + 1];
            for (int sum = 0; sum <= divisor; sum++) {
                for (int mod = 0; mod < divisor; mod++) {
                    free[sum][mod] = 0;
                    capped[sum][mod] = 0;
                }
            }

            free[0][0] = 1;
            capped[0][0] = 1;
            int p = 1;
            int d = 10 * divisor * divisor;
            for (int i = 1; i < cdigits; i++) {
                for (int sum = 0; sum <= divisor; sum++) {
                    for (int mod = 0; mod <= divisor; mod++) {
                        nfree[sum][mod] = 0;
                        ncapped[sum][mod] = 0;
                    }
                }
                //long[][] nfree = new long[maxSum + 1][maxSum + 1];
                //long[][] ncapped = new long[maxSum + 1][maxSum + 1];
                for (int sum = 0; sum <= Math.min(divisor, i * 9); sum++) {
                    for (int mod = 0; mod < divisor; mod++) {
                        for (int digit = 0; digit <= 9; digit++) {
                            if (sum < digit) continue;
                            int newMod = (mod - p * digit + d) % divisor;
                            nfree[sum][mod] += free[sum - digit][newMod];
                            if (digit < digits[i]) {
                                ncapped[sum][mod] += free[sum - digit][newMod];
                            } else if (digit == digits[i]) {
                                ncapped[sum][mod] += capped[sum - digit][newMod];
                            }
                        }
                    }
                }
                { long[][] t = free; free = nfree; nfree = t; }
                { long[][] t = capped; capped = ncapped; ncapped = t; }
                p = 10 * p % divisor;
            }
            if (free[divisor][0] != 0) {
                maxDivisor = divisor;
            }
            result += capped[divisor][0];
        }
        out.println(result + (full ? 1 : 0));
    }

    public static void main(String[] args) throws Exception {        
        in = new Scanner(new File("just.in"));
        out = new PrintWriter("just.out");

        new just_gk().run();

        in.close();
        out.close();
    }
}
