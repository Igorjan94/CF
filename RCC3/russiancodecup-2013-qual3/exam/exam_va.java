import java.io.*;
import java.util.*;

public class exam_va implements Runnable {
	public static void main(String[] args) {
		new Thread(new exam_va()).run();
	}

	BufferedReader br;
	StringTokenizer in;
	PrintWriter out;

	public String nextToken() throws IOException {
		while (in == null || !in.hasMoreTokens()) {
			in = new StringTokenizer(br.readLine(), ": ");
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
		int t1 = nextInt() * 60 * 60 + nextInt() * 60 + nextInt();
		int t2 = nextInt() * 60 * 60 + nextInt() * 60 + nextInt();

		if (t1 >= t2)
			t2 += 24 * 60 * 60;

		t1 += nextInt() * 60;

		if (t1 <= t2) {
			out.println("Perfect");
		} else if (t1 <= t2 + 60 * 60) {
			out.println("Test");
		} else {
			out.println("Fail");
		}

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
