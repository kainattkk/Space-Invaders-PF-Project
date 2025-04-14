#include <iostream>
#include "help.h"
#include <cstdlib>
#include <fstream>
#include <ctime>
bool win = false; // see if u won or not
bool menu_check = false; //if you are checking the score in menu, only then will u have option to return to main page using "enter" key
using namespace std;
int  bottom_limit = 516;
int highscores[6] = { 0,0,0,0,0,0 };
bool endgame = false;
bool continued = false;
int aliens[50][2];
bool showAliens[50] = { true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,
					 true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true };
//bool check to display aliens
int lifess = 2; // lives ka index. goes from 2 to 0.ends at -1
int numaliens = 0; // number of aliens killed 
int score = 0;
int bul_x, bul_y; //coords of bullet
bool bullet = false;
int numofbul = 0; //makes sure there is one bullet at a time
int step_y = 0;
int step_circ = 25;
int level_x = 220, level_y = 130; //level box coordinates
bool kill = false; //bool check for killing aliens
int speed; //speed of the aliens
int lives[3][2];
int frequency; //frequency delay of the aliens
int freqval;
int box_x = 390, box_y = 495;
bool diff_check = true; //so difficulty menu is displayed only in case of new game
int speedval = 0; // another variable to save speed since the difficulty menu isn't displayed everytime
int pchoice = 1; //for pause menu
int delay_counter = 1; // i have used this to add manual delay in the program
bool displayLife[3] = { true, true, true }; //bool check to display lives
int bulletsshot = 0;

void drawCircle(int circ_x, int circ_y) //draws aliens
{
	// Draw the main body of the alien (circle)
	myEllipse(circ_x, circ_y, circ_x + 30, circ_y + 30, 255, 0, 0, 255, 0, 0);

	//// Draw the eyes (circles)
	/*myEllipse(circ_x + 10, circ_y + 10, circ_x + 12, circ_y + 12, 255, 255, 255);
	myEllipse(circ_x + 18, circ_y + 10, circ_x + 20, circ_y + 12, 255, 255, 255);*/

	//// Draw the mouth (rectangle)
	/*myRect(circ_x + 12, circ_y + 18, circ_x + 18, circ_y + 20, 0, 255, 0);*/
	//// Draw the left arm (rectangle)
	//myRect(circ_x - 3, circ_y + 5, circ_x + 2, circ_y + 15, 0, 255, 0);

	//// Draw the right arm (rectangle)
	//myRect(circ_x + 28, circ_y + 5, circ_x + 33, circ_y + 15, 0, 255, 0);
}
void savegame() //to save the game once the user commands to
{
	ofstream outaliens("aliens.txt");
	ofstream outlives("lives.txt");
	ofstream outship("spaceship.txt");
	ofstream outbullet("bullet.txt");
	ofstream outscore("score.txt");
	ofstream outbools("bools.txt");
	int index = 0;
	outaliens << numaliens << endl;
	outaliens << step_y << endl;
	outaliens << step_circ << endl;
	for (int j = 0; j < 50; j++) { //store the coordinates of the aliens

		outaliens << aliens[index][0] << endl;
		outaliens << aliens[index][1] << endl;
		++index;

	}
	for (int i = 0; i < 50; i++)
	{
		outaliens << showAliens[i] << endl; //bool states so only the alive aliens are loaded next time
	}
	outlives << lifess << endl;
	int life = 0;
	for (int i = 0; i < 3; ++i) { //store the coordinates of the lives
		outlives << lives[life][0] << endl;
		outlives << lives[life][1] << endl;
		outlives << displayLife[i] << endl; //bool check to display only when it hasn't been lost alr
		life++;
	}
	outship << box_x << endl; //store the coordinates of the ship
	outship << box_y << endl;
	outbullet << bul_x << endl; //store the coordinates of the bullet
	outbullet << bul_y << endl;
	outbullet << bulletsshot << endl;
	outscore << score << endl; //store the score
	outbools << diff_check << endl; //store the menu state
	outbools << speedval << endl;
	outbools << delay_counter << endl;
	outbools << pchoice << endl;
	outbools << freqval << endl;
}

