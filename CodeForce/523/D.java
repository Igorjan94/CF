import java.io.*;
import java.util.*;
import java.math.BigInteger;
import java.util.Map.Entry;

import static java.lang.Math.*;

public class D extends PrintWriter {
	class Event implements Comparable<Event> {

		final int id;
		final boolean type;
		final long time;

		public Event(int id, long time, boolean type) {
			this.id = id;
			this.time = time;
			this.type = type;
		}

		public int compareTo(Event e) {
			int cmp;
			if ((cmp = Long.compare(time, e.time)) != 0) {
				return cmp;
			}
			if ((cmp = Boolean.compare(type, e.type)) != 0) {
				return cmp;
			}

			return Integer.compare(id, this.id);
		}

	}

	void run() {
		int n = nextInt(), m = nextInt(), f = m;

		Queue<Integer> v = new ArrayDeque<Integer>(n);
		PriorityQueue<Event> h = new PriorityQueue<Event>(n * 2);

		long[] ans = new long[n], d = new long[n];

		for (int i = 0; i < n; i++) {
			h.add(new Event(i, nextInt(), true));
			d[i] = nextInt();
		}

		while (!h.isEmpty()) {
			Event e = h.poll();
			if (e.type) {
				int id = e.id;
				if (f > 0) {
					--f;
					h.add(new Event(id, e.time + d[id], false));
				} else {
					v.add(id);
				}
			} else {
				ans[e.id] = e.time;
				if (v.isEmpty()) {
					f = min(f + 1, m);
				} else {
					int id = v.poll();
					h.add(new Event(id, e.time + d[id], false));
				}
			}

		}

		for (long e : ans) {
			println(e);
		}

	}

	void skip() {
		while (hasNext()) {
			next();
		}
	}

	int[][] nextMatrix(int n, int m) {
		int[][] matrix = new int[n][m];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				matrix[i][j] = nextInt();
		return matrix;
	}

	String next() {
		while (!tokenizer.hasMoreTokens())
			tokenizer = new StringTokenizer(nextLine());
		return tokenizer.nextToken();
	}

	boolean hasNext() {
		while (!tokenizer.hasMoreTokens()) {
			String line = nextLine();
			if (line == null) {
				return false;
			}
			tokenizer = new StringTokenizer(line);
		}
		return true;
	}

	int[] nextArray(int n) {
		int[] array = new int[n];
		for (int i = 0; i < n; i++) {
			array[i] = nextInt();
		}
		return array;
	}

	int nextInt() {
		return Integer.parseInt(next());
	}

	long nextLong() {
		return Long.parseLong(next());
	}

	double nextDouble() {
		return Double.parseDouble(next());
	}

	String nextLine() {
		try {
			return reader.readLine();
		} catch (IOException err) {
			return null;
		}
	}

	public D(OutputStream outputStream) {
		super(outputStream);
	}

	static BufferedReader reader;
	static StringTokenizer tokenizer = new StringTokenizer("");
	static Random rnd = new Random();
	static boolean OJ;

	public static void main(String[] args) throws IOException {
		OJ = System.getProperty("ONLINE_JUDGE") != null;
		D solution = new D(System.out);
		if (OJ) {
			reader = new BufferedReader(new InputStreamReader(System.in));
			solution.run();
		} else {
			reader = new BufferedReader(new FileReader(new File(D.class.getName() + ".txt")));
			long timeout = System.currentTimeMillis();
			while (solution.hasNext()) {
				solution.run();
				solution.println();
				solution.println("----------------------------------");
			}
			solution.println("time: " + (System.currentTimeMillis() - timeout));
		}
		solution.close();
		reader.close();
	}
}
