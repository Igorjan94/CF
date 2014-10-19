/*--------------------------------------------------------------*/
/* ACM ICPC 2008-2009, NEERC                                    */
/* Northern Subregional Contest                                 */
/* St Petersburg, November 1, 2008                              */
/*--------------------------------------------------------------*/
/* Problem C. Class                                             */
/*                                                              */
/* Original idea         Georgiy Korneev                        */
/* Problem statement     Georgiy Korneev                        */
/* Testset               Georgiy Korneev                        */
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
public class class_rs implements Runnable {
	private final String problemID = getClass().getName().split("_")[0].toLowerCase();
	private BufferedReader in;
	private PrintWriter out;
	
	private void check(boolean expr, String message) {
		if (!expr) {
			throw new AssertionError(message);
		}
	}
	
	private void solve() throws IOException {
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int r = Integer.parseInt(st.nextToken());
		int c = Integer.parseInt(st.nextToken());
		check((1 <= r) && (r <= 100), "r is not in [1..100]");
		check((1 <= c) && (c <= 100), "c is not in [1..100]");
		check((1 <= n) && (n <= r * c), "n is not in [1..r*c]");
		char[][] field = new char[r][c];
		for (int i = 0; i < r; i++) {
			Arrays.fill(field[i], '.');
		}
		field[0][0] = '#';
		n--;
		int step = 1;
		int fullness = 1;
		while (step < r && step < c) {
			if (n >= 2) {
				fullness++;
			}
			if (n > 0) {
				field[0][step] = '#';
				n--;
			}
			if (n > 0) {
				field[step][0] = '#';
				n--;
			}
			step++;
		}
		out.println(fullness);
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (n > 0 && field[i][j] == '.') {
					field[i][j] = '#';
					n--;
				}
				out.print(field[i][j]);
			}
			out.println();
		}
	}
	
	public static void main(String[] args) {
		new Thread(new class_rs()).start();
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
