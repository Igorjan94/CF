/*--------------------------------------------------------------*/
/* ACM ICPC 2008-2009, NEERC                                    */
/* Northern Subregional Contest                                 */
/* St Petersburg, November 1, 2008                              */
/*--------------------------------------------------------------*/
/* Problem E. Enchanted Mirror                                  */
/*                                                              */
/* Original idea         Andrew Lopatin                         */
/* Problem statement     Andrew Lopatin                         */
/* Testset               Andrew Lopatin                         */
/*--------------------------------------------------------------*/
/* Solution                                                     */
/*                                                              */
/* Author                Roman Satukov                          */
/*--------------------------------------------------------------*/
 
import java.io.*;

/**
 * @author Roman V Satyukov
 */
public class enchanted_rs implements Runnable {
	private final String problemID = getClass().getName().split("_")[0].toLowerCase();
	private BufferedReader in;
	private PrintWriter out;
	
	private void check(boolean expr, String message) {
		if (!expr) {
			throw new AssertionError(message);
		}
	}
	
	private void checkCapital(String s) {
		for (int i = 0; i < s.length(); i++) {
			char ch = s.charAt(i);
			check(('A' <= ch) && (ch <= 'Z'), "Not all strings consist of capital english letters");
		}
	}

	private void solve() throws IOException {
		String s1 = in.readLine();
		String s2 = in.readLine();
		String t1 = in.readLine();
		String t2 = in.readLine();
		int n = s1.length();
		check(s2.length() == n, "Not all strings have the same length");
		check(t1.length() == n, "Not all strings have the same length");
		check(t2.length() == n, "Not all strings have the same length");
		check((1 <= n) && (n <= 100), "Length of the strings is not in [1..100]");
		checkCapital(s1);
		checkCapital(s2);
		checkCapital(t1);
		checkCapital(t2);
		int[][] count = new int[26][26];
		for (int i = 0; i < n; i++) {
			count[s1.charAt(i) - 'A'][s2.charAt(n - 1 - i) - 'A']++;
			count[t1.charAt(i) - 'A'][t2.charAt(n - 1 - i) - 'A']--;
		}
		for (int i = 0; i < 26; i++) {
			for (int j = 0; j < 26; j++) {
				if (count[i][j] != 0) {
					out.println("No");
					return;
				}
			}
		}
		out.println("Yes");
	}
	
	public static void main(String[] args) {
		new Thread(new enchanted_rs()).start();
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
