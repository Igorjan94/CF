import java.awt.KeyEventDispatcher;
import java.awt.KeyboardFocusManager;
import java.awt.event.KeyEvent;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import java.util.Random;
import java.util.Scanner;
import java.util.InputMismatchException;

import javax.swing.WindowConstants;

public class MainFrame {
	
	static int tempcur = 0;
	static double qq[][][];

	static double f(double x1, double x2)
	{
		return (x2 - x1 * x1) * (x2 - x1 * x1) * 1 + (x1 - 1) * (x1 - 1) * 5;
	}

	static int addLine(double x1, double y1, double x2, double y2, int i)
	{
		double x = x1, y = y1;
		int count = 0;
		if (x1 > x2) {
			x = x2;
			x2 = x1;
			x1 = x;
		}
		if (y1 > y2) {
			y = y2;
			y2 = y1;
			y1 = y;
		}
		int temp = 50;
		double dx = (x2 - x1) / temp;
		double dy = (y2 - y1) / temp;
		while (x <= x2) {
			qq[tempcur][0][i + count] = x;
			qq[tempcur][1][i + count++] = y;
			x += dx;
			y += dy;
		}
		return count;
	}

	public static void main(String[] args) throws IOException {

		Scanner sc = new Scanner(new File("/home/igorjan/206round/Ann/output.txt~"));
		String strert = sc.nextLine();
		qq = new double[5][3][1000000];
		double prevx, prevy, curx = 0, cury = 0;
		try
		{
			for (int j = 0; j <= 100; j++)
				try {
					while (!sc.hasNextDouble())
						sc.next();
					for (int i = 0; sc.hasNextDouble(); i++)
					{
						prevx = curx;
						prevy = cury;
						qq[tempcur][0][i] = curx = sc.nextDouble();
						qq[tempcur][1][i] = cury = sc.nextDouble();
						if (i != 0)
							i += addLine(prevx, prevy, curx, cury, i);
						/*qq[tempcur][2][i] = f(qq[tempcur][0][i], qq[tempcur][1][i]);
						qq[tempcur][0][++i] = qq[tempcur][0][i - 1] - 0.001;
						qq[tempcur][1][i] =   qq[tempcur][1][i - 1];
						qq[tempcur][2][i] = f(qq[tempcur][0][i], qq[tempcur][1][i]);
						qq[tempcur][0][++i] = qq[tempcur][0][i - 1] + 0.002;
						qq[tempcur][1][i] =   qq[tempcur][1][i - 1];
						qq[tempcur][2][i] = f(qq[tempcur][0][i], qq[tempcur][1][i]);
						qq[tempcur][0][++i] = qq[tempcur][0][i - 1] - 0.001;
						qq[tempcur][1][i] =   qq[tempcur][1][i - 1] - 0.001;
						qq[tempcur][2][i] = f(qq[tempcur][0][i], qq[tempcur][1][i]);
						qq[tempcur][0][++i] = qq[tempcur][0][i - 1];
						qq[tempcur][1][i] =   qq[tempcur][1][i - 1] + 0.002;
						qq[tempcur][2][i] = f(qq[tempcur][0][i], qq[tempcur][1][i]);*/
					} 
					tempcur++;	
				}
				catch (InputMismatchException e) {
					System.out.println(tempcur);
				}
		} catch (Exception e) {}
		Random rnd = new Random();
		final List<Plot3D> testPlot = new ArrayList<Plot3D>();

		sc = new Scanner(new File("input.txt"));

		sc.useLocale(Locale.ENGLISH);
		final int m = sc.nextInt(), n = sc.nextInt();
		final double dt = sc.nextDouble(), r = sc.nextDouble();

		final int[] met = new int[m];
		int nn = 1000;
		double eps = 0.01, x1 = -4, x2 = -4, z = 0.0, delta = 0.01;
		double[][] dd = new double[3][1000000];
		int[] colds = new int[1000000];
		int counter = 0;
		for (; z <= 2; z += 0.05)
			for (int i = 0; i < nn; i++)
				for (int j = 0; j < nn; j++)
					if (Math.abs(f(x1 + eps * i, x2 + eps * j) - z) < delta)
					{
						dd[0][counter] = x1 + eps * i;
						dd[1][counter] = x2 + eps * j;
						dd[2][counter] = z;
						colds[counter] = (int)(z*Math.pow(2, 22));
						counter++;
					}

		for (int i = 0; i < m; i++) {
			met[i] = sc.nextInt();
			double sx = sc.nextDouble(), sy = sc.nextDouble(), sz = sc.nextDouble();
			int red = sc.nextInt(), green = sc.nextInt(), blue = sc.nextInt();
			int color = (red << 16) | (green << 8) | blue;
			if (i == 0)
				testPlot.add(new Plot3D(dd[0], dd[1], new double[10000], colds));
			else
				testPlot.add(new Plot3D(qq[i - 1], color));
//			testPlot.add(new Plot3D(LorenzSystemSolver.solove(met[i], r, sx, sy, sz, dt, n), color));
		}

		sc.close();

		int nc = 30000;
		double lc = 100.0;

		double[][] cord = new double[3][nc * 3];
		for (int d = 0; d < 3; d++) {
			for (int i = 0; i < nc; i++) {
				cord[d][nc * d + i] = i * lc / nc;
			}
		}

		testPlot.add(new Plot3D(cord, 0xFFFFFF));

		final PlotViewer pw = new PlotViewer(testPlot);
		pw.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		pw.setVisible(true);

		KeyboardFocusManager manager = KeyboardFocusManager.getCurrentKeyboardFocusManager();
		manager.addKeyEventDispatcher(new KeyEventDispatcher() {
			double tr = r;
			int m = testPlot.size() - 1;

			@Override
			public boolean dispatchKeyEvent(KeyEvent e) {
				if (e.getID() == KeyEvent.KEY_PRESSED) {
					if (e.getKeyCode() == 45 || e.getKeyCode() == 61) {
						if (e.getKeyCode() == 45) {
							tr = Math.max(0, tr - 0.1);
						} else {
							tr = Math.min(100, tr + 0.1);
						}

						for (int i = 0; i < m; i++) {
							double sx = testPlot.get(i).x[0], sy = testPlot.get(i).y[0], sz = testPlot.get(i).z[0];
							double[][] g = LorenzSystemSolver.solove(met[i], tr, sx, sy, sz, dt, n);
							testPlot.get(i).x = g[0];
							testPlot.get(i).y = g[1];
							testPlot.get(i).z = g[2];
						}

						pw.drawPlot();
						pw.setTitle("[+/-] r = " + tr);
					}
				}
				return false;
			}
		});

	}
}
