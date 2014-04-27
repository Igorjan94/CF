import java.io.*;
import java.util.*;

public class match_pk_exp {

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
		
		long globalSum = 0;
		long globalCount = 0;
		
		for (int mask = 0; mask < (1 << n); mask++) {
			if (Integer.bitCount(mask) != n / 2)
				continue;
			globalCount++;
			int tmask = mask;
			ArrayList<Integer> f = new ArrayList<Integer>();
			ArrayList<Integer> s = new ArrayList<Integer>();
			for (int i = 0; i < n; i++) {
				if (tmask % 2 == 1)
					f.add(a[i]);
				else
					s.add(a[i]);
				tmask /= 2;
			}
			Collections.sort(f);
			Collections.sort(s);
			Collections.reverse(s);
			for (int i = 0; i < n / 2; i++) {
				globalSum += Math.abs(f.get(i) - s.get(i));
			}
		}
		out.println(globalSum / globalCount);

	}

	public void run() {
		try {
			br = new BufferedReader(new InputStreamReader(System.in));
			out = new PrintWriter(System.out);

			// br = new BufferedReader(new FileReader("match_pk_exp.in"));
			// out = new PrintWriter("match_pk_exp.out");
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
		new match_pk_exp().run();
	}
}