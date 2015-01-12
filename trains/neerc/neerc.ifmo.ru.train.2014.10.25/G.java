import java.io.*;
import java.util.*;
import java.math.BigInteger;
import java.util.Map.Entry;
import static java.lang.Math.*;

public class G {

	final static String task_name = null;

	double eps = 1e-9;

	int svm(double x, double y, double ax, double ay, double bx, double by) {
		double d = (ax - x) * (by - y) - (ay - y) * (bx - x);

		if (d > eps) {
			return 1;
		}

		if (d < -eps) {
			return -1;
		}

		return 0;

	}

	double dist(double dx, double dy) {
		return sqrt(dx * dx + dy * dy);
	}

	void update(int h, double c, double x, double[] pl, double[] pr, double[] py, double[][] dp) {
		double y = py[h], lx = x - 1, rx = x + 1, ly = y, ry = y;

		for (int i = h - 1; i >= 0; i--) {
			if (svm(x, y, pr[i], py[i], lx, ly) < 0) {
				break;
			}

			if (svm(x, y, pl[i], py[i], rx, ry) > 0) {
				break;
			}

			if (svm(x, y, pl[i], py[i], lx, ly) >= 0) {
				lx = pl[i];
				ly = py[i];
				dp[0][i] = min(dp[0][i], c + dist(lx - x, ly - y));
			}

			if (svm(x, y, pr[i], py[i], rx, ry) <= 0) {
				rx = pr[i];
				ry = py[i];
				dp[1][i] = min(dp[1][i], c + dist(rx - x, ry - y));
			}
		}

	}

	void run() {
		int n;
		while ((n = nextInt()) != 0) {
			double[] pl = new double[n + 1], pr = new double[n + 1], py = new double[n + 1];

			pl[0] = pr[0] = nextDouble();
			py[0] = nextDouble();
			for (int i = 1; i <= n; i++) {
				py[i] = nextDouble();
				pl[i] = nextDouble();
				pr[i] = nextDouble();
			}

			Set<Double> f = new HashSet<Double>(n + 1);
			for (int i = 0; i <= n; i++) {
				f.add(pl[i]);
				f.add(pr[i]);
			}

			double[][] dp = new double[2][n];
			Arrays.fill(dp[0], Double.POSITIVE_INFINITY);
			Arrays.fill(dp[1], Double.POSITIVE_INFINITY);

			for (double d : f) {
				if (pl[n] <= d && d <= pr[n]) {
					update(n, 0.0, d, pl, pr, py, dp);
				}
			}

			for (int i = n - 1; i > 0; i--) {
				update(i, dp[0][i], pl[i], pl, pr, py, dp);
				update(i, dp[1][i], pr[i], pl, pr, py, dp);
			}

			out.println(min(dp[0][0], dp[1][0]));
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
		while (!st.hasMoreTokens())
			st = new StringTokenizer(nextLine());
		return st.nextToken();
	}

	boolean hasNext() {
		while (!st.hasMoreTokens()) {
			String line = nextLine();
			if (line == null) {
				return false;
			}
			st = new StringTokenizer(line);
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
			return in.readLine();
		} catch (IOException err) {
			return null;
		}
	}

	static PrintWriter out;
	static BufferedReader in;
	static StringTokenizer st = new StringTokenizer("");
	static Random rnd = new Random();

	public static void main(String[] args) throws IOException {
		if (task_name == null) {
			in = new BufferedReader(new InputStreamReader(System.in));
			out = new PrintWriter(System.out);
		} else {
			in = new BufferedReader(new FileReader(new File(task_name + ".in")));
			out = new PrintWriter(new FileWriter(new File(task_name + ".out")));
		}

		new G().run();
		out.close();
		in.close();
	}
}