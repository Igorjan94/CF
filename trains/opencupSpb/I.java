import java.io.*;
import java.util.*;
import java.math.BigInteger;
import java.util.Map.Entry;

import static java.lang.Math.*;

public class I extends PrintWriter {

	private static final String input = null;
	private static final String output = null;

	void run() {
		int n = nextInt();

		int[] c = nextArray(n);
		int[] f = nextArray(n);

		long[][] dp = new long[2][n];

		long inf = 1_000_000_000_000_000L;

		Arrays.fill(dp[0], inf);
		Arrays.fill(dp[1], inf);

		dp[1][0] = 0;
		dp[0][0] = c[0] - f[0];

		for (int i = 1; i < n; i++) {

			if (c[i - 1] <= f[i] || f[i - 1] >= c[i]) {
				println(-1);
				return;
			}

			if (c[i - 1] <= c[i]) {
				dp[0][i] = min(dp[0][i], dp[0][i - 1]);
			}

			if (f[i - 1] >= f[i]) {
				dp[1][i] = min(dp[1][i], dp[1][i - 1]);
			}
			int l = c[i] - f[i];
			dp[0][i] = min(dp[0][i], dp[1][i] + l);
			dp[1][i] = min(dp[1][i], dp[0][i] + l);

		}

		long ans = dp[1][n - 1];
		if (ans < inf) {
			println(ans);
		} else {
			println(-1);
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

	public I(OutputStream outputStream) {
		super(outputStream);
	}

	static BufferedReader reader;
	static StringTokenizer tokenizer = new StringTokenizer("");
	static Random rnd = new Random();
	static boolean OJ;

	public static void main(String[] args) throws IOException {
		I solution;
		if (input == null) {
			reader = new BufferedReader(new InputStreamReader(System.in));
		} else {
			reader = new BufferedReader(new FileReader(new File(input)));
		}

		if (output == null) {
			solution = new I(System.out);
		} else {
			solution = new I(new FileOutputStream(output));
		}

		solution.run();
		solution.close();
		reader.close();
	}
}