void continuegame() //to load the saved game 
{
	ifstream inaliens("aliens.txt");
	ifstream inlives("lives.txt");
	ifstream inship("spaceship.txt");
	ifstream inbullet("bullet.txt");
	ifstream inscore("score.txt");
	ifstream inbools("bools.txt");
	if (!inaliens)
	{
		cout << "error in reading alien coordinates" << endl;
	}
	else {
		while (inaliens)
		{
			inaliens >> numaliens;
			inaliens >> step_y;
			inaliens >> step_circ;
			int index = 0;
			for (int i = 0; i < 50; i++) {

				inaliens >> aliens[index][0];
				inaliens >> aliens[index][1];


				++index;

			}
			for (int i = 0; i < 50; i++) //read the bool states
			{
				inaliens >> showAliens[i];
			}
		}
	}
	if (!inlives)
	{
		cout << "error in reading lives coordinates" << endl;
	}
	else {
		while (inlives) {
			inlives >> lifess;
			int life = 0;
			for (int i = 0; i < 3; ++i) { //reads the coordinates of the lives
				inlives >> lives[life][0];
				inlives >> lives[life][1];
				inlives >> displayLife[i];
				life++;
			}
		}
	}
	if (!inship)
	{
		cout << "error in reading spaceship coordinates" << endl;
	}
	else {
		while (inship)
		{
			inship >> box_x; //reads the coordinates of the ship
			inship >> box_y;
		}
	}
	if (!inbullet)
	{
		cout << "error in reading bullet coordinates" << endl;
	}
	else {
		while (inbullet)
		{
			inbullet >> bul_x; //reads the coordinates of the bullet
			inbullet >> bul_y;
			inbullet >> bulletsshot;
		}
	}
	if (!inscore)
	{
		cout << "error in reading bullet coordinates" << endl;
	}
	else {
		while (inscore)
		{
			inscore >> score; //reads the score
		}
	}
	if (!inbools)
	{
		cout << "error in reading bools" << endl;
	}
	else {
		while (inbools)
		{
			inbools >> diff_check;
			inbools >> speedval;
			inbools >> delay_counter;
			inbools >> pchoice;
			inbools >> freqval;
		}
	}
}

void input_highscore(int highscores[]) { //to input scores from a file
	ifstream ifile("scores.txt");
	int score; int count = 0;
	while (ifile >> score) {
		highscores[count] = score;
		count++;
	}
}

void highscores_display()
{
	myRect(100, 65, 760, 480, 0, 180, 150);
	if (menu_check == false)
		drawText(20, 2, 80, 0, 130, 220, "          your score is ", true, score);
	drawText(25, 10, 120, 0, 255, 210, "           highscores ");
	drawText(20, 10, 180, 0, 150, 150, "      1.", true, highscores[0]);
	drawText(20, 10, 230, 0, 150, 150, "      2.", true, highscores[1]);
	drawText(20, 10, 280, 0, 150, 150, "      3.", true, highscores[2]);
	drawText(20, 10, 330, 0, 150, 150, "      4.", true, highscores[3]);
	drawText(20, 10, 380, 0, 150, 150, "      5.", true, highscores[4]);
	if (menu_check == true)
		drawText(20, 10, 430, 0, 150, 150, "      press enter to return");
}

