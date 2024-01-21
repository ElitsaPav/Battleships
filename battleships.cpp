#include <iostream> 

using namespace std;

void fillBoard(char** board, int size) {

	for (int i = 0; i < size; i++) {
		board[i] = new char[size];
		for (int j = 0; j < size; j++) {
			board[i][j] = '.';
		}
	}

}

void freeBoard(char** board, int size) {
	for (int i = 0; i < size; i++)
		delete[] board[i];
	delete[] board;
}

void printBoard(char** board, const int SIZE) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			cout << ' ' << board[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	
}

void clear() { cout << "\x1B[2J\x1B[H"; }

//direction of placement and check for invalid input
void inputDirection(char& direction) {
	cin >> direction;
	while (direction != 'v' && direction != 'h') {
		cout << "Invalid direction. Try again" << endl;
		cin >> direction;
	}
}

//coordinates of the ship and check for invalid coordinates
void inputShotCoordinates(int& x, int& y, int size) {
	cin >> x >> y;
	while (x> size || y > size) {
		cout << "Invalid coordinates. Try again" << endl;
		cin >> x >> y;
	}
}

// input game mode (play with computer or two players)
void inputOption(int& gameOption) {
    cout << "Choose game mode (two players (1) / play with PC (2))" << endl;
	cin >> gameOption;
	while (gameOption < 1 || gameOption > 2) {
		cout << "Invalid option. Try again" << endl;
		cin >> gameOption;
	}
}

// check if coordinates are invalid
bool outOfBoardHorisontal(int y, int& lenOfShip,char direction, int size) {
	int counter = 0;                                                                                                                                                                                                                                          
	
	while (counter < lenOfShip) {
		if (y >= size) {
			return true;
		}
		y++;
		counter++;
	}
	return false;
}

bool outOfBoardVertical(int x, int& lenOfShip, char direction, int size) {
	int counter = 0;

	while (counter < lenOfShip) {
		if (x >= size) {
			return true;
		}
		x++;
		counter++;
	}
	return false;
}

// invalid x or y coordinate case
bool outOfBoard(int x, int y, int& lenOfShip, char direction, int size) {

	if (direction == 'h') {
		return outOfBoardHorisontal(y, lenOfShip, direction, size);
	}
	else {
		return outOfBoardVertical(x, lenOfShip, direction, size);
	}

}


//check for overlapping of ships
bool horizontalOverlap(char** board, int& lenOfShip, int x, int y) {

	int counter = 0;
	while (counter < lenOfShip) {
		if (board[x][y] >= 'A' && board[x][y] <= 'D') {
			return true;
		}
	
			y++;
		counter++;
	}
	return false;
}

bool verticalOverlap(char** board, int& lenOfShip, int x, int y) {

	int counter = 0;
	while (counter < lenOfShip) {
		if (board[x][y] >= 'A' && board[x][y] <= 'D') {
			return true;
		}
		x++;
		counter++;
	}
	return false;
}

//includes two cases of overlapping
bool overlap(char** board, int& lenOfShip, char& direction, int x, int y) {
	if (direction == 'h') {
		return horizontalOverlap(board, lenOfShip, x, y);
	} 
	else {
		return verticalOverlap(board, lenOfShip, x, y);
	}
}

bool incorrectInput(char** board, int x, int y, int& lenOfShip, char direction, int size ) {

	return outOfBoard(x, y, lenOfShip, direction, size) || overlap(board, lenOfShip, direction, x, y);
}

//place ship horisontally (change only second coordinate)
bool horisontal(char** board, int& lenOfShip, char& direction, int& x, int& y, char& sign) {
	int counter = 0;
	if (direction == 'h') {
			while (counter < lenOfShip) {
				board[x][y] = sign;
				counter++;
				y++;
			}
		
		return true;
	}

	return false;

}

// place ship vertically
bool vertical(char** board, int& lenOfShip, char& direction, int& x, int& y, char& sign) {
	int counter = 0;
	 if (direction == 'v') {
		
			while (counter < lenOfShip) {
				board[x][y] = sign;
				counter++;
				x++;        //increment first coordinate
		}
		
		return true;
	}

	 return false;
}

