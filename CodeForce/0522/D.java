import java.io.*;
import java.util.*;
import java.math.BigInteger;
import java.util.Map.Entry;

import static java.lang.Math.*;

public class D extends PrintWriter {

	int[] x, y;
	int inf = 1234567890;

	void swap(int i, int j) {
		if (i == j)
			return;
		x[i] ^= x[j];
		x[j] ^= x[i];
		x[i] ^= x[j];
		y[i] ^= y[j];
		y[j] ^= y[i];
		y[i] ^= y[j];
	}

	interface QuadTree {
		int getMin();

		int getMin(int ql, int qr, int qd, int qu, int last);
	}

	class Square implements QuadTree {
		int sx, sy, d, val = inf;
		QuadTree ne, nw, se, sw;

		public int getMin() {
			return val;
		}

		public Square(int f, int t, int sx, int sy, int d) {
			this.sx = sx;
			this.sy = sy;
			this.d = d;

			d /= 2;

			int m = f;
			{
				for (int i = f; i <= t; i++) {
					val = min(val, y[i] - x[i]);
					if (x[i] < sx + d && y[i] < sy + d) {
						swap(i, m++);
					}
				}
				sw = build(f, m - 1, sx, sy, d);
				f = m;
			}
			{
				for (int i = f; i <= t; i++) {
					if (x[i] < sx + d && y[i] >= sy + d) {
						swap(i, m++);
					}
				}
				nw = build(f, m - 1, sx, sy + d, d);
				f = m;
			}
			{
				for (int i = f; i <= t; i++) {
					if (y[i] < sy + d) {
						swap(i, m++);
					}
				}
				se = build(f, m - 1, sx + d, sy, d);
				ne = build(m, t, sx + d, sy + d, d);
			}

		}

		public int getMin(int ql, int qr, int qd, int qu, int last) {
			if (qr < ql || qu < qd) {
				return inf;
			}

			if (qr < sx || sx + d < ql) {
				return inf;
			}
			if (qu < sy || sy + d < qd) {
				return inf;
			}

			if (last < val) {
				return last;
			}

			if (ql <= sx && sx + d < qr) {
				if (qd <= sy && sy + d < qu) {
					return getMin();
				}
			}

			int ans = inf;

			if (se != null) {
				ans = min(ans, se.getMin(ql, qr, qd, qu, ans));
			}
			if (sw != null) {
				ans = min(ans, sw.getMin(ql, qr, qd, qu, ans));
			}
			if (ne != null) {
				ans = min(ans, ne.getMin(ql, qr, qd, qu, ans));
			}
			if (nw != null) {
				ans = min(ans, nw.getMin(ql, qr, qd, qu, ans));
			}

			return ans;
		}
	}

	class Point implements QuadTree {
		int id;

		public Point(int id) {
			this.id = id;

		}

		public int getMin() {
			return y[id] - x[id];
		}

		public int getMin(int ql, int qr, int qd, int qu, int last) {
			if (ql <= x[id] && x[id] <= qr) {
				if (qd <= y[id] && y[id] <= qu) {
					return min(last, getMin());
				}
			}
			return last;
		}

	}

	QuadTree build(int f, int t, int sx, int sy, int d) {
		if (t < f) {
			return null;
		}

		if (f == t) {
			return new Point(f);
		}

		return new Square(f, t, sx, sy, d);
	}

	void run() {
		int n = nextInt(), m = nextInt(), s = 0;
		int[] a = nextArray(n);
		int[] b = a.clone();
		Map<Integer, Integer> p = new TreeMap<Integer, Integer>();

		x = new int[n];
		y = new int[n];

		for (int i = n - 1; i >= 0; i--) {
			Integer prev = p.get(a[i]);
			p.put(a[i], i);

			if (prev != null) {
				x[s] = i;
				y[s] = prev;
				++s;
			}
		}
		// long qb = System.currentTimeMillis();

		QuadTree qt = build(0, s - 1, 0, 0, 1 << 19);
		// println(System.currentTimeMillis() - qb);

		// println(s);
		int h = 0;
		while (--m >= 0) {
			int l = nextInt() - 1, r = nextInt() - 1, ans = -1;

			if (qt != null) {
				ans = qt.getMin(l, inf, 0, r, inf);
				if (ans == inf) {
					ans = -1;
				}
			}

			// int t = check(b, l, r);
			//
			// if (t != ans) {
			// println(t + " " + ans);
			// println(l + " " + r);
			// println(Arrays.toString(b));
			// flush();
			// System.exit(0);
			// }
			// h += ans;
			println(ans);

		}

		// println(h);

	}

	int check(int[] a, int l, int r) {
		int ans = -1;

		for (int i = l; i <= r; i++) {
			for (int j = i + 1; j <= r; j++) {
				if (a[i] == a[j] && (ans == -1 || j - i < ans)) {
					ans = j - i;
				}
			}
		}

		return ans;
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

	public D(OutputStream outputStream) {
		super(outputStream);
	}

	static BufferedReader reader;
	static StringTokenizer tokenizer = new StringTokenizer("");
	static Random rnd = new Random();
	static boolean OJ;

	public static void main(String[] args) throws IOException {
		OJ = System.getProperty("ONLINE_JUDGE") != null;
		D solution = new D(System.out);
		if (OJ) {
			reader = new BufferedReader(new InputStreamReader(System.in));
			solution.run();
		} else {
			reader = new BufferedReader(new FileReader(new File(D.class.getName() + ".txt")));
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
