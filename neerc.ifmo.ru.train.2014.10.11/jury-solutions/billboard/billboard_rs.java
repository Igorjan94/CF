/*--------------------------------------------------------------*/
/* ACM ICPC 2008-2009, NEERC                                    */
/* Northern Subregional Contest                                 */
/* St Petersburg, November 1, 2008                              */
/*--------------------------------------------------------------*/
/* Problem B. Billboard                                         */
/*                                                              */
/* Original idea         Georgiy Korneev                        */
/* Problem statement     Mikhail Dorkin                         */
/* Testset               Mikhail Dorkin                         */
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
public class billboard_rs implements Runnable {
	private final String problemID = getClass().getName().split("_")[0].toLowerCase();
	private BufferedReader in;
	private PrintWriter out;
	
	private class SegmentsTree {
		private int dx;
		private int[] w;
		
		public SegmentsTree(int n, int value) {
			dx = 1;
			while (dx < n) {
				dx = dx << 1;
			}
			w = new int[2 * dx];
			Arrays.fill(w, value);
		}

		public int getFirst(int value) {
			if (w[1] < value) {
				return -1;
			}
			int cur = 1;
			while (cur < dx) {
				int left = cur << 1;
				if (w[left] >= value) {
					cur = left;
				} else {
					cur = left + 1;
				}
			}
			return cur - dx;
		}

		public int getValue(int pos) {
			return w[pos + dx];
		}

		public void setValue(int pos, int value) {
			pos += dx;
			w[pos] = value;
			pos = pos >> 1;
			while (pos >= 1) {
				w[pos] = Math.max(w[pos << 1], w[(pos << 1) + 1]);
				pos = pos >> 1;
			}
		}
	}
	
	private void check(boolean expr, String message) {
		if (!expr) {
			throw new AssertionError(message);
		}
	}
	
	private void solve() throws IOException {
		StringTokenizer st = new StringTokenizer(in.readLine());
		int h = Integer.parseInt(st.nextToken());
		int w = Integer.parseInt(st.nextToken());
		int n = Integer.parseInt(st.nextToken());
		check((1 <= h) && (h <= 1000000000), "h is not in [1..10^9]");
		check((1 <= w) && (w <= 1000000000), "w is not in [1..10^9]");
		check((1 <= n) && (n <= 200000), "n is not in [1..200,000]");
		SegmentsTree stree = new SegmentsTree(n, w);
		for (int i = 0; i < n; i++) {
			int cur = Integer.parseInt(in.readLine());
			check((1 <= cur) && (cur <= 1000000000), "w_" + (i + 1) + " is not in [1..10^9]");
			int pos = stree.getFirst(cur);
			if (pos >= h) {
				pos = -1;
			}
			out.println((pos == -1) ? -1 : pos + 1);
			if (pos != -1) {
				stree.setValue(pos, stree.getValue(pos) - cur);
			}
		}
	}
	
	public static void main(String[] args) {
		new Thread(new billboard_rs()).start();
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
