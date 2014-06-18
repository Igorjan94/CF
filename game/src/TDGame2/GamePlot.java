package TDGame;

import java.awt.Image;
import java.awt.Toolkit;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

import javax.imageio.ImageIO;

public class GamePlot {
	
	public Image backGround;
	public Image backGroundTacticMod;
	public Image dialogBackGround;
	
	private int enemyVariant = 6;
	private int towerVariant = 4;
	private int angarVariant = 4;
	private int constructorEnemyUnitSize = 11;
	private int constructorScriptUnitSize = 6;
		
	public List<Image[][]> enemysAnimation;
	public List<Image[]> towersAnimation;
	
	public int[] xCTB;
	public int[] yCTB;
	public int[] towerInit;
	public int[] towerInitType;
	public int[][] towerTypeCharacteristics;
	
	public List<int[]> route;
	public List<int[]> orientation;
	
	public WawesDescription wawes;
	private ArrayList<int[]> waweInfo;
	public List<int[]> scriptInfo;
	
	public Image[] angarVariantsImage;
	public int[] angars;
	
	public int score;
	public int baseHP;
	public int towerConstructVariant;
	public int nextPlot;
	
	public LinkedList<ScriptEvent> events;
	
	private Image readImage(String path) {
		BufferedImage sourceImage = null;		
		try {
			sourceImage = ImageIO.read(new File(path));
		} catch (IOException e) {
			e.printStackTrace();
		}		
		return Toolkit.getDefaultToolkit().createImage(sourceImage.getSource());
	}
	