void putShipOnBoard(char** board, int& lenOfShip, char& direction, int& x, int& y, char& sign) {
	if (horisontal(board, lenOfShip, direction, x, y, sign));
	else (vertical(board, lenOfShip, direction, x, y, sign));
}

// fill array with number of each type
void numberOfShips(int* arrNum) {
	int num = 0;
	int size = 4;
	const char* arr[4] = { "Boats", "Submarines", "Destroyers", "Carriers" };
	for (int i = 0; i < size; i++) {
		cout << "Enter number of " << arr[i] << ": " << endl;   // how many ships of each type
		cin >> num;
		arrNum[i] = num;
	}
	clear();

}

void putShipsOnBoard(char** board, char symbol,const char* typeOfShip, int numOfCurrentShip, int lenOfShip, char& direction, int size, int& x, int& y) {
	
	for (int i = 0; i < numOfCurrentShip; i++) {
		bool incorrectShip = true;
		while (incorrectShip) {
			cout << typeOfShip << ":" << endl;
			cout << "Choose direction: (v or h)" << endl;
			inputDirection(direction);
			cout << "Enter coordinates:" << endl;
			inputShotCoordinates(x, y, size);
			incorrectShip = incorrectInput(board, x, y, lenOfShip, direction, size);  //if incorrect while loop continues
			if (incorrectShip) {
				cout << "Try again!" << endl;
			}
		}
		if (!incorrectShip) {
			putShipOnBoard(board, lenOfShip, direction, x, y, symbol);  // if correct put the ship on board
			cout << endl;
		}
	}
}



void shot(char** board, int& x, int& y, int size) {
	cin >> x >> y;
	while (x >= size || y >= size) {        //check for invalid coordinates of shot
		cout << "Invalid coordinates. Try again" << endl;
		cin >> x >> y;
	}
}

void shotResult(char** board, int& x, int& y) {
	if (board[x][y] >= 'A' && board[x][y] <= 'D') { 
		board[x][y] = 'X';                           
		cout << "Great shot!" << endl;
	}
	else if (board[x][y] == 'X' || board[x][y] == 'O') {
		cout << "You already shot here!" << endl;
	}
	else {
		board[x][y] = 'O';
		cout << "You missed!" << endl;
	}
	cout << endl;
}

//see if the are remaining ships on board
bool leftShips(char** board, int size) {

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j] >= 'A' && board[i][j] <= 'D')
				return true;
		}
	}
        return false;
}


// this mask board shows only the X and the O on the other player's board
void makeMaskBoard(char** board, char** maskBoard, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j] >= 'A' && board[i][j] <= 'D') {   // ship case
				maskBoard[i][j] = '.';  
			}
			else {
				maskBoard[i][j] = board[i][j];  // X or O case
			}
		}
	}
}


void battle(char** board1, char** board2, char** maskBoard, int size, int& x, int& y) {

	bool lostGame = false;   //game is not lost
	while (!lostGame) {   
		if (leftShips(board1, size)) {                  // first player shots 
			makeMaskBoard(board2, maskBoard, size);
			cout << "Your board: " << endl;
			printBoard(board1, size);
			cout << "Their board: " << endl;
			printBoard(maskBoard, size);
			cout << "Player One: " << endl;
			shot(board2, x, y, size);
			clear();
			shotResult(board2, x, y);
		}
		else {
			lostGame = true;                                //if there are no left ships
			cout << "Player Two is winner!" << endl;
			break;
		}

		if (leftShips(board2, size)) {
			makeMaskBoard(board1, maskBoard, size);
			cout << "Your board: " << endl;
			printBoard(board2, size);
			cout << "Their board: " << endl;
            printBoard(maskBoard, size);
			cout << "Player Two: " << endl;
			shot(board1, x, y, size);
			clear();
			shotResult(board1, x, y);
		}
		else {
			lostGame = true;
			cout << "Player One is winner!" << endl;
			break;
		}

	}

}


