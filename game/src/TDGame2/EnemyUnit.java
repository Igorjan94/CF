package TDGame;

import java.awt.Graphics2D;
import java.awt.Image;

public class EnemyUnit {

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
	private int HP;
	private int[] dist;
	private int[] orient;
	private int bounty;
	private int maxHP;
	private int damageToBase;
	private boolean baseAttack;

	public EnemyUnit(Image[][] images, int velocity, int hp, int startX, int startY, int[] distantion, int[] orientation, int bounty, int damageToBase) {
				
		this.image = images;
		this.speed = velocity;
		this.x = startX;
		this.y = startY;
		this.progress = 0;
		this.distanceComplite = 0;
		this.life = true;
		this.animation = 0;
		this.animationDelay = (int) (Math.random() * 21);
		this.bangNotHappen = true;
		this.HP = hp;
		this.dist = distantion;
		this.orient = orientation;
		this.bounty = bounty;
		this.maxHP = hp;
		this.damageToBase = damageToBase;
		this.baseAttack = false;
		
	}

	public int getWidth() {
		return image[0][0].getWidth(null);
	}

	public int getHeight() {
		return image[0][0].getHeight(null);
	}
	
	public int getHP() {
		return HP;
	}
	
	/*public void setExplosion() {
		this.bangNotHappen = false;
	}*/
	
	public void kill() {
		this.life = false;
	}
	
	public void applyDamage(int dmg) {
		this.HP -= dmg;
		if(this.HP <= 0) {
			this.bangNotHappen = false;
			this.animation = 0;
			this.animationDelay = 0;
		}
	}
	
	public boolean getState() {
		return this.bangNotHappen;
	}
	
	public boolean getLifeState() {
		return this.life;
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
	
	public int getBounty() {
		return this.bounty;
	}
	
	public int getDamageToBase() {
		return this.damageToBase;
	}
	
	public boolean getBaseAttack() {
		return this.baseAttack;
	}

	public void draw(Graphics2D g) {

		if (life) {
			
			if(this.bangNotHappen) {
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
				
				if (progress >= this.dist[distanceComplite]) {
					
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
					
				}
	
				if (distanceComplite == this.dist.length) {
					this.baseAttack = true;
					this.bangNotHappen = false;
				}
				
			}
			
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
				
				g.drawLine(x, y + this.getHeight(), x + (int) this.getWidth() * HP / maxHP, y + this.getHeight());
					
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
			
		}
	}
	
}
