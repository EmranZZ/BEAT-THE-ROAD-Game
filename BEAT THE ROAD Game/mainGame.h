
// Scene number 2 ~ Main game scene - 1

#define maxEnemy 20
#define ENEMY_CAR_DY_FPS 50

int initialFrame = 0;
int heroPositionX = 520, heroPositionY = 50, CarFaceNow = -1;
int heroMovedx = 30, heroMovedy = 20;
int enemyWidth = 65, enemyHight = 120;
int enemyXpos, enemyYpos;
int lastEnemyCar = 0;
int upperX, upperY;

char runways[18][30] =  {   "image\\mainGame\\runway\\1.bmp",
							"image\\mainGame\\runway\\2.bmp",
							"image\\mainGame\\runway\\3.bmp",
							"image\\mainGame\\runway\\4.bmp",
							"image\\mainGame\\runway\\5.bmp",
							"image\\mainGame\\runway\\6.bmp",
							"image\\mainGame\\runway\\7.bmp",
							"image\\mainGame\\runway\\8.bmp",
							"image\\mainGame\\runway\\9.bmp",
							"image\\mainGame\\runway\\10.bmp",
							"image\\mainGame\\runway\\11.bmp",
							"image\\mainGame\\runway\\12.bmp",
							"image\\mainGame\\runway\\13.bmp",
							"image\\mainGame\\runway\\14.bmp",
							"image\\mainGame\\runway\\15.bmp",
							"image\\mainGame\\runway\\16.bmp",
							"image\\mainGame\\runway\\17.bmp",
							"image\\mainGame\\runway\\18.bmp" };


char bike[7][40] = {    "image\\mainGame\\HeroCar\\1.bmp", 
						"image\\mainGame\\HeroCar\\2.bmp",
						"image\\mainGame\\HeroCar\\3.bmp",
						"image\\mainGame\\HeroCar\\4.bmp",
						"image\\mainGame\\HeroCar\\5.bmp",
						"image\\mainGame\\HeroCar\\6.bmp",
						"image\\mainGame\\HeroCar\\7.bmp" };


char enemyCarImages[7][40] = {    "image\\mainGame\\enemy\\1.bmp", 
							      "image\\mainGame\\enemy\\2.bmp", 
							      "image\\mainGame\\enemy\\3.bmp", 
							      "image\\mainGame\\enemy\\4.bmp", 
							      "image\\mainGame\\enemy\\5.bmp", 
							      "image\\mainGame\\enemy\\6.bmp", 
							      "image\\mainGame\\enemy\\7.bmp"};


struct enemyCars{
	char image[40];
	int posX = 100, posY = 850;
	bool isShow = false;
}

enemyCars[maxEnemy];


void initiateEnemy(){

	for (int i = 0; i < maxEnemy; i++){

		strcpy_s(enemyCars[i].image, enemyCarImages[i % 7]);
		enemyCars[i].posX = 100;
		enemyCars[i].posY = 850;
		enemyCars[i].isShow = false;
	}
}

void addNewEnemyCar(){

	for (int i = 0; i < maxEnemy; i++){

		if (enemyCars[i].isShow == false){

			enemyCars[i].isShow = true;
			enemyCars[i].posX = rand() % (1029 - 212) + 212;
			enemyCars[i].posY = 850;
			break;
		}
	}
}

void renderEnemy(){

	for (int i = 0; i < maxEnemy; i++){

		if (enemyCars[i].isShow == true){
			iShowBMP2(enemyCars[i].posX, enemyCars[i].posY, enemyCars[i].image, 255);
		}
	}
}

void renderBg(){

	int curFrame = initialFrame;

	for (int yCordinate = 750; yCordinate >= 0; yCordinate -= 50){

		iShowBMP(0, yCordinate, runways[curFrame]);
		curFrame--;
		if (curFrame == -1) curFrame = 17;
	}

}

void renderMainBike(){

	CarFaceNow++;
	CarFaceNow %= 7;
	iShowBMP2(heroPositionX, heroPositionY, bike[CarFaceNow], 255);
}

void moveMainHero(int dx, int dy){

	heroPositionX += dx;
	heroPositionY += dy;

	if (heroPositionX <= 212) heroPositionX = 212;
	if (heroPositionX >= 1029) heroPositionX = 1029;
	if (heroPositionY <= 20) heroPositionY = 20;
	if (heroPositionY >= 670) heroPositionY = 670;
}

void showScore(string givenScore){

	int sz = givenScore.size();
	char score_string[50];

	for (int i = 0; i < sz; i++){
		score_string[i] = givenScore[i];
	}

	score_string[sz] = '\0';

	iSetColor(234,189,194);
	iFilledRectangle(20, 740, 100, 50);

	iSetColor(150, 90 , 180);
	iText(25, 772, "Score :", GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(0, 0, 0);
	iText(50, 750, score_string, GLUT_BITMAP_TIMES_ROMAN_24);
}

bool isInside(int x, int y, int X, int Y, int p, int q){

	if (x <= p && X >= p){
		if (y <= q && Y >= q){
			return true;
		}
	}

	return false;	
}

bool checkCollision(){

	for (int i = 0; i < maxEnemy; i++){

		if (enemyCars[i].isShow == true){

			upperX = enemyCars[i].posX + enemyWidth - 5; // enemy upper position X = X
			upperY = enemyCars[i].posY + enemyHight; // enemy upper position Y = Y
			enemyXpos = enemyCars[i].posX + 5; // enemy lower position X = x
			enemyYpos = enemyCars[i].posY; // enemy lower position Y = y

			if (isInside(enemyXpos, enemyYpos, upperX, upperY, heroPositionX, heroPositionY)){
				return true;
			}

			else if (isInside(enemyXpos, enemyYpos, upperX, upperY, heroPositionX + 65, heroPositionY + 120)){
				return true;
			}

			else if (isInside(enemyXpos, enemyYpos, upperX, upperY, heroPositionX + 65, heroPositionY)){
				return true;
			}

			else if (isInside(enemyXpos, enemyYpos, upperX, upperY, heroPositionX, heroPositionY + 120)){
				return true;
			}

			else if (isInside(enemyXpos, enemyYpos, upperX, upperY, heroPositionX + 32, heroPositionY + 60)){
				return true;
			}
		}
	}

	return false;
}

