import java.io.*;
import java.util.*;

public class forest_va implements Runnable {
	public static void main(String[] args) {
		new Thread(new forest_va()).run();
	}

	BufferedReader br;
	StringTokenizer in;
	PrintWriter out;

	public String nextToken() throws IOException {
		while (in == null || !in.hasMoreTokens()) {
			in = new StringTokenizer(br.readLine());
		}

		return in.nextToken();
	}

	public int nextInt() throws IOException {
		return Integer.parseInt(nextToken());
	}

	public long nextLong() throws IOException {
		return Long.parseLong(nextToken());
	}

	public double nextDouble() throws IOException {
		return Double.parseDouble(nextToken());
	}

	public long gcd(long a, long b) {
		return b == 0 ? a : gcd(b, a % b);
	}

	public void print(long a, long b) {
		long d = gcd(a, b);
		out.println((a / d) + (b != d ? "/" + (b / d) : ""));
	}

	public void solve() throws IOException {
		int n = nextInt();
		int m = nextInt();

		if (n > m) {
			int q = n;
			n = m;
			m = q;
		}

		if (n == 1) {
			if (m == 2) {
				print(2, 1);
				return;
			}
			if (m == 3) {
				print(2, 1);
				return;
			}
			print(2 * 4 + 2 * 2 + 1L * (m - 4) * 3, 4);
			return;
		}

		if (n == 2) {
			if (m == 2) {
				print(3 * 4, 4);
				return;
			}
			if (m == 3) {
				print(4 * 2 * 4 + 2 * 5 * 2, 12);
				return;
			}
			print(27L * n * m - 9 * 4 - 6 * 4 - 8L * n * (m - 4), 27);
			return;
		}

		if (n == 3) {
			if (m == 3) {
				print(81L * 16 * n * m - 4 * 4 * 9 * 16 - 4 * 3 * 81 - 16 * 16,
						81 * 16);
				return;
			}

			print(9L * 16 * n * m - 4 * 4 * 16 - 2 * 3 * 9 - 4 * 1 * 4 * 9 - 2
					* 2 * 16 - 2L * (m - 4) * 1 * 3 * 16 - 1L * (m - 4) * 1 * 9
					* 4, 9 * 16);
			return;
		}

		print(2304L
				* n
				* m	
				- (4 * 4 * 2304 / 9 + 12 * 1 * 2304 / 4 + 2L * (n + m - 8) * 1
						* 2304 / 3 + 2L * (n + m - 8) * 9 * 2304 / 32 + 1L
						* (n - 4) * (m - 4) * 81 * (2304 / 256)), 2304);
	}

	public void run() {
		try {
			br = new BufferedReader(new InputStreamReader(System.in));
			out = new PrintWriter(System.out);

			int t = nextInt();
			for (int i = 0; i < t; i++)
				solve();

			out.close();
		} catch (IOException e) {
			e.printStackTrace();
			System.exit(1);
		}
	}
}