int alienBul_x, alienBul_y; // coordinates of alien bullet
bool alienBullet = false;
int whichKey = 0;
void high(int highscores[]) {
	//first i will make a txt file or open current file and read the first 5 scores.
	input_highscore(highscores);//first we input scores
	ofstream highout("scores.txt");
	int temp; // then we sort the scores
	for (int i = 0; i < 6; i++) {
		for (int j = 1; j < 6; j++) {
			if (highscores[j] > highscores[j - 1]) {
				temp = highscores[j];
				highscores[j] = highscores[j - 1];
				highscores[j - 1] = temp;
			}
		}
	}

	if (!highout) {
		cout << "error" << endl;
	}
	else {// now i will write the top 5 scores
		for (int i = 0; i < 5; i++) {
			highout << highscores[i] << '\n';
		}
	}
	highscores_display(); //now display
}
void removeBox(int box_x, int box_y)  //removes rectangles
{
	myRect(box_x, box_y, box_x + 40, box_y + 20, 0, 0, 0);
	myRect(box_x + 15, box_y - 5, box_x + 25, box_y + 5, 0, 0, 0);
	myRect(box_x + 15, box_y - 15, box_x + 25, box_y - 5, 0, 0, 0);
	myRect(box_x + 13, box_y - 10, box_x + 27, box_y - 5, 0, 0, 0);
	myRect(box_x + 11, box_y - 5, box_x + 29, box_y, 0, 0, 0);
	myRect(box_x - 10, box_y + 5, box_x + 50, box_y + 10, 0, 0, 0);
	myRect(box_x + 15, box_y + 20, box_x + 25, box_y + 25, 0, 0, 0, 0, 0, 0);
}
void removeCircle(int circ_x, int circ_y) //removes aliens
{
	myEllipse(circ_x, circ_y, circ_x + 30, circ_y + 30, 0, 0, 0);
	/*myEllipse(circ_x + 10, circ_y + 10, circ_x + 12, circ_y + 12, 0, 0, 0);
	myEllipse(circ_x + 18, circ_y + 10, circ_x + 20, circ_y + 12, 0, 0, 0);*/
	/*myRect(circ_x + 12, circ_y + 18, circ_x + 18, circ_y + 20, 0, 0, 0);*/
	//// Draw the left arm (rectangle)
	//myRect(circ_x - 3, circ_y + 5, circ_x + 2, circ_y + 15, 0, 0, 0);

	//// Draw the right arm (rectangle)
	//myRect(circ_x + 28, circ_y + 5, circ_x + 33, circ_y + 15, 0, 0, 0);
}

void drawBox(int box_x, int box_y)  //draws rectangles
{
	// Draw the main body of the spaceship
	myRect(box_x, box_y, box_x + 40, box_y + 20, 50, 50, 50, 200, 200, 200);

	// Draw the cockpit
	myRect(box_x + 15, box_y - 5, box_x + 25, box_y + 5, 0, 0, 0, 0, 0, 0);

	// Draw the pointy top using smaller rectangles
	myRect(box_x + 15, box_y - 15, box_x + 25, box_y - 5, 50, 50, 50, 200, 200, 200);
	myRect(box_x + 13, box_y - 10, box_x + 27, box_y - 5, 50, 50, 50, 200, 200, 200);
	myRect(box_x + 11, box_y - 5, box_x + 29, box_y, 50, 50, 50, 200, 200, 200);

	// Draw the wings
	myRect(box_x - 10, box_y + 5, box_x + 50, box_y + 10, 100, 100, 100, 200, 200, 200);

	// Draw the rocket flames
	myRect(box_x + 15, box_y + 20, box_x + 25, box_y + 25, 255, 69, 0, 255, 165, 0);


}
void drawbullet(int bul_x, int bul_y) //draws bullets
{
	myRect(bul_x, bul_y, bul_x + 3, bul_y + 15, 0, 150, 150, 0, 255, 175);
}
void removebullet(int bul_x, int bul_y) //removes bullets
{
	myRect(bul_x, bul_y, bul_x + 3, bul_y + 15, 0, 0, 0);
}
void drawpause(int menu_x, int menu_y) //draws the pause menu
{
	myRect(menu_x, menu_y, menu_x + 380, menu_y + 290, 80, 251, 122);
}
void removepause(int menu_x, int menu_y) //removes the pause menu
{
	myRect(menu_x, menu_y, menu_x + 380, menu_y + 290, 0, 0, 0);
}
void drawLife(int life_x, int life_y) //draws lives
{
	myEllipse(life_x - 10, life_y - 3, life_x + 10, life_y + 17, 255, 0, 255, 178, 120, 255);
	myEllipse(life_x + 10, life_y - 3, life_x + 30, life_y + 17, 255, 0, 255, 178, 120, 255);
	myRect(life_x - 10, life_y + 7, life_x + 30, life_y + 17, 255, 0, 255, 178, 120, 255);
	myRect(life_x - 7, life_y + 15, life_x + 27, life_y + 20, 255, 0, 255, 178, 120, 255);
	myRect(life_x - 5, life_y + 18, life_x + 25, life_y + 23, 255, 0, 255, 178, 120, 255);
	myRect(life_x - 2, life_y + 24, life_x + 22, life_y + 28, 255, 0, 255, 178, 120, 255);
	myRect(life_x + 2, life_y + 29, life_x + 18, life_y + 34, 255, 0, 255, 178, 120, 255);
	myRect(life_x + 7, life_y + 35, life_x + 13, life_y + 38, 255, 0, 255, 178, 120, 255);

}
void removeLife(int life_x, int life_y) //remove lives
{
	myEllipse(life_x - 10, life_y - 3, life_x + 10, life_y + 17, 0, 0, 0, 0, 0, 0);
	myEllipse(life_x + 10, life_y - 3, life_x + 30, life_y + 17, 0, 0, 0, 0, 0, 0);
	myRect(life_x - 10, life_y + 7, life_x + 30, life_y + 17, 0, 0, 0, 0, 0, 0);
	myRect(life_x - 7, life_y + 15, life_x + 27, life_y + 20, 0, 0, 0, 0, 0, 0);
	myRect(life_x - 5, life_y + 18, life_x + 25, life_y + 23, 0, 0, 0, 0, 0, 0);
	myRect(life_x - 2, life_y + 24, life_x + 22, life_y + 28, 0, 0, 0, 0, 0, 0);
	myRect(life_x + 2, life_y + 29, life_x + 18, life_y + 34, 0, 0, 0, 0, 0, 0);
	myRect(life_x + 7, life_y + 35, life_x + 13, life_y + 38, 0, 0, 0, 0, 0, 0);
}

