import java.io.*;
import java.util.*;
import java.math.BigInteger;
import java.util.Map.Entry;

import static java.lang.Math.*;

public class E extends PrintWriter {

	boolean eq(int ls, int lt, int len, char[] s, char[] t) {

		for (int i = 0; i < len; i++) {
			if (s[ls + i] != t[lt + i]) {
				return false;
			}
		}

		return true;
	}

	int solve(int n, char[] s, char[] t) {
		int l = 0, r = 0;

		for (int i = 0; i < n; i++) {
			if (s[i] != t[i]) {
				l = i;
				break;
			}
		}

		for (int i = n - 1; i >= 0; i--) {
			if (s[i] != t[i]) {
				r = i;
				break;
			}
		}

		if (l == r) {
			return 2;
		}		

		int m = 0;

		if (eq(l + 1, l, r - l, s, t)) {
			 ++m;
		}
		if (eq(l, l + 1, r - l, s, t)) {
			 ++m;
		}

		return m;

	}

	void run() {
		int n = nextInt();

		char[] s = next().toCharArray();
		char[] t = next().toCharArray();

		println(solve(n, s, t));
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

	public E(OutputStream outputStream) {
		super(outputStream);
	}

	static BufferedReader reader;
	static StringTokenizer tokenizer = new StringTokenizer("");
	static Random rnd = new Random();
	static boolean OJ;

	public static void main(String[] args) throws IOException {
		OJ = System.getProperty("ONLINE_JUDGE") != null;
		E solution = new E(System.out);
		if (OJ) {
			reader = new BufferedReader(new InputStreamReader(System.in));
			solution.run();
		} else {
			reader = new BufferedReader(new FileReader(new File(E.class.getName() + ".txt")));
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
