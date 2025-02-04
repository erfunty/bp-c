// https://www.geeksforgeeks.org/pacman-game-in-c/

// Pacman Game in C language 
#include <conio.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <windows.h> 

// All the elements to be used 
// Declared here 
#define WIDTH 40 
#define HEIGHT 20 
#define PACMAN 'C' 
#define WALL '#' 
#define FOOD '.' 
#define EMPTY ' ' 
#define DEMON 'X'
#define PRIZE '$' 

// Global Variables are 
// Declared here 
int res = 0; 
int score = 0; 
int pacman_x, pacman_y; 
char board[HEIGHT][WIDTH]; 
int food = 0; 
int curr = 0;
int cspeed=0;

int saveg(){
	FILE *savefile=fopen("saved_game.bin","wb");
	if(savefile==NULL){
		printf("error loading game...");
		return 1;
	}
	fwrite(board,sizeof(char),HEIGHT*WIDTH,savefile);
	fwrite(&curr,sizeof(int),1,savefile);
	fwrite(&cspeed,sizeof(int),1,savefile);
	fclose(savefile);
}

int loadgame(){
	FILE *savefile=fopen("saved_game.bin","rb");
	if(savefile==NULL){
		printf("error loading game...");
		return 1;
	}
	fread(board,sizeof(char),HEIGHT*WIDTH,savefile);
	fread(&curr,sizeof(int),1,savefile);
	fread(&cspeed,sizeof(int),1,savefile);
	fclose(savefile);
	score=curr;
	int foundc=0;
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			if(board[i][j]==FOOD){
				food++;
			}
			if(board[i][j]==PACMAN){
				pacman_x=j;
				pacman_y=i;
				foundc=1;
				break;
			}

		}
	}
	if (!foundc) {
        printf("Pacman not found in loaded game!\n");
        return 1;
    }

}
void initialize() 
{ 
	// Putting Walls as boundary in the Game 
	for (int i = 0; i < HEIGHT; i++) { 
		for (int j = 0; j < WIDTH; j++) { 
			if (i == 0 || j == WIDTH - 1 || j == 0 
				|| i == HEIGHT - 1) { 
				board[i][j] = WALL; 
			} 
			else
				board[i][j] = EMPTY; 
		} 
	} 

	// Putting Walls inside the Game 
	int count = 50; 
	while (count != 0) { 
		int i = (rand() % (HEIGHT + 1)); 
		int j = (rand() % (WIDTH + 1)); 

		if (board[i][j] != WALL && board[i][j] != PACMAN) { 
			board[i][j] = WALL; 
			count--; 
		} 
	} 

	int val = 5; 
	while (val--) { 
		int row = (rand() % (HEIGHT + 1)); 
		for (int j = 3; j < WIDTH - 3; j++) { 
			if (board[row][j] != WALL 
				&& board[row][j] != PACMAN) { 
				board[row][j] = WALL; 
			} 
		} 
	} 

	// Putting Demons in the Game 
	count = 10; 
	while (count != 0) { 
		int i = (rand() % (HEIGHT + 1)); 
		int j = (rand() % (WIDTH + 1)); 

		if (board[i][j] != WALL && board[i][j] != PACMAN) { 
			board[i][j] = DEMON; 
			count--; 
		} 
	}
	// Putting prize in the Game 
	count = 5; 
	while (count != 0) { 
		int i = (rand() % (HEIGHT + 1)); 
		int j = (rand() % (WIDTH + 1)); 

		if (board[i][j] != WALL && board[i][j] != PACMAN) { 
			board[i][j] = PRIZE; 
			count--; 
		} 
	}
    cspeed=0;
	// Cursor at Center 
	pacman_x = WIDTH / 2; 
	pacman_y = HEIGHT / 2; 
	board[pacman_y][pacman_x] = PACMAN; 

	// Points Placed 
	for (int i = 0; i < HEIGHT; i++) { 
		for (int j = 0; j < WIDTH; j++) { 
			if (i % 2 == 0 && j % 2 == 0 
				&& board[i][j] != WALL 
				&& board[i][j] != PRIZE
				&& board[i][j] != DEMON 
				&& board[i][j] != PACMAN) { 

				board[i][j] = FOOD; 
				food++; 
			} 
		} 
	} 
} 

void draw() 
{ 
	// Clear screen 
	system("cls"); 

	// Drawing All the elements in the screen 
	for (int i = 0; i < HEIGHT; i++) { 
		for (int j = 0; j < WIDTH; j++) { 
			printf("%c", board[i][j]); 
		} 
		printf("\n"); 
	} 
	printf("Score: %d\n", score); 
} 

