package task7;

import java.awt.image.BufferedImage;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class SimViz extends JFrame {
	public SimViz(int scale, Digit digit) {
		int m = scale * digit.len;
		BufferedImage canvas = new BufferedImage(m, m, BufferedImage.TYPE_INT_RGB);
		JLabel label = new JLabel();
		label.setIcon(new ImageIcon(canvas));
		JPanel mainPanel = new JPanel();
		mainPanel.add(label);
		add(mainPanel);
		setBounds(42, 42, m + 42, m + 42);
		for (int y = 0; y < m; y++) {
			for (int x = 0; x < m; x++) {
				int grey = (int) Math.round(digit.getSignal(x / scale, y / scale) * 255);
				canvas.setRGB(x, y, (grey << 16) | (grey << 8) | (grey << 0));
			}
		}

		setTitle("Digit = " + digit.label);

		repaint();
	}

	private static final long serialVersionUID = 10L;
}