void instructions() {
	myRect(100, 65, 760, 480, 0, 180, 150);
	drawText(25, 10, 110, 0, 255, 210, "           Instructions ");
	drawText(20, 10, 180, 0, 150, 150, "     Use Cursor keys to move the box");
	drawText(20, 10, 230, 0, 150, 150, "     use space to shoot the aliens");
	drawText(20, 10, 280, 0, 150, 150, "     use esc to pause the game");
	drawText(20, 10, 330, 0, 150, 150, "     loss of life, loss of 10 points");
	drawText(20, 10, 380, 0, 150, 150, "     use enter to return");
}
void difficulty() //sets difficulty level of the game
{
	int level; //for level of difficulty
	myRect(level_x, level_y, level_x + 380, level_y + 290, 240, 100, 100);
	drawText(25, 250, 160, 240, 150, 150, " Difficulty");
	drawText(20, 250, 230, 230, 80, 80, " for easy     1");
	drawText(20, 250, 295, 230, 50, 50, " for medium   2");
	drawText(20, 250, 365, 255, 0, 0, " for hard     3");
	//cin >> level;
	do {
		if (isKeyPressed(whichKey)) {
			if (whichKey == 9) { //easy mode
				frequency = 16;
				speed = 20;
			}
			else if (whichKey == 10) //medium mode
			{
				frequency = 10;
				speed = 10;
			}
			else if (whichKey == 11) //hard mode
			{
				frequency = 1;
				speed = 5;
			}
			myRect(level_x, level_y, level_x + 380, level_y + 290, 0, 0, 0);
		}
	} while (whichKey != 9 && whichKey != 10 && whichKey != 11);
}