// Function enables to move the Cursor 
void move(int move_x, int move_y) 
{ 
    if(cspeed>0){
	int x = pacman_x + 2*move_x; 
	int y = pacman_y + 2*move_y; 

	if (board[y][x] != WALL) { 
		if (board[y][x] == FOOD) { 
			score++; 
			food--; 
			curr++; 
			if (food == 0) { 
				res = 2; 
				return; 
			} 
		} 
		else if(board[y][x] == PRIZE){
			cspeed=cspeed+10;
		}
		else if (board[y][x] == DEMON) { 
			res = 1; 
		} 

		board[pacman_y][pacman_x] = EMPTY; 
		pacman_x = x; 
		pacman_y = y; 
		board[pacman_y][pacman_x] = PACMAN; 
	} 
	    cspeed--;
		return;
	}
	else{
	int x = pacman_x + move_x; 
	int y = pacman_y + move_y; 

	if (board[y][x] != WALL) { 
		if (board[y][x] == FOOD) { 
			score++; 
			food--; 
			curr++; 
			if (food == 0) { 
				res = 2; 
				return; 
			} 
		} 
		else if(board[y][x] == PRIZE){
			cspeed=cspeed+10;
		}
		else if (board[y][x] == DEMON) { 
			res = 1; 
		} 

		board[pacman_y][pacman_x] = EMPTY; 
		pacman_x = x; 
		pacman_y = y; 
		board[pacman_y][pacman_x] = PACMAN; 
	} 
	}
} 
int random_move(int *totalFood){
	int rch;
	while(1){
		draw();
		if (kbhit()) {
		rch=getch();
		if (rch == 'z' || rch == 'Z') { 
	        printf("Exit Game! "); 
		    break; 
	    } 
		}

		printf("Total Food count: %d\n", totalFood); 
		printf("Total Food eaten: %d\n", curr);
		printf("To exit the auto-play,Enter z."); 
		if (res == 1) { 
			// Clear screen 
			system("cls"); 
			printf("Game Over! Dead by Demon\n Your Score: "
				"%d\n", 
				score); 
			return 1; 
		} 

		if (res == 2) { 
			// Clear screen 
			system("cls"); 
			printf("You Win! \n Your Score: %d\n", score); 
			return 1; 
		} 

		Sleep(1000);
		int r=rand()%4;
		switch (r) { 
		case 0: 
			move(0, -1); 
			break; 
		case 1: 
			move(0, 1); 
			break; 
		case 2: 
			move(-1, 0); 
			break; 
		case 3: 
			move(1, 0); 
			break;
		}


	}
}
// Main Function 
int main() 
{ 
	char ch,sch; 
    int totalFood;
	// Instructions to Play 
	printf(" Use buttons for w(up), a(left) , d(right) and "
		"s(down)\nAlso, Press q for quit and p for saveand r for auto-play.\n"); 
    printf("Do you want to continue the previous game?\nY\nN\n");
	sch = getch(); 
	if (sch != 'Y' && sch != 'y'&& sch != 'n' && sch != 'N') { 
		printf("Exit Game! "); 
		return 1; 
	} 
	if(sch == 'Y' || sch == 'y'){
		loadgame();
		totalFood = food;
	}
	if(sch == 'n' || sch == 'N'){
		initialize();
		food -= 35; 
	    totalFood = food; 
	}
	printf("Enter Y to continue: \n"); 

	ch = getch(); 
	if (ch != 'Y' && ch != 'y') { 
		printf("Exit Game! "); 
		return 1; 
	} 

	while (1) { 
		draw(); 
		printf("Total Food count: %d\n", totalFood); 
		printf("Total Food eaten: %d\n", curr);
		if(cspeed>0){
			printf("Number of moving speeds:%d\n",cspeed);
		} 
		if (res == 1) { 
			// Clear screen 
			system("cls"); 
			printf("Game Over! Dead by Demon\n Your Score: "
				"%d\n", 
				score); 
			return 1; 
		} 

		if (res == 2) { 
			// Clear screen 
			system("cls"); 
			printf("You Win! \n Your Score: %d\n", score); 
			return 1; 
		} 

		// Taking the Input from the user 
		ch = getch(); 

		// Moving According to the 
		// input character 
		switch (ch) { 
		case 'w': 
			move(0, -1); 
			break; 
		case 's': 
			move(0, 1); 
			break; 
		case 'a': 
			move(-1, 0); 
			break; 
		case 'd': 
			move(1, 0); 
			break;
		case 'r':
		    random_move(&totalFood);
			break;
		case 'p':
		    saveg();
			break;
		case 'q': 
			printf("Game Over! Your Score: %d\n", score); 
			return 0; 
		} 
	} 

	return 0; 
}
