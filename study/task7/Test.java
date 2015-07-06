package task7;

import java.io.IOException;
import java.util.List;
import java.util.Random;

public class Test {

	public static void main(String[] args) throws IOException {
		Random rnd = new Random();
		List<Digit> d = IOUtils.readDigitSet("ann/train");
		for (int i = 0; i < 10; i++) {
			(new SimViz(10, d.get(rnd.nextInt(d.size())))).setVisible(true);
		}

	}

}
