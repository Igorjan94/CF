package TDGame;

import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.Image;
import java.util.ArrayList;

public class ScriptEvent {
	
	static final int xStartPosition = 270;
	static final int yStartPosition = 130;
	static final int width = 70;
	static final Font textFont = new Font("Dialog", Font.BOLD, 13);
	
	final Image dialogBackGround;
	
	private int delay;
	private String[] message;
	
	ScriptEvent(Image dialogBackGround, int delay, String[] message) {
		this.dialogBackGround = dialogBackGround;
		this.delay = delay;
		this.message = message;
	}
	
	ScriptEvent(final Image dialogBackGround, final int delay, String message) {
		this.dialogBackGround = dialogBackGround;
		this.delay = delay;
		int length = 0;
		String temp = "";
		String[] words = message.split(" ");
		ArrayList<String> text = new ArrayList<String>();
		for(String word : words) {
			length += word.length() + 1;
			if(length > width) {
				length = 0;
				text.add(temp);
				temp = "";
			}
			temp += word + " ";
		}
		text.add(temp);
		this.message = new String[text.size()];
		text.toArray(this.message);
	}
	
	public int getDelay() {
		return delay;
	}
	
	public void draw(Graphics2D g) {
		Font temp = g.getFont();
		g.setFont(textFont);
		g.drawImage(dialogBackGround, 250, 100, null);
		for(int i = 0; i < message.length; i++) {
			g.drawString(message[i], xStartPosition, yStartPosition + i * 20);
		}
		g.setFont(temp);
	}
	
	public void drawWarningToNextWawe(Graphics2D g, int number) {
		Font temp = g.getFont();
		g.setFont(textFont);
		g.setFont(g.getFont().deriveFont(23f));
		g.drawImage(dialogBackGround, 250, 100, null);
		g.drawString("Are you ready? " + (number + 2) + " wave begins!", xStartPosition, yStartPosition + 80);
		g.setFont(temp);
	}
	
}
