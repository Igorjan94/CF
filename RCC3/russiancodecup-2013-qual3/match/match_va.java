import java.io.*;
import java.util.*;

public class match_va implements Runnable {
	public static void main(String[] args) {
		new Thread(new match_va()).run();
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

	public void solve() throws IOException {
		int n = nextInt();

		int[] a = new int[n];

		for (int i = 0; i < a.length; i++) {
			a[i] = nextInt();
		}

		Arrays.sort(a);

		long sum = 0;
		for (int i = 0; i < a.length; i++) {
			sum += a[i] * (i < n / 2 ? -1 : 1);
		}

		out.println(sum);
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
