package TDGame;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Stroke;
import java.util.List;
import java.util.concurrent.ConcurrentHashMap;

public class KeyControl {
	
	private Image backgroundTacticMod;
	private int[] xTowerBuildC;
	private int[] yTowerBuildC;
	private boolean tacticActive;
	private boolean enterWaiting;
	private boolean showBuyDialog;
	private int score;
	private int gamerPositionChoice;
	private String message;
	private String altMessage;
	private int newTowerType;
	private boolean towerTypeC;
	private int[][] towerTypeCharacteristics;
	private int towerVariant;
	private List<Image[]> towerInfoIcon;
	private int updateChoice;
	private int[] towerInfo;
	private int[] towerUpdate;
	private int updDamage;
	private int updRange;
	private int updRate;
	private int[] updateConstants;
	private int sellChoice;
	
	static final Color TDamage = new Color(220, 0, 0);
	static final Color TRadius = new Color(0, 220, 0);
	static final Color TRate = new Color(20, 240, 240);
	static final Color TInf = new Color(10, 10, 10);
	
	KeyControl(Image tacticModImage, int startScore, int[][] TTC, int TV, List<Image[]> towerInfoIcon, int[] xC, int[] yC) {
		score = startScore;
		backgroundTacticMod = tacticModImage;
		tacticActive = false;
		enterWaiting = false;
		towerTypeC = false;
		xTowerBuildC = xC;
		yTowerBuildC = yC;
		towerTypeCharacteristics = TTC;
		towerVariant = TV;
		altMessage = "";
		message = "";
		this.towerInfoIcon = towerInfoIcon;
		updateChoice = 0;
		updDamage = 0;
		updRange = 0;
		updRate = 0;
		towerUpdate = new int[4];
		updateConstants = new int[10];
		gamerPositionChoice = -1;
		sellChoice = -1;
	}
	
	public void upScore(int add) {
		score += add;
	}
	
	//сделать сдвиг индексов чтобы можно было копировать ссылку на массив
	private void knowUpdateConst(int towerType) {
		updateConstants[0] = towerTypeCharacteristics[towerType][4];
		updateConstants[1] = towerTypeCharacteristics[towerType][5];
		updateConstants[2] = towerTypeCharacteristics[towerType][6];
		updateConstants[3] = towerTypeCharacteristics[towerType][7];
		updateConstants[4] = towerTypeCharacteristics[towerType][8];
		updateConstants[5] = towerTypeCharacteristics[towerType][9];
		updateConstants[6] = towerTypeCharacteristics[towerType][0];
		updateConstants[7] = towerTypeCharacteristics[towerType][1];
		updateConstants[8] = towerTypeCharacteristics[towerType][2];
		updateConstants[9] = towerTypeCharacteristics[towerType][3];
	}
	
