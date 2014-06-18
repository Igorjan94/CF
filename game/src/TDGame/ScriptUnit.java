package TDGame;

import java.awt.Graphics2D;
import java.awt.Image;

public class ScriptUnit {

	private Image[][] image;

	private int speed;
	private int x;
	private int y;
	private int progress;
	private int distanceComplite;
	private boolean life;
	private int animation;
	private int animationDelay;
	private boolean bangNotHappen;
	private int[] dist;
	private int[] orient;
	private int waiting;
	private int waitingProgress;

	public ScriptUnit(Image[][] images, int velocity, int startX, int startY, int[] distantion, int[] orientation) {
				
		this.image = images;
		this.speed = velocity;
		this.x = startX;
		this.y = startY;
		this.progress = 0;
		this.distanceComplite = 0;
		this.life = true;
		this.animation = 0;
		this.animationDelay = 0;
		this.bangNotHappen = true;
		this.dist = distantion;
		this.orient = orientation;
		this.waiting = 50;
		this.waitingProgress = 0;
		
	}

	public int getWidth() {
		return image[0][0].getWidth(null);
	}

	public int getHeight() {
		return image[0][0].getHeight(null);
	}
	
	public void setExplosion() {
		this.bangNotHappen = false;
	}
	
	public int getX() {
		return this.x;
	}
	
	public int getY() {
		return this.y;
	}
	
	public int getXC() {
		return this.x + image[0][0].getWidth(null) / 2;
	}
	
	public int getYC() {
		return this.y + image[0][0].getHeight(null) / 2;
	}

	public void draw(Graphics2D g) {

		if (life) {
			
			if(this.bangNotHappen) {
				
				if(this.waitingProgress == 0) {
					this.progress += speed;
					
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
				}
				
				if (progress >= this.dist[distanceComplite]) {
					
					if(this.waiting == this.waitingProgress) {
						switch (this.orient[this.distanceComplite]) {
						case 0:
							this.x -= (progress - this.dist[distanceComplite]);
							break;
						case 1:
							this.y -= (progress - this.dist[distanceComplite]);
							break;
						case 2:
							this.x += (progress - this.dist[distanceComplite]);
							break;
						case 3:
							this.y += (progress - this.dist[distanceComplite]);
							break;
						}
						this.distanceComplite++;
						this.progress = 0;
						this.waitingProgress = -1;
					}
					
					this.waitingProgress++;
					
				}
	
				if (distanceComplite == this.dist.length) {
					distanceComplite = 0;
				}
				
			}
			
/*			if(this.bangNotHappen) {
				
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
//				g.drawImage(image[4][this.animation], this.x, this.y, null);
				if(this.animationDelay == 20) {
					this.life = false;
				}
			}
*/			
			this.animationDelay++;
			this.animationDelay %= 21;
			this.animation = this.animationDelay / 7;
			
		}
	}
	
}
