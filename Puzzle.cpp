#define WINDOWS 1
#include <iostream>
#include <iomanip>

//global variable
using namespace std;
const int boardsize = 5;
int PMin = 0, PMax = 5;
int PuzzleNum = 15; 
static bool initialize;
bool PuzzlePlaceable;

void pause()
{
	#ifdef WINDOWS
		system("pause");
	#else
		cout << "Press Enter to continue..." << endl;
		system("read");
	#endif
}

void clrscr()
{
	#ifdef WINDOWS
		system("cls");
	#else
		system("clear");
	#endif
}

void initialization() {
	cin.clear();
	cin.ignore(255, '\n');
};
void GameStart();
void Menu();
void Setting();
void NumOfPuzzle();
void RangeOfRandomNum();
void useful();
void difficulty();
void rules();
void guideline();


class puzzle
{
public:
	char mid;
	int top, left, right, bottom, Puzzlex, Puzzley, temp1;
	int numofrotate;
	bool placed;

	void print() {
		cout << ' ' << top << ' ' << endl
			<< left << mid << right << endl
			<< ' ' << bottom << ' ' << endl;
	}

	void Rotation(bool clockwise) {

		for (int i = 0; i < numofrotate; i++) {
			if (clockwise) {
				temp1 = top;
				top = left;
				left = bottom;
				bottom = right;
				right = temp1;

			}
			else {
				temp1 = top;
				top = right;
				right = bottom;
				bottom = left;
				left = temp1;
			}
		}
	}
};


class board {
public:

	puzzle * PuzzlePiece;
	puzzle puzzleplaced[boardsize][boardsize];
	puzzle solution[boardsize][boardsize];

	void GenPuzzle() {
		PuzzlePiece = new puzzle[PuzzleNum];
		char tem = 'A';
		for (int i = 0; i < PuzzleNum; i++) {
			PuzzlePiece[i].top = rand() % (PMax - PMin + 1) + PMin;
			PuzzlePiece[i].left = rand() % (PMax - PMin + 1) + PMin;
			PuzzlePiece[i].right = rand() % (PMax - PMin + 1) + PMin;
			PuzzlePiece[i].bottom = rand() % (PMax - PMin + 1) + PMin;
			PuzzlePiece[i].Puzzlex = 0;
			PuzzlePiece[i].Puzzley = 0;
			if (tem == 'Q') tem++;//skip genarate Q
			PuzzlePiece[i].mid = tem;
			tem++;
			PuzzlePiece[i].placed = false;
		}
	}

	void gameboard() {
		if (!initialize) {
			initialize = true;
			for (int i = 0; i < boardsize; i++) {
				for (int j = 0; j < boardsize; j++) {
					puzzleplaced[i][j].mid = '0';
				}
			}
		}

		cout << "    A  B  C  D  E  \n";

		cout << "  +";
		for (int i = 0; i < boardsize * 3; i++) {
			cout << "-";
		}
		cout << "+\n";

		for (int i = 0; i < boardsize; i++) {

			//First row of 3x3
			cout << "  |";
			for (int j = 0; j < boardsize; j++) {
				cout << " ";
				if (puzzleplaced[i][j].mid != '0')
					cout << puzzleplaced[i][j].top;
				else cout << " ";
				cout << " ";
			}
			cout << "|";
			cout << endl;

			//Second row of 3x3
			cout << " " << i + 1 << "|";
			for (int j = 0; j < boardsize; j++) {
				if (puzzleplaced[i][j].mid != '0') {//if the puzzle not_placed print the left,mid and right
					cout << puzzleplaced[i][j].left << puzzleplaced[i][j].mid << puzzleplaced[i][j].right;
				}
				else cout << "   ";//else print 3 spaces

			}
			cout << "|";
			cout << endl;

			//Third row of 3x3
			cout << "  |";
			for (int j = 0; j < boardsize; j++) {
				cout << " ";
				if (puzzleplaced[i][j].mid != '0')
					cout << puzzleplaced[i][j].bottom;
				else cout << " ";
				cout << " ";
			}
			cout << "|";
			cout << endl;

		}
		cout << "  +";
		for (int i = 0; i < boardsize * 3; i++) {
			cout << "-";
		}
		cout << "+" << endl;
	}

	
	void GenSample() {
		int counter = 0;
		int row = 0;

		for (int i = 0; i < boardsize; i++) {
			for (int j = 0; j < boardsize; j++) {
				if (counter < PuzzleNum) {
					solution[i][j] = PuzzlePiece[counter];//1d --> 2d
					row = i;
					counter++;
				}
				else solution[i][j].mid = '0';
			}
		}

		//Generate the sample solution
		for (int i = 1; i <= row + 1; i++) {
			for (int j = 0; j <= boardsize; j++) {
				solution[i][j].top = solution[i - 1][j].bottom;//forcing top = bottom
				for (int n = 0; n < PuzzleNum; n++) {
					if (solution[i][j].mid == PuzzlePiece[n].mid) {
						PuzzlePiece[n].top = solution[i - 1][j].bottom;
					}
				}
			}
		}

		for (int i = 0; i <= row; i++) {
			for (int j = 1; j <= boardsize; j++) {
				solution[i][j].left = solution[i][j - 1].right;//forcing left = right
				for (int n = 0; n < PuzzleNum; n++) {
					if (solution[i][j].mid == PuzzlePiece[n].mid) {
						PuzzlePiece[n].left = solution[i][j - 1].right;
					}
				}
			}
		}
	}
	
