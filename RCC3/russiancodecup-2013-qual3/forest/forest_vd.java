import java.io.*;
import java.util.*;

public class forest_vd {

	long gcd(long a, long b) {
		return (b == 0) ? a : gcd(b, a % b);
	}

	void print(long a, long b) {
		long gcd = gcd(a, b);
		a /= gcd;
		b /= gcd;
		out.print(a);
		if (b != 1) {
			out.print("/" + b);
		}
		out.println();
	}

	void solve() throws IOException {
		long n = nextLong();
		long m = nextLong();
		if (n > m) {
			long t = n;
			n = m;
			m = t;
		}
		if (n == 1) {
			if (m == 2 || m == 3) {
				print(2, 1);
			} else {
				print(3 * m, 4);
			}
		} else if (n == 2) {
			if (m == 2) {
				print(3, 1);
			} else if (m == 3) {
				print(13, 3);
			} else {
				print(27 * m * 2 - 4 * 9 - 3 * 8 - 16 * (m - 4), 27);
			}
		} else if (n == 3) {
			if (m == 3) {
				print(16 * 81 * 9 - 16 * 9 * 16 - 12 * 81 - 16 * 16, 81 * 16);
			} else {
				print(9
						* 16
						* 3
						* m
						- (16 * 16 + 6 * 9 + 1 * 9 * 16 + 4 * 16 + 2 * (m - 4)
								* 3 * 16 + (m - 4) * 4 * 9), 9 * 16);

			}
		} else {
			long znam = 4 * 4 * 4 * 4 * 9;
			print(n
					* m
					* znam
					- (4 * (4 * (znam / 9) + znam / 2 + znam / 4) + 2
							* (m - 4 + n - 4) * (znam / 3) + 9
							* (m - 4 + n - 4) * (znam / 16) + 9 * 9 * 9
							* (m - 4) * (n - 4)), znam);
		}
	}

	public void run() throws IOException {
		br = new BufferedReader(new InputStreamReader(System.in));
		out = new PrintWriter(System.out);
		int t = nextInt();
		for (int i = 0; i < t; i++) {
			solve();
		}
		br.close();
		out.close();
	}

	public static void main(String[] args) throws IOException {
		new forest_vd().run();
	}

	BufferedReader br;
	StringTokenizer str;
	PrintWriter out;

	String next() throws IOException {
		while (str == null || !str.hasMoreTokens()) {
			String s = br.readLine();
			if (s != null) {
				str = new StringTokenizer(s);
			} else {
				return null;
			}
		}
		return str.nextToken();
	}

	long nextLong() throws IOException {
		return Long.parseLong(next());
	}

	int nextInt() throws IOException {
		return Integer.parseInt(next());
	}

	double nextDouble() throws IOException {
		return Double.parseDouble(next());
	}

}
