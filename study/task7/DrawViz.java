package task7;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.geom.Line2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.WindowConstants;

public class DrawViz extends JFrame {
	static void writeln(Object o) {
		System.out.println(o);
	}

	int n = IOUtils.imageLength, m = n * 25;
	int cnt;
	int lastX = -1, lastY = -1;
	BufferedImage canvas = new BufferedImage(m, m, BufferedImage.TYPE_INT_RGB);

	public DrawViz(final ArtificialNeuralNetwork ann) {

		canvas = new BufferedImage(m, m, BufferedImage.TYPE_INT_RGB);
		final JLabel label = new JLabel();
		label.setIcon(new ImageIcon(canvas));
		JPanel mainPanel = new JPanel();
		mainPanel.add(label);
		add(mainPanel);
		setBounds(84, 84, m + 42, m + 42);

		label.addMouseListener(new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent e) {
				setTitle(e.getButton() + " " + lastX + " " + lastY);
				switch (e.getButton()) {
				case 1: {
					int curX = e.getX(), curY = e.getY();
					if (lastX != -1 && lastY != -1) {

						Graphics2D g = (Graphics2D) canvas.getGraphics();
						g.setColor(Color.WHITE);
						g.setStroke(new BasicStroke(m / n));
						g.draw(new Line2D.Float(lastX, lastY, curX, curY));
						repaint();

					}
					lastX = curX;
					lastY = curY;
				}

					break;
				case 2: {
					double[] matrix = new double[n * n];
					int s = m / n;
					for (int y = 0; y < m; y++) {
						for (int x = 0; x < m; x++) {
							matrix[(x / s) + (y / s) * n] += canvas.getRGB(x, y) & 0xFF;

						}
					}

					for (int y = 0, i = 0; y < n; y++) {
						for (int x = 0; x < n; x++, i++) {
							matrix[i] /= s * s * 255;
						}
					}

					canvas = new BufferedImage(m, m, BufferedImage.TYPE_INT_RGB);
					label.setIcon(new ImageIcon(canvas));
					repaint();

					Digit digit = new Digit(matrix, n, 0);
					digit.label = ann.getArgMax(digit);
					(new SimViz(s, digit)).setVisible(true);
				}
				// break;
				default: {
					lastX = -1;
					lastY = -1;
				}
				}
			}
		});

	}

	public static void main(String[] args) throws IOException, ClassNotFoundException {
		ArtificialNeuralNetwork ann = IOUtils.readAnn(path + "output.ann");
		DrawViz dv = new DrawViz(ann);
		dv.setVisible(true);
		dv.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	}

	static final String path = "ann" + File.separator;
	private static final long serialVersionUID = 10L;

}