	void showsolution() {
		cout << setfill(' ') << setw(20) << "Sample Solution!\n";
		cout << "---------------------\n";
		cout << "    A  B  C  D  E  \n";
		cout << "  +---------------+\n";

		for (int i = 0; i < boardsize; i++) {
			cout << "  |";
			//first row
			for (int j = 0; j < boardsize; j++) {
				if (j == 0)
					cout << " ";
				else cout << "  ";
				if (solution[i][j].mid != '0')
					cout << solution[i][j].top;
				else cout << " ";
			}
			cout << " |\n";
			//second row
			cout << " " << i + 1 << "|";
			for (int j = 0; j < boardsize; j++) {
				if (solution[i][j].mid != '0') {
					cout << solution[i][j].left << solution[i][j].mid << solution[i][j].right;
				}
				else cout << "   ";
			}
			cout << "|\n";
			//third row
			cout << "  |";
			for (int j = 0; j < boardsize; j++) {
				cout << " ";
				if (solution[i][j].mid != '0')
					cout << solution[i][j].bottom;
				else cout << " ";
				cout << " ";
			}

			cout << "|\n";
		}

		cout << "  +---------------+" << endl;
	}


	void printnotshow() { //print the puzzle not in the gameboard 
		
		cout << "\nPuzzle not-yet-placed:\n\n";
		for (int i = 0; i < 1; i++) {
			for (int j = 0; j < PuzzleNum; j++) {
				cout << " ";
				if (PuzzlePiece[j].placed == false && PuzzlePiece[j].mid != '0')
					cout << PuzzlePiece[j].top << " ";
				else cout << "  ";
				cout << " ";
			}
			cout << "\n";

			for (int j = 0; j < PuzzleNum; j++) {
				if (PuzzlePiece[j].placed == false && PuzzlePiece[j].mid != '0')
					cout << PuzzlePiece[j].left << PuzzlePiece[j].mid << PuzzlePiece[j].right << " ";
				else cout << "    ";

			}
			cout << "\n";


			for (int j = 0; j < PuzzleNum; j++) {
				cout << " ";
				if (PuzzlePiece[j].placed == false && PuzzlePiece[j].mid != '0') cout << PuzzlePiece[j].bottom << " ";
				else cout << "  ";
				cout << " ";
			}cout << "\n";

		}


	}




