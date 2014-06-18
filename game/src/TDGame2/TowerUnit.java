package TDGame;

import java.awt.Graphics2D;
import java.awt.Image;
import java.util.List;

public class TowerUnit {

	private int x;
	private int y;
	private Image[] towerImage;
	private int animation;
	private int animationDelay;
	private int attack;
	private int range;
	private int cd;
	private int cdStatus;
	//private int attackType;
	//private int damageType;
	//private boolean splash;
	private int ammo;
	private int xC;
	private int yC;
	private int towerType;
	private int psyhoStatus;

	// подумать нужен ли тип атаки !!!!!!!!!!

	public TowerUnit(Image[] img, int xCoord, int yCoord, int damage, int dist, int cooldown, int ammoCount, int TT) {

		this.towerImage = img;
		this.x = xCoord;
		this.y = yCoord;
		this.animation = 0;
		this.animationDelay = (int) (Math.random() * 35);
		this.attack = damage;
		this.range = dist;
		this.cd = cooldown;
		this.cdStatus = cooldown;
		this.ammo = ammoCount;
		this.xC = xCoord + img[0].getWidth(null) / 2;
		this.yC = yCoord + img[0].getHeight(null) / 2;
		this.towerType = TT;

	}

	public int getWidth() {
		return towerImage[0].getWidth(null);
	}

	public int getHeight() {
		return towerImage[0].getHeight(null);
	}
	
	public int[] getTowerInfo() {
		return new int[]{this.attack, this.range, this.cd, this.ammo, this.towerType};
	}
	
	public void doUpdate(int[] newValues) {
		this.attack += newValues[0];
		this.range += newValues[1];
		this.cd -= newValues[2];
		this.cdStatus = 0;
		this.psyhoStatus = 0;
	}

	public void draw(Graphics2D g) {

		g.drawImage(towerImage[this.animation], this.x, this.y, null);
		if(this.towerType != 4) {
		g.drawOval(this.xC - this.range, this.yC - this.range, this.range * 2, this.range * 2);
		} else {
			//g.fillOval(this.xC - this.range, this.yC - this.range, this.range * 2, this.range * 2);
		}

		this.animationDelay++;
		this.animationDelay %= 35;
		this.animation = this.animationDelay / 7;

	}

	public void kill(List<EnemyUnit> enemies, List<Shell> shells) {
		int ammoCount = this.ammo;
		if(this.cdStatus == this.cd) {
			for (EnemyUnit enemy : enemies) {
				if (enemy.getState()) {
					if(ammoCount > 0) {
						int xDist = enemy.getXC() - this.xC;
						int yDist = enemy.getYC() - this.yC;
						if (xDist * xDist + yDist * yDist < this.range * this.range) {
							enemy.applyDamage(this.attack);
							if(this.towerType == 1 && ammoCount == this.ammo) {
								this.psyhoStatus = ++this.psyhoStatus % 12;
								if(this.psyhoStatus == 1) {
									shells.add(new Shell(this.xC, this.yC, this.range, true));
								} else {
									shells.add(new Shell(this.xC, this.yC, this.range, false));
								}
							} else {
								shells.add(new Shell(this.xC, this.yC, enemy.getXC(), enemy.getYC(), 10, towerType));
							}
							ammoCount--;
						}
					}						
				}
			}
			if(ammoCount != this.ammo) {
				this.cdStatus = 0;
			}
		}
		if(this.cdStatus != this.cd) {
			this.cdStatus++;
		}
	}

}
