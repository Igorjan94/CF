package TDGame;

import java.util.ArrayList;

public class WawesDescription {
	
	private ArrayList<ArrayList<int[]>> wawes;
	private int waweNumber;
	private ArrayList<Integer> retention;
	private boolean deathmatchMode;
	
	static final int[] deathModeX = new int[]{130, 727, 845};
	static final int[] deathModeY = new int[]{-25, -25, 495};
	
	WawesDescription(boolean mode) {
		wawes = new ArrayList<ArrayList<int[]>>();
		retention = new ArrayList<Integer>();
		waweNumber = -1;
		deathmatchMode = mode;
	}
	
	private void generateNextWawe(int number) {
		//размер вэйвинфо надо бы знать
		//и число юнитов
		
		ArrayList<int[]> waweInfo = new ArrayList<int[]>();
		
		//Easy mode!!!
		int[] tempMas;
		
		if(waweNumber < 5) {
			
			for(int i = 0; i < 2 + number / 2; i++) {
				tempMas = new int[11];
				tempMas[0] = (int) (Math.random() * 4); //type unit
				tempMas[1] = 1 + (int) (Math.random() * (number + 1)); // count
				tempMas[3] = 1 + (int) (Math.random() * 3); //speed
				tempMas[4] = 10 + (int) (Math.random() * number * 2); //hp
				tempMas[5] = 1 + (int) (Math.random() * number * 100); //delay
				tempMas[8] = (int) (Math.random() * 3); //distance & orientation wave
				tempMas[6] = deathModeX[tempMas[8]]; //startX
				tempMas[7] = deathModeY[tempMas[8]]; //startY			
				tempMas[9] = 1; // bounty
				tempMas[10] = 1; // base damage
				tempMas[2] = 50  + (int) (Math.random() * 75); // creation delay
				waweInfo.add(tempMas);
			}
			
			tempMas = new int[11];
			tempMas[0] = 4; //type unit
			tempMas[1] = 1; // count
			tempMas[3] = 2; //speed
			tempMas[4] = 100 + (int) (Math.random() * number * 2); //hp
			tempMas[5] = 150 + number * 100; //delay
			tempMas[8] = (int) (Math.random() * 3); //distance & orientation wave
			tempMas[6] = deathModeX[tempMas[8]]; //startX
			tempMas[7] = deathModeY[tempMas[8]]; //startY			
			tempMas[9] = 10; // bounty
			tempMas[10] = 10; // base damage
			tempMas[2] = 1; // creation delay
			waweInfo.add(tempMas);
			
		} else if(waweNumber < 10) {
			
			for(int i = 0; i < 2 + number / 1.5; i++) {
				tempMas = new int[11];
				tempMas[0] = (int) (Math.random() * 4); //type unit
				tempMas[1] = 1 + (int) (Math.random() * (number * 1.3 + 1)); // count
				tempMas[3] = 1 + (int) (Math.random() * 5); //speed
				tempMas[4] = 10 + (int) (Math.random() * number * 3); //hp
				tempMas[5] = 1 + (int) (Math.random() * number * 100); //delay
				tempMas[8] = (int) (Math.random() * 3); //distance & orientation wave
				tempMas[6] = deathModeX[tempMas[8]]; //startX
				tempMas[7] = deathModeY[tempMas[8]]; //startY			
				tempMas[9] = 1 + (int) Math.random(); // bounty
				tempMas[10] = 1; // base damage
				tempMas[2] = 50  + (int) (Math.random() * 75); // creation delay
				waweInfo.add(tempMas);
			}
			
			tempMas = new int[11];
			tempMas[0] = 4; //type unit
			tempMas[1] = 1; // count
			tempMas[3] = 2; //speed
			tempMas[4] = 150 + (int) (Math.random() * number * 4); //hp
			tempMas[5] = 150 + number * 100; //delay
			tempMas[8] = (int) (Math.random() * 3); //distance & orientation wave
			tempMas[6] = deathModeX[tempMas[8]]; //startX
			tempMas[7] = deathModeY[tempMas[8]]; //startY			
			tempMas[9] = 12; // bounty
			tempMas[10] = 10; // base damage
			tempMas[2] = 1; // creation delay
			waweInfo.add(tempMas);
			
		} else if(waweNumber < 15) {
			
			for(int i = 0; i < 2 + number / 1.2; i++) {
				tempMas = new int[11];
				tempMas[0] = (int) (Math.random() * 4); //type unit
				tempMas[1] = 5 + (int) (Math.random() * (number * 1.5)); // count
				tempMas[3] = 1 + (int) (Math.random() * 9); //speed
				if(tempMas[3] < 5) {
					tempMas[4] = 50 + (int) (Math.random() * number * 4); //hp
				} else if(tempMas[3] < 7) {
					tempMas[4] = 25 + (int) (Math.random() * number * 2); //hp
				} else {
					tempMas[4] = 10 + (int) (Math.random() * number); //hp
				}
				tempMas[5] = 1 + (int) (Math.random() * number * 100); //delay
				tempMas[8] = (int) (Math.random() * 3); //distance & orientation wave
				tempMas[6] = deathModeX[tempMas[8]]; //startX
				tempMas[7] = deathModeY[tempMas[8]]; //startY			
				tempMas[9] = 1 + (int) Math.random(); // bounty
				tempMas[10] = 1; // base damage
				tempMas[2] = 50  + (int) (Math.random() * 75); // creation delay
				waweInfo.add(tempMas);
			}
			
			tempMas = new int[11];
			tempMas[0] = 4; //type unit
			tempMas[1] = 1; // count
			tempMas[3] = 5; //speed
			tempMas[4] = 200 + (int) (Math.random() * number * 3); //hp
			tempMas[5] = 150 + number * 100; //delay
			tempMas[8] = (int) (Math.random() * 3); //distance & orientation wave
			tempMas[6] = deathModeX[tempMas[8]]; //startX
			tempMas[7] = deathModeY[tempMas[8]]; //startY			
			tempMas[9] = 15; // bounty
			tempMas[10] = 10; // base damage
			tempMas[2] = 1; // creation delay
			waweInfo.add(tempMas);
			
		} else if(waweNumber < 25) {
			
			for(int i = 0; i < 2 + number / 1.1; i++) {
				tempMas = new int[11];
				tempMas[0] = (int) (Math.random() * 4); //type unit
				tempMas[1] = 7 + (int) (Math.random() * (number * 1)); // count
				tempMas[3] = 1 + (int) (Math.random() * 10); //speed
				if(tempMas[3] < 5) {
					tempMas[4] = 150 + (int) (Math.random() * number * 4); //hp
				} else if(tempMas[3] < 7) {
					tempMas[4] = 75 + (int) (Math.random() * number * 3); //hp
				} else {
					tempMas[4] = 25 + (int) (Math.random() * number * 2); //hp
				}
				tempMas[5] = 1 + (int) (Math.random() * number * 100); //delay
				tempMas[8] = (int) (Math.random() * 3); //distance & orientation wave
				tempMas[6] = deathModeX[tempMas[8]]; //startX
				tempMas[7] = deathModeY[tempMas[8]]; //startY			
				tempMas[9] = 1 + (int) (Math.random() * 2); // bounty
				tempMas[10] = 1; // base damage
				tempMas[2] = 50  + (int) (Math.random() * 75); // creation delay
				waweInfo.add(tempMas);
			}
			
			tempMas = new int[11];
			tempMas[0] = 4; //type unit
			tempMas[1] = 1; // count
			tempMas[3] = 3; //speed
			tempMas[4] = 250 + (int) (Math.random() * number * 5); //hp
			tempMas[5] = 150 + number * 100; //delay
			tempMas[8] = (int) (Math.random() * 3); //distance & orientation wave
			tempMas[6] = deathModeX[tempMas[8]]; //startX
			tempMas[7] = deathModeY[tempMas[8]]; //startY			
			tempMas[9] = 25; // bounty
			tempMas[10] = 10; // base damage
			tempMas[2] = 1; // creation delay
			waweInfo.add(tempMas);
			
		} else if(waweNumber < 50) {
			
			for(int i = 0; i < 2 + number; i++) {
				tempMas = new int[11];
				tempMas[0] = (int) (Math.random() * 4); //type unit
				tempMas[1] = 1 + (int) (Math.random() * (number * 2)); // count
				tempMas[3] = 1 + (int) (Math.random() * 9); //speed
				if(tempMas[3] < 5) {
					tempMas[4] = 500 + (int) (Math.random() * number * 6); //hp
				} else if(tempMas[3] < 7) {
					tempMas[4] = 250 + (int) (Math.random() * number * 4); //hp
				} else {
					tempMas[4] = 100 + (int) (Math.random() * number * 2); //hp
				}
				tempMas[5] = 1 + (int) (Math.random() * number * 100); //delay
				tempMas[8] = (int) (Math.random() * 3); //distance & orientation wave
				tempMas[6] = deathModeX[tempMas[8]]; //startX
				tempMas[7] = deathModeY[tempMas[8]]; //startY			
				tempMas[9] = 2 + (int) (Math.random() * 2); // bounty
				tempMas[10] = 1; // base damage
				tempMas[2] = 50  + (int) (Math.random() * 75); // creation delay
				waweInfo.add(tempMas);
			}
			
			tempMas = new int[11];
			tempMas[0] = 4; //type unit
			tempMas[1] = 1; // count
			tempMas[3] = 6; //speed
			tempMas[4] = 150 + (int) (Math.random() * number * 8); //hp
			tempMas[5] = 150 + number * 100; //delay
			tempMas[8] = 2; //distance & orientation wave
			tempMas[6] = deathModeX[2]; //startX
			tempMas[7] = deathModeY[2]; //startY			
			tempMas[9] = 30; // bounty
			tempMas[10] = 10; // base damage
			tempMas[2] = 1; // creation delay
			waweInfo.add(tempMas);
			
		} else if(waweNumber < 100) {			
			for(int i = 0; i < 2 + number; i++) {
				tempMas = new int[11];
				tempMas[0] = (int) (Math.random() * 4); //type unit
				tempMas[1] = 1 + (int) (Math.random() * (number * 2.5)); // count
				tempMas[3] = 3 + (int) (Math.random() * 7); //speed
				if(tempMas[3] < 5) {
					tempMas[4] = 2500 + (int) (Math.random() * number * 5); //hp
				} else if(tempMas[3] < 7) {
					tempMas[4] = 1000 + (int) (Math.random() * number * 3); //hp
				} else {
					tempMas[4] = 250 + (int) (Math.random() * number * 2); //hp
				}
				tempMas[5] = 1 + (int) (Math.random() * number * 100); //delay
				tempMas[8] = (int) (Math.random() * 3); //distance & orientation wave
				tempMas[6] = deathModeX[tempMas[8]]; //startX
				tempMas[7] = deathModeY[tempMas[8]]; //startY			
				tempMas[9] = 4 + (int) (Math.random() * 2); // bounty
				tempMas[10] = 1; // base damage
				tempMas[2] = 50  + (int) (Math.random() * 75); // creation delay
				waweInfo.add(tempMas);
			}
			
			tempMas = new int[11];
			tempMas[0] = 4; //type unit
			tempMas[1] = 1; // count
			tempMas[3] = 2; //speed
			tempMas[4] = 1000 + (int) (Math.random() * number * 20); //hp
			tempMas[5] = 150 + number * 100; //delay
			tempMas[8] = 2; //distance & orientation wave
			tempMas[6] = deathModeX[2]; //startX
			tempMas[7] = deathModeY[2]; //startY			
			tempMas[9] = 50; // bounty
			tempMas[10] = 10; // base damage
			tempMas[2] = 1; // creation delay
			waweInfo.add(tempMas);
			
		} else {
			
			for(int i = 0; i < 2 + number; i++) {
				tempMas = new int[11];
				tempMas[0] = (int) (Math.random() * 4); //type unit
				tempMas[1] = 1 + (int) (Math.random() * (number * 2)); // count
				tempMas[3] = 5 + (int) (Math.random() * 6); //speed
				if(tempMas[3] < 6) {
					tempMas[4] = 5000 + (int) (Math.random() * number * 10); //hp
				} else if(tempMas[3] < 8) {
					tempMas[4] = 2000 + (int) (Math.random() * number * 5); //hp
				} else {
					tempMas[4] = 1000 + (int) (Math.random() * number * 2); //hp
				}
				tempMas[5] = 1 + (int) (Math.random() * number * 100); //delay
				tempMas[8] = (int) (Math.random() * 3); //distance & orientation wave
				tempMas[6] = deathModeX[tempMas[8]]; //startX
				tempMas[7] = deathModeY[tempMas[8]]; //startY			
				tempMas[9] = 5; // bounty
				tempMas[10] = 1; // base damage
				tempMas[2] = 50  + (int) (Math.random() * 75); // creation delay
				waweInfo.add(tempMas);
			}
			
			tempMas = new int[11];
			tempMas[0] = 4; //type unit
			tempMas[1] = 1; // count
			tempMas[3] = 5 + (int) (Math.random() * 6); //speed
			tempMas[4] = 10000 + (int) (Math.random() * number * 25); //hp
			tempMas[5] = 150 + number * 100; //delay
			tempMas[8] = (int) (Math.random() * 3); //distance & orientation wave
			tempMas[6] = deathModeX[tempMas[8]]; //startX
			tempMas[7] = deathModeY[tempMas[8]]; //startY			
			tempMas[9] = 10 * number; // bounty
			tempMas[10] = 25; // base damage
			tempMas[2] = 1; // creation delay
			waweInfo.add(tempMas);
			
		}
		
		switch(waweNumber) {
		case 4:
			tempMas = new int[11];
			tempMas[0] = 5; //type unit
			tempMas[1] = 1; // count
			tempMas[3] = 1 + (int) (Math.random() * 4); //speed
			tempMas[4] = 1000 + (int) (Math.random() * number * 5); //hp
			tempMas[5] = 500 + number * 100; //delay
			tempMas[8] = 2; //distance & orientation wave
			tempMas[6] = deathModeX[2]; //startX
			tempMas[7] = deathModeY[2]; //startY			
			tempMas[9] = 100 * number; // bounty
			tempMas[10] = 20; // base damage
			tempMas[2] = 1; // creation delay
			waweInfo.add(tempMas);
			break;
		case 9:
			tempMas = new int[11];
			tempMas[0] = 5; //type unit
			tempMas[1] = 1; // count
			tempMas[3] = 1 + (int) (Math.random() * 4); //speed
			tempMas[4] = 1500 + (int) (Math.random() * number * 10); //hp
			tempMas[5] = 500 + number * 100; //delay
			tempMas[8] = 2; //distance & orientation wave
			tempMas[6] = deathModeX[2]; //startX
			tempMas[7] = deathModeY[2]; //startY			
			tempMas[9] = 100 * number; // bounty
			tempMas[10] = 20; // base damage
			tempMas[2] = 1; // creation delay
			waweInfo.add(tempMas);
			break;
		case 14:
			tempMas = new int[11];
			tempMas[0] = 5; //type unit
			tempMas[1] = 1; // count
			tempMas[3] = 1 + (int) (Math.random() * 4); //speed
			tempMas[4] = 2500 + (int) (Math.random() * number * 20); //hp
			tempMas[5] = 500 + number * 100; //delay
			tempMas[8] = 2; //distance & orientation wave
			tempMas[6] = deathModeX[2]; //startX
			tempMas[7] = deathModeY[2]; //startY			
			tempMas[9] = 100 * number; // bounty
			tempMas[10] = 20; // base damage
			tempMas[2] = 1; // creation delay
			waweInfo.add(tempMas);
			break;
		case 24:
			tempMas = new int[11];
			tempMas[0] = 5; //type unit
			tempMas[1] = 1; // count
			tempMas[3] = 1 + (int) (Math.random() * 4); //speed
			tempMas[4] = 5000 + (int) (Math.random() * number * 50); //hp
			tempMas[5] = 500 + number * 100; //delay
			tempMas[8] = 2; //distance & orientation wave
			tempMas[6] = deathModeX[2]; //startX
			tempMas[7] = deathModeY[2]; //startY			
			tempMas[9] = 100 * number; // bounty
			tempMas[10] = 20; // base damage
			tempMas[2] = 1; // creation delay
			waweInfo.add(tempMas);
			break;
		case 49:
			tempMas = new int[11];
			tempMas[0] = 5; //type unit
			tempMas[1] = 1; // count
			tempMas[3] = 1 + (int) (Math.random() * 4); //speed
			tempMas[4] = 15000 + (int) (Math.random() * number * 100); //hp
			tempMas[5] = 500 + number * 100; //delay
			tempMas[8] = 2; //distance & orientation wave
			tempMas[6] = deathModeX[2]; //startX
			tempMas[7] = deathModeY[2]; //startY			
			tempMas[9] = 100 * number; // bounty
			tempMas[10] = 20; // base damage
			tempMas[2] = 1; // creation delay
			waweInfo.add(tempMas);
			break;
		case 99:
			tempMas = new int[11];
			tempMas[0] = 5; //type unit
			tempMas[1] = 1; // count
			tempMas[3] = 1 + (int) (Math.random() * 4); //speed
			tempMas[4] = 1000000; //hp
			tempMas[5] = 1000 + number * 100; //delay
			tempMas[8] = 2; //distance & orientation wave
			tempMas[6] = deathModeX[2]; //startX
			tempMas[7] = deathModeY[2]; //startY			
			tempMas[9] = 1000 * number; // bounty
			tempMas[10] = 50; // base damage
			tempMas[2] = 1; // creation delay
			waweInfo.add(tempMas);
			break;
		}
		
		wawes.add(waweInfo);
		
		/*
		if(waweNumber < 5) {
			for(int i = 0; i < 2 + number; i++) {
				int[] tempMas = new int[11];
				tempMas[0] = (int) (Math.random() * 4); //type unit
				tempMas[1] = 1 + (int) (Math.random() * (number * 2 + 1)); // count
				tempMas[3] = 1 + (int) (Math.random() * 3); //speed
				tempMas[4] = 15 + (int) (Math.random() * number * 4); //hp
				tempMas[5] = 1 + (int) (Math.random() * number * 100); //delay
				tempMas[8] = (int) (Math.random() * 3); //distance & orientation wave
				tempMas[6] = deathModeX[tempMas[8]]; //startX
				tempMas[7] = deathModeY[tempMas[8]]; //startY			
				tempMas[9] = 1; // bounty
				tempMas[10] = 1; // base damage
				tempMas[2] = 50  + (int) (Math.random() * 75); // creation delay
				waweInfo.add(tempMas);
			}
		} else if(waweNumber < 10) {
			for(int i = 0; i < 2 + number; i++) {
				int[] tempMas = new int[11];
				tempMas[0] = (int) (Math.random() * 4); //type unit
				tempMas[1] = 1 + (int) (Math.random() * (number * 2 + 1)); // count
				tempMas[3] = 1 + (int) (Math.random() * 5); //speed
				tempMas[4] = 20 + (int) (Math.random() * number * 7); //hp
				tempMas[5] = 1 + (int) (Math.random() * number * 100); //delay
				tempMas[8] = (int) (Math.random() * 3); //distance & orientation wave
				tempMas[6] = deathModeX[tempMas[8]]; //startX
				tempMas[7] = deathModeY[tempMas[8]]; //startY			
				tempMas[9] = 1; // bounty
				tempMas[10] = 1; // base damage
				tempMas[2] = 50  + (int) (Math.random() * 75); // creation delay
				waweInfo.add(tempMas);
			}
		} else if(waweNumber < 15) {			
			for(int i = 0; i < 2 + number; i++) {
				int[] tempMas = new int[11];
				tempMas[0] = (int) (Math.random() * 4); //type unit
				tempMas[1] = 5 + (int) (Math.random() * (number * 1.5)); // count
				tempMas[3] = 1 + (int) (Math.random() * 9); //speed
				if(tempMas[3] < 5) {
					tempMas[4] = 25 + (int) (Math.random() * number * 10); //hp
				} else if(tempMas[3] < 7) {
					tempMas[4] = 10 + (int) (Math.random() * number * 7); //hp
				} else {
					tempMas[4] = 1 + (int) (Math.random() * number * 5); //hp
				}
				tempMas[5] = 1 + (int) (Math.random() * number * 100); //delay
				tempMas[8] = (int) (Math.random() * 3); //distance & orientation wave
				tempMas[6] = deathModeX[tempMas[8]]; //startX
				tempMas[7] = deathModeY[tempMas[8]]; //startY			
				tempMas[9] = 1; // bounty
				tempMas[10] = 1; // base damage
				tempMas[2] = 50  + (int) (Math.random() * 75); // creation delay
				waweInfo.add(tempMas);
			}
		} else if(waweNumber < 25) {
			for(int i = 0; i < 2 + number; i++) {
				int[] tempMas = new int[11];
				tempMas[0] = (int) (Math.random() * 4); //type unit
				tempMas[1] = 7 + (int) (Math.random() * (number * 1)); // count
				tempMas[3] = 1 + (int) (Math.random() * 10); //speed
				if(tempMas[3] < 5) {
					tempMas[4] = 100 + (int) (Math.random() * number * 10); //hp
				} else if(tempMas[3] < 7) {
					tempMas[4] = 50 + (int) (Math.random() * number * 7); //hp
				} else {
					tempMas[4] = 1 + (int) (Math.random() * number * 3); //hp
				}
				tempMas[5] = 1 + (int) (Math.random() * number * 100); //delay
				tempMas[8] = (int) (Math.random() * 3); //distance & orientation wave
				tempMas[6] = deathModeX[tempMas[8]]; //startX
				tempMas[7] = deathModeY[tempMas[8]]; //startY			
				tempMas[9] = 1; // bounty
				tempMas[10] = 1; // base damage
				tempMas[2] = 50  + (int) (Math.random() * 75); // creation delay
				waweInfo.add(tempMas);
			}
		} else if(waweNumber < 50) {			
			for(int i = 0; i < 2 + number; i++) {
				int[] tempMas = new int[11];
				tempMas[0] = (int) (Math.random() * 4); //type unit
				tempMas[1] = 1 + (int) (Math.random() * (number * 2)); // count
				tempMas[3] = 1 + (int) (Math.random() * 9); //speed
				if(tempMas[3] < 5) {
					tempMas[4] = 250 + (int) (Math.random() * number * 8); //hp
				} else if(tempMas[3] < 7) {
					tempMas[4] = 100 + (int) (Math.random() * number * 5); //hp
				} else {
					tempMas[4] = 50 + (int) (Math.random() * number * 2); //hp
				}
				tempMas[5] = 1 + (int) (Math.random() * number * 100); //delay
				tempMas[8] = (int) (Math.random() * 3); //distance & orientation wave
				tempMas[6] = deathModeX[tempMas[8]]; //startX
				tempMas[7] = deathModeY[tempMas[8]]; //startY			
				tempMas[9] = 1; // bounty
				tempMas[10] = 1; // base damage
				tempMas[2] = 50  + (int) (Math.random() * 75); // creation delay
				waweInfo.add(tempMas);
			}
		} else if(waweNumber < 100) {			
			for(int i = 0; i < 2 + number; i++) {
				int[] tempMas = new int[11];
				tempMas[0] = (int) (Math.random() * 4); //type unit
				tempMas[1] = 1 + (int) (Math.random() * (number * 2.5)); // count
				tempMas[3] = 3 + (int) (Math.random() * 7); //speed
				if(tempMas[3] < 5) {
					tempMas[4] = 500 + (int) (Math.random() * number * 10); //hp
				} else if(tempMas[3] < 7) {
					tempMas[4] = 250 + (int) (Math.random() * number * 7); //hp
				} else {
					tempMas[4] = 100 + (int) (Math.random() * number * 4); //hp
				}
				tempMas[5] = 1 + (int) (Math.random() * number * 100); //delay
				tempMas[8] = (int) (Math.random() * 3); //distance & orientation wave
				tempMas[6] = deathModeX[tempMas[8]]; //startX
				tempMas[7] = deathModeY[tempMas[8]]; //startY			
				tempMas[9] = 1; // bounty
				tempMas[10] = 1; // base damage
				tempMas[2] = 50  + (int) (Math.random() * 75); // creation delay
				waweInfo.add(tempMas);
			}
		} else {
			for(int i = 0; i < 2 + number; i++) {
				int[] tempMas = new int[11];
				tempMas[0] = (int) (Math.random() * 4); //type unit
				tempMas[1] = 1 + (int) (Math.random() * (number * 2)); // count
				tempMas[3] = 5 + (int) (Math.random() * 6); //speed
				if(tempMas[3] < 6) {
					tempMas[4] = 1500 + (int) (Math.random() * number * 16); //hp
				} else if(tempMas[3] < 8) {
					tempMas[4] = 1000 + (int) (Math.random() * number * 8); //hp
				} else {
					tempMas[4] = 500 + (int) (Math.random() * number * 4); //hp
				}
				tempMas[5] = 1 + (int) (Math.random() * number * 100); //delay
				tempMas[8] = (int) (Math.random() * 3); //distance & orientation wave
				tempMas[6] = deathModeX[tempMas[8]]; //startX
				tempMas[7] = deathModeY[tempMas[8]]; //startY			
				tempMas[9] = 1; // bounty
				tempMas[10] = 1; // base damage
				tempMas[2] = 50  + (int) (Math.random() * 75); // creation delay
				waweInfo.add(tempMas);
			}
		}		
		wawes.add(waweInfo);*/
		
	}
	
	public boolean waweStart(int round) {
		if(deathmatchMode) {
			waweNumber++;
			return true;
		}
		if(waweNumber + 1 < retention.size()) {
			if(retention.get(waweNumber + 1) == round) {
				waweNumber++;
				return true;
			}
		}
		return false;
	}
	
	public void addWawe(int delay, ArrayList<int[]> waweInfo) {
		retention.add(delay);
		wawes.add(waweInfo);
	}
	
	public ArrayList<int[]> getWawe() {
		if(deathmatchMode) {
			generateNextWawe(waweNumber);
		}
		return wawes.get(waweNumber);
	}
	
	public boolean getMode() {
		return deathmatchMode;
	}
	
	public int getWaweNumber() {
		return waweNumber;
	}
	
	public int getWaveCount() {
		return wawes.size();
	}
	
}
