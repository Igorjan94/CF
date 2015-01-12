import java.io.*;
import java.util.*;
import java.math.BigInteger;
import java.util.Map.Entry;
import static java.lang.Math.*;

public class F {

	final static String task_name = "flat";

	void run() {
		int n = nextInt();
		int c = nextInt();

		int allRooms = 0, bedrooms = 0, balcony = 0;

		while (--n >= 0) {
			int a = nextInt();
			String t = next().intern();

			allRooms += a;

			switch (t) {
			case "bedroom": {
				bedrooms += a;
			}
				break;
			case "balcony": {
				balcony += a;
			}
				break;
			default:
			}
		}

		out.println(allRooms);
		out.println(bedrooms);
		out.println(((allRooms - balcony) + (balcony * 0.5)) * c);

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

		new F().run();
		out.close();
		in.close();
	}
}