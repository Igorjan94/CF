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
/* Author                Roman Satukov                          */
/*--------------------------------------------------------------*/
 
import java.io.*;

/**
 * @author Roman V Satyukov
 */
public class holes_rs implements Runnable {
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
		check((0 <= n) && (n <= 510), "n is not in [0..510]");
		
		if (n == 0) {
			out.println("1");
			return;
		}
		int ansLength = (n + 1) / 2;
		int left = n;
		for (int i = 0; i < ansLength; i++) {
			if ((i > 0 || ansLength == 1) && (left / 2 == ansLength - i - 1)) {
				out.print("0");
				left--;
				continue;
			}
			if (left / 2 == ansLength - i - 1) {
				out.print("4");
				left--;
				continue;
			}
			out.print("8");
			left -= 2;
		}
		out.println();
	}
	
	public static void main(String[] args) {
		new Thread(new holes_rs()).start();
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
