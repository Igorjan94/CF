import java.io.*;
import java.util.*;
import java.math.BigInteger;
import java.util.Map.Entry;

import static java.lang.Math.*;

public class A extends PrintWriter {

	private static final String input = null;
	private static final String output = null;

	void run() {
		int n = nextInt(), m = 0;
		int[] x = new int[n], y = new int[n];

		for (int i = 0; i < n; i++) {
			x[i] = nextInt();
			y[i] = nextInt();
		}

		double[] d = new double[n * (n + 1) / 2];

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < i; j++) {
				if (x[i] == x[j]) {
					if (abs(y[i]) == abs(y[j])) {
						println(0);
						return;
					}
				} else {
					double p = (x[i] * x[i]) - (x[j] * x[j]) + (y[i] * y[i]) - (y[j] * y[j]);
					double q = x[i] - x[j];
					d[m++] = p / q;
				}
			}
		}

		if (m == 0) {
			println(1);
			return;
		}

		Arrays.sort(d, 0, m);

		int ans = 2;

		double eps = 1e-9;

		for (int i = 1; i < m; i++) {
			if (d[i] - d[i - 1] > eps) {
				++ans;
			}
		}

		println(ans);

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

	public A(OutputStream outputStream) {
		super(outputStream);
	}

	static BufferedReader reader;
	static StringTokenizer tokenizer = new StringTokenizer("");
	static Random rnd = new Random();
	static boolean OJ;

	public static void main(String[] args) throws IOException {
		A solution;
		if (input == null) {
			reader = new BufferedReader(new InputStreamReader(System.in));
		} else {
			reader = new BufferedReader(new FileReader(new File(input)));
		}

		if (output == null) {
			solution = new A(System.out);
		} else {
			solution = new A(new FileOutputStream(output));
		}

		solution.run();
		solution.close();
		reader.close();
	}
}