package task7;

import java.io.Serializable;
import java.util.Random;

public class ArtificialNeuralNetwork implements Serializable {

	static Random rand;
	private static final long serialVersionUID = 10L;
	private final static double c = 1;
	int in, out;
	int n;
	Layer[] layers;
	double[] ans;
	double[][] error;

	public static void writeln(double[] a) {
		for (int i = 0; i < a.length; i++)
			System.out.printf("%6.3f ", a[i]);
		System.out.println();
	}

	static void writeln(Object o) {
		System.out.println(o);
	}

	public ArtificialNeuralNetwork(int... layerSizes) {
		n = layerSizes.length - 1;
		layers = new Layer[n];
		in = layerSizes[0];
		out = layerSizes[n];
		ans = new double[out + 1];
		error = new double[n + 1][];
		error[n] = new double[out + 1];
		for (int i = 0; i < n; i++)
			layers[i] = new Layer(layerSizes[i], layerSizes[i + 1]);
	}

	void get(Digit digit) {
		ans = digit.getSignal();
		for (int i = 0; i < n; i++) {
			ans = layers[i].output(ans);
		}
	}

	public void add(Digit digit) {
		get(digit);
		for (int i = 0; i < out; i++)
			error[n][i] = -((i != digit.label ? 0 : c) - ans[i]);// * ans[i] * (1 - ans[i]);
		for (int i = n - 1; i >= 0; --i)
			error[i] = layers[i].getError(error[i + 1]);
	}

	public int getArgMax(Digit digit) {
		get(digit);
		double max = 0;
		int index = 0;
		for (int i = 0; i < out; i++)
			if (ans[i] > max)
				max = ans[index = i];
		return index;
	}

}
