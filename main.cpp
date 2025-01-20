#include <iostream>
#include <conio.h>

using namespace std;

// constants
const int J = 4;
const int VALUE_TO_WIN = 16;

// entery point
void playGame();
int main(){
	cout<<"1.shoro bazi\n";
	cout<<"2.darbare bazi\n";
    cout<<"3.khoroj az bazi\n";
	char a;
    cin>>a;
    if (a=='1'){
    	system("CLS");
	playGame();
	cout << "\nPress any key to close the game ...\n";
	getch();}
	else if(a=='2'){
        system("CLS");
	cout<<"salam...be bazi 2048 man khosh omadi\n";
	cout<<"bazi khaily sadast... ba estefade az kelid haye l, d, u, r bvazi kon\n";
	cout<<"man danshjoye term 1 karshenasi computer hastam...Farid afrakhte... 990122680054...omid varam az bazi lezat bebari\n";
    cout<<"baraye bazgasht be menu kelid t ro bezanid";
    getch();}
	else (a=='3');
	    system("CLS");
	cout<<"badan mibinamet";
}

// global variables : shared state
bool gameOver, stuck, win;
int score;
char input_char;
string logMessage;
int arr[J];

// game manager section
void setGlobals();
void gameLoop();
void render();
void playGame(){
	setGlobals();
	render();
	while (!gameOver){
		gameLoop();
	}
	if (win)
		cout << "You won ! :D";
	else if (stuck)
		cout << "You lost the game :(";
	else
		cout << "See you later :D";
}


void updateScore();
void setGlobals(){
	for(int j=0; j<J; j++)
		arr[j] = 0;
	arr[J/2] = 2;
	gameOver = false;
	stuck = false;
	win = false;
	updateScore();
	logMessage = "";
}


void input();
void update();
void render();
void gameLoop(){
	input();
	update();
	render();
}

// input section
void input(){
	cout << "[Move: L R |Exit: E]\n";
	input_char = getch();
	switch(input_char){
		case 'l':
			input_char = 'L';
			break;
		case 'r':
			input_char = 'R';
			break;
		case 'e':
			input_char = 'E';
			break;
	}
}

// update (game logic) section
bool move(char);
void updateScore();
void gameOverCheck();
void addTile(char);
void update(){
	bool moved;
	switch(input_char){
		case 'E':
			gameOver = true;
			break;
		case 'L':
		case 'R':
			moved = move(input_char);
			if (moved)
				addTile(input_char);
			break;
		default:
			logMessage = "* COMMAND WAS NOT VALID!";
	}
	updateScore();
	gameOverCheck();
}

bool moveLeft();
bool moveRight();
bool move(char direction){
	bool moved = false;
	switch(direction){
		case 'L':
			moved = moveLeft();
			break;
		case 'R':
			moved = moveRight();
			break;
	}
	return moved;
}

bool moveLeft(){
	bool moved = false;
	for (int j=0; j<J-1; j++){
		int next = j+1;
		for (; next < J-1; next++)
			if (arr[next] > 0)
				break;
		
		if (arr[j] == 0){
			if (arr[next] > 0){
				arr[j] = arr[next];
				arr[next] = 0;
				moved = true;
				j--;
			}
		}else{
			if(arr[j] == arr[next]){
				arr[j] += arr[next];
				arr[next] = 0;
				moved = true;
			}
		}
	}
	return moved;
}

bool moveRight(){
	bool moved = false;
	for (int j=J-1; j>0; j--){
		int next = j-1;
		for (; next > 0; next--)
			if (arr[next] > 0)
				break;
		
		if (arr[j] == 0){
			if (arr[next] > 0){
				arr[j] = arr[next];
				arr[next] = 0;
				j++;
				moved = true;
			}
		}else{
			if(arr[j] == arr[next]){
				arr[j] += arr[next];
				arr[next] = 0;
				moved = true;
			}
		}
	}
	return moved;
}

void addTile(char direction){
	if (direction == 'L')
		arr[J-1] = 2;
	else
		arr[0] = 2;
}

void updateScore(){
	score = 0;
	for (int j=0; j<J; j++)
		score += arr[j];
}

void stuckCheck();
void winCheck();
void gameOverCheck(){
	winCheck();
	stuckCheck();
		
	 if (stuck || win){
	 	gameOver = true;
	 }
}

void stuckCheck(){
	stuck = true;
	for(int j=0; j<J; j++)
		if (arr[j] == 0){
			stuck = false;
			break;
		}
		
	for(int j = 0; j<J-1; j++)
		if (arr[j] == arr[j+1]){
			stuck = false;
			break;
		}
}

void winCheck(){
	for (int j=0; j<J; j++)
		if (arr[j] == VALUE_TO_WIN){
			win = true;
			break;
		}
}

// render section
void topPannel();
void printBoard();
void bottomPannel();
void render(){
	system("CLS");
	topPannel();
	printBoard();
	bottomPannel();
}

void topPannel(){
	cout << "[2048 Clone ===========]\n";
	if (logMessage != ""){
		cout << logMessage;
		logMessage = "";
	}
	cout << '\n';
}

void printCell(int);
void printBoard(){
	for (int j=0; j<J; j++){
		printCell(arr[j]);
	}
	cout << '\n';
}

void printCell(int value){
	if (value == 0)
			cout << "[    ]";
		else if (value < 10){
			cout << "[ " << value << "  ]";
		}else if (value < 100){
			cout << "[ " << value << " ]";
		}else if (value < 1000){
			cout << "[ " << value << "]";
		}else {
			cout << "[" << value << "]";
		}
}

void bottomPannel(){
	cout << "Score: " << score << '\n';
}

