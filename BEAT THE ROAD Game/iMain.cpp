#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include "iGraphics.h"
#include "mainMenu.h"
#include "Background.h"
#include "mainGame.h"

int NEW_CAR_ARRIVE_TIME = 10; 
int CYCLE_LENGTH = 120; // difficulity Level ~ Decreases Gradually 
int DIFFICULTY_LOWER_BOUND = 50; // Maximum Difficulity 
int screenWidth = 1300, ScreenHight = 800; // initially assign width and height of Frame 
int curScene = -1; // Ongoing Scene Number which will help to understand the Sce
int fps = 100; // Seed for iSetTimer functionz 
int newCarArrivalCounter = -1;  
int cycle = 0; // to calcualte the level of the game
int newScore = 0;
bool paused = false;
bool isMusic = true; // when isMusic==true, sound is ON; when isMusic==false, sound is OF


// resets all the values 
void resetAll(){

	initiateEnemy();
	heroPositionX = 520;
	heroPositionY = 50;
	lastEnemyCar = 0;
	CYCLE_LENGTH = 120;
	newCarArrivalCounter = -1;
	NEW_CAR_ARRIVE_TIME = 10;
	CarFaceNow = -1;
	cycle = 0;
	newScore = 0;
}

void iDraw()
{
	iClear();

	if (curScene == -1) loadingpage_load();

	else if (curScene == 0) showMainMenu();

	else if (curScene == 1) showStarter();

	else if (curScene == 2){

		renderBg();
		showScore(to_string(newScore));
		renderEnemy();
		renderMainBike();
	}

	else if (curScene == 3) showHighScore();

	else if (curScene == 4) showAbout();

	else if (curScene == 5) exitScene();

	else if (curScene == 6) showStarter2();

	else if (curScene == 8) enterPlayerNameScene();

	else if (curScene == 7) showCurrentScore(to_string(newScore), newScore);

	else {

		cout << curScene << endl;
		if(curScene != 2) curScene = 0;
	}
}

void iMouseMove(int mx, int my)
{
	
}

void iPassiveMouseMove(int mx, int my)
{
	
}

void iMouse(int button, int state, int mx, int my)
{
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (curScene == -1) {

			if(FirstCover) FirstCover = false;
			else secondCover = false;
			if (!FirstCover && !secondCover) curScene = 0;
		}

		else if (curScene == 0){
			curScene = getMainMenuInput(mx, my);
		}

		else if (curScene == 3){
			if (mx > 1050 && my < 105) curScene = 0;
		}

		else if (curScene == 4){
			if (mx < 231 && my > 20 && my < 105) curScene = 0;
		}

		else if (curScene == 5){
			exit(0);
		}

		else if (curScene == 1){
			curScene = 6;
		}

		else if (curScene == 6){
			curScene = 8;
		}

		else if (curScene == 8){
			if (playerNameSize > 0) curScene = 2;
		}

		else if (curScene == 7){

			if (mx > 975 && mx < 1262 && my > 40 && my < 120) {
				curScene = 0;
				resetAll();
			}
		}
	}
	
	
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		if (curScene == -1) {

			if (FirstCover) FirstCover = false;
			else secondCover = false;
		}
		
	}
}

void iKeyboard(unsigned char key)
{
	if (curScene == 8){
		// Here \b means backspace button in keyBoard
		if (key == '\b' && playerNameSize > 0){

			playerName[playerNameSize - 1] = '\0';
			playerNameSize--;
		}

		// \r is enter key
		else if (key == '\r'){
			if (playerNameSize > 0) curScene = 2;
		}
		else{

			playerName[playerNameSize] = key;
			playerNameSize++;
			playerName[playerNameSize] = '\0';
		}
	}

	// this is the implementation enter key
	else if (key == '\r') 
	{
		if (curScene == -1) {

			if (FirstCover) FirstCover = false;
			else secondCover = false;
			if (!FirstCover && !secondCover) curScene = 0;
		}

		else if (curScene == 5){
			exit(0);
		}

		else if (curScene == 1){
			curScene = 6;
		}

		else if (curScene == 6){
			curScene = 8;
		}

		else if (curScene == 8){
			curScene = 2;
		}

		else if (curScene == 7){
			curScene = 0;
			resetAll();
		}
	}

	else if (key == 'w'){

		if (curScene == 2 && !paused){
			moveMainHero(0, heroMovedy);
		}
	}

	else if (key == 'a' && !paused){
		if (curScene == 2){
			moveMainHero( -1 * heroMovedx, 0);
		}
	}

	else if (key == 's' && !paused){
		if (curScene == 2){
			moveMainHero(0, -1*heroMovedy);
		}
	}

	else if (key == 'd' && !paused){
		if (curScene == 2){
			moveMainHero(heroMovedx, 0);
		}
	}

	else if (key == 'p' || key == 'P'){
		if (curScene == 2){
			if (!paused){
				iPauseTimer(0);
				paused = true;
			}

			else {
				iResumeTimer(0);
				paused = false;
			}
		}
	}

	else if (key == 'm' || key == 'M'){
		if (isMusic){
			PlaySound(0,0,0);
			isMusic = false;
		}
		else {
			isMusic = true;
			PlaySound("music\\tokyo.wav", NULL, SND_LOOP | SND_ASYNC);
		}
	}
}

void iSpecialKeyboard(unsigned char key)
{

	
	if (key == GLUT_KEY_RIGHT )
	{
		if (curScene == 2 && !paused){
			moveMainHero(heroMovedx, 0);
		}
	}

	if (key == GLUT_KEY_LEFT)
	{
		if (curScene == 2 && !paused){
			moveMainHero(-1 * heroMovedx, 0);
		}
	}

	if (key == GLUT_KEY_UP)
	{
		if (curScene == 2 && !paused){
			moveMainHero(0, heroMovedy);
		}
	}
	if (key == GLUT_KEY_DOWN)
	{
		if (curScene == 2 && !paused){
			moveMainHero(0, -1 * heroMovedy);
		}
	}
}

void change(){

	if (curScene == 2){

		if (checkCollision()) {
			curScene = 7;
			saveScoreToFile(newScore);
		}

		else {

			initialFrame++;
			initialFrame %= 18;

			newScore++;
			
			newCarArrivalCounter++;
			newCarArrivalCounter %= NEW_CAR_ARRIVE_TIME;

			if (newCarArrivalCounter == 0) addNewEnemyCar();

			// enemy position update
			for (int i = 0; i < maxEnemy; i++){

				if (enemyCars[i].isShow == true) {
					enemyCars[i].posY -= ENEMY_CAR_DY_FPS;
					if (enemyCars[i].posY < 0) enemyCars[i].isShow = false;
				}
			}

			cycle++;

			if (cycle == CYCLE_LENGTH){

				cycle = 0;
				CYCLE_LENGTH -= 10;
				
				//  level 2
				if (CYCLE_LENGTH == DIFFICULTY_LOWER_BOUND * 2) {
					NEW_CAR_ARRIVE_TIME = 6;
				}

				// level 3
				if (CYCLE_LENGTH <= DIFFICULTY_LOWER_BOUND) {
					CYCLE_LENGTH += 10;
					NEW_CAR_ARRIVE_TIME = 3;
				}
			}
		}
	}
}

int main()
{
	initiateEnemy();
	playerNameSize = 0;
	playerName[playerNameSize] = '\0';
	iSetTimer(fps, change);
	PlaySound("music\\tokyo.wav", NULL, SND_LOOP | SND_ASYNC);
	iInitialize(screenWidth, ScreenHight, "RoadRushNostalgicaX");
	iStart();
	return 0;
}