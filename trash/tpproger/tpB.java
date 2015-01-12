import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Calendar;
import java.util.HashMap;
import java.util.Map;
import java.util.StringTokenizer;

public class tpB {

	static BufferedReader bufferedReader;
	static StringTokenizer stringTokenizer;
	static PrintWriter out;
	static String task = "a";

	void writeln(Object o) {
		System.out.println(o);
	}

	void run() {
		int n = nextInt();
		Map<String, Integer> map = new HashMap<>();
		String city, time;
		int t;
		for (int i = 0; i < n; i++) {
			city = next();
			time = next().substring(3);
			t = Integer.parseInt(time);
			map.put(city, t);
		}
		String from, to, begin;
		int m = nextInt();
		for (int i = 0; i < m; i++) {
			from = next();
			to = from.substring(from.indexOf('-') + 1);
			from = from.substring(0, from.indexOf('-'));
			begin = next();
			time = next();
			Calendar c = Calendar.getInstance();
			c.set(0, 0, 0, Integer.parseInt(begin.substring(0, 2)), Integer.parseInt(begin.substring(3)), 0);
			c.add(Calendar.HOUR, Integer.parseInt(time.substring(0, 2)) + map.get(to) - map.get(from));
			c.add(Calendar.MINUTE, Integer.parseInt(time.substring(3)));
			writeln(c.getTime().toString().substring(11, 16));
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
		} catch (IOException err) {
			return null;
		}
	}

	public static void main(String[] args) throws IOException {
		bufferedReader = new BufferedReader(new InputStreamReader(System.in));
		out = new PrintWriter(System.out);
		// bufferedReader = new BufferedReader(new FileReader(task + ".txt"));
		// out = new PrintWriter(new File(task + ".out"));
		new tpB().run();
		out.close();
		bufferedReader.close();
	}
}