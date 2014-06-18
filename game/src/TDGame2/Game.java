package TDGame;

import java.awt.BorderLayout;
import java.awt.Canvas;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.image.BufferStrategy;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.ConcurrentHashMap;

import javax.swing.JFrame;

public class Game extends Canvas implements Runnable {

	private static final long serialVersionUID = 42;
	
	private static String NAME = "TDGame ver 1.7";
	
	private static int WIDTH = 1024;
	private static int HEIGHT = 512;

	private boolean running;
	private boolean paused;

	private static long timeDelay = 25;
	
	private GamePlot plot;
	private KeyControl interfaceModerator;
	private int nextPlot = -1;
	
	private List<int[]> route;
	private List<int[]> orientation;
	
	private List<EnemyUnit> enemys;
	private List<ScriptUnit> bots;
	private ConcurrentHashMap<Integer, TowerUnit> towers;
	private List<Shell> shells;
	
	private WawesDescription wawes;
	private List<int[]> waweInfo;
	private int waweBegin;
		
	private List<int[]> scriptInfo;
	
	private LinkedList<ScriptEvent> events;
	private int eventsDelay;
	private int eventProgress;
	
	private List<Image[][]> enemysAnimation;
	
	private Image backGround;
	private Image dialogBackGround;
		
	private Image[] angarVariantsImage;
	private int[] angars;	
	
	private int round;
	
	private int baseHP;
	private int enemiesDestroyed;
	private int killsInWave;
	private int notKilled;
	private int notKilledInWave;
	private int notRespEnemyCount;
	private int enemiesInWawe;
	private boolean showInfo;
	
	private Color pausedBackground;
	private Color textMessageInfo;
	private Font pausedState;
	private Font messageInfo;
	
	//--------------------------------

	public void start() {
		this.running = true;
		new Thread(this).start();
	}

	public void run() {

		long delta;
		
		init();

		while (running) {

			delta = System.currentTimeMillis();
			update();
			render();
			
			if(paused) {
				while(paused) {
					try {
						Thread.sleep(250);
					} catch (InterruptedException e) {
						System.out.println("Тред отказывается спать o_O");
						e.printStackTrace();
					}
				}
			}

			long delay = timeDelay - System.currentTimeMillis() + delta;
			if (delay > 0) {

				try {
					Thread.sleep(delay);
				} catch (InterruptedException e) {
					System.out.println("Тред отказывается спать");
					e.printStackTrace();
				}

			} else {
				//удалить ветвь нафиг перед продакшоном
				System.out.println("Таймингопроблемы");
			}

		}
	}
	
	private void loadLVL(int number) {
		
		this.plot = new GamePlot(number);
		this.interfaceModerator = new KeyControl(plot.backGroundTacticMod, plot.score, plot.towerTypeCharacteristics, plot.towerConstructVariant, plot.towersAnimation, plot.xCTB, plot.yCTB);
		
		route = plot.route;
		orientation = plot.orientation;
		
		enemys = new ArrayList<EnemyUnit>();
		towers = new ConcurrentHashMap<Integer, TowerUnit>();
		shells = new LinkedList<Shell>();
		bots = new ArrayList<ScriptUnit>();
		
		backGround = plot.backGround;
		dialogBackGround = plot.dialogBackGround;
		angarVariantsImage = plot.angarVariantsImage;
		
		angars = plot.angars;
		
		enemysAnimation = plot.enemysAnimation;
		
		baseHP = plot.baseHP;
		enemiesDestroyed = 0;
		killsInWave = 0;
		notRespEnemyCount = 0;
		notKilled = 0;
		notKilledInWave = 0;
		enemiesInWawe = 0;
		showInfo = false;
				
		paused = false;
		round = 0;
		
		wawes = plot.wawes;
		scriptInfo = plot.scriptInfo;
		
		events = plot.events;
		eventsDelay = 0;
		eventProgress = 1;
		
		waweBegin = 0;
		
		nextPlot = plot.nextPlot;
		
		int count = -1;
		for(int index : plot.towerInit) {
			this.interfaceModerator.buildTower(index, towers, plot.towerInitType[++count]);
		}
		
		for(int i = 0; i < scriptInfo.size(); i++) {
			if(scriptInfo.get(i)[2] <= round) {
				bots.add(new ScriptUnit(enemysAnimation.get(scriptInfo.get(i)[0]), scriptInfo.get(i)[1], scriptInfo.get(i)[3], scriptInfo.get(i)[4], route.get(scriptInfo.get(i)[5]), orientation.get(scriptInfo.get(i)[5])));
			}
		}
	}