void shoot(int& box_x, int& box_y) //a function for bullet
{
	int length = 20;
	kill = false;

	removebullet(box_x, box_y);
	box_y -= length; //updates the y coordinate of the bullet so it travels upwards
	//Sleep(20);
	// Check for collision with aliens
	for (int i = 0; i < 50; ++i) {
		if (box_x < aliens[i][0] + 50 &&
			box_x + 10 > aliens[i][0] && // Adjusted the condition here
			box_y < aliens[i][1] + 50 &&
			box_y + 50 > aliens[i][1]) {
			// Move the alien out of the visible area
			removeCircle(aliens[i][0], aliens[i][1]);
			//	aliens[i][0] = -1000;
			aliens[i][1] = -1000;
			if (showAliens[i] == true)
			{
				showAliens[i] = false;
				numaliens++;
				if (numaliens <= 15 && bulletsshot <= 15 && speedval == 20) {
					score += 50;
				}
				if (numaliens <= 15 && bulletsshot <= 15 && speedval == 10) {
					score += 60;
				}
				if (numaliens <= 15 && bulletsshot <= 15 && speedval == 5) {
					score += 70;
				}
				else if (numaliens <= 15 && bulletsshot > 15 && speedval == 20)
				{
					score += 40;
				}
				else if (numaliens <= 15 && bulletsshot > 15 && speedval == 10)
				{
					score += 50;
				}
				else if (numaliens <= 15 && bulletsshot > 15 && speedval == 5)
				{
					score += 60;
				}
				else if (numaliens <= 30 && bulletsshot <= 30 && speedval == 20)
				{
					score += 30;
				}
				else if (numaliens <= 30 && bulletsshot <= 30 && speedval == 10)
				{
					score += 40;
				}
				else if (numaliens <= 30 && bulletsshot <= 30 && speedval == 5)
				{
					score += 50;
				}
				else if (numaliens <= 30 && bulletsshot > 30 && speedval == 20)
				{
					score += 20;
				}
				else if (numaliens <= 30 && bulletsshot > 30 && speedval == 10)
				{
					score += 30;
				}
				else if (numaliens <= 30 && bulletsshot > 30 && speedval == 5)
				{
					score += 40;
				}
				else if (numaliens <= 50 && bulletsshot <= 50 && speedval == 20)
				{
					score += 10;
				}
				else if (numaliens <= 50 && bulletsshot <= 50 && speedval == 10)
				{
					score += 20;
				}
				else if (numaliens <= 50 && bulletsshot <= 50 && speedval == 5)
				{
					score += 30;
				}
				else if (numaliens <= 50 && bulletsshot > 50 && speedval == 20)
				{
					score += 5;
				}
				else if (numaliens <= 50 && bulletsshot > 50 && speedval == 10)
				{
					score += 10;
				}
				else if (numaliens <= 50 && bulletsshot > 50 && speedval == 5)
				{
					score += 15;
				}
				myRect(860, 340, 1010, 385, 0, 0, 0, 0, 0, 0);
				drawText(20, 870, 339, 178, 123, 255, " ", true, score);
				box_y = -100; // move bullet out of screen
				numofbul = 0; // so no more bullets are there
				break;
			}
		}
	}
	drawbullet(box_x, box_y);
}
void collision(int& box_x, int& box_y) //to move the spaceship back once it collides with any of the aliens and remove a life
{

	for (int i = 0; i < 50; ++i) {
		if (box_x < aliens[i][0] + 40 &&
			box_x + 70 > aliens[i][0] && // Adjusted the condition here
			box_y < aliens[i][1] + 50 &&
			box_y + 50 > aliens[i][1]) {
			removeBox(box_x, box_y);
			box_x = 390;
			box_y = 480;
			displayLife[lifess] == false;
			removeLife(lives[lifess][0], lives[lifess][1]); // remove a life
			lifess--;
			score -= 10;

			myRect(860, 340, 1010, 385, 0, 0, 0, 0, 0, 0);
			drawText(20, 870, 339, 178, 123, 255, " ", true, score);
		}
	}
}

// Function to draw alien bullet
void drawAlienBullet(int x, int y) {
	myRect(x, y, x + 3, y + 15, 255, 0, 0, 255, 0, 0);
}

// Function to remove alien bullet
void removeAlienBullet(int x, int y) {
	myRect(x, y, x + 3, y + 15, 0, 0, 0);
}

