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
/* Author                Roman Satukov                          */
/*--------------------------------------------------------------*/
 
import java.io.*;

/**
 * @author Roman V Satyukov
 */
public class access_rs implements Runnable {
    private final String problemID = getClass().getName().split("_")[0].toLowerCase();
    private BufferedReader in;
    private PrintWriter out;
    private int[][] go;
    private int[] rule;
    private int free;

    private void check(boolean expr, String message) {
        if (!expr) {
            throw new AssertionError(message);
        }
    }
    
    private long parseIP(String str) {
        String[] tmp = str.split("\\.");
        check(tmp.length == 4, "Bad IP address");
        long result = 0;
        for (int i = 0; i < 4; i++) {
            int cur = Integer.parseInt(tmp[i]);
            check((0 <= cur) && (cur <= 255), "Bad IP address");
            result = (result << 8) + cur;
        }
        return result;
    }

    private void addRule(long ip, long size, boolean allow, int ruleNumber) {
        int cur = 0;
        for (int i = 31; i >= 32 - size; i--) {
            int bit = ((ip & (1L << i)) == 0) ? 0 : 1;
            if (go[bit][cur] == -1) {
                go[bit][cur] = free++;
            }
            cur = go[bit][cur];
        }
        if (rule[cur] != 0 && Math.abs(rule[cur]) < ruleNumber) {
            return;
        }
        rule[cur] = (allow) ? ruleNumber : -ruleNumber;
    }

    private boolean checkAllow(long ip) {
        int cur = 0;
        int minRule = (rule[cur] != 0) ? rule[cur] : Integer.MAX_VALUE;
        for (int i = 31; i >= 0; i--) {
            int bit = ((ip & (1L << i)) == 0) ? 0 : 1;
            cur = go[bit][cur];
            if (cur < 0) {
                break;
            }
            minRule = (rule[cur] != 0 && Math.abs(rule[cur]) < Math.abs(minRule)) ? rule[cur] : minRule;
        }
        return minRule >= 0;
    }

    private void solve() throws IOException {
        int n = Integer.parseInt(in.readLine());
        check((0 <= n) && (n <= 100000), "n is not in [0..100,000]");
        int maxs = 32 * n + 1;
        go = new int[2][maxs];
        rule = new int[maxs];
        free = 1;
        for (int i = 0; i < maxs; i++) {
            go[0][i] = go[1][i] = -1;
        }
        for (int i = 0; i < n; i++) {
            String line = in.readLine();
            boolean allow = false;
            if (line.startsWith("allow from ")) {
                line = line.substring("allow from ".length());
                allow = true;
            } else if (line.startsWith("deny from ")) {
                line = line.substring("deny from ".length());
                allow = false;
            } else {
                check(false, "Unexpected line");
            }
            int pos = line.indexOf('/');
            long ip, size;
            if (pos >= 0) {
                ip = parseIP(line.substring(0, pos));
                size = Integer.parseInt(line.substring(pos + 1));
            } else {
                ip = parseIP(line);
                size = 32;
            }
            addRule(ip, size, allow, i + 1);
        }
        
        int m = Integer.parseInt(in.readLine());
        check((1 <= m) && (m <= 100000), "m is not in [1..100,000]");
        for (int i = 0; i < m; i++) {
            long ip = parseIP(in.readLine());
            if (checkAllow(ip)) {
                out.print("A");
            } else {
                out.print("D");
            }
        }
        out.println();
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
    
    public static void main(String[] args) {
        new Thread(new access_rs()).start();
    }
}