	void checkAns(int i) {
		PuzzlePlaceable = false;  // initialize
		
		/* 
		Ans Rules

						x increases to the right
					+-------------------------------------------+>>
					|	 1						1   1			|
			y		|	4A2					   4C2 2D4			|
		increases	|	 3 <-- same				3 ^	3			|
		downwards	|	 3 <-- number             |				|
					|	2B4					same number			|
					v	 1										|
					+-------------------------------------------+

		cases :
			the top of the puzzle placing below a existing puzzle must have the same number as the existing's bottomtum number :
				puzzleplaced[y][x].top == puzzleplaced[y - 1][x].bottom

			the bottomtom of the puzzle placing above a existing puzzle must have the same number as the existing's top number:
				puzzleplaced[y][x].bottom == puzzleplaced[y + 1][x].top

			the right of the puzzle placing on the left side of a existing puzzle must have the same number as the existing's left number :
				puzzleplaced[y][x].right == puzzleplaced[y][x + 1].left

			the left of the puzzle placing on the right side of a existing puzzle must have the same number as the existing's right number :
				puzzleplaced[y][x].left == puzzleplaced[y][x - 1].right
		*/
		

		if (PuzzlePiece[i].Puzzlex == 0) {	// check its x axis, if 0, it is on "A"
			PuzzlePlaceable = true;
			cout << "Your puzzle will be placed on A.\n";
		}
		else if (puzzleplaced[PuzzlePiece[i].Puzzley][PuzzlePiece[i].Puzzlex - 1].mid == '0') {	// check left side
			PuzzlePlaceable = true;
			cout << "Your puzzle's Left side doesn't have a puzzle.\n";
		}
		else if (puzzleplaced[PuzzlePiece[i].Puzzley][PuzzlePiece[i].Puzzlex].left == puzzleplaced[PuzzlePiece[i].Puzzley][PuzzlePiece[i].Puzzlex - 1].right) {
			PuzzlePlaceable = true;
			cout << "Your puzzle's Left value equals to the existing puzzle's Right value!\n";
		}
		else {
			PuzzlePlaceable = false;
			cout << "Your puzzle's Left value does not equal to the existing puzzle's Right value!\n";
			return;
		}

		if (PuzzlePiece[i].Puzzlex == 4) {	// if 4, it is on "E"
			PuzzlePlaceable = true;
			cout << "Your puzzle will be placed on E.\n";
		}
		else if (puzzleplaced[PuzzlePiece[i].Puzzley][PuzzlePiece[i].Puzzlex + 1].mid == '0') {	//check right side
			PuzzlePlaceable = true;
			cout << "Your puzzle's Right side doesn't have a puzzle.\n";
		}
		else if (puzzleplaced[PuzzlePiece[i].Puzzley][PuzzlePiece[i].Puzzlex].right == puzzleplaced[PuzzlePiece[i].Puzzley][PuzzlePiece[i].Puzzlex + 1].left) {
			PuzzlePlaceable = true;
			cout << "Your puzzle's Right value equals to the existing puzzle's Left value!\n";
		}
		else {
			PuzzlePlaceable = false;
			cout << "Your puzzle's Right value does not equal to the existing puzzle's Left value!\n";
			return;
		}

		if (PuzzlePiece[i].Puzzley == 0) {	// if 0, it is on "1"
			PuzzlePlaceable = true;
			cout << "Your puzzle will be placed on 1.\n";
		}
		else if (puzzleplaced[PuzzlePiece[i].Puzzley - 1][PuzzlePiece[i].Puzzlex].mid == '0') {	//check top
			PuzzlePlaceable = true;
			cout << "Your puzzle's Top side doesn't have a puzzle.\n";
		}
		else if (puzzleplaced[PuzzlePiece[i].Puzzley][PuzzlePiece[i].Puzzlex].top == puzzleplaced[PuzzlePiece[i].Puzzley - 1][PuzzlePiece[i].Puzzlex].bottom) {
			PuzzlePlaceable = true;
			cout << "Your puzzle's Top value equals to the existing puzzle's Bottum value!\n";
		}
		else {
			PuzzlePlaceable = false;
			cout << "Your puzzle's Top does not equal to the existing puzzle's Bottum value!\n";
			return;
		}

		if (PuzzlePiece[i].Puzzley == 4) { // if 4, it is on "5"
			PuzzlePlaceable = true;
			cout << "Your puzzle will be placed on 5.\n";
		}
		else if (puzzleplaced[PuzzlePiece[i].Puzzley + 1][PuzzlePiece[i].Puzzlex].mid == '0') {	//check bottom
			PuzzlePlaceable = true;
			cout << "Your puzzle's Bottum side doesn't have a puzzle.\n";
		}
		else if (puzzleplaced[PuzzlePiece[i].Puzzley][PuzzlePiece[i].Puzzlex].bottom == puzzleplaced[PuzzlePiece[i].Puzzley + 1][PuzzlePiece[i].Puzzlex].top) {
			PuzzlePlaceable = true;
			cout << "Your puzzle's Bottum value equals to the existing puzzle's Top value!\n";
		}
		else {
			PuzzlePlaceable = false;
			cout << "Your puzzle's Bottum value does not equal to the existing puzzle's Top value!\n";
			return;
		}
	}
};


