import java.io.*;
import java.util.*;

public class match_pk {

	BufferedReader br;
	PrintWriter out;
	StringTokenizer st;

	public String nextToken() throws IOException {
		while ((st == null) || (!st.hasMoreTokens()))
			st = new StringTokenizer(br.readLine());
		return st.nextToken();
	}

	public int nextInt() throws IOException {
		return Integer.parseInt(nextToken());
	}

	public double nextDouble() throws IOException {
		return Double.parseDouble(nextToken());
	}

	public long nextLong() throws IOException {
		return Long.parseLong(nextToken());
	}

	public void solve() throws IOException {
		int n = nextInt();
		int[] a = new int[n];
		for (int i = 0; i < n; i++) {
			a[i] = nextInt();
		}
		Arrays.sort(a);
		long ans = 0;
		for (int i = 0; i < n; i++) {
			ans += (i < n / 2) ? -a[i] : a[i];
		}
		out.println(ans);
	}

	public void run() {
		try {
			br = new BufferedReader(new InputStreamReader(System.in));
			out = new PrintWriter(System.out);

			//br = new BufferedReader(new FileReader("match.in"));
			//out = new PrintWriter("match_pk.out");

			int t = nextInt();
			for (int i = 0; i < t; i++) {
				solve();
			}
			out.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		new match_pk().run();
	}
}