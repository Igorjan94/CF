import java.io.*;
import java.util.*;

public class message_va_wa implements Runnable {
	public static void main(String[] args) {
		new Thread(new message_va_wa()).run();
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

	int mod = 1000000007;

	public void solve() throws IOException {
		char[] c = nextToken().toCharArray();

		int all = 1;
		for (int i = 0; i < c.length; i++) {
			if (c[i] == '?') {
				all = (all * 2) % mod;
			}
		}

		int right = 1;
		for (int i = 0; i < c.length / 2; i++) {
			if (c[i] == '?') {
				if (c[i + c.length / 2] == '?')
					right = (right * 2) % mod;
			}
			if (c[i + c.length / 2] == '?') {
				continue;
			}
			if (c[i] != c[i + c.length / 2])
				right = 0;
		}

		out.println(((all - right) % mod + mod) % mod);
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