// Function to handle alien bullet movement and collision
void alienShoot(int& box_x, int& box_y) {
	int length = 10;
	removeAlienBullet(alienBul_x, alienBul_y);
	alienBul_y += length;

	// Check for collision with the player
	if (alienBul_x < box_x + 40 &&
		alienBul_x + 3 > box_x &&
		alienBul_y < box_y + 20 &&
		alienBul_y + 15 > box_y) {
		removeBox(box_x, box_y);
		box_x = 390; // put spaceship in middle
		box_y = 480;
		displayLife[lifess] = false;
		removeLife(lives[lifess][0], lives[lifess][1]); //remove life
		lifess--;
		score -= 10;

		myRect(860, 340, 1010, 385, 0, 0, 0, 0, 0, 0);
		drawText(20, 870, 339, 178, 123, 255, " ", true, score);


	}

	drawAlienBullet(alienBul_x, alienBul_y); //redraw

	if (alienBul_y + 5 > bottom_limit - 17) {
		removeAlienBullet(alienBul_x, alienBul_y);
		alienBullet = false;
	}
}
void alienRandomShoot() {
	int randomIndex = rand() % 50; //used a built in function of cstdlib. mod 50 has been used to ensure that answer is till 50 (since 50 aliens)
	if (aliens[randomIndex][1] > 0) {//if the alien is the one which is still on screen (not set to -1000 because it died)
		alienBul_x = aliens[randomIndex][0] + 15;
		alienBul_y = aliens[randomIndex][1] + 30;
		alienBullet = true;
	}
}