	private void init() {
		
		addKeyListener(new KeyAdapter() {
			public void keyPressed(KeyEvent e) {
				
				int tempKeyCode = e.getKeyCode();
				//System.out.println(tempKeyCode);
				
				//пробел
				if (tempKeyCode == 32) {
					paused ^= true;
				}
				if(!paused) {
					switch(tempKeyCode) {
					//равно
					case 61:
						if(timeDelay > 10) {
							timeDelay -= 5;
						} else if(timeDelay > 3) {
							timeDelay--;
						}
						break;
					//минус
					case 45:
						if(timeDelay < 10) {
							timeDelay++;
						} else if(timeDelay < 75) {
							timeDelay += 5;
						}
						break;
					//и
					case 73:
						showInfo ^= true;
						break;
					//икс
					case 88:
						System.out.println(round);
						timeDelay = 25;
						loadLVL(nextPlot);
						break;
					//рестарт
					//сделать поумнее. загружать не предыдущий будущему лвл, а текущий.
					//низя запустить в геймменю
					case 82:
						System.out.println(round);
						timeDelay = 25;
						loadLVL(nextPlot - 1);
						break;
					default:
						interfaceModerator.getKeyCode(tempKeyCode, towers);					
					}
				}
			}
		});
		
		loadLVL(nextPlot);
		
		pausedBackground = new Color(0, 0, 0, 180);
		textMessageInfo = new Color(0, 255, 0);
		pausedState = new Font("TimesRoman", Font.TYPE1_FONT, 24);
		messageInfo = new Font("Dialog", Font.ROMAN_BASELINE, 13);
		
	}

	public void render() {

		BufferStrategy bs = getBufferStrategy();
		if (bs == null) {
			createBufferStrategy(2);
			requestFocus();
			return;
		}

		Graphics2D g = (Graphics2D) bs.getDrawGraphics();
				
		//рисовач
		
		g.setColor(Color.green);
		g.drawImage(backGround, 0, 0, 1024, 512, null);
		
		for(TowerUnit tower : towers.values()) {
			tower.draw(g);
		}		
		for(EnemyUnit enemy : enemys) {
			enemy.draw(g);
		}
		for(ScriptUnit bot : bots) {
			bot.draw(g);
		}
		for(Shell ammo : shells) {
			ammo.draw(g);
		}
		
		for(int index : angars) {
			//добавить смещение чтоб юниты по центру выползали
			g.drawImage(angarVariantsImage[orientation.get(waweInfo.get(index)[8])[0]], waweInfo.get(index)[6],  waweInfo.get(index)[7], null);
		}
		
		this.interfaceModerator.draw(g);
		
		if(showInfo == true) {
			Color tempColor = g.getColor();
			g.setColor(new Color(0, 0, 255, 100));
			g.fillRect(900, 80, 125, 220);
			g.setColor(tempColor);
			g.drawString("Info:", 910, 100);
			g.drawLine(910, 102, 980, 102);
			g.drawString("Base HP: " + baseHP, 915, 120);
			g.drawString("Killed: " + enemiesDestroyed, 915, 135);
			g.drawString("Not killed: " + notKilled, 915, 150);
			if(wawes.getMode()) {
				g.drawString("Wave status: " + (wawes.getWaweNumber() + 1) + "/" + (char)8734, 915, 165);
			} else {
				g.drawString("Wave status: " + (wawes.getWaweNumber() + 1) + "/" + wawes.getWaveCount(), 915, 165);
			}
			g.drawString("Wave info:", 910, 185);
			g.drawLine(910, 187, 980, 187);
			g.drawString("Amount: " + enemiesInWawe, 915, 205);
			g.drawString("Kills: " + killsInWave, 915, 220);
			g.drawString("Not resp: " + notRespEnemyCount, 915, 235);
			g.drawString("Not killed: " + notKilledInWave, 915, 250);
			g.drawString("On map: " + (enemiesInWawe - notRespEnemyCount - killsInWave - notKilledInWave), 915, 265);
			g.drawLine(905, 275, 1000, 275);
			g.drawLine(905, 276, 1000, 276);
			g.drawString("Speed: x" + String.format("%.2f", ((float) 25 / timeDelay)), 910, 290);
		}
		
		if(paused) {
			
			g.setFont(this.pausedState);
			g.setColor(this.pausedBackground);
			
			g.fillRect(370, 200, 310, 90);
			g.setColor(this.textMessageInfo);
			
			g.drawString("Game paused", 450, 250);
			g.setFont(this.messageInfo);
			
		}
		
		if(eventProgress < events.size()) {
			if(eventsDelay == events.get(eventProgress).getDelay()) {
				eventsDelay = 0;
				events.get(eventProgress).draw(g);
				eventProgress++;
				paused = true;
			}
		}
		
		if(wawes.getMode()) {
			if(killsInWave + notKilledInWave == enemiesInWawe) {
				events.get(2).drawWarningToNextWawe(g, wawes.getWaweNumber());
				paused = true;
			}
		}
		
		if(baseHP <= 0) {
			g.drawImage(dialogBackGround, 250, 100, null);
			events.get(0).draw(g);
			round = -2;
			paused = true;
		}
		
		//конец рисовача
		
		g.dispose();
		bs.show();

	}

