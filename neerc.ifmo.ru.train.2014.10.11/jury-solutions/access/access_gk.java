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
/* Author                Georgiy Korneev                        */
/*--------------------------------------------------------------*/
 
import java.util.*;
import java.io.*;
import static java.lang.Long.parseLong;

public class access_gk {
    static BufferedReader in;
    static PrintWriter out;
    Map<Long, Boolean> acl = new HashMap<Long, Boolean>();

    long prefix(long ip, long mask) {
    	return (mask << 33) + ((ip >> (32 - mask)) & ((1L << mask) - 1));
    }

    Boolean getDeepest(long ip, long mask) {
        for (long i = mask; i >= 0; i--) {
            Boolean allow = acl.get(prefix(ip, i));
            if (allow != null) {
                return allow;
            }
        }
        return null;
    }

    public void nextNetwork(String line, boolean allow) {
    	toParts(line.substring(line.lastIndexOf(' ') + 1));
        long ip = ((parts[0] * 256 + parts[1]) * 256 + parts[2]) * 256 + parts[3];
        long mask = cparts == 4 ? 32 : parts[4];

        if (getDeepest(ip, mask) == null) {
            acl.put(prefix(ip, mask), allow);
        }
    }

	long[] parts = new long[5];
	int cparts = 0;

	void toParts(String line) {
    	cparts = 0;
    	int value = 0;
    	for (char ch : line.toCharArray()) {
    		if ('0' <= ch && ch <= '9') {
    			value = value * 10 + ch - '0';
    		} else {
    			parts[cparts++] = value;
    			value = 0;
    		}
    	}
		parts[cparts++] = value;
	}

    public long nextIp() throws IOException {
    	toParts(in.readLine());
        return ((parts[0] * 256 + parts[1]) * 256 + parts[2]) * 256 + parts[3];
    }

    public void run() throws IOException {
        int n = Integer.parseInt(in.readLine());
        for (int i = 0; i < n; i++) {
        	String line = in.readLine();
            boolean allow = line.startsWith("allow");
            nextNetwork(line, allow);
        }

        int m = Integer.parseInt(in.readLine());
        for (int i = 0; i < m; i++) {
            Boolean allow = getDeepest(nextIp(), 32);
            out.print(allow == null || allow ? 'A' : 'D');
        }
        out.println();
    }

    public static void main(String[] args) throws Exception {        
        in = new BufferedReader(new FileReader(new File("access.in")));
        out = new PrintWriter("access.out");

        new access_gk().run();

        in.close();
        out.close();
    }
}