int main()
{
	high(highscores);
	int left_limit = 20, right_limit = 800, top_limit = 70; //main box coordinates

	int step_size = 15; //coordinates and step size of the spaceship
	char direction = ' ';
	bool move_circ = true; //bool check for the alien to allow movement
	int pausex = 220, pausey = 130; //pause box coordinates
	int life_x = 870, life_y = 180, life = 0; //coordinates for lives
	int ans;
	int whichKey = 0;
	myRect(100, 65, 760, 480, 150, 0, 255);
	drawText(24, 10, 110, 0, 180, 200, "     Welcome to space invaders");
	drawText(20, 10, 210, 0, 150, 150, "        to continue   press enter");
	drawText(20, 10, 260, 0, 150, 150, "        to start          press 1");
	drawText(20, 10, 310, 0, 150, 150, "        for instructions  press 2");
	drawText(20, 10, 360, 0, 150, 150, "        for highscores    press 3");
	drawText(20, 10, 410, 0, 150, 150, "        to exit           press 0");
	while (whichKey != 8 && whichKey != 9 && whichKey != 10) {
		if (isKeyPressed(whichKey)) {
			if (whichKey == 8) {
				system("CLS");
				myRect(100, 105, 760, 410, 255, 0, 0);
				drawText(23, 2, 220, 255, 0, 0, "            OKAY BYE BYE");
				Sleep(2000);
			}
			else if (whichKey == 10)
			{
				instructions();
				char a;
				cin >> a;
				isKeyPressed(whichKey);

			}
			else if (whichKey == 11)
			{
				menu_check = true;
				highscores_display();
				char a;
				cin >> a;
				isKeyPressed(whichKey);
			}
			else if (whichKey == 5)
			{
				//diff_check = false;
				continuegame();
				continued = true;
				whichKey = 9;
			}

			if (whichKey == 5)
			{
				myRect(100, 65, 760, 480, 0, 0, 0);
				myRect(100, 65, 760, 480, 150, 0, 255);
				drawText(24, 10, 110, 0, 180, 200, "     Welcome to space invaders");
				drawText(20, 10, 210, 0, 150, 150, "        to continue   press enter");
				drawText(20, 10, 260, 0, 150, 150, "        to start          press 1");
				drawText(20, 10, 310, 0, 150, 150, "        for instructions  press 2");
				drawText(20, 10, 360, 0, 150, 150, "        for highscores    press 3");
				drawText(20, 10, 410, 0, 150, 150, "        to exit           press 0");
				continue;
			}

			if (whichKey == 9) {
				whichKey = 0;
				myRect(100, 65, 760, 480, 0, 0, 0);

				if (continued == false) {
					int circ_x = 30, circ_y = 70; //coordinates and step size of the aliens
					int index = 0;
					for (int j = 0; j < 5; ++j) {
						for (int i = 0; i < 10; ++i) {
							aliens[index][0] = circ_x + i * 40;
							aliens[index][1] = circ_y + j * 35;
							++index;
						}
					}
				}

				if (diff_check == true)
				{
					difficulty();
					speedval = speed;
					freqval = frequency;
				}
				system("CLS"); // to clear before the first output
				Sleep(3); // to make sure theres a small delay and clear doesnt cause any bugs

				while (pchoice == 1) {
					drawText(20, 10, 10, 0, 255, 0, "            Space Invaders");

					// drawText function draws text on the screen with arguments size, x, y, r, g, b, text
					myRect(left_limit - 20, top_limit - 15, right_limit + 18, bottom_limit + 10, 150, 0, 255); // myRect function draws a rectangle with arguments x1, y1, x2, y2, r, g, b, r2, g2, b2
					//drawText(20, 10, 525, 0, 255, 0, "Use Cursor keys to move the box!");
					drawBox(box_x, box_y);

					// Modify the loop that draws the aliens to use the array
					for (int i = 0; i < 50; ++i) {

						drawCircle(aliens[i][0], aliens[i][1]);
					}

					myRect(850, 330, 1020, 395, 155, 255, 220);
					drawText(20, 870, 270, 155, 255, 220, "score");
					if (delay_counter == 1)
					{
						drawText(20, 870, 280, 155, 255, 220, "", true, score);
					}
					drawText(20, 830, 100, 155, 255, 220, "  lives");
					myRect(850, 160, 1020, 230, 155, 255, 220);

					//to make an array of the lives
					for (int i = 0; i < 3; ++i) {
						lives[life][0] = life_x + i * 50;
						lives[life][1] = life_y;
						life++;
					}
					for (int i = 0; i < 3; ++i) { //to display the lives
						if (displayLife[i] == true)
						{
							drawLife(lives[i][0], lives[i][1]);
						}
					}

					while (whichKey != 7) // 7 is the code for ESC key
					{
						if (numaliens == 50) { //meaning if all aliens are killed
							system("CLS"); // clear screen
							Sleep(5); //wait
							win = true; // means u won
							break;	//exit the loop
						}
						delay_counter++;
						if (isKeyPressed(whichKey)) // isKeyPressed function returns true if a key is pressed and whichKey tells that which key was pressed
						{
							switch (whichKey)
							{
							case 1:
								direction = 'L';
								break;
							case 2:
								direction = 'U';
								break;
							case 3:
								direction = 'R';
								break;
							case 4:
								direction = 'D';
								break;
							case 6:
								bullet = true;
								kill = false;
								if (numofbul == 0) //makes bullet only when the bullets already present are 0
								{
									bul_x = box_x + 20;
									bul_y = box_y - 15;
								}
								break;
							case 7:
								//whichKey = 0;
								drawpause(pausex, pausey); //draws the pause menu
								drawText(25, 250, 160, 255, 255, 0, "   Paused");
								drawText(22, 250, 220, 175, 175, 60, " to resume  1");
								drawText(22, 250, 270, 175, 175, 60, " to save    2");
								drawText(22, 250, 320, 175, 175, 60, " to quit    0");
								//cin >> pchoice;
								while (whichKey != 9 && whichKey != 10 && whichKey != 8) {
									if (isKeyPressed(whichKey)) {
										if (whichKey == 9) //resumes game
										{
											removepause(pausex, pausey);
											break;
										}
										else if (whichKey == 8) //quits game
										{
											removepause(pausex, pausey);
											myRect(70, 105, 760, 410, 255, 127, 80);
											drawText(23, 2, 210, 255, 0, 0, "              game over");
											drawText(23, 2, 270, 0, 130, 220, "          your score is ", true, score);
											highscores[5] = score; // store score as the 6th element
											high(highscores);
											//drawText(20, 870, 280, 155, 255, 220, "", true, score)
											endgame = true;
											Sleep(3000);

											break;
										}
										else if (whichKey == 10)
										{
											diff_check = false;
											savegame();
											endgame = true;
											break;
										}
									}
								}
								whichKey = 0;
								break;
							}
						}
						if (endgame == true)
							break;
						if (delay_counter % freqval == 0 && alienBullet == false) {//delay is extra to make bullet slower and it will only make a new bullet when there  is no other bullet
							alienRandomShoot();//set coords
						}
						if (alienBullet) {//if alien bullet = true
							alienShoot(box_x, box_y);
						}

						collision(box_x, box_y);
						Sleep(1); //  milliseconds

						switch (direction)
						{
						case 'L':
							// Left
							removeBox(box_x, box_y);
							if (box_x > left_limit)
								box_x -= step_size;
							drawBox(box_x, box_y);
							break;
						case 'U':
							// Up
							removeBox(box_x, box_y);
							if (box_y > top_limit + 15)
								box_y -= step_size;
							drawBox(box_x, box_y);
							break;
						case 'R':
							// Right
							removeBox(box_x, box_y);
							if (box_x + 45 < right_limit)
								box_x += step_size;
							drawBox(box_x, box_y);
							break;
						case 'D':
							// Down
							removeBox(box_x, box_y);
							if (box_y + 40 < bottom_limit)
								box_y += step_size;
							drawBox(box_x, box_y);
							break;
						}

						Sleep(10);
						if (bullet == true) //if true then shoots bullet
						{
							if (numofbul == 0) //makes sure there is one bullet at a time
							{
								bulletsshot++;
								if (bul_y > 100 && kill != true) //to set a y coordinate limit for the bullet only if it hasn't killed one yet
								{
									drawbullet(bul_x, bul_y);
									shoot(bul_x, bul_y);
									numofbul++;
								}
							}
							else  //in case bullet reaches the top of the box
							{
								numofbul = 0;
								removebullet(bul_x, bul_y);
							}
						}

						if (delay_counter % speedval == 0)
						{ // this is a manual delay for aliens. increase the value after mod to increase the delay. decrease it to decrease the delay

							for (int i = 0; i < 50; i++)
							{
								removeCircle(aliens[i][0], aliens[i][1]);
							}
							step_y = 0;
							if (aliens[0][0] + 110 > right_limit - 350)
							{//right corner
								step_circ *= -1;
								step_y += 25;
							}
							for (int i = 0; i < 50; ++i)
							{
								// Adjust the position based on the index

								aliens[i][0] = aliens[i][0] + step_circ;
								aliens[i][1] = aliens[i][1] + step_y;
								if (showAliens[i] == true)
								{
									drawCircle(aliens[i][0], aliens[i][1]);
								}

							}
							if (aliens[0][0] < left_limit + 30)
							{
								step_circ *= -1;
							}
						}

						if (aliens[0][1] > bottom_limit - 80 && aliens[0][1] < bottom_limit - 30) //to terminate the program once any alien reaches the bottom
						{
							break;
						}
						else if (aliens[10][1] > bottom_limit - 80 && aliens[10][1] < bottom_limit - 30)
						{
							break;
						}
						else if (aliens[20][1] > bottom_limit - 80 && aliens[20][1] < bottom_limit - 30)
						{
							break;
						}
						else if (aliens[30][1] > bottom_limit - 80 && aliens[30][1] < bottom_limit - 30)
						{
							break;
						}
						else if (aliens[40][1] > bottom_limit - 80 && aliens[40][1] < bottom_limit - 30)
						{
							break;
						}
						if (lifess == -1) { //when lives become 0
							break;
						}
					}
					system("cls"); //clear screen
					int sound = 0;
					while (whichKey != 7) // 7 is the code for esc key
					{
						if (sound != 3) { //beep sound

							Beep(700, 300);
							sound++;
						}
						if (win == false) { //check if won
							myRect(100, 105, 760, 410, 255, 0, 0);

							drawText(23, 2, 210, 255, 0, 0, "              game over");

							drawText(23, 2, 270, 0, 130, 220, "          your score is ", true, score);
							endgame = true;
							highscores[5] = score;
							menu_check = false;
							high(highscores);
							Sleep(5000);
							break;
						}
						else
						{
							myRect(100, 105, 760, 410, 173, 216, 230);
							drawText(23, 2, 210, 173, 216, 230, "             you win!!!!");
							drawText(23, 2, 270, 173, 216, 230, "          your score is ", true, score);
							endgame = true;
							highscores[5] = score;
							menu_check = false;
							high(highscores);
							Sleep(7000);
							break;
						}
					}
					if (endgame = true) {

						break;
					}
				}
			}
			return 0;
		}
	}
}
