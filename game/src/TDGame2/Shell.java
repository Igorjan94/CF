package TDGame;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Stroke;
//import java.awt.Image;

public class Shell {

	//private Image[][] image;

	//private int speed;
	private int x1;
	private int y1;
	private int x2;
	private int y2;
	private int lifeDuration;
	private boolean life;
	private int type;
	private int range;
	/*private int animation;
	private int animationDelay;*/
	private boolean bangNotHappen;
	private boolean psyhoVision;

	public Shell(int startX, int startY, int endX, int endY, int shellSpeed, int type) {
				
		//this.image = images;
		//this.speed = shellSpeed;
		this.x1 = startX;
		this.y1 = startY;
		this.x2 = endX;
		this.y2 = endY;
		this.life = true;
		switch(type) {
		case 0:
			this.lifeDuration = 10;
			break;
		case 2:
			this.lifeDuration = 10;
			break;
		case 3:
			this.lifeDuration = 5;
			break;
		default:
			this.lifeDuration = 10;
		}		
		/*this.animation = 0;
		this.animationDelay = (int) (Math.random() * 21);*/
		this.bangNotHappen = true;
		this.type = type;
	}
	
	public Shell(int startX, int startY, int radius, boolean visible) {		
		this.x1 = startX;
		this.y1 = startY;
		this.life = true;
		this.lifeDuration = 100;
		this.bangNotHappen = true;
		this.range = radius;
		this.type = 1;
		this.psyhoVision = visible;
	}
	
	public void setExplosion() {
		this.bangNotHappen = false;
	}
	
	public boolean getState() {
		return this.bangNotHappen;
	}
	
	public boolean getLifeState() {
		return this.life;
	}

	public void draw(Graphics2D g) {

		if (life) {
			
			/*if(type != 0) {			
				if(this.bangNotHappen) {
					
					switch (this.orient[this.distanceComplite]) {
					case 0:
						this.x += speed;
						break;
					case 1:
						this.y += speed;
						break;
					case 2:
						this.x -= speed;
						break;
					case 3:
						this.y -= speed;
						break;
					}
		
				//снаряд попал	
				if (distanceComplite == this.dist.length) {
						this.bangNotHappen = false;
						//придумать чё делать с анимацией при достижении конца пути
						this.animation = 0;
						this.animationDelay = 0;
					}
				}
				
				//сама анимация
				if(this.bangNotHappen) {
					
					switch (this.orient[this.distanceComplite]) {
					case 0:
						g.drawImage(image[0][this.animation], this.x, this.y, null);
						break;
					case 1:
						g.drawImage(image[1][this.animation], this.x, this.y, null);
						break;
					case 2:
						g.drawImage(image[2][this.animation], this.x, this.y, null);
						break;
					case 3:
						g.drawImage(image[3][this.animation], this.x, this.y, null);
						break;
					}
					
				} else {
					//эпичный взрыв
					g.drawImage(image[4][this.animation], this.x, this.y, null);
					if(this.animationDelay == 20) {
						this.life = false;
					}
				}
				
				this.animationDelay++;
				this.animationDelay %= 21;
				this.animation = this.animationDelay / 7;
			} else {
				
				Color tempColor = g.getColor();
				g.setColor(new Color(112, 239, 250));
				//g.setColor(new Color(2, 2, 250, 130));
				g.drawLine(x1, y1, x2 + 2, y2);
				g.drawLine(x1, y1, x2, y2 + 2);
				g.drawLine(x1, y1, x2 + 2, y2 + 2);
				g.drawLine(x1, y1, x2 + 4, y2);
				g.drawLine(x1, y1, x2, y2 + 4);
				//g.fillOval(x2 - 25, y2 - 25, this.lifeDuration * 10, this.lifeDuration * 10);
				g.setColor(tempColor);
				
				this.lifeDuration--;
				if(this.lifeDuration == 0) {
					this.life = false;
				}
				
			}
			
		}*/
			Color tempColor = g.getColor();
			
			switch(type) {
			
			case 0:
				g.setColor(new Color(10, 10, 10, 220));
				g.drawLine(x1, y1, x2, y2);
				g.drawLine(x1, y1 + 1, x2 + 1, y2);
				g.drawLine(x1 + 1, y1, x2, y2 + 1);
				g.fillOval(this.x2 - (10 - this.lifeDuration) * 3, this.y2 - (10 - this.lifeDuration) * 3, (10 - this.lifeDuration) * 3 * 2, (10 - this.lifeDuration) * 3 * 2);
				g.setColor(tempColor);
				break;
				
			case 1:
				if(this.psyhoVision) {
					g.setColor(new Color(255, 255, 128));
					Stroke temp = g.getStroke();
					BasicStroke pen = new BasicStroke(5);
					g.setStroke(pen);
					g.drawOval(this.x1 - (100 - this.lifeDuration) * this.range / 100, this.y1 - (100 - this.lifeDuration) * this.range / 100, (100 - this.lifeDuration) * this.range / 50, (100 - this.lifeDuration) * this.range / 50);
					g.setColor(tempColor);
					g.setStroke(temp);
				}
				break;
		
			case 2:	
				if(lifeDuration >= 6) {
					g.setColor(new Color(112, 239, 250));
					g.drawLine(x1, y1, x2 + 2, y2);
					g.drawLine(x1, y1, x2, y2 + 2);
					g.drawLine(x1, y1, x2 + 2, y2 + 2);
					g.drawLine(x1, y1, x2 + 4, y2);
					g.drawLine(x1, y1, x2, y2 + 4);
				}
				g.setColor(new Color(200, 2, 2, 190));
				g.fillOval(this.x2 - this.lifeDuration * 5, this.y2 - this.lifeDuration * 5, this.lifeDuration * 5 * 2, this.lifeDuration * 5 * 2);
				g.setColor(tempColor);
				break;
				
			case 3:
			//дефолтная оборонит турелька на базе
			case 4:
				if(lifeDuration >= 3) {
					g.setColor(new Color(232, 21, 69));
					g.drawLine(x1, y1 - 2, x2, y2 - 2);
					g.drawLine(x1, y1 + 2, x2, y2 + 2);
					g.drawLine(x1 + 2, y1, x2 + 2, y2);
					g.drawLine(x1 - 2, y1, x2 - 2, y2);
					g.setColor(new Color(255, 149, 70));
					g.drawLine(x1, y1 + 1, x2, y2 + 1);
					g.drawLine(x1, y1 - 1, x2, y2 - 1);
					g.drawLine(x1 + 1, y1, x2 + 1, y2);
					g.drawLine(x1 - 1, y1, x2 - 1, y2);
					g.setColor(new Color(255, 255, 255));
					g.drawLine(x1, y1, x2, y2);									
				}
				g.setColor(new Color(200, 2, 2, 90));
				g.fillOval(this.x2 - this.lifeDuration * 3, this.y2 - this.lifeDuration * 3, this.lifeDuration * 3 * 2, this.lifeDuration * 3 * 2);
				g.setColor(tempColor);
				break;
			}
			
			this.lifeDuration--;
			if(this.lifeDuration == 0) {
				this.life = false;
			}
			
		}
	}
	
}
