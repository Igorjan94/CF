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
/* Author                Roman Satukov                          */
/*--------------------------------------------------------------*/
 
import java.io.*;
import java.util.*;

/**
 * @author Roman V Satyukov
 */
public class deposits_rs implements Runnable {
	private final String problemID = getClass().getName().split("_")[0].toLowerCase();
	private BufferedReader in;
	private PrintWriter out;
	
	private void check(boolean expr, String message) {
		if (!expr) {
			throw new AssertionError(message);
		}
	}
	
	private void solve() throws IOException {
		int n = Integer.parseInt(in.readLine());
		check((1 <= n) && (n <= 100000), "n is not in [1..100,000]");
		int[] a = new int[n];
		StringTokenizer st = new StringTokenizer(in.readLine());
		for (int i = 0; i < n; i++) {
			a[i] = Integer.parseInt(st.nextToken());
			check((1 <= a[i]) && (a[i] <= 1000000), "some of a[i] is not in [1..1000,000]");
		}
		int m = Integer.parseInt(in.readLine());
		check((1 <= m) && (m <= 100000), "m is not in [1..100,000]");
		int[] b = new int[m];
		st = new StringTokenizer(in.readLine());
		for (int i = 0; i < m; i++) {
			b[i] = Integer.parseInt(st.nextToken());
			check((1 <= b[i]) && (b[i] <= 1000000), "some of b[i] is not in [1..1000,000]");
		}
		
		Arrays.sort(b);
		int w = -1;
		int[] c = new int[m];
		for (int i = 0; i < m; i++) {
			if (i == 0 || b[i] != b[i - 1]) {
				w++;
				b[w] = b[i];
				c[w] = 1;
			} else {
				c[w]++;
			}
		}
		m = w + 1;
		
		long[] count = new long[1000001];
		for (int i = 0; i < m; i++) {
			int addon = b[i];
			int number = c[i];
			for (int j = b[i]; j <= 1000000; j += addon) {
				count[j] += number;
			}
		}
		long answer = 0;
		for (int i = 0; i < n; i++) {
			answer += count[a[i]];
		}
		out.println(answer);
	}
	
	public static void main(String[] args) {
		new Thread(new deposits_rs()).start();
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
