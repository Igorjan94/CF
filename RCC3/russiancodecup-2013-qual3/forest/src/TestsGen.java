import java.io.*;
import java.util.*;

public class TestsGen {

	static class TestWriter {
		static PrintWriter out;
		static int done = 0;

		static void init(int n) throws FileNotFoundException {
			done++;
			if (done < 10)
				out = new PrintWriter(str + "0" + String.valueOf(done));
			else
				out = new PrintWriter(str + String.valueOf(done));
			out.println(n);
		}

		static void close() {
			out.close();
		}

		static void printTest(int n, int m, boolean newTest) throws IOException {
			if (newTest) {
				TestWriter.init(1);
			}
			out.println(n + " " + m);
			if (newTest) {
				TestWriter.close();
			}
		}

	}

	static final Random rnd = new Random(556668949239L);

	static String str = "../tests/";

	static void genSample() throws IOException {
		TestWriter.init(2);
		TestWriter.printTest(1, 3, false);
		TestWriter.printTest(4, 5, false);
		TestWriter.close();
	}

	static int MAX = (int) (1e+7);

	private static void genCorrectness() throws IOException {
		TestWriter.init(100 * 100 - 1);
		for (int i = 1; i <= 100; i++) {
			for (int j = 1; j <= 100; j++) {
				if (i + j > 2) {
					TestWriter.printTest(i, j, false);
				}
			}
		}
		TestWriter.close();
		TestWriter.init(201);
		for (int i = 1; i <= 100; i++) {
			TestWriter.printTest(i, MAX, false);
			TestWriter.printTest(MAX, i, false);
		}
		TestWriter.printTest(MAX, MAX, false);
		TestWriter.close();
	}

	static void genPerfomance() throws IOException {
		TestWriter.init(10000);
		for (int i = 0; i < 10000; i++) {
			int n = 0, m = 0;
			while (n + m <= 1) {
				n = rnd.nextInt(MAX) + 1;
				m = rnd.nextInt(MAX) + 1;
			}
			TestWriter.printTest(n, m, false);
		}
		TestWriter.close();
	}

	public static void main(String[] args) throws IOException {
		new File("../tests").mkdir();
		genSample();
		genCorrectness();
		genPerfomance();
		return;
	}

}