	public void getKeyCode(int code, ConcurrentHashMap<Integer, TowerUnit> towers) {
		
		switch(code) {
		
		//s
		case 83:
			if(gamerPositionChoice != -1 && towers.containsKey(gamerPositionChoice) && sellChoice == -1) {
				sellChoice = gamerPositionChoice;
				message = "Вы действительно хотите";
			} else {
				sellChoice = -1;
				message = "Характеристики башни: ";
			}
			break;
		
		//тактик мод
		case 86:
			if(tacticActive) {
				gamerPositionChoice = -1;
				enterWaiting = false;
				towerTypeC = false;
				showBuyDialog = false;
				updateChoice = 0;
				towerUpdate = new int[4];
				updDamage = 0;
				updRange = 0;
				updRate = 0;
				sellChoice = -1;
			}
			tacticActive ^= true;
			break;
		
		//стрелка влево
		case 37:
			switch(updateChoice) {
			case 1:
				if(updDamage > 0) {
					updDamage -= updateConstants[3];
					towerUpdate[0] = updDamage;
				}
				break;
			case 2:
				if(updRange > 0) {
					updRange -= updateConstants[4];
					towerUpdate[1] = updRange;
				}
				break;
			case 3:
				if(updRate > 0) {
					updRate -= updateConstants[5];
					towerUpdate[2] = updRate;
				}
				break;
			}
			break;
		
		//стрелка вправо
		case 39:
			switch(updateChoice) {
			case 1:
				if(towerInfo[0] + updDamage < updateConstants[0]) {
					updDamage += updateConstants[3];
					towerUpdate[0] = updDamage;
				}
				break;
			case 2:
				if(towerInfo[1] + updRange < updateConstants[1]) {
					updRange += updateConstants[4];
					towerUpdate[1] = updRange;
				}
				break;
			case 3:
				if(towerInfo[2] - updRate > updateConstants[2]) {
					updRate += updateConstants[5];
					towerUpdate[2] = updRate;
				}
				break;
			}
			break;
		
		//стрелка вверх
		case 40:
			if(updateChoice > 0) {
				updateChoice = updateChoice % 3 + 1;
			}
			break;
		
		//стрелка вниз
		case 38:
			if(updateChoice > 0) {
				updateChoice--;
				if(updateChoice == 0) {
					updateChoice = 3;
				}
			}
			break;
		
		//бэкспейс
		case 8:
			if(tacticActive) {
				//понавешать ифов в зависимости от текущего состояния
				tacticActive ^= true;
				towerTypeC = false;
				enterWaiting = false;
				gamerPositionChoice = -1;
				showBuyDialog = false;
				updateChoice = 0;
				//уже осторожнее
				towerUpdate = new int[4];
				updDamage = 0;
				updRange = 0;
				updRate = 0;
				sellChoice = -1;
			}
			break;
		
			//ентер
			case 10:
				if(enterWaiting) {
					if(sellChoice != -1) {
						score += priceChanges(towerInfo[0], towerInfo[1], towerInfo[2], towerTypeCharacteristics[towerInfo[4]][0], towerTypeCharacteristics[towerInfo[4]][1], towerTypeCharacteristics[towerInfo[4]][2], towerInfo[3], towerInfo[4], true) / 2 + 100;
						towers.remove(sellChoice);
						sellChoice = -1;
						enterWaiting = false;
						showBuyDialog = false;
						towerTypeC = false;
						gamerPositionChoice = -1;
						updateChoice = 0;
						updDamage = 0;
						updRange = 0;
						updRate = 0;
						towerUpdate = new int[4];
					} else if(updateChoice == 0) {
						int tempCost = priceChanges(towerTypeCharacteristics[newTowerType][0], towerTypeCharacteristics[newTowerType][1], towerTypeCharacteristics[newTowerType][2], 0, 0, 0, towerTypeCharacteristics[newTowerType][3], newTowerType, false);
						if(score >= tempCost) {
							buildTower(gamerPositionChoice, towers, newTowerType);
							score -= tempCost;
							enterWaiting = false;
							showBuyDialog = false;
							towerTypeC = false;
							gamerPositionChoice = -1;
						} else {
							message = "Не хватает очков";
							enterWaiting = false;
							altMessage = "Выберите другую или накопите";
						}
					} else {
						if(priceChanges(towerInfo[0] + towerUpdate[0], towerInfo[1] + towerUpdate[1], towerInfo[2] - towerUpdate[2], towerInfo[0], towerInfo[1], towerInfo[2], towerInfo[3], towerInfo[4], true) <= score) {
							score -= priceChanges(towerInfo[0] + towerUpdate[0], towerInfo[1] + towerUpdate[1], towerInfo[2] - towerUpdate[2], towerInfo[0], towerInfo[1], towerInfo[2], towerInfo[3], towerInfo[4], true);
							towers.get(gamerPositionChoice).doUpdate(towerUpdate);
							enterWaiting = false;
							towerTypeC = false;
							showBuyDialog = false;
							updateChoice = 0;
							updDamage = 0;
							updRange = 0;
							updRate = 0;
							towerUpdate = new int[4];
							gamerPositionChoice = -1;
						} else {
							message = "Не хватает очков. Требуется: ";
						}
					}
				}					
				break;
		
		//циферка не 0 и не на боковой клаве
		default:
			if(sellChoice == -1) {
				if (code - 48 > 0 && code - 48 < 10) {
					if(tacticActive) {
						if(!towerTypeC) {
							//сделать константу для числа позиций у башен
							if(code - 48 < 10) {
								gamerPositionChoice = code - 49; //0 - 48, posit in mas - 0	
								showBuyDialog = true;
								towerTypeC = true;
								if(!towers.containsKey(gamerPositionChoice)) {
									message = "Выберите тип новой башни:";
									altMessage = "возможные значения: 1 - " + towerVariant;							
								} else {
									//апдейт башни
									updateChoice =  1;							
									message = "Характеристики башни: ";
									altMessage = "";
									enterWaiting = true;
									towerInfo = towers.get(gamerPositionChoice).getTowerInfo();
									knowUpdateConst(towerInfo[4]);
								}
							} else {
								showBuyDialog = true;
								message = "неверная позиция башни, повторите";
								altMessage = "";
							}
						} else {
							if(updateChoice == 0) {
								if(code - 49 < towerVariant) {
									enterWaiting = true;
									newTowerType = code - 49;
									knowUpdateConst(newTowerType);
									message = "итоговая стоимость: ";
									altMessage = "вы можете сменить тип";
								} else {
									message = "неверный тип башни, повторите";
									altMessage = "";
								}
							}
						}
					}
				}
			}
			
		}
		
	}
	
