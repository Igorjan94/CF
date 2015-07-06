package task7;

import java.io.Serializable;
import java.util.Random;

public class Layer implements Serializable {
	private static final long serialVersionUID = 10L;
	public static final Random rand = new Random();
	public static final double eps = 0.01;
	public static double e = 1;

	int in, out;
	double[][] w;
	double[] errorToReturn, ans, input;

	public static double f(double x) {
		return 1. / (1. + Math.exp(-x));
	}

	public static double ff(double x) {
		x = f(x);
		return x * (1 - x);
	}

	public static double sum(double[] x, double[][] w, int j) {
		double ans = 0;
		for (int i = 0; i < x.length; i++)
			ans += x[i] * w[i][j];
		return ans;
	}

	public Layer(int in, int out) {
		this.in = ++in;
		this.out = ++out;
		ans = new double[out];
		errorToReturn = new double[in];
		w = new double[in][out];
		for (int i = 0; i < in; i++)
			for (int j = 0; j < out; j++)
				w[i][j] = (eps * (rand.nextInt() % 100));
	}

	public double[] output(double[] input) {
		input[input.length - 1] = -1;
		this.input = input;
		for (int i = 0; i < out; i++)
			ans[i] = f(sum(input, w, i));
		return ans;
	}

	public double[] getError(double[] error) {

		for (int i = 0; i < in; i++) {
			errorToReturn[i] = 0;
			for (int j = 0; j < out; j++) {
				errorToReturn[i] += error[j] * w[i][j];
				w[i][j] -= e * error[j] * input[i] * ff(ans[j]);
			}
		}
		return errorToReturn;
	}
}