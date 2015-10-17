import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.StringTokenizer;

public class G {

	static BufferedReader bufferedReader;
	static StringTokenizer stringTokenizer;
	static PrintWriter out;

	class Node {
		Node l, r;
		int f, t;

		int[] a, b, c;
		int[] u, d;

		long[] s;

		Node(int id, int val) {
			a = new int[] { val };
			b = new int[] { id };
			s = new long[] { id };

			f = t = id;
		}

		Node(Node l, Node r) {
			this.l = l;
			this.r = r;

			f = l.f;
			t = r.t;

			int n = l.a.length;
			int m = r.a.length;

			a = new int[n + m];
			b = new int[n + m];
			c = new int[n + m];

			for (int lp = 0, rp = 0, i = 0; i < a.length; i++) {
				if ((lp < n && (rp >= m || l.a[lp] <= r.a[rp]))) {
					a[i] = l.a[lp];
					b[i] = l.b[lp];
					c[i] = ~lp;
					++lp;
				}
				else {
					a[i] = r.a[rp];
					b[i] = r.b[rp];
					c[i] = rp;
					++rp;
				}
			}

			u = new int[n + m];
			d = new int[n + m];

			s = new long[n + m];

			int pu = -1, pd = -1;
			long ps = 0;

			for (int i = 0; i < s.length; i++) {
				u[i] = pu;
				d[i] = pd;
				s[i] = ps;

				if (c[i] < 0) {
					u[i] = i;
				}
				else {
					d[i] = i;
				}

				s[i] += b[i];

				pu = u[i];
				pd = d[i];
				ps = s[i];

			}


		}

		void sum(int from, int to, int i) {
			if (to < from || t < from || to < f) {
				return;
			}

			if (from <= f && t <= to) {
				curSum += s[i];
				cnt += i + 1;
			}
			else {

				int lp = u[i];
				if (lp != -1) {
					l.sum(from, to, ~c[lp]);
				}

				int rp = d[i];
				if (rp != -1) {
					r.sum(from, to, c[rp]);
				}
			}
		}

	}

	long curSum;
	long cnt;

	long sum(int d, int k) {
		curSum = cnt = 0;
		tree.sum(d + 1, 1 << 21, k);
		return curSum - cnt * d;
	}

	Node[] node;
	Node tree;

	void run() {

		int q = nextInt(), n = nextInt();

		node = new Node[n];

		for (int i = 0; i < n; i++) {
			int t = nextInt();
			node[i] = new Node(t, i);
		}

		Arrays.sort(node, new Comparator<Node>() {
			public int compare(Node u, Node v) {
				int cmp = Integer.compare(u.f, v.f);
				if (cmp == 0) {
					return Integer.compare(u.a[0], v.a[0]);
				}
				return cmp;
			}
		});

		int size = n;
		while (size > 1) {
			int cur = 0;

			for (int i = 1; i < size; i += 2) {
				node[cur++] = new Node(node[i - 1], node[i]);
			}

			if (size % 2 == 1) {
				node[cur++] = node[size - 1];
			}
			size = cur;
		}

		tree = node[0];

		while (--q >= 0) {
			int d = nextInt(), r = nextInt();

			int x = 0, y = n - 1;

			while (y - x > 1) {
				int z = (x + y) / 2;

				if (sum(d, z) < r) {
					x = z;
				}
				else {
					y = z;
				}
			}

			if (sum(d, x) < r) {
				++x;
			}

			if (x == n || sum(d, x) < r) {
				out.print(0);
			}
			else {
				out.print(x + 1);
			}
			out.print(' ');

		}

	}

	int nextInt() {
		return Integer.parseInt(next());
	}

	long nextLong() {
		return Long.parseLong(next());
	}

	String next() {
		while (stringTokenizer == null || !stringTokenizer.hasMoreTokens()) {
			stringTokenizer = new StringTokenizer(nextLine());
		}
		return stringTokenizer.nextToken();
	}

	String nextLine() {
		try {
			return bufferedReader.readLine();
		}
		catch (IOException err) {
			return null;
		}
	}

	public static void main(String[] args) throws IOException {
		bufferedReader = new BufferedReader(new InputStreamReader(System.in));
		out = new PrintWriter(System.out);
		// bufferedReader = new BufferedReader(new FileReader(task + ".txt"));
		// out = new PrintWriter(new File(task + ".out"));
		new G().run();
		out.close();
		bufferedReader.close();
	}
}