int main()
{
	Menu();
	return 0;
}


void GameStart() {
	board game;
	char opt, x, y; // character for opt = option, x / y = user-input for x / y axis
	bool quit = false; // if the user quits = true, else = false
	int counter = PuzzleNum;
	game.GenPuzzle();
	game.GenSample();

	do {
		clrscr();
		game.gameboard();
		game.printnotshow();

		cout << "\nExample: Choosing puzzle with letter \"A\" input \"A\"!\n";
		cout << "Enter \"Q\" to Quit!\n";
		cout << "*If chosen puzzle already used-->Take back*\n";
		cout << "Enter which puzzle you want to choose: ";
		cin >> opt; 

		if (opt == 'Q' || opt == 'q') {//if opt = q or Q --> quit
			do {
				cout << "Quit? Y/N : ";
				cin >> opt;
				switch (opt) {
				case('Y'):
				case('y'):
					cout << setfill(' ')<< setw(20) << "\nYou lost!!!\n";
					quit = true; // user quits
					pause();
					clrscr();
					game.showsolution();
					initialize = false; // allows the gameboard to be initialized again
					pause();
					Menu();
					break;
				case('N'):
				case('n'):
					break;
				default:
					initialization();
					cout << "Wrong Input! Try again.\n";
				}
			} while (opt != 'Y' && opt != 'y' && opt != 'N' && opt != 'n'); // user must input 'Y'/'y'/'N'/'n'
		}
		else {
			for (int i = 0; i < PuzzleNum; i++) {
				if (game.PuzzlePiece[i].mid == opt) { // let the puzzle piece be the one user chosen
					if (game.PuzzlePiece[i].placed == false) { // if the puzzle have not yet been placed
						int num = 0;
						do {
							game.PuzzlePiece[i].print();
							cout << "\nRotate? (Y/N):";
							cin >> opt; // option for Rotation
							switch (opt) {
							case'Y':
							case'y':
								do {
									cout << "\nHow many times? (1 - 3): ";
									cin >> num;
									if (num < 1 || num > 3) {
										initialization(); // if invalid input -> clear cin
										cout << "Wrong input! Try again. \n";
									}
								} while (num < 1 || num > 3);

								game.PuzzlePiece[i].numofrotate = num; // sub into int 'numofrotate' in class puzzle

								do {
									cout << "Now rotating " << game.PuzzlePiece[i].numofrotate << " times\n";
									cout << "1: Clockwise | 2: Anticlockwise 3: Cancel : ";
									cin >> opt;
									switch (opt) {
									case'1': game.PuzzlePiece[i].Rotation(true); break; // rotation: true ->
									case'2': game.PuzzlePiece[i].Rotation(false); break;
									case'3': break;
									default:
										cout << "\nWrong input! Try again.\n";
										initialization();
										continue;
									}
								} while (opt != '1' && opt != '2' && opt != '3');

							case'N':break;
							case'n':break;
							default:
								initialization();
								cout << "\nWrong input! Try again.\n"; break;
							}
						} while (opt != 'n' && opt != 'N' && opt != 'Y' && opt != 'y' && opt != '3');

					input:	game.PuzzlePiece[i].print();
						cout << "\nExmaple: to place on A1 enter \"A 1\"\n";
						cout << "Where do you want to put it? :";
						cin >> x >> y;// where x is column, y is row, i.e. puzzle[y][x]
						if (isupper(x) == 0) x = (int)(x - 'a');// check if user input lowercase, then get x axis value
						else x = (int)(x - 'A');
						y = (int)(y - '1');// get y axis value
						if ((x < 0 || x > 4) || (y < 0 || y > 4)) {
							cout << "Wrong input! Try again.\n";
							initialization();
							pause();
							clrscr();
							game.gameboard();
							game.printnotshow();
							goto input;
						}
						else {
							game.PuzzlePiece[i].Puzzley = y;// sub y as puzzle's row value
							game.PuzzlePiece[i].Puzzlex = x;

							if (game.puzzleplaced[y][x].mid == '0') {// check if the place is taken
								game.puzzleplaced[game.PuzzlePiece[i].Puzzley][game.PuzzlePiece[i].Puzzlex] = game.PuzzlePiece[i]; // call the puzzle
								game.checkAns(i);	//initialize answer checking, where i is the puzzle[i]

								if (PuzzlePlaceable) {	//if PuzzlePlaceable = 1, it is placeable
									cout << "Puzzle Placed! \n";
									game.PuzzlePiece[i].placed = true;	// puzzle is placed
									counter--;
									pause();
									break;
								}
								else {	//not placeable
									cout << "The puzzle cannot be placed here! Try again.\n";
									game.puzzleplaced[game.PuzzlePiece[i].Puzzley][game.PuzzlePiece[i].Puzzlex].mid = '0';
									game.PuzzlePiece[i].placed = false;
									pause();
									break;
								}
							}
							else {
								cout << "Place taken! Try again.\n";
								pause();
								break;
							}
						}

					}
					else if (game.PuzzlePiece[i].placed == true) {//if sth found
						game.puzzleplaced[game.PuzzlePiece[i].Puzzley][game.PuzzlePiece[i].Puzzlex].mid = '0'; //if equal to what the player choose, take away
						game.PuzzlePiece[i].placed = false;
						cout << "Took back selected puzzle!\n";
						counter++;
						pause();
						break;
					}
				}
			}
		}
	} while (counter != 0 && quit == false);

	for (int i = 0; i < boardsize; i++) {
		if (game.PuzzlePiece[i].placed == false) game.gameboard();
		else {
			game.gameboard();
			cout << "You won!\n";
			pause();
			initialize = false;
			break;
		}
	}
}

