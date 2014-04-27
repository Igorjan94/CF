import java.io.*;
import java.util.*;

public class forest_vd_slow {

	static int[] DX = { 1, -1, 0, 0 };
	static int[] DY = { 0, 0, -1, 1 };

	boolean inLim(int x, int y, int n, int m) {
		return (x < n) && (y < m) && (x >= 0) && (y >= 0);
	}


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
		int n = nextInt();
		int m = nextInt();
		long[][] d = new long[n][m];
		for (int x = 0; x < n; x++) {
			for (int y = 0; y < m; y++) {
				for (int t = 0; t < 4; t++) {
					if (inLim(x + DX[t], y + DY[t], n, m)) {
						d[x + DX[t]][y + DY[t]]++;
					}
				}
			}
		}
		long a = 0;
		long b = 1;

		for (int x = 0; x < n; x++) {
			for (int y = 0; y < m; y++) {
				long cura = 1;
				long curb = 1;
				for (int t = 0; t < 4; t++) {
					if (inLim(x + DX[t], y + DY[t], n, m)) {
						cura *= (d[x + DX[t]][y + DY[t]] - 1);
						curb *= d[x + DX[t]][y + DY[t]];
					}
				}
				a = a * curb + b * cura;
				b = b * curb;
				long gcd = gcd(a, b);
				a /= gcd;
				b /= gcd;
			}
		}
		a = 1L * n * m * b - a;
		print(a, b);		
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
		new forest_vd_slow().run();
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
