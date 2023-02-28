/// scene number -1

using namespace std;

char coverPageImage[50] = "image\\cover\\cover.bmp";
char coverPageText[50] = "image\\cover\\coverText.bmp";
bool FirstCover = true, secondCover = true;

char playerName[1000];
char playerNameBackup[1000];
int playerNameSize = 0;

char enterNameBG[50] = "image\\mainGame\\namePage.bmp";

void loadingpage_load(){
	if (FirstCover) iShowBMP2(0, 0, coverPageImage, 0);
	else {
		iShowBMP2(0, 0, coverPageText, 0);
	}
}


char startingImage[50] = "image\\mainGame\\howToPlay.bmp";
char startingImage2[50] = "image\\mainGame\\howToPlay2.bmp";
char endingImage[50] = "image\\mainGame\\score.bmp";

void showStarter(){
	/// scene number 1
	iShowBMP(0, 0, startingImage);
}

void showStarter2(){
	/// scene number 6
	iShowBMP(0, 0, startingImage2); 
}



/// scene number 3

char highScoreBg[50] = "image\\highScore.bmp";

void showHighScore(){
	iShowBMP(0, 0, highScoreBg);
	ofstream file_make("highScore.txt", ios::app);
	file_make.close();
	ifstream myFile("highScore.txt");
	char highestScoreString[50], ScorerName[1000];
	int scorerNameIndex = 0;
	string temp = "";
	myFile >> highestScoreString;
	while (!myFile.eof()) {
		myFile >> temp;
		for (int i = 0; i < temp.size(); i++) ScorerName[scorerNameIndex++] = temp[i];
		temp = "";
		ScorerName[scorerNameIndex++] = ' ';
	}
	ScorerName[scorerNameIndex] = '\0';
	myFile.close();
	
	iSetColor(0, 0, 0);
	iText(320, 350, highestScoreString, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(300, 410, ScorerName, GLUT_BITMAP_TIMES_ROMAN_24);
}

/// scene number 4
char aboutImage[50] = "image\\about.bmp";

void showAbout(){
	iShowBMP(0, 0, aboutImage);
}


/// scene number 5

char endScene[50] = "image\\endScene.bmp";

void exitScene(){
	iShowBMP(0, 0, endScene);
}

// scene number 7
void showCurrentScore(string givenScore, int scoreToSave){
	int sz = givenScore.size();
	char score_string[50];

	for (int i = 0; i < sz; i++){
		score_string[i] = givenScore[i];
	}
	score_string[sz] = '\0';
	iShowBMP(0, 0, endingImage);
	iSetColor(255,0,0);
	iText(280,340, score_string, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(250, 380, playerNameBackup, GLUT_BITMAP_TIMES_ROMAN_24); 
	playerNameSize = 0;
	playerName[playerNameSize] = '\0';
}

void saveScoreToFile(int scoreToSave){
	ofstream file_make("highScore.txt", ios::app);
	file_make.close();
	ifstream myFileI("highScore.txt");
	int highestTillNow;
	myFileI >> highestTillNow;
	myFileI.close();
	if (highestTillNow < scoreToSave){
		ofstream myFileO("highScore.txt");
		myFileO << scoreToSave << '\n' << playerNameBackup;
		myFileO.close();
	}
}



// scene number = 8

void enterPlayerNameScene(){
	iShowBMP(0, 0, enterNameBG);
	// color of the text while entering player name
	iSetColor(255,255,255); 
	iText(120, 120, playerName, GLUT_BITMAP_TIMES_ROMAN_24);
	for (int i = 0; i < playerNameSize; i++) playerNameBackup[i] = playerName[i];
	playerNameBackup[playerNameSize] = '\0';
}