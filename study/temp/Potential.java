import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class Potential {
	public static void main(String[] args) throws IOException {
		try (BufferedReader br = new BufferedReader(new FileReader(new File("output.txt")))) {
			Random rnd = new Random();
			int inf = 0;
			String[] manufacturers = br.readLine().split(" ");
			int n = manufacturers.length;
			int[] man = new int[n];
			for (int i = 0; i < n; i++) {
				man[i] = Integer.parseInt(manufacturers[i]);
				inf = Math.max(inf, man[i]);
			}

			int loop = 100, cur = 0;

			String[] consumers = br.readLine().split(" ");
			int m = consumers.length;
			int[] con = new int[m];
			for (int i = 0; i < m; i++) {
				con[i] = Integer.parseInt(consumers[i]);
				inf = Math.max(inf, con[i]);
			}

			int[][] w = new int[n][m];

			for (int i = 0; i < n; i++) {
				String[] line = br.readLine().split(" ");
				for (int j = 0; j < m; j++) {
					w[i][j] = Integer.parseInt(line[j]);
					inf = Math.max(inf, w[i][j]);
				}
			}

			print("read", man, con, w);

			int sum = 0;

			for (int i = 0; i < n; i++) {
				sum += man[i];
			}

			for (int i = 0; i < m; i++) {
				sum -= con[i];
			}

			if (sum < 0) {
				int[] updMan = new int[n + 1];
				int[][] updW = new int[n + 1][m];

				for (int i = 0; i < n; i++) {
					updMan[i] = man[i];
				}

				updMan[n] = -sum;

				for (int i = 0; i < n; i++) {
					for (int j = 0; j < m; j++) {
						updW[i][j] = w[i][j];
					}
				}

				man = updMan;
				w = updW;
				++n;
				print("close", man, con, w);
			}

			if (sum > 0) {
				int[] updCon = new int[m + 1];
				int[][] updW = new int[n][m + 1];

				for (int i = 0; i < m; i++) {
					updCon[i] = con[i];
				}

				updCon[m] = sum;

				for (int i = 0; i < n; i++) {
					for (int j = 0; j < m; j++) {
						updW[i][j] = w[i][j];
					}
				}
				con = updCon;
				w = updW;
				++m;
				print("close", man, con, w);

			}

			int[][] x = new int[n][m];

			int[] manc = man.clone(), conc = con.clone();
			for (int i = 0; i < n; i++) {
				for (int j = 0; manc[i] > 0 && j < m; j++) {
					x[i][j] = Math.min(manc[i], conc[j]);
					manc[i] -= x[i][j];
					conc[j] -= x[i][j];
				}
			}

			print("NW", man, con, x);
			inf *= n * m + 1;
			int step = 0;

			while (true) {
				int[] u = new int[n], v = new int[m];
				Arrays.fill(u, inf);
				Arrays.fill(v, inf);

				while (true) {
					boolean found = false;
					for (int i = 0; i < n; i++) {
						if (u[i] == inf) {
							u[i] = 0;
							found = true;
							break;
						}
					}
					if (!found) {
						for (int j = 0; j < m; j++) {
							if (v[j] == inf) {
								v[j] = 0;
								found = true;
								break;
							}
						}
					}
					if (!found) {
						break;
					}

					for (int i = 0; i < n; i++) {
						for (int j = 0; j < m; j++) {
							if (x[i][j] != 0) {
								if (u[i] == inf && v[j] == inf) {
									continue;
								}

								if (u[i] == inf) {
									u[i] = w[i][j] - v[j];
								} else {
									v[j] = w[i][j] - u[i];
								}
							}
						}
					}
				}

				int[][] delta = new int[n][m];
				boolean optimal = true;
				int mi = 0, mj = 0, md = inf;
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < m; j++) {
						delta[i][j] = w[i][j] - u[i] - v[j];
						if (delta[i][j] < 0) {
							optimal = false;
							if (delta[i][j] < md) {
								md = delta[i][j];
								mi = i;
								mj = j;
							}
						}
					}
				}

				if (optimal) {
					break;
				}

				List<Integer> lx = new ArrayList<Integer>();
				List<Integer> ly = new ArrayList<Integer>();

				int hi = rnd.nextInt(n), hj = rnd.nextInt(m);
				for (int i = 0; i < n; i++) {
					if (i != mi && x[i][mj] > 0) {
						hi = i;
						break;
					}
				}
				for (int j = 0; j < m; j++) {
					if (j != mj && x[mi][j] > 0) {
						hj = j;
						break;
					}
				}

				lx.add(mi);
				ly.add(hj);

				lx.add(hi);
				ly.add(hj);

				lx.add(hi);
				ly.add(mj);

				lx.add(mi);
				ly.add(mj);

				int len = lx.size();

				Collections.reverse(lx);
				Collections.reverse(ly);
				int phi = inf;

				for (int q = 0; q < len; q++) {
					int i = lx.get(q), j = ly.get(q);
					if (q % 2 == 0) {
						phi = Math.min(phi, Math.min(man[i], con[j]) - x[i][j]);
					} else {
						phi = Math.min(phi, x[i][j]);
					}
				}

				for (int q = 0; q < len; q++) {
					int i = lx.get(q), j = ly.get(q);
					if (q % 2 == 0) {
						x[i][j] += phi;
					} else {
						x[i][j] -= phi;
					}
				}

				if (phi == 0) {
					if (++cur == loop) {
						break;
					}
				} else {
					cur = 0;
					print(++step, man, con, x);
				}
			}

			print("ans", man, con, x);
		}

	}

	static boolean dfs(int sx, int sy, int x, int y, List<Integer> lx, List<Integer> ly, boolean d, boolean[][] color, boolean[][] p) {
		if (color[x][y]) {
			return sx == x && sy == y;
		}
		color[x][y] = true;

		if (d) {
			for (int i = 0; i < p.length; i++) {
				if (i != x && (p[i][y]) && dfs(sx, sy, i, y, lx, ly, !d, color, p)) {
					lx.add(x);
					ly.add(y);
					return true;
				}
			}
		} else {
			for (int i = 0; i < p[x].length; i++) {
				if (i != y && (p[x][i]) && dfs(sx, sy, x, i, lx, ly, !d, color, p)) {
					lx.add(x);
					ly.add(y);
					return true;
				}
			}
		}

		return false;
	}

	static void print(int name, int[] a, int[] b, int[][] c) {
		print(Integer.toString(name), a, b, c);
	}

	static void print(String name, int[] a, int[] b, int[][] c) {
		int n = a.length, m = b.length;
		int x = name.length(), y = 0;
		for (int v : a) {
			x = Math.max(x, Integer.toString(v).length());
		}
		for (int v : b) {
			y = Math.max(y, Integer.toString(v).length());
		}
		for (int[] d : c) {
			for (int v : d) {
				y = Math.max(y, Integer.toString(v).length());
			}
		}

		System.out.printf("%" + x + "s |", name);
		for (int v : b) {
			System.out.printf(" %" + y + "d", v);
		}
		System.out.println();

		for (int i = 0; i <= x; i++) {
			System.out.print('-');
		}
		System.out.print('+');
		for (int i = 0; i < m; i++) {
			for (int j = 0; j <= y; j++) {
				System.out.print('-');
			}
		}
		System.out.println();

		for (int i = 0; i < n; i++) {
			System.out.printf("%" + x + "d |", a[i]);
			for (int v : c[i]) {
				System.out.printf(" %" + y + "d", v);
			}
			System.out.println();
		}
		System.out.println();
	}
}