void Menu() {

	char quit = 'n';

	do {
		clrscr();
		int opt; // move to private
		int chance;
		srand(time(NULL));
		chance = rand() % 100;

		if (chance < 25) cout << "I want to play a Game...\n\n";
		else cout << "Welcome to the Game!!!\n\n";
		cout << "*** Main Menu ***\n";
		cout << "[1] Start Game\n";
		cout << "[2] Settings\n";
		cout << "[3] Useful feature(s) added\n";
		cout << "[4] Credits\n";
		cout << "[5] Exit\n";
		cout << "*****************\n";
		cout << "Option(1 - 5): ";
		cin >> opt;

		switch (opt) {
		case 1:
			GameStart();
			break;

		case 2:
			Setting();
			break;

		case 3:
			useful();
			break;

		case 4://Credits
			clrscr();
			cout << right << setfill(' ') << setw(15) << "Group 6" << endl; 
			cout << setfill('-') << setw(30) << ' ' << endl;  
			cout << left << setfill(' ') << setw(15) << "Ho Kwun Kan" << "21020294A\n";
			cout << left << setfill(' ') << setw(15) << "Lee Kin Long" << "21119085A\n";
			cout << left << setfill(' ') << setw(15) << "Leung Pak Ho" << "21109381A\n";
			cout << left << setfill(' ') << setw(15) << "Ng Tsz To" << "21112810A\n";
			cout << left << setfill(' ') << setw(15) << "So Yat Hei" << "21094375A\n";
			pause();
			Menu();
			break;

		case 5://Exits
			cout << "Are you sure you want to exit? (Y/N): ";
			cin >> quit;

			switch (quit) {
			case 'n': break;
			case 'N': break;
			case 'y':
			case 'Y':
				cout << "\n***See you next time!!!***\n";
				exit(1);
				break;
			default:
				initialization();
				cout << "\nWrong Input!!!\n\n";
				pause();
				break;
			}

			break;
		default:
			initialization();
			cout << "\nWrong Input!!!\n\n";
			pause();
			break;
		}
	} while (quit == 'y' || 'Y');
}

void NumOfPuzzle() {
	int temp = PuzzleNum;

	clrscr();
	initialization();

	cout << "Current Number: " << PuzzleNum << "\n";
	cout << "Enter the new number: ";
	cin >> temp;

	if (temp < 1 || temp > 25) { //if wrong input --> call itself again
		cout << "Invalid input! Number must be within 1 to 25.\n";
		pause();
		NumOfPuzzle();
	}

	PuzzleNum = temp;

	cout << "Current Number: " << PuzzleNum << "\n";
	pause();
	Setting();//back to setting
}

