import java.io.*;
import java.util.*;
import java.math.BigInteger;
import java.util.Map.Entry;

import static java.lang.Math.*;

public class D extends PrintWriter {

	private static final String input = null;
	private static final String output = null;

	void run() {
		int n = nextInt(), m = 1_000_000 + 1;

		int l = -1, r = -1;

		int[] d = nextArray(n);

		int[] p = new int[m];
		for (int i = 0; i < m; i++) {
			p[i] = i;
		}

		for (int i = 2; i < m; i++) {
			if (p[i] == i) {
				for (int j = 2 * i; j < m; j += i) {
					p[j] = min(i, p[j]);
				}
			}
		}

		int[] size = new int[m];
		int[][] v = new int[m][];

		for (int i = 0; i < n; i++) {
			int cur = d[i];

			while (cur > 1) {
				int prime = p[cur];
				while (cur % prime == 0) {
					cur /= prime;
				}

				v[prime] = set(v[prime], size[prime]++, i);
			}
		}

		for (int i = 0; i < m; i++) {
			final int k = size[i];

			if (k > 0) {
				if (k == 1) {
					if (l == r) {
						l = r = v[i][0];
					}
				} else {
					int[] val = new int[k];

					for (int j = 0; j < k; j++) {
						val[j] = v[i][j] - 2 * j;
					}

					int[] min = new int[k];

					min[k - 1] = val[k - 1];

					for (int j = k - 2; j >= 0; j--) {
						min[j] = min(val[j], min[j + 1]);
					}

					for (int j = 0; j < k; j++) {
						int x = j, y = k - 1;
						int f = val[j] + 1;

						while (y - x > 1) {
							int z = (x + y) / 2;
							if (f <= min[z]) {
								y = z;
							} else {
								x = z;
							}
						}

						y = max(x - 1, j);
						while ((y + 1) < k && val[y + 1] <= f) {
							++y;
						}

						x = j;

						int w = val[x] - val[y] + 1;
						int fr = v[i][x];
						int to = v[i][y];

						int la = min(w, fr);
						w -= la;
						fr -= la;

						int ra = min(w, n - 1 - to);
						w -= ra;
						to += ra;

						if (to - fr > r - l) {
							l = fr;
							r = to;
						}
					}
				}
			}
		}

		println((l + 1) + " " + (r + 1));

	}

	int[] set(int[] vector, int index, int val) {
		if (vector == null) {
			vector = new int[index + 8];
		}
		if (index < vector.length) {
			vector[index] = val;
			return vector;
		} else {
			int[] victor = Arrays.copyOf(vector, max(index + 1, vector.length * 2));
			victor[index] = val;
			return victor;
		}
	}

	long gcd(long a, long b) {
		return b == 0 ? a : gcd(b, a % b);
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

	public D(OutputStream outputStream) {
		super(outputStream);
	}

	static BufferedReader reader;
	static StringTokenizer tokenizer = new StringTokenizer("");
	static Random rnd = new Random();
	static boolean OJ;

	public static void main(String[] args) throws IOException {
		D solution;
		if (input == null) {
			reader = new BufferedReader(new InputStreamReader(System.in));
		} else {
			reader = new BufferedReader(new FileReader(new File(input)));
		}

		if (output == null) {
			solution = new D(System.out);
		} else {
			solution = new D(new FileOutputStream(output));
		}

		solution.run();
		solution.close();
		reader.close();
	}
}