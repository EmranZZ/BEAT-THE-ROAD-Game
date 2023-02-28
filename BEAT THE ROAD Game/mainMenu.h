#include <iostream>

/// scene number = 0

using namespace std;

char playButton[50] = "image/menu/play.bmp";
char highScoreButton[50] = "image/menu/highScore.bmp";
char aboutButton[50] = "image/menu/about.bmp";
char exitButton[50] = "image/menu/exit.bmp";

void showMainMenu(){
	iShowBMP(0, 0, "image/menu/bg.bmp");
	iShowBMP2(900, 560, playButton, 0);
	iShowBMP2(900, 440, highScoreButton, 0);
	iShowBMP2(900, 320, aboutButton, 0);
	iShowBMP2(900, 200, exitButton, 0);
}

int getMainMenuInput(int mx,int my){

	if (mx > 900 && mx < 1200 && my < 680 && my > 200){

		// cheking which button is clicked 
		if (my > 560) return 1; // play
		else if (my > 440) return 3; // high score
		else if (my > 320) return 4; // about 
		else if (my > 200) return 5; // exit
	}
	return 0;
}