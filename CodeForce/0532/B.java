import java.io.*;
import java.util.*;
import java.math.BigInteger;
import java.util.Map.Entry;

import static java.lang.Math.*;

public class B extends PrintWriter {

	void dfs(int v, List<Integer>[] g, long[][] dp, long[] a) {

		if (g[v].isEmpty()) {
			dp[1][v] = a[v];
			return;
		}

		long sum = 0, sumA = 0, sumB = 0;
		int e = 0;

		for (int u : g[v]) {
			dfs(u, g, dp, a);
			if (dp[0][u] < dp[1][u]) {
				++e;
				sum += dp[1][u];
			} else {
				sum += dp[0][u];
			}
		}

		if (e % 2 == 1) {
			sumB = sum;
			sumA = 0;

			for (int u : g[v]) {
				if (dp[0][u] < dp[1][u]) {
					sumA = max(sumA, sum - dp[1][u] + dp[0][u]);
				} else {
					sumA = max(sumA, sum - dp[0][u] + dp[1][u]);
				}
			}

		} else {
			sumA = sum;
			sumB = 0;
			for (int u : g[v]) {
				if (dp[0][u] < dp[1][u]) {
					sumB = max(sumB, sum - dp[1][u] + dp[0][u]);
				} else {
					sumB = max(sumB, sum - dp[0][u] + dp[1][u]);
				}
			}
		}

		dp[0][v] = sumA;
		dp[1][v] = max(sumA + a[v], sumB);

	}

	void run() {
		int n = nextInt();

		List<Integer>[] g = new List[n];

		for (int i = 0; i < n; i++) {
			g[i] = new ArrayList<Integer>();
		}

		long[] a = new long[n];

		for (int i = 0; i < n; i++) {
			int j = nextInt() - 1;
			a[i] = nextLong();

			if (0 <= j) {
				g[j].add(i);
			}
		}

		long[][] dp = new long[2][n];
		dfs(0, g, dp, a);

		println(max(dp[0][0], dp[1][0]));

	}

	void skip() {
		while (hasNext()) {
			next();
		}
	}

	int[][] nextMatrix(int n, int m) {
		int[][] matrix = new int[n][m];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				matrix[i][j] = nextInt();
		return matrix;
	}

	String next() {
		while (!tokenizer.hasMoreTokens())
			tokenizer = new StringTokenizer(nextLine());
		return tokenizer.nextToken();
	}

	boolean hasNext() {
		while (!tokenizer.hasMoreTokens()) {
			String line = nextLine();
			if (line == null) {
				return false;
			}
			tokenizer = new StringTokenizer(line);
		}
		return true;
	}

	int[] nextArray(int n) {
		int[] array = new int[n];
		for (int i = 0; i < n; i++) {
			array[i] = nextInt();
		}
		return array;
	}

	int nextInt() {
		return Integer.parseInt(next());
	}

	long nextLong() {
		return Long.parseLong(next());
	}

	double nextDouble() {
		return Double.parseDouble(next());
	}

	String nextLine() {
		try {
			return reader.readLine();
		} catch (IOException err) {
			return null;
		}
	}

	public B(OutputStream outputStream) {
		super(outputStream);
	}

	static BufferedReader reader;
	static StringTokenizer tokenizer = new StringTokenizer("");
	static Random rnd = new Random();
	static boolean OJ;

	public static void main(String[] args) throws IOException {
		OJ = System.getProperty("ONLINE_JUDGE") != null;
		B solution = new B(System.out);
		if (OJ) {
			reader = new BufferedReader(new InputStreamReader(System.in));
			solution.run();
		} else {
			reader = new BufferedReader(new FileReader(new File(B.class.getName() + ".txt")));
			long timeout = System.currentTimeMillis();
			while (solution.hasNext()) {
				solution.run();
				solution.println();
				solution.println("----------------------------------");
			}
			solution.println("time: " + (System.currentTimeMillis() - timeout));
		}
		solution.close();
		reader.close();
	}
}
