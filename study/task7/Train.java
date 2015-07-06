package task7;

import java.io.File;
import java.io.IOException;
import java.util.List;

public class Train {

	static final String path = "ann" + File.separator;

	static void writeln(Object o) {
		System.out.println(o);
	}

	public static void main(String[] args) throws IOException {
		int n = IOUtils.imageLength;

		int count = 60000;
		List<Digit> train = IOUtils.readDigitSet(path + "train");
		List<Digit> test = IOUtils.readDigitSet(path + "test");
		train = train.subList(0, count);
		ArtificialNeuralNetwork networks[] = new ArtificialNeuralNetwork[n - 2];
		int[][][] cm = new int[n][10][10];
		int begin = 12;
		int index = begin;
		double mx = 0;
		double cur = System.currentTimeMillis();
		writeln("begin");
		for (int hidden = begin; hidden < begin + 1; ++hidden) {
			networks[hidden] = new ArtificialNeuralNetwork(n * n, n * 10, 10);

			int counter = 0;
			for (Digit digit : train) {
				if (++counter % 2000 == 0)
				{
					writeln(counter);
					//ArtificialNeuralNetwork.writeln(digit.getSignal());
					Layer.e /= 1.3;///e polls.addVote?owner_id=-29253653&poll_id=161027588&answer_id=525733035
				}
				networks[hidden].add(digit);
			}

			for (Digit digit : test) {
				++cm[hidden][digit.label][networks[hidden].getArgMax(digit)];
			}
			double percent = 0;
			double sum = 0;
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++)
					sum += cm[hidden][i][j];
				percent += cm[hidden][i][i];
			}
			percent /= sum;
			if (percent > mx) {
				mx = percent;
				index = hidden;
			}
			writeln("percent = " + (percent * 100) + "%");
		}
		writeln(index);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				System.out.printf("%4d ", cm[index][i][j]);
			}
			System.out.println();
		}
		writeln(System.currentTimeMillis() - cur);
		IOUtils.writeAnn(networks[index], path + "output.ann");
	}
}