// code for "playing with PC" option
void computerSetShips(char** board, char symbol, const char* typeOfShip, int numOfCurrentShip, int lenOfShip, char& direction, int size, int& x, int& y) {
	for (int i = 0; i < numOfCurrentShip; i++) {
		bool incorrectShip = true;
		while (incorrectShip) {
			srand(time(NULL));    // different random result every time
			int directionPc = rand() % 2;
			if (directionPc == 0) {
				direction = 'v';
			}
			else {
				direction = 'h';
			}

			x = rand() % size;   // random coordinates
			y = rand() % size;
			incorrectShip = incorrectInput(board, x, y, lenOfShip, direction, size);

		}
		if (!incorrectShip) {
			putShipOnBoard(board, lenOfShip, direction, x, y, symbol);
			cout << endl;
		}
	}
}

void pcShot(char** board, int& x, int& y, int size) {
	srand(time(NULL));
	x = rand() % size;   //pc shots on random
	y = rand() % size;
}

void battleWithPC(char** board1, char** board2, char** maskBoard, int size, int& x, int& y) {

	bool lostGame = false;
	while (!lostGame) {                    // the player shots 
		if (leftShips(board1, size)) {
			makeMaskBoard(board2, maskBoard, size);
			cout << "Your board: " << endl;
			printBoard(board1, size);
			cout << "PC board: " << endl;
			printBoard(maskBoard, size);
			cout << "Your turn: " << endl;
			shot(board2, x, y, size);
			clear();
			shotResult(board2, x, y);
		}
		else {
			lostGame = true;
			cout << "You lost the game!" << endl;
			break;
		}

		if (leftShips(board2, size)) {
			cout << "PC: " << endl;
			pcShot(board1, x, y, size);  // pc shots
			shotResult(board1, x, y);
		}
		else {
			lostGame = true;
			cout << "PC lost the game!" << endl;
			break;
		}

	}

}


int main() {
	
	int size = 10;
	int gameOption = 0;
	inputOption(gameOption);
	cout << "Enter size of board: " << endl;
	cin >> size;
	cout << endl;
	bool isFirstPlayer = true;
	char** board1 = new char* [size];
	char** board2 = new char* [size];
	char** maskBoard = new char* [size];
	const char* shipTypes[4] = { "Boat", "Submarine", "Destroyer", "Carrier" };  //number of types
	const char arrSymbols[4] = { 'A', 'B', 'C', 'D' };
	int lenOfShip[4] = { 2, 3, 4, 5 };
	int* numofships = new int [4];
	numberOfShips(numofships);

	char direction;
	int x = 0;
	int y = 0;
	int numOfShips = 1;

	fillBoard(board1, size);
	fillBoard(board2, size);
	fillBoard(maskBoard, size);

	cout << " Player One sets ships " << endl;
	
	// for every of the 4 types of ships
	for (int i = 0; i < 4; i++) {     
		putShipsOnBoard(board1, arrSymbols[i], shipTypes[i], numofships[i], lenOfShip[i], direction, size, x, y);
        clear();                        //clears the text every time
        printBoard(board1, size);  //print board after every placement
	}
	clear();

	// second player case
	if (gameOption == 1) {
		cout << " Player Two sets ships " << endl;

		for (int i = 0; i < 4; i++) {
			putShipsOnBoard(board2, arrSymbols[i], shipTypes[i], numofships[i], lenOfShip[i], direction, size, x, y);
			clear();
			printBoard(board2, size);
		}
		clear();


		cout << "Start of battle..." << endl << endl;
		battle(board1, board2, maskBoard, size, x, y);
	}

	// pc case
	else {
		cout << " PC sets ships " << endl;
		for (int i = 0; i < 4; i++) {
			computerSetShips(board2, arrSymbols[i], shipTypes[i], numofships[i], lenOfShip[i], direction, size, x, y);

		}
		clear();
	



		cout << "Start of battle..." << endl << endl;
		battleWithPC(board1, board2, maskBoard, size, x, y);
	}

	freeBoard(board1, size);
	freeBoard(board2, size);
	freeBoard(maskBoard, size);


	return 0;
}