	public void update() {
		
		if(wawes.getMode()) {
			if(killsInWave + notKilledInWave == enemiesInWawe) {
				//System.out.println("sasdafsdf");
				killsInWave = 0;
				notKilledInWave = 0;
				wawes.waweStart(0);
				waweInfo = wawes.getWawe();
				waweBegin = round;
				enemiesInWawe = 0;
				for(int[] tempMas : waweInfo) {
					enemiesInWawe += tempMas[1];
				}
			}
		} else if(wawes.waweStart(round - waweBegin)) {
			waweInfo = wawes.getWawe();
			waweBegin = round;
			killsInWave = 0;
			notKilledInWave = 0;
			enemiesInWawe = 0;
			for(int[] tempMas : waweInfo) {
				enemiesInWawe += tempMas[1];
			}			
		}
		
		for(TowerUnit tower : towers.values()) {
			tower.kill(enemys, shells);
		}
		
		round++;
		eventsDelay++;
		
		for(int i = 0; i < waweInfo.size(); i++) {
			if(waweInfo.get(i)[5] <= round - waweBegin) {
				if(waweInfo.get(i)[1] > 0) {
					if((round - waweBegin) % waweInfo.get(i)[2] == 0) {
						enemys.add(new EnemyUnit(enemysAnimation.get(waweInfo.get(i)[0]), waweInfo.get(i)[3], 
								waweInfo.get(i)[4], waweInfo.get(i)[6], waweInfo.get(i)[7], route.get(waweInfo.get(i)[8]), 
								orientation.get(waweInfo.get(i)[8]), waweInfo.get(i)[9], waweInfo.get(i)[10]));
						waweInfo.get(i)[1]--;
					}
				}
			}
		}
		
		Iterator<EnemyUnit> it = enemys.iterator();
		while(it.hasNext()) {
			EnemyUnit tempEnemy = it.next();
			if(tempEnemy.getBaseAttack() == true) {
				baseHP -= tempEnemy.getDamageToBase();
				//killsInWave++;
				notKilled++;
				notKilledInWave++;
				tempEnemy.kill();
			}
			if(tempEnemy.getState() == false) {
				this.interfaceModerator.upScore(tempEnemy.getBounty());
			}
			if(tempEnemy.getLifeState() == false) {
				if(tempEnemy.getHP() <= 0) {
					enemiesDestroyed++;
					killsInWave++;
				}
				it.remove();
			}
		}
		
		Iterator<Shell> ammo = shells.iterator();
		while(ammo.hasNext()) {
			if(ammo.next().getLifeState() == false) {
				ammo.remove();
			}
		}
		
		notRespEnemyCount = 0;
		for(int[] tempMas : waweInfo) {
			notRespEnemyCount += tempMas[1];
		}
		
		
		if(round == -1) {
			System.out.println(round);
			timeDelay = 25;
			loadLVL(0);
		}
		
		if(events.size() == eventProgress) {
			System.out.println(round);
			timeDelay = 25;
			loadLVL(nextPlot);
		}
		
	}

	public static void main(String[] args) {
		Game game = new Game();
		game.setPreferredSize(new Dimension(WIDTH, HEIGHT));
		JFrame frame = new JFrame(Game.NAME);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setLayout(new BorderLayout());
		frame.add(game, BorderLayout.CENTER);
		//game.setBounds(100, 0, 640, 480);
		frame.pack();
		//frame.setResizable(false);
		frame.setVisible(true);
		game.start();
	}

}