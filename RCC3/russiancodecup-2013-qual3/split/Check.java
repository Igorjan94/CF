import java.util.StringTokenizer;

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;
import ru.ifmo.testlib.Outcome.Type;


public class Check implements Checker {
	
	@Override
	public Outcome test(InStream inf, InStream ouf, InStream ans) {
		int juryAns = ans.nextInt();
		if (juryAns == -1) {
			if (ouf.nextInt() == -1) {
				return new Outcome(Type.OK, "OK");
			} else {
				return new Outcome(Type.WA, "Expected \"-1\"");
			}
		}
		int n = inf.nextInt();
		String[] lines = new String[3];
		int[][] a = new int[3][n];
		int[] count = new int[3 * n];
		for (int i = 0; i < 3; i++) {
			lines[i] = ouf.nextLine();
			StringTokenizer st = new StringTokenizer(lines[i]);
			for (int j = 0; j < n; j++) {
				if (!st.hasMoreElements()) {
					return new Outcome(Type.WA, "Unexpected end of line in line #" + (i + 1));
				}
				a[i][j] = Integer.parseInt(st.nextToken());
				if (i == 0 && j == 0 && a[i][j] == -1) {
					return new Outcome(Type.WA, "-1 unexpected");
				}
				if (a[i][j] < 1 || a[i][j] > 3 * n) {
					return new Outcome(Type.WA, "Invalid element " + a[i][j]);
				}
				count[a[i][j] - 1]++;
				if (count[a[i][j] - 1] > 1) {
					return new Outcome(Type.WA, "Duplicate element " + a[i][j]);
				}
			}
			if (st.hasMoreElements()) {
				return new Outcome(Type.WA, "Line #" + i + " contains more than n elements");
			}
		}
		
		for (int i = 0; i < n; i++) {
			if (a[0][i] + a[1][i] != a[2][i]) {
				return new Outcome(Type.WA, a[0][i] + " + " + a[1][i] + " != " + a[2][i]);
			}
		}

		return new Outcome(Type.OK, "OK");
	}
}
