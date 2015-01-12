import java.io.*;
import java.util.*;
import java.math.BigInteger;
import java.util.Map.Entry;
import static java.lang.Math.*;

public class A {

	final static String task_name = "ate";

	void run() {
		int n = nextInt();

		int ans = 0;

		for (int a = 0; a < 100; a++) {
			for (int b = 0; b < 100; b++) {
				if (n - a - b == 0) {
					++ans;
				}
			}
		}

		out.println(ans);

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

		new A().run();
		out.close();
		in.close();
	}
}