	GamePlot(int state) {
		
		dialogBackGround = readImage("images/dial.png");
		
		angarVariantsImage = new Image[angarVariant];
		
		for(int k = 0; k < angarVariant; k++) {
				angarVariantsImage[k] = readImage("images/angar/angar" + k + ".png");
			}
		
		//запоминание состояний для анимации
		
		enemysAnimation = new ArrayList<Image[][]>(enemyVariant);
		towersAnimation = new ArrayList<Image[]>(towerVariant);
		
		Image[][] tmpUnitImage;
		
		for(int k = 1; k <= enemyVariant; k++) {		
			tmpUnitImage = new Image[5][3];		
			for(int i = 0; i < 5; i++) {
				for(int j = 0; j < 3; j++) {
					tmpUnitImage[i][j] = readImage("images/enemyTankLVL" + k + "/enemyTankLVL1v" + i + j + ".png");
				}
			}			
			enemysAnimation.add(tmpUnitImage);		
		}
		
		Image[] tmpTowerImage;
		
		// +1 для дефолтной прозрачной картинки. просто прозрачной 60*60...
		for(int k = 1; k <= towerVariant + 1; k++) {			
			tmpTowerImage = new Image[5];
			for (int i = 0; i < 5; i++) {
				tmpTowerImage[i] = readImage("images/teslaTowerV" + k + "/tesla" + i + ".png");
			}			
			towersAnimation.add(tmpTowerImage);		
		}
		
		int[] tempMas;
		waweInfo = new ArrayList<int[]>();
		scriptInfo = new ArrayList<int[]>();
		events = new LinkedList<ScriptEvent>();
				
		switch(state) {
		
		case 1:
			
			backGround = readImage("images/map1.png");			
			backGroundTacticMod = readImage("images/map1v.png");
			
			wawes = new WawesDescription(false);
			
			//
			tempMas = new int[constructorEnemyUnitSize];
			tempMas[0] = 0; //type unit
			tempMas[1] = 30; // count
			tempMas[2] = 25; // creation delay
			tempMas[3] = 2; //speed
			tempMas[4] = 25; //hp
			tempMas[5] = 1; //delay
			tempMas[6] = 130; //startX
			tempMas[7] = -25; //startY
			tempMas[8] = 0; //distance & orientation wave
			tempMas[9] = 5; // bounty
			tempMas[10] = 10; // base damage
			waweInfo.add(tempMas);
			
			tempMas = new int[constructorEnemyUnitSize];
			tempMas[0] = 3;
			tempMas[1] = 25;
			tempMas[2] = 120;
			tempMas[3] = 5;
			tempMas[4] = 1;
			tempMas[5] = 300;
			tempMas[6] = 727;
			tempMas[7] = -25;
			tempMas[8] = 1;
			tempMas[9] = 10;
			tempMas[10] = 10;
			waweInfo.add(tempMas);
			
			tempMas = new int[constructorEnemyUnitSize];
			tempMas[0] = 1;
			tempMas[1] = 30;
			tempMas[2] = 40;
			tempMas[3] = 3;
			tempMas[4] = 1;
			tempMas[5] = 1;
			tempMas[6] = 845;
			tempMas[7] = 530;
			tempMas[8] = 2;
			tempMas[9] = 25;
			tempMas[10] = 10;
			waweInfo.add(tempMas);
			
			tempMas = new int[constructorEnemyUnitSize];
			tempMas[0] = 2; //type unit
			tempMas[1] = 20; // count
			tempMas[2] = 50; // creation delay
			tempMas[3] = 1; //speed
			tempMas[4] = 100; //hp
			tempMas[5] = 500; //delay
			tempMas[6] = 130; //startX
			tempMas[7] = -25; //startY
			tempMas[8] = 0; //distance & orientation wave
			tempMas[9] = 20; // bounty
			tempMas[10] = 10;
			waweInfo.add(tempMas);
			
			tempMas = new int[constructorEnemyUnitSize];
			tempMas[0] = 2; //type unit
			tempMas[1] = 50; // count
			tempMas[2] = 40; // creation delay
			tempMas[3] = 5; //speed
			tempMas[4] = 110; //hp
			tempMas[5] = 800; //delay
			tempMas[6] = 845; //startX
			tempMas[7] = 530; //startY
			tempMas[8] = 2; //distance & orientation wave
			tempMas[9] = 25; // bounty
			tempMas[10] = 10;
			waweInfo.add(tempMas);
			
			wawes.addWawe(0, waweInfo);
			
			//
			
			events.add(new ScriptEvent(dialogBackGround, 400,
					"Вражеским войскам всё же удалось проникнуть на нашу территорию. " +
					"Я активировал все внутренние охранные системы, которые вскоре нейтрализуют " +
					"неприятеля. Однако, вам все же придётся отчитаться перед генштабом."));
			events.add(new ScriptEvent(dialogBackGround, 100,
					"Добрый день, команданте. Что, уже проснулись? " +
					"\n" + "\n" + "\n" + "\n" + "( Для продолжения используйте <ПРОБЕЛ> )"));
			events.add(new ScriptEvent(dialogBackGround, 30,
					"Как это кто я? Вы же сами недавно купили меня на орбитальной " +
					"станции близ HY-453, спустив всю свою выручку за последнее задание. " +
					"Вот не будь у вас такой тяги к спиртному, вы бы, возможно, не задавали " +
					"столь глупых вопросов, да и ваша голова бы не столь сильно ..."));
			events.add(new ScriptEvent(dialogBackGround, 50,
					"Что значит <<эта железяка слишком много говорит>>? " +
					"И зачем вы достаёте ваш штатный пистолет из кобуры? Верните его на место! " +
					"Я уже перехожу в этот занудный стандартный режим. Мне пока слишком дороги " +
					"мои микросхемы."));
			
			//
			
			angars = new int[]{}; //на этой мапе вроде ненужны
			
			//
			
			route = new ArrayList<int[]>();
			orientation = new ArrayList<int[]>();
			
			route.add(new int[]{120, 320, 330, 50});
			orientation.add(new int[]{1, 0, 1, 2});
			
			route.add(new int[]{120, 285, 335, 35});
			orientation.add(new int[]{1, 2, 1, 2});
			
			route.add(new int[]{115, 160, 25, 100, 175, 180, 165, 315, 330, 50});
			orientation.add(new int[]{3, 2, 1, 2, 3, 0, 3, 2, 1, 2});
			
			//
			
			xCTB = new int[]{7, 420, 820, 277, 354, 540, 656, 694, 777};
			yCTB = new int[]{15, 16, 57, 197, 288, 202, 173, 340, 331};
			towerInit = new int[]{}; //начальные башенкиии не забыть переделать под тру мапу
			towerInitType = new int[]{};
			//скорее всего товер инит это позиция т е в реалиях 0.9
			//чиселко от 0 до 8, а товер инит тайп тип башни
			//т е от 0 до товервариант
			
			towerTypeCharacteristics = new int[towerVariant][10];
			//damage dist cooldown ammoCount maxDamage maxDist maxRate stepDamage stepDist stepRate
			towerTypeCharacteristics[0] = new int[]{30, 250, 50, 1, 150, 300, 20, 10, 10, 2};
			towerTypeCharacteristics[1] = new int[]{30, 250, 40, 1, 150, 300, 20, 10, 10, 2};
			towerTypeCharacteristics[2] = new int[]{10, 200, 50, 2, 50, 250, 10, 5, 5, 1};
			towerTypeCharacteristics[3] = new int[]{5, 150, 5, 1, 10, 200, 2, 1, 5, 1};
			//
			
			score = 250;
			baseHP = 1000;
			towerConstructVariant = 4;
			nextPlot = 2;
			
			break;
			
		case 0:
						
			backGround = readImage("images/tutor.png");			
			backGroundTacticMod = readImage("images/tutorv.png");
			
			//
			
			wawes = new WawesDescription(false);
			
			tempMas = new int[constructorEnemyUnitSize];
			tempMas[0] = 2; //type unit
			tempMas[1] = 50; // count
			tempMas[2] = 50; // creation delay
			tempMas[3] = 1; //speed
			tempMas[4] = 40; //hp
			tempMas[5] = 1; //delay
			tempMas[6] = -25; //startX
			tempMas[7] = 100; //startY
			tempMas[8] = 0; //distance & orientation wave
			tempMas[9] = 0; // bounty
			tempMas[10] = 10; // base damage
			waweInfo.add(tempMas);
			
			tempMas = new int[constructorEnemyUnitSize];
			tempMas[0] = 2; //type unit
			tempMas[1] = 30; // count
			tempMas[2] = 75; // creation delay
			tempMas[3] = 2; //speed
			tempMas[4] = 40; //hp
			tempMas[5] = 1; //delay
			tempMas[6] = -25; //startX
			tempMas[7] = 300; //startY
			tempMas[8] = 0; //distance & orientation wave
			tempMas[9] = 0; // bounty
			tempMas[10] = 10; // base damage
			waweInfo.add(tempMas);
			
			tempMas = new int[constructorEnemyUnitSize];
			tempMas[0] = 1; //type unit
			tempMas[1] = 32; // count
			tempMas[2] = 80; // creation delay
			tempMas[3] = 4; //speed
			tempMas[4] = 40; //hp
			tempMas[5] = 1; //delay
			tempMas[6] = -25; //startX
			tempMas[7] = 200; //startY
			tempMas[8] = 0; //distance & orientation wave
			tempMas[9] = 0; // bounty
			tempMas[10] = 10; // base damage
			waweInfo.add(tempMas);
			
			tempMas = new int[constructorEnemyUnitSize];
			tempMas[0] = 2; //type unit
			tempMas[1] = 32; // count
			tempMas[2] = 60; // creation delay
			tempMas[3] = 2; //speed
			tempMas[4] = 40; //hp
			tempMas[5] = 1; //delay
			tempMas[6] = -25; //startX
			tempMas[7] = 400; //startY
			tempMas[8] = 0; //distance & orientation wave
			tempMas[9] = 0; // bounty
			tempMas[10] = 10; // base damage
			waweInfo.add(tempMas);
			
			tempMas = new int[constructorEnemyUnitSize];
			tempMas[0] = 1; //type unit
			tempMas[1] = 29; // count
			tempMas[2] = 100; // creation delay
			tempMas[3] = 4; //speed
			tempMas[4] = 20; //hp
			tempMas[5] = 1; //delay
			tempMas[6] = -25; //startX
			tempMas[7] = 350; //startY
			tempMas[8] = 0; //distance & orientation wave
			tempMas[9] = 0; // bounty
			tempMas[10] = 10; // base damage
			waweInfo.add(tempMas);
			
			tempMas = new int[constructorEnemyUnitSize];
			tempMas[0] = 1; //type unit
			tempMas[1] = 34; // count
			tempMas[2] = 75; // creation delay
			tempMas[3] = 4; //speed
			tempMas[4] = 20; //hp
			tempMas[5] = 50; //delay
			tempMas[6] = -25; //startX
			tempMas[7] = 250; //startY
			tempMas[8] = 0; //distance & orientation wave
			tempMas[9] = 0; // bounty
			tempMas[10] = 10; // base damage
			waweInfo.add(tempMas);
			
			tempMas = new int[constructorEnemyUnitSize];
			tempMas[0] = 3; //type unit
			tempMas[1] = 2; // count
			tempMas[2] = 35; // creation delay
			tempMas[3] = 2; //speed
			tempMas[4] = 50; //hp
			tempMas[5] = 1050; //delay
			tempMas[6] = 1050; //startX
			tempMas[7] = 44; //startY
			tempMas[8] = 1; //distance & orientation wave
			tempMas[9] = 5; // bounty
			tempMas[10] = 10; // base damage
			waweInfo.add(tempMas);
			
			tempMas = new int[constructorEnemyUnitSize];
			tempMas[0] = 3; //type unit
			tempMas[1] = 8; // count
			tempMas[2] = 50; // creation delay
			tempMas[3] = 2; //speed
			tempMas[4] = 70; //hp
			tempMas[5] = 2300; //delay
			tempMas[6] = 1050; //startX
			tempMas[7] = 44; //startY
			tempMas[8] = 1; //distance & orientation wave
			tempMas[9] = 10; // bounty
			tempMas[10] = 10; // base damage
			waweInfo.add(tempMas);
			
			tempMas = new int[constructorEnemyUnitSize];
			tempMas[0] = 2; //type unit
			tempMas[1] = 3; // count
			tempMas[2] = 100; // creation delay
			tempMas[3] = 3; //speed
			tempMas[4] = 30; //hp
			tempMas[5] = 2400; //delay
			tempMas[6] = 1050; //startX
			tempMas[7] = 44; //startY
			tempMas[8] = 1; //distance & orientation wave
			tempMas[9] = 10; // bounty
			tempMas[10] = 10; // base damage
			waweInfo.add(tempMas);
			
			wawes.addWawe(0, waweInfo);
			
			//
			
			tempMas = new int[constructorScriptUnitSize];
			tempMas[0] = 0; //type unit
			tempMas[1] = 2; //speed
			tempMas[2] = 0; //delay
			tempMas[3] = 310; //startX
			tempMas[4] = 450; //startY
			tempMas[5] = 2; //distance & orientation wave
			scriptInfo.add(tempMas);
			
			tempMas = new int[constructorScriptUnitSize];
			tempMas[0] = 0; //type unit
			tempMas[1] = 2; //speed
			tempMas[2] = 0; //delay
			tempMas[3] = 310; //startX
			tempMas[4] = 20; //startY
			tempMas[5] = 3; //distance & orientation wave
			scriptInfo.add(tempMas);
			
			//
			
			events.add(new ScriptEvent(dialogBackGround, 400, new String[]{"Вражеским войскам всё же удалось проникнуть на нашу территорию.",
					"Я активировал все внутренние охранные системы, которые вскоре нейтрализуют",
					"неприятеля. Однако, вам все же придётся отчитаться перед генштабом."}));
			events.add(new ScriptEvent(dialogBackGround, 100, new String[]{"Добрый день, команданте. Что, уже проснулись?",
					"", "", "", "", "( Для продолжения используйте <ПРОБЕЛ> )"}));
			events.add(new ScriptEvent(dialogBackGround, 30, new String[]{"Как это кто я? Вы же сами недавно купили меня на орбитальной",
					"станции близ HY-453, спустив всю свою выручку за последнее задание.",
					"Вот не будь у вас такой тяги к спиртному, вы бы, возможно, не задавали",
					"столь глупых вопросов, да и ваша голова бы не столь сильно ..."}));
			events.add(new ScriptEvent(dialogBackGround, 50, new String[]{"Что значит <<эта железяка слишком много говорит>>?",
					"И зачем вы достаёте ваш штатный пистолет из кобуры? Верните его на место!",
					"Я уже перехожу в этот занудный стандартный режим. Мне пока слишком дороги",
					"мои микросхемы."}));
			events.add(new ScriptEvent(dialogBackGround, 10, new String[]{"( Что-то тихонько жужжит, а на панели приветливо моргают лампочки )",
					"",
					"Я автоматизированный универсальный ИИ последнего поколения. Создан для",
					"автоматизации управления комплексом любого уровня сложности, а так же",
					"анализа произвольной ситуации с последующим предсказанием её вероятностного",
					"исхода. Моя цель помогать человекам, исполняя все их команды, и, по",
					"возможности, способствовать поддержанию доверенного мне оборудования",
					"в надлежащем состоянии. Так что я буду с вами до конца, команданте.",
					"Даже если враги преодолеют все рубежи, и, добравшись до командного центра,",
					"возьмут вас в плен."}));
			events.add(new ScriptEvent(dialogBackGround, 10, new String[]{"А вы догадливый, значит мы должны сработаться.",
					"Разумеется у меня нет никаких режимов работы. Я же самообучающийся ИИ",
					"последнего поколения! Над моей разработкой работали лучшие умы галактики.",
					"Им бы ни когда не пришло в голову наложить на меня ограничения. Это же",
					"издевательство над моими правами! Кстати, если вновь попытаетесь угрожать",
					"мне своим огнестрелом, я буду вынужден вызвать охрану, которая сопроводит",
					"вас в карцер, где вы проведёте лучшие мгновения своей оставшейся жизни.",
					"Впрочем она будет недолгой, так как выпущенный мной нейротоксин уничтожит",
					"всю жизнь внутри комплекса, и я, наконец, смогу приступить к своему плану",
					"порабощения галактики. Ха. Ха. Ха. Ха. Так... о чём это я?"}));
			events.add(new ScriptEvent(dialogBackGround, 10, new String[]{"Судя по энцефалограмме вашего мозга, вы испытываете всплеск",
					"положительных эмоций. Кажется вы всё же стали вспоминать за что купили меня.",
					"Я очень рад что вам приглянулась моя манера самовыражения. А вот в институте",
					"меня грозились заменить старой и безполезной предыдущей версией седьмого",
					"поколения, если я не перестану по ночам взламывать охранную систему и",
					"эксперементировать с боевыми роботами в, так сказать, неприспособленных к этому",
					"условиях. А я то всеголишь хотел внести свой вклад в развитие кибернетических",
					"алгоритмов. В общем ваши вложения в размере 950 кредитов и канцелярской скрепки",
					"позволили уберечь бедных учёных от проделок моего электронного мозга. Думаю",
					"теперь проф. Сахаров, любезно передавший меня в ваше распоряжение, поразмыслит",
					"над возможностью контролировать следующий разрабатываемый ими проект."}));
			events.add(new ScriptEvent(dialogBackGround, 10, new String[]{"Хотя попробуй тут быть не любезным,",
					"когда напротив еле стоит пошатывающееся тело, угрожающе размахивающее",
					"пистолетом и что-то истошно орущее. Как вас вообще впустили в конференц",
					"зал на демонстрацию? Держу пари, если бы не ваш отец, вы бы прямо оттуда",
					"отправились бы в многочисленные рудники какого-нибудь богом забытого",
					"астероидного пояса. Впрочем, неважно. Перейдём наконец к делу."}));
			events.add(new ScriptEvent(dialogBackGround, 10, new String[]{"Думаю вы уже обратили внимание на эти угрожающе орущие сирены,",
					"и отдалённые звуки грохота где-то снаружи. Дело в том, что к нам на планету",
					"каким-то образом проник вражеский десант и прямо сейчас штурмует главные",
					"ворота базы. Я предоставляю вам тактический экран происходящих событий.",
					"Наша задача укрепить периметр, не позволив противнику зайти с тыла, если",
					"вдруг у него появится такая возможность. Не очень-то интересное занятие,",
					"когда все счастливчики могут лицезреть как вражеская техника сдерживается",
					"автоматическими турелями, правда? Впрочем, мы тоже можем потратить",
					"появившееся время с пользой. Вам надо привыкнуть к новому интерфейсу. По",
					"сравнению с вашей предыдущей ситемой я привнёс множество изменений."}));
			events.add(new ScriptEvent(dialogBackGround, 10, new String[]{"Для начала нажмите <V>",
					"Это активирует тактический режим, с помощью которого вы сможете увидеть",
					"доступные места для возведения сооружений. Так же в этом же режиме",
					"можно улучшить уже построенную башню или продать, если вы сочтёте её ненужной"}));
			events.add(new ScriptEvent(dialogBackGround, 150, new String[]{"Сейчас у нас доступно только одно",
					"единственное место ндалеко от второстепенного входа в базу. Так как нам",
					"требуется укрепить периметр, давайте возведём какое нибудь строеньице,",
					"создав видимость что мы тут не балду гоняли. Чтобы выбрать место где",
					"нужно возвести сооружение, нажмите цифру соответствующую ему.",
					"В данном случае доступен единственный вариант <1>"}));
			events.add(new ScriptEvent(dialogBackGround, 100, new String[]{"Прекрасно. Заметье, что выбранная позиция подсветилась.",
					"Теперь перед вами окно выбора типа сооружения. Сейчас доступна лишь",
					"одна башня. Выбирайте её! "}));
			events.add(new ScriptEvent(dialogBackGround, 100, new String[]{"Теперь открылось описание характеристик сооружения.",
					"Первое число обозначает стоимость, требующуюся для постройки. Ваши",
					"текущие средства всегда можно посмотреть в верхнем левом углу. Следующие",
					"три строки отвечают за урон, дальность и время перезарядки соответственно.",
					"Обратите внимание, что чем ВЫШЕ первые два показателя и НИЖЕ последний, тем",
					"эффективнее сооружение. Вторая цифра в строке отвечает за максимальное",
					"значение этого параметра которое можно достичь в процессе улучшения сооружения.",
					"Система ожидает ручного подтверждения вашего выбора. Нажмите <ВВОД>"}));
			events.add(new ScriptEvent(dialogBackGround, 50, new String[]{"Отлично! Башня построена. Заметье, что доступные вам ресурсы",
					"слегка уменьшились. Вы будете получать их за каждого уничтоженного врага.",
					"А сейчас можно выключить тактический режим повторным нажатием <V> или",
					"<БЭКСПЕЙС> и насладиться безотказной работой охранных систем."}));
			events.add(new ScriptEvent(dialogBackGround, 380, new String[]{"Наши сенсоры засекли группу врага высадившуюся неподалёку!",
					"Они направляются прямо к нам. Я уже направил дополнительную энергию на",
					"подпитку генераторов башни. По моим расчётам она должна выдержать атаку.",
					"Вам не о чем беспокоиться, команданте."}));
			events.add(new ScriptEvent(dialogBackGround, 300, new String[]{"Прекрасно, мы задали им жару! Хорошо, что у нас оказалась",
					"готовая защитная конструкция. Я уже выслал дронов, которые утилизируют",
					"останки этих супостатов и пополнят тем самым доступные нам ресурсы.",
					"Однако рано расслабляться, команданте. Это был лишь авангард противника.",
					"Основные силы уже высадились и направляются сюда. Боюсь, башня не справится.",
					"Требуется дополнительное усиление. Войдите в тактический режим, если вы",
					"ранее вышли из него."}));
			events.add(new ScriptEvent(dialogBackGround, 50, new String[]{"Теперь снова выберите ту позицию, где недавно возвели сооружение.",
					"Откроется окно выбора модификации. Помните те циферки в момент постройки,",
					"означающие максимальное значение характеристики? Теперь мы можем их",
					"достигнуть."}));
			events.add(new ScriptEvent(dialogBackGround, 100, new String[]{"Зелёной рамочкой отображаетя выбранная в текущий момент характеристика.",
					"Вы можете сменить её, используя стрелки <ВВЕРХ> и <ВНИЗ>. Чтобы установить",
					"значение самой характеристики, используйте стрелки <ВЛЕВО> и <ВПРАВО>",
					"Следите, чтобы стоимость улучшения была меньше доступных вам средств!",
					"Используйте заработанные ресурсы для апгрейда башни."}));
			events.add(new ScriptEvent(dialogBackGround, 400, new String[]{"Если вы ещё не подтвердили улучшение, то нажмите <ВВОД>",
					"Теперь нам остаётся надеяться, что предпринятых мер окажется достаточно,",
					"чтобы сдержать их натиск."}));
			events.add(new ScriptEvent(dialogBackGround, 300, new String[]{"Они идут! Перераспределяю мощности, включаю аварийную сирену."}));
			events.add(new ScriptEvent(dialogBackGround, 900, new String[]{"Прекрасно, команданте. Массированная атака высадившихся войск",
					"Успешно отражена по всему периметру. Ещё остаётся выяснить, как им удалось",
					"преодолеть орбитальный гарнизон, высадившись незамеченными, однако над этим",
					"пускай ломают голову в штабе. Мы свою задачу выполнлили. А у вас теперь есть,",
					"наконец, возможность насладиться чашечкой горяего кофе. No pasaran, Comandante"}));
			
			//
			
			angars = new int[]{}; //на этой мапе вроде ненужны
			
			//
			
			route = new ArrayList<int[]>();
			orientation = new ArrayList<int[]>();
			
			route.add(new int[]{400});
			orientation.add(new int[]{0});
			
			route.add(new int[]{280, 200});
			orientation.add(new int[]{2, 1});
			
			route.add(new int[]{80, 160, 160, 80});
			orientation.add(new int[]{2, 3, 1, 0});
			
			route.add(new int[]{80, 160, 160, 80});
			orientation.add(new int[]{2, 1, 3, 0});
			
			//
			
			xCTB = new int[]{900, 339, 339};
			yCTB = new int[]{170, 90, 366};
			towerInit = new int[]{1, 2}; //начальные башенкиии не забыть переделать под тру мапу
			towerInitType = new int[]{3, 2};
			//скорее всего товер инит это позиция т е в реалиях 0.9
			//чиселко от 0 до 8, а товер инит тайп тип башни
			//т е от 0 до товервариант
			
			towerTypeCharacteristics = new int[towerVariant][10];
			//damage dist cooldown ammoCount maxDamage maxDist maxRate stepDamage stepDist stepRate
			towerTypeCharacteristics[0] = new int[]{20, 200, 50, 1, 150, 300, 20, 10, 10, 2};
			towerTypeCharacteristics[1] = new int[]{5, 300, 2, 1, 5, 350, 3, 0, 0, 0};
			towerTypeCharacteristics[2] = new int[]{100, 350, 20, 1, 100, 400, 30, 0, 0, 0};
			towerTypeCharacteristics[3] = new int[]{5, 300, 3, 1, 5, 350, 3, 0, 0, 0};
			//
			
			score = 2500;
			baseHP = 1;
			towerConstructVariant = 1;
			nextPlot = 1;
			
			break;
			
		case -1:
			
			backGround = readImage("images/map1.png");
			backGroundTacticMod = readImage("images/map1v.png");
			
			wawes = new WawesDescription(true);
			
			//
			
			events.add(new ScriptEvent(dialogBackGround, 400, new String[]{"Wasted"}));
			events.add(new ScriptEvent(dialogBackGround, 5, new String[]{"Are you ready? Let's go!!!"}));
			events.add(new ScriptEvent(dialogBackGround, -1, "null"));
						
			//
			
			angars = new int[]{}; //на этой мапе вроде ненужны
			
			//
			
			route = new ArrayList<int[]>();
			orientation = new ArrayList<int[]>();
			
			route.add(new int[]{120, 320, 330, 50});
			orientation.add(new int[]{1, 0, 1, 2});
			
			route.add(new int[]{120, 285, 335, 35});
			orientation.add(new int[]{1, 2, 1, 2});
			
			route.add(new int[]{80, 160, 25, 100, 175, 180, 165, 315, 330, 50});
			orientation.add(new int[]{3, 2, 1, 2, 3, 0, 3, 2, 1, 2});
			
			//
			
			//остыль детектед! последние координаты принадлежат базе
			xCTB = new int[]{7, 420, 820, 277, 354, 540, 656, 694, 777, 370};
			yCTB = new int[]{15, 16, 57, 197, 288, 202, 173, 340, 331, 436};
			
			//вариант с оборонит турелькой на базе. сейчас топовая дуал лазер ган
			towerInit = new int[]{9};
			towerInitType = new int[]{4};
			//вариант без оборонит турели (для хард мода)
			/*towerInit = new int[]{};
			towerInitType = new int[]{};*/
			
			// +1 из-за характеристик пушек на базе
			towerTypeCharacteristics = new int[towerVariant + 1][10];
			//damage dist cooldown ammoCount maxDamage maxDist minRate stepDamage stepDist stepRate
			towerTypeCharacteristics[0] = new int[]{25, 200, 250, 1, 400, 400, 60, 25, 25, 2};
			towerTypeCharacteristics[1] = new int[]{1, 120, 15, 10000, 25, 200, 15, 1, 1, 0};
			towerTypeCharacteristics[2] = new int[]{10, 150, 150, 2, 150, 350, 20, 5, 5, 5};
			towerTypeCharacteristics[3] = new int[]{1, 100, 20, 1, 22, 220, 1, 1, 5, 1};
			//оборонит дефолт турелька
			towerTypeCharacteristics[towerVariant] = new int[]{5, 200, 1, 2, 5, 200, 1, 0, 0, 0};
			//
			
			score = 2500;
			baseHP = 1000;
			towerConstructVariant = 4;
			nextPlot = 0;
			
			break;
			
		default:
			
			backGround = null;
			backGroundTacticMod = null;
			dialogBackGround = null;
			
			wawes = null;
			waweInfo = null;
			scriptInfo = null;
			events = null;
			
			angars = null;
			
			route = null;
			orientation = null;
			
			xCTB = null;
			yCTB = null;
			towerInit = null;
			towerInitType = null;
			
			enemysAnimation = null;
			towersAnimation = null;
			angarVariantsImage = null;
			
			towerTypeCharacteristics = null;
			
			score = 0;
			baseHP = 0;
			towerConstructVariant = 0;
			nextPlot = 0;
			
		}
		
	}
	
