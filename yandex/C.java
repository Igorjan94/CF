import java.io.*;
import java.util.*;

public class C {

	int findd(String a, int k, char c) {
		for (int i = k; i < 8; i++)
			if (a.charAt(i) == c)
				return i;
		return -1;
	}

	void run() throws IOException {
		String a = next();
		String s = "0000";
		int k = 0, prev = 0;
		for (int i = 0; i < 4; i++) {
			while (findd(a, k, s.charAt(i)) == -1) {
				char c = s.charAt(i);
				c++;
				s = s.substring(0, i) + c + s.substring(i + 1);
			}

			prev = k;
			k = findd(a, k, s.charAt(i)) + 1;
			if (8 - k + 1 < 4 - i) {
				char c = s.charAt(i);
				c++;
				s = s.substring(0, i) + c + s.substring(i-- + 1);
				k = prev;
				continue;
			}
		}		System.out.print(s);

		pw.println(s);
	}

	int[] na(int a_len) throws IOException {
		int[] _a = new int[a_len];
		for (int i = 0; i < a_len; i++)
			_a[i] = ni();
		return _a;
	}

	String next() throws IOException {
		while (st == null || !st.hasMoreTokens())
			st = new StringTokenizer(br.readLine());
		return st.nextToken();
	}

	int ni() throws IOException {
		return Integer.parseInt(next());
	}

	long nextLong() throws IOException {
		return Long.parseLong(next());
	}

	String nl() throws IOException {
		return br.readLine();
	}

	static PrintWriter pw;
	static BufferedReader br;
	static StringTokenizer st;

	public static void main(String[] args) throws IOException {
		pw = new PrintWriter("number.out");
		br = new BufferedReader(new FileReader(new File("number.in")));

		new C().run();

		br.close();
		pw.close();
	}

}
