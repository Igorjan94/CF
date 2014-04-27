import java.io.*;
import java.util.*;

public class TestGen {

	int MAX_COUNT_OF_PLAYERS = 1000000;

	PrintWriter out;
	Random rnd;
	int tNumber;

	class Test {
		ArrayList<TestCase> tests;
		int sum = 0;

		void printTest() throws IOException {
			if (tNumber < 10)
				out = new PrintWriter("../tests/0" + tNumber);
			else
				out = new PrintWriter("../tests/" + tNumber);
			System.err.println("[" + tNumber + "]");
			tNumber++;

			out.println(tests.size());
			for (TestCase t : tests) {
				out.print(t);
			}

			out.close();
		}

		Test() {
			tests = new ArrayList<TestGen.TestCase>();
		}

		public void add(TestCase testCase) throws IOException {
			if (sum + testCase.players.size() > MAX_COUNT_OF_PLAYERS) {
				printTest();
				tests = new ArrayList<TestGen.TestCase>();
				sum = 0;
			}
			tests.add(testCase);
			sum += testCase.players.size();
		}

	}

	class Ship {
		int a, b;

		public Ship(int a, int b) {
			this.a = a;
			this.b = b;
			if ((a + b) % 4 != 0) {
				throw new AssertionError();
			}
		}

		Ship(int sum) {
			if (sum % 4 != 0)
				throw new AssertionError();
			a = rnd.nextInt(sum + 1);
			b = sum - a;
		}

		@Override
		public String toString() {
			return a + " " + b;
		}
	}

	class TestCase {

		ArrayList<Integer> players;

		TestCase() {
			players = new ArrayList<Integer>();
		}

		@Override
		public String toString() {
			StringBuilder res = new StringBuilder("");
			res.append(players.size());
			res.append("\n");
			for (int i = 0; i < players.size(); i++) {
				if (i != 0) {
					res.append(" ");
				}
				res.append(players.get(i));
			}
			res.append("\n");
			return res.toString();
		}
	}

	TestCase randomTest(int n, int k) {
		TestCase res = new TestCase();
		for (int i = 0; i < n; i++) {
			res.players.add(rnd.nextInt(k) + 1);
		}
		return res;
	}

	TestCase limitedTest(int n, int k, int t) {
		TestCase res = new TestCase();
		int[] p = new int[t];
		for (int i = 0; i < t; i++) {
			p[i] = 1 + rnd.nextInt(k);
		}
		for (int i = 0; i < n; i++) {
			res.players.add(p[rnd.nextInt(t)]);
		}
		return res;
	}
	
	TestCase tuiMorseTest(int n) {
		TestCase res = new TestCase();
		int[] p = new int[2];
		for (int i = 0; i < 2; i++)
			p[i] = 1 + rnd.nextInt(100000);
		for (int i = 0 ;i < n; i++) {
			res.players.add(p[Integer.bitCount(i) % 2]);
		}
		return res;
	}
	
	TestCase sample() {
		TestCase res = new TestCase();
		res.players.add(20);
		res.players.add(30);
		res.players.add(10);
		res.players.add(40);
		return res;
	}
	
	public void solve() throws IOException {
		tNumber = 1;
		rnd = new Random(31);

		Test t = new Test();
		t.add(sample());
		t.printTest();
		for (int d = 2; d < 10; d += 2) {
			int maxV = 10;
			if (d == 8)
				maxV = 4;
			for (int mask = 0; mask < Math.pow(maxV, d); mask++) {
				TestCase tc = new TestCase();
				int tmask = mask;
				for (int i = 0; i < d; i++) {
					tc.players.add(tmask % maxV + 1);
					tmask /= maxV;
				}
				t.add(tc);
			}
		}
		t.add(randomTest(100000, 1000000));
		t.add(randomTest(100000, 2));
		t.add(limitedTest(100000, 1000000, 10));
		t.add(limitedTest(100000, 1000000, 10000));
		t.add(tuiMorseTest(100000));
		t.printTest();
	}

	public void run() {
		try {

			solve();

		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		new TestGen().run();
	}
}