	public void draw(Graphics2D g) {
		
		Color tempColor = g.getColor();
		
		g.setFont(g.getFont().deriveFont(Font.BOLD).deriveFont( 15f ));
		g.drawString("sc: " + score, 920, 25);
		
		if(tacticActive) {
			g.drawImage(backgroundTacticMod, 0, 0, null);
		}
		
		g.setFont(g.getFont().deriveFont(Font.BOLD).deriveFont(13f));
		if(showBuyDialog) {
			g.setColor(new Color(0, 0, 255, 130));
			g.fillRect(400, 200, 300, 200);			
			g.setColor(tempColor);
			if(enterWaiting && !message.substring(0, 3).equals("нев")) {
				if(sellChoice != -1) {
					g.drawString(message, 450, 250);
				} else if(updateChoice == 0) {
					int newTowerDamage = towerTypeCharacteristics[newTowerType][0];
					int newTowerRadius = towerTypeCharacteristics[newTowerType][1];
					int newTowerRate = towerTypeCharacteristics[newTowerType][2];
					g.drawString(message + priceChanges(newTowerDamage, newTowerRadius, newTowerRate, 0, 0, 0, towerTypeCharacteristics[newTowerType][3], newTowerType, false), 450, 250);
					g.drawImage(towerInfoIcon.get(newTowerType)[0], 430, 297, null);
					g.setColor(TDamage);
					g.fillRect(520, 300, (int) 150, 12);
					g.setColor(TInf);
					g.drawString(newTowerDamage + " /   " + updateConstants[0], 580, 311);
					g.setColor(TRadius);
					g.fillRect(520, 320, (int) 150, 12);
					g.setColor(TInf);
					g.drawString(newTowerRadius + " /   " + updateConstants[1], 580, 331);
					g.setColor(TRate);
					g.fillRect(520, 340, (int) 150, 12);
					g.setColor(TInf);
					g.drawString(newTowerRate + " /   " + updateConstants[2], 580, 351);
					g.setColor(tempColor);
				} else {
					int towerDamage = towerInfo[0];
					int towerRadius = towerInfo[1];
					int towerRate = towerInfo[2];
					int towerAmmo = towerInfo[3];
					g.drawString(message + priceChanges(towerInfo[0] + towerUpdate[0], towerInfo[1] + towerUpdate[1], towerInfo[2] - towerUpdate[2], towerInfo[0], towerInfo[1], towerInfo[2], towerAmmo, towerInfo[4], true), 450, 250);
					g.drawImage(towerInfoIcon.get(towerInfo[4])[0], 430, 297, null);
					g.setColor(new Color(250, 250, 170, 130));
					g.fillRect(520, 300, (int) 150, 12);
					g.fillRect(520, 320, (int) 150, 12);
					g.fillRect(520, 340, (int) 150, 12);
					g.setColor(TDamage);
					g.fillRect(520, 300, (int) 150 * (towerDamage - updateConstants[6]) / (updateConstants[0] - updateConstants[6]), 12);
					g.setColor(TRadius);
					g.fillRect(520, 320, (int) 150 * (towerRadius - updateConstants[7]) / (updateConstants[1] - updateConstants[7]), 12);
					g.setColor(TRate);
					if((updateConstants[2] - updateConstants[8]) != 0) {
						g.fillRect(520, 340, (int) 150 * (towerRate - updateConstants[8]) / (updateConstants[2] - updateConstants[8]), 12);
					} else {
						g.fillRect(520, 340, 150, 12);
					}
					g.setColor(tempColor);
				}
			} else {
				g.drawString(message, 450, 250);
			}
			g.drawString(altMessage, 450, 270);
			
			if(updateChoice > 0 && sellChoice == -1) {
				g.setColor(new Color(240, 230, 100));
				g.fillRect(520 + (int) 150 * (towerInfo[0] - updateConstants[6]) / (updateConstants[0] - updateConstants[6]), 300, updDamage * 150 / (updateConstants[0] - updateConstants[6]), 12);
				g.fillRect(520 + (int) 150 * (towerInfo[1] - updateConstants[7]) / (updateConstants[1] - updateConstants[7]), 320, updRange * 150 / (updateConstants[1] - updateConstants[7]), 12);
				if((updateConstants[2] - updateConstants[8]) != 0) {
					g.fillRect(520 + (int) 150 * (updateConstants[8] - towerInfo[2]) / (updateConstants[8] - updateConstants[2]), 340, updRate * 150 / (updateConstants[8] - updateConstants[2]), 12);
				}
				g.setColor(TInf);
				g.drawString(towerInfo[0] + " + " + updDamage, 580, 311);
				g.drawString(towerInfo[1] + " + " + updRange, 580, 331);
				g.drawString(towerInfo[2] + " / " + String.valueOf(towerInfo[2] - updRate), 580, 351);
				g.setColor(tempColor);
			}			
			
		}
		
		if(updateChoice > 0 && sellChoice == -1) {
			switch(updateChoice) {
			case 1:
				g.drawRect(518, 298, 153, 15);
				break;
			case 2:
				g.drawRect(518, 318, 153, 15);
				break;
			case 3:
				g.drawRect(518, 338, 153, 15);
				break;
			}
		}
		
		if(sellChoice != -1) {
			int sell = sellChoice;
			g.drawString("продать выбранную башню?", 450, 270);
			g.setColor(new Color(255, 255, 128, 100));
			g.fillOval(xTowerBuildC[sell] - 13, yTowerBuildC[sell] - 13, 86, 86);
			g.setColor(new Color(255, 255, 128));
			Stroke temp = g.getStroke();
			BasicStroke pen = new BasicStroke(4);
			g.setStroke(pen);
			g.drawOval(xTowerBuildC[sell] - 13, yTowerBuildC[sell] - 13, 86, 86);
			g.setColor(tempColor);
			g.setStroke(temp);
		}
		
		if(gamerPositionChoice != -1 && sellChoice == -1) {
			g.setColor(new Color(50, 255, 50, 100));
			g.fillRect(xTowerBuildC[gamerPositionChoice], yTowerBuildC[gamerPositionChoice], 60, 60);
			g.setColor(tempColor);
		}
		
	}
	