void RangeOfRandomNum() {
	int temp1 = PMin;
	int temp2 = PMax;

	clrscr();
	initialization();

	cout << "Current range of random numbers: " << PMin << " - " << PMax << endl;
	cout << "Example: change to 0 - 9 by entering \"0 9\"\n";
	cout << "Enter a new range of random numbers(0-9): ";
	cin >> temp1;
	cin >> temp2;

	//check whether the numbers is in the range first
	if (temp1 < 0 || temp1 > 9) { //if wrong input --> call itself again
		cout << "Invalid input! Number must be within 0 to 9.\n";
		pause();
		RangeOfRandomNum();
	}
	else if (temp2 < 0 || temp2 > 9) {//if wrong input --> call itself again
		cout << "Invalid input! Number must be within 0 to 9.\n";
		pause();
		RangeOfRandomNum();
	}

	if (temp1 >= temp2) { //if wrong range --> call itself again
		cout << "\nWrong range of random numbers. Try again. \n\n";
		pause();
		RangeOfRandomNum();
	}

	PMin = temp1;
	PMax = temp2;

	cout << "\nRange of random numbers changed to: " << PMin << " - " << PMax << endl;
	pause();
	Setting();//back to setting
}

void Setting() {
	clrscr();
	int opt; // <-- private variable

	initialization();

	cout << "*** Settings Menu ***\n";
	cout << "[1] Number of puzzle pieces\n";
	cout << "[2] Range of random numbers\n";
	cout << "[3] Return to Main Menu\n";
	cout << "*********************\n";
	cout << "Option(1 - 3): ";
	cin >> opt;
	switch (opt) {
	case(1): NumOfPuzzle(); break;
	case(2): RangeOfRandomNum(); break;
	case(3): Menu(); break;
	default: //wrong input, call itself again
		initialization();
		cout << "\nWrong Input!!!\n";
		pause();
		Setting();
		break;
	}
}

void useful() {
	clrscr();
	int opt;// <-- private variable

	cout << "*** Useful feature(s) added ***\n";
	cout << "[1] Guideline\n";
	cout << "[2] Rules\n";
	cout << "[3] Suggested difficulty\n";
	cout << "[4] Return to Main Menu\n";
	cout << "*******************************\n";
	cout << "Option(1 - 4): ";
	cin >> opt;
	switch (opt) {
	case 1:
		guideline();
		break;

	case 2:
		rules();
		break;

	case 3:
		difficulty();
		break;
	case 4:
		Menu();
		break;
	default: //wrong input, call itself again
		initialization();
		cout << "\nWrong Input!!!\n";
		pause();
		useful();
		break;
	}
}

void guideline() {
	clrscr();
	cout << right << setfill(' ') << setw(40) << "Game Guideline" << endl;
	cout << setfill('-') << setw(80) << ' ' << endl; 
	cout << "When the game starts, an empty game board is shown\n";
	cout << "A set of puzzle pieces for putting into the game board is displayed\n";
	cout << "Your goal is to place all puzzle pieces into the game board\n";
	cout << "When the puzzle is done, you win\n";
	cout << "Otherwise, you lose\n";
	pause();
	useful();

}

void rules() {
	clrscr();
	cout << right << setfill(' ') << setw(40) << "Rules" << endl; 
	cout << setfill('-') << setw(80) << ' ' << endl; 
	cout << "Every time you can either place a puzzle piece in or take one out of the game board. \n";
	cout << "You can choose any not-yet-placed puzzle piece and place it at any location in the game board\n";
	cout << "The touching sides of two puzzle must have the same number\n";
	cout << "You can take any placed puzzle piece out from the game board.\n";
	pause();
	useful();

}

void difficulty() {
	int opt;
	do {
		clrscr();
		cout << "*** Suggested difficulty ***\n";
		cout << "[1] Easy\n";
		cout << "[2] Normal\n";
		cout << "[3] Difficult\n";
		cout << "[4] Return to previous page\n";
		cout << "****************************\n";
		cout << "Option(1 - 3): ";
		cin >> opt;
		switch (opt) {
		case 1: {
			PuzzleNum = 15;
			PMin = 0;
			PMax = 3;
			cout << "It is easy now\n"; pause();
			break;
		}
		case 2: {
			PuzzleNum = 20;
			PMin = 0;
			PMax = 6;
			cout << "It is normal now\n"; pause();
			break;
		}
		case 3: {
			PuzzleNum = 25;
			PMin = 0;
			PMax = 9;
			cout << "It is difficult now\n"; pause();
			break;
		}
		case 4: {
			useful();
			break;
		}
		default:
			initialization();
			cout << "Wrong input! Try again.";
			pause();
			continue;
		}
	} while (opt != 1 && opt != 2 && opt != 3);
}
