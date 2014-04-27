import java.io.*;
import java.util.*;

public class ExamTestsGen {

    static int done = 0;

    static final Random rand = new Random(556668949239L);

    static final int MAX_TIME = 2000;
    static final int SEC_IN_DAY = 60 * 60 * 24;

    int randFromTo(int from, int to) {
	return rand.nextInt(to - from + 1) + from;
    }

    class Test {
	int S, F, k;

	public Test(int s, int f, int k) {
	    super();
	    S = (s + SEC_IN_DAY) % SEC_IN_DAY;
	    F = (f + SEC_IN_DAY) % SEC_IN_DAY;
	    this.k = k;
	}

    }

    static ArrayList<Test> test = new ArrayList<Test>();
    static PrintWriter out;

    static void print() throws IOException {
	done++;
	System.err.println(done);
	PrintWriter out;
	if (done < 10)
	    out = new PrintWriter("../tests/0" + String.valueOf(done));
	else
	    out = new PrintWriter("../tests/" + String.valueOf(done));

	out.println(test.size());
	for (int i = 0; i < test.size(); i++) {
	    int S = test.get(i).S, F = test.get(i).F, k = test.get(i).k;
	    out.printf("%02d:%02d:%02d %02d:%02d:%02d %d\r\n", S / 3600,
		    S / 60 % 60, S % 60, F / 3600, F / 60 % 60, F % 60, k);
	}
	test.clear();
	out.close();
    }

    void genSimple() throws IOException {
	test.add(new Test(3723, 3903, 3));
	test.add(new Test(83534, 899, 91));
	test.add(new Test(0, 0, 1000));
	test.add(new Test(3600, 18000, 666));
	print();
    }

    void genAll() throws IOException {
	for (int i = 0; i < 2440; i++)
	    test.add(new Test(rand.nextInt(SEC_IN_DAY), rand
		    .nextInt(SEC_IN_DAY), rand.nextInt(MAX_TIME)));

	ArrayList<Integer> times = new ArrayList<>();
	for (int i = 1; i < 6; i++)
	    times.add(i);
	for (int i = 50; i < 71; i++)
	    times.add(i);
	for (int i = 23; i < 26; i++)
	    for (int j = -10; j < 11; j++)
		times.add(i * 60 + j);
	times.add(2000);
	int[] mn = { 1, 60, 450, 3600};

	for (int k : mn)
	    for (int d = -10; d < 11; d++)
		for (int time : times) {
		    int t = rand.nextInt(SEC_IN_DAY);
		    test.add(new Test(t, t + k * d, time));
		}
	print();
    }

    public void run() throws IOException {
	new File("../tests").mkdir();

	genSimple();

	genAll();
    }

    public static void main(String[] args) throws IOException {
	new ExamTestsGen().run();
    }
}
