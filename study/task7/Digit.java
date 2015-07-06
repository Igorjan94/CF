package task7;

import java.io.Serializable;

public class Digit implements Serializable {
	public int label;
	public final int len;
	public final int size;
	private final double[] signal;

	public Digit(double[] signal, int len, int label) {
		this.size = len * len + 1;
		this.signal = new double[len * len + 1];
		for (int i = 0; i < size - 1; i++)
			this.signal[i] = signal[i];
		this.signal[size - 1] = -1;
		this.label = label;
		this.len = len;
	}
	
	public Digit(byte[] buffer, int off, int len, int label) {
		this.len = len;
		this.size = len * len + 1;
		this.label = label;
		signal = new double[size];
		for (int i = 0; i < size - 1; i++)
			signal[i] = (buffer[i + off] & 0xff) / 255.0;
		signal[size - 1] = -1;
	}

	double getSignal(int i) {
		return signal[i];
	}

	double getSignal(int x, int y) {
		return signal[x + len * y];
	}
	
	double[] getSignal() {
		return signal;
	}

	private static final long serialVersionUID = 10L;
}