	public void buildTower(int numberPosition, ConcurrentHashMap<Integer, TowerUnit> towers, int towerType) {
		if(towers.containsKey(numberPosition) == false) {
			towers.put(numberPosition, new TowerUnit(towerInfoIcon.get(towerType), xTowerBuildC[numberPosition], yTowerBuildC[numberPosition], towerTypeCharacteristics[towerType][0], towerTypeCharacteristics[towerType][1], towerTypeCharacteristics[towerType][2], towerTypeCharacteristics[towerType][3], towerType));
		}
	}
	
	public int priceChanges(int dmgN, int rangeN, int cdN, int dmgO, int rangeO, int cdO, int ammoD, int towerType, boolean upTower) {
		int price;
		if(upTower) {
			if(ammoD < 100) {
				price = (int) Math.pow((dmgN * rangeN * ammoD / (float) cdN), 1.2);
				price -= (int) Math.pow((dmgO * rangeO * ammoD / (float) cdO), 1.2);
			} else {
				price = (int) Math.pow((dmgN * rangeN / (float) cdN), 1.7);
				price -= (int) Math.pow((dmgO * rangeO / (float) cdO), 1.7);
			}
			switch(towerType) {
			case 0:
				price *= 10;
				break;
			case 1:
				price *= 50;
				break;
			case 2:
				price *= 3;
				break;
			case 3:
				price *= 6;
				break;
			}
		} else {
			if(ammoD < 100) {
				price = (int) (dmgN * rangeN * ammoD / cdN);
			} else {
				price = (int) (dmgN * rangeN / cdN);
			}
			switch(towerType) {
			case 0:
				price *= 10;
				break;
			case 1:
				price *= 50;
				break;
			case 2:
				price *= 8;
				break;
			case 3:
				price *= 45;
				break;
			}
		}
		return price;
	}
	
}