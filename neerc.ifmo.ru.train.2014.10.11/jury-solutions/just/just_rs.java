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
/* Author                Roman Satukov                          */
/*--------------------------------------------------------------*/
 
import java.io.*;

/**
 * @author Roman V Satyukov
 */
public class just_rs implements Runnable {
    private final String problemID = getClass().getName().split("_")[0].toLowerCase();
    private BufferedReader in;
    private PrintWriter out;
    
    private static final int MAX_DIGITS_SUM = 108;
    private static final int MAX_DIGITS = 12;
    private long[][][] ans;
    
    private void check(boolean expr, String message) {
        if (!expr) {
            throw new AssertionError(message);
        }
    }
    
    private boolean isLucky(long n) {
        long sum = 0;
        long nn = n;
        while (n > 0) {
            sum = sum + (n % 10);
            n = n / 10;
        }
        return (nn % sum == 0);
    }
    
    private long calc(long n, int sumDigits) {
        String decimalN = "" + n;
        for (int digits = 0; digits < decimalN.length(); digits++) {
            for (int sum = 0; sum <= sumDigits; sum++) {
                for (int mod = 0; mod < sumDigits; mod++) {
                    ans[digits][sum][mod] = 0;
                }
            }
        }
        ans[0][0][0] = 1;
        for (int digits = 0; digits < decimalN.length(); digits++) {
            for (int sum = 0; sum <= sumDigits; sum++) {
                for (int mod = 0; mod < sumDigits; mod++) {
                    for (int d = 0; d < 10; d++) {
                        if (ans[digits][sum][mod] == 0) {
                            continue;
                        }
                        ans[digits + 1][sum + d][(10 * mod + d) % sumDigits] += ans[digits][sum][mod];
                    }
                }
            }
        }
        long result = 0;
        for (int i = 0; i < decimalN.length(); i++) {
            int sum = 0;
            int value = 0;
            for (int j = 0; j < i; j++) {
                sum += decimalN.charAt(j) - '0';
                value = (value * 10 + (decimalN.charAt(j) - '0')) % sumDigits;
            }
            for (int d = 0; d < decimalN.charAt(i) - '0'; d++) {
                int currentSum = sumDigits - sum - d;
                if (currentSum < 0) {
                    continue;
                }
                int currentValue = (10 * value + d) % sumDigits;
                for (int j = i + 1; j < decimalN.length(); j++) {
                    currentValue = (10 * currentValue) % sumDigits;
                }
                currentValue = (sumDigits - currentValue) % sumDigits;
                result = result + ans[decimalN.length() - i - 1][currentSum][currentValue];
            }
        }
        return result;
    }
    
    private void solve() throws IOException {
        long n = Long.parseLong(in.readLine());
        check((1 <= n) && (n <= 1000000000000L), "n is not in [1..10^12]");
        
        ans = new long[MAX_DIGITS + 1][MAX_DIGITS_SUM + 1][MAX_DIGITS_SUM + 1];
        long result = 0;
        if (n == 1000000000000L) {
            n--;
            result++;
        }
        for (int sum = 1; sum <= MAX_DIGITS_SUM; sum++) {
            result = result + calc(n, sum);
        }
        if (isLucky(n)) {
            result++;
        }
        out.println(result);
    }
    
    public static void main(String[] args) {
        new Thread(new just_rs()).start();
    }

    public void run() {
        try {
            in = new BufferedReader(new FileReader(new File(problemID + ".in")));
            out = new PrintWriter(new File(problemID + ".out"));
            solve();
            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
}
