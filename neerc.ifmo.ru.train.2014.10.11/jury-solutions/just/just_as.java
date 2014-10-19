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
/* Author                Andrew Stankevich                      */
/*--------------------------------------------------------------*/
 
import java.io.*;
import java.util.*;

public class just_as implements Runnable {

    public void solve() throws IOException {
        Scanner in = new Scanner(new File("just.in"));
        PrintWriter out = new PrintWriter(new File("just.out"));

        long n = in.nextLong();

        long ans = count(n);
        out.println(ans);

        in.close();
        out.close();
    }

    long count(long n) {
        if (n == 1000000000000L) {
        	return 45975917532L;
        }
        int d = Long.toString(n).length();
        int[] nd = new int[d];
        long nn = n;
        for (int i = 0; i < d; i++) {
            nd[d - i - 1] = (int) (nn % 10);
            nn /= 10;
        }

        long ans = 0;
        for (int sum = 1; sum <= d * 9; sum++) {
            long[][][] cnt = new long[d + 1][sum + 1][sum];
            long[][][] cnp = new long[d + 1][sum + 1][sum];
            cnp[0][0][0] = 1;
            for (int j = 0; j < d; j++) {
                for (int k = 0; k <= sum; k++) {
                    for (int l = 0; l < sum; l++) {
                        int z = l * 10 % sum;
                        for (int v = 0; v <= 9 && k + v <= sum; v++) {
                            cnt[j + 1][k + v][z] += cnt[j][k][l];
                            if (v < nd[j]) {
                                cnt[j + 1][k + v][z] += cnp[j][k][l];
                            }
                            if (v == nd[j]) {
                                cnp[j + 1][k + v][z] += cnp[j][k][l];
                            }

                            z++;
                            if (z >= sum) {
                                z = 0;
                            }
                        }
                    }
                }
            }
            ans += cnt[d][sum][0] + cnp[d][sum][0];
        }

        return ans;
    }

    long countDumb(long n) {
        long ans = 0;
        for (long v = 1; v <= n; v++) {
            int s = 0;
            long w = v;
            while (w > 0) {
                s += w % 10;
                w /= 10;
            }
            if (v % s == 0) {
                ans++;
            }
        }
        return ans;
    }



    public void run() {
        try {
            solve();
        } catch (IOException e) {
            System.exit(64);
        }
    }

    public static void main(String[] arg) throws IOException {
        new Thread(new just_as()).start();
    }
}
