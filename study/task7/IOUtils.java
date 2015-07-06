package task7;

import java.io.ByteArrayOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.List;

public class IOUtils {
	public static final int imageLength = 28, imageSize = imageLength * imageLength;;

	public static void writeAnn(ArtificialNeuralNetwork ann, String path) throws IOException {
		try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(path))) {
			oos.writeObject(ann);
		}
	}

	public static ArtificialNeuralNetwork readAnn(String path) throws IOException, ClassNotFoundException {
		try (ObjectInputStream oos = new ObjectInputStream(new FileInputStream(path))) {
			return (ArtificialNeuralNetwork) oos.readObject();
		}
	}

	public static List<Digit> readDigitSet(String path) throws IOException {
		ByteArrayOutputStream stream = new ByteArrayOutputStream();
		byte[] buffer = new byte[1 << 12];

		try (FileInputStream fis = new FileInputStream(path + ".images")) {
			int len;
			while ((len = fis.read(buffer)) > 0) {
				stream.write(buffer, 0, len);
			}
		}

		byte[] images = stream.toByteArray();
		stream.reset();

		try (FileInputStream fis = new FileInputStream(path + ".labels")) {
			int len;
			while ((len = fis.read(buffer)) > 0) {
				stream.write(buffer, 0, len);
			}
		}
		byte[] labels = stream.toByteArray();

		List<Digit> digitSet = new ArrayList<Digit>(1 << 15);

		for (int i = 16, j = 8; i + imageSize <= images.length && j < labels.length; i += imageSize, j += 1) {
			int label = labels[j];
			digitSet.add(new Digit(images, i, imageLength, label));
		}

		return digitSet;
	}
}
