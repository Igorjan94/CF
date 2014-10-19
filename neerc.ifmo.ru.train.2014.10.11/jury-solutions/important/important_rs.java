/*--------------------------------------------------------------*/
/* ACM ICPC 2008-2009, NEERC                                    */
/* Northern Subregional Contest                                 */
/* St Petersburg, November 1, 2008                              */
/*--------------------------------------------------------------*/
/* Problem I. Important Wires                                   */
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
import java.util.StringTokenizer;

/**
 * @author Roman V Satyukov
 */
public class important_rs implements Runnable {
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
		check((1 <= n) && (n <= 10), "n is not in [1..10]");
		out.println("Yes");
		for (int i = 0; i < n; i++) {
			StringTokenizer st = new StringTokenizer(in.readLine().split(":")[0]);
			String left = st.nextToken();
			check(left.length() == 1, "Function name is not a letter");
			check((('A' <= left.charAt(0)) && (left.charAt(0) <= 'Z')), "Function name is not a capital english letter");
			if (i > 0) {
				out.print("&");
			}
			out.print("((" + left + ")=>(" + left + "))");
		}
		out.println();
	}
	
	public static void main(String[] args) {
		new Thread(new important_rs()).start();
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