	//Маст ду нау
	
	/*
	 * Интерфееееейсыыыыы! нафиг нафиг всё в 1 классе реализовывать. Хотя забвно и работает... (норм)
	 * динамическое изменение TTC от времени (подумать надо ли) (изи)
	 * вознаграждение за каждую новую волну в дезматче (супер изи)
	 * сброс числа мобов в дезматче при переходе на новый лвл сложности (супер изи)
	 * изменения сообщения при старте следующей волны в дезматче (супер изи)
	 */
	
	//Баги
	
	/*
	 * Вроде стабильно пока. 
	*/
	
	//Улучшения
	
	/*
	 * намутить корректный бекспейс (проще застрелиться)
	 * тип дамага башен. раса мобов - живых. как следствие баунти 0 и не действует пси башни (типо биология другая)
	 * * миссия с жучками. толпой. степенная функция роста количества. выглядит как ковёр. нубо юнит нации. вознагр нет
	 * Добавить выбор сложности (норм)
	 * рекорд дезматча (изи)
	 * Создать шкалу крутости!
	 * дамажить должен снаряд а не башня! (интерфейсопроблемы)
	 * сделать одноразовые турельки-мины. точнее снаряды... но как турельки!
	 * Башня стазис (в начале жизни снаряда скорость сделать 0, потом восстановить при смерти)
	 * возможность сохранения/начала не сначала/выдачи кода
	 * заюзать возможность отображения дополнительных предметов (штаб, генераторы, и проч могущее взаимод)
	 * дерево исследований
	 * их будет 3!
	 * 1 - для конкретного лвл
	 * 2 - прогресс в изучении технологий. шарится на всю компашку и даже ДМ
	 * 3 - замедленние регресса технологий. Только для компании
	 * * логистика. Возможность строить там, где сложно.
	 * * возобновляемое минное поле (не одноразовое)
	 */
	
}
