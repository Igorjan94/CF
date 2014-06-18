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
    final static double POINTS_PER_LINE = 100.0;
	static double qq[][][];
	static boolean d3 = false;

	static double f(double x1, double x2)
	{
		return (x2 - x1 * x1) * (x2 - x1 * x1) * 100 + (x1 - 1) * (x1 - 1) * 5;
	}

	public static void writeln(Object o) {
        System.out.println(o);
	}

	static int addLine(double x1, double y1, double x2, double y2, int i)
	{
		double x = x1, y = y1, z = f(x1, y1);
		int count = 0;
		double dx = (x2 - x1) / POINTS_PER_LINE;
		double dy = (y2 - y1) / POINTS_PER_LINE;
		double dz = (f(x1, y1) - f(x2, y2)) / POINTS_PER_LINE;
		if (Math.sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) > 1) {
            dx /= 10;
            dy /= 10;
            dz /= 10;
		}
		while (true) {
			qq[tempcur][0][i + count] = x;
			qq[tempcur][1][i + count] = y;
			qq[tempcur][2][i + count++] = d3 ? z : 0;
			if (x2 > x1 && x > x2 || x1 > x2 && x < x2)
                break;
            x += dx;
			y += dy;
			z += dz;
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
            while (true)
				try {
					while (!sc.hasNextDouble())
						sc.next();
					for (int i = 0; sc.hasNextDouble(); i++)
					{
						prevx = curx;
						prevy = cury;
						qq[tempcur][0][i] = curx = sc.nextDouble();
						qq[tempcur][1][i] = cury = sc.nextDouble();
                        qq[tempcur][2][i] = f(curx, cury);
						if (i != 0)
							i += addLine(prevx, prevy, curx, cury, i);
					}
					tempcur++;
				}
				catch (InputMismatchException e) {
					System.out.println(tempcur);
				}
		} catch (Exception e) {}

		sc = new Scanner(new File("input.txt"));
        sc.useLocale(Locale.ENGLISH);
		final int m = sc.nextInt();
		final double eps = sc.nextDouble();
		final double zeps = sc.nextDouble();
		final double delta = sc.nextDouble();
		final double x10 = sc.nextDouble();
		final double x20 = sc.nextDouble();
		final double z0 = sc.nextDouble();
		final double x1max = sc.nextDouble();
		final double x2max = sc.nextDouble();
		final double zmax = sc.nextDouble();

		double[][] dd = new double[3][1000000];
		int[] colds = new int[1000000];
		int counter = 0;
		for (double z = z0; z <= zmax; z += zeps)
			for (double x1 = x10; x1 < x1max; x1 += eps)
				for (double x2 = x20; x2 < x2max; x2 += eps)
					if (Math.abs(f(x1, x2) - z) < delta)
					{
						dd[0][counter] = x1;
						dd[1][counter] = x2;
						dd[2][counter] = z;
						colds[counter] = (int)(z * Math.pow(2, 22) * 1.5);
						counter++;
					}

		final List<Plot3D> testPlot = new ArrayList<Plot3D>();
		if (d3)
            testPlot.add(new Plot3D(dd, colds));
        else
            testPlot.add(new Plot3D(dd[0], dd[1], new double[1000000], colds));
		for (int i = 0; i < m; i++) {
			int red = sc.nextInt(), green = sc.nextInt(), blue = sc.nextInt();
			int color = (red << 16) | (green << 8) | blue;
            testPlot.add(new Plot3D(qq[i], color));
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
	}
}
