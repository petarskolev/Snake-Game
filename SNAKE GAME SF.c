#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define N 24
#define M 60

int i, j, Field[N][M], x, y, Gy, Head, a, b, Tail, Game, Apple, var, direction, Score;
int NumberOfApples = 0;

void SnakeBody() {
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			Field[i][j] = 0;
		}
	}
	
	x = N / 2;
	y = M / 2;
	Gy = y;
	Head = 5;
	Tail = 1;
	Game = 0;
	Apple = 0;
	Score = 0;
	direction = 'd';

	for (i = 0; i < Head; i++) {
		Gy++;
		Field[x][Gy - Head] = i + 1;
	} // Creating Snake's body in the middle of the screen

}

int EndGame() {
	printf("\a");
	Sleep(2500);
	if (Field[x][y] > 0) {
		system("Cls");
		printf("\n\n\n\n            Game Over :)\n");
		printf("            Score: %d\n\n", Score);
		Game = 1;
	}

	if (NumberOfApples == 51) {
		system("Cls");
		printf("\n\n\n\n            YOU WON\n");
		printf("            Maximum Score: %d/n/n", Score);
		Game = 1;
	}
	return 0;
}

void Borders() {
	
	for (i = 0; i <= M ; i++) {
		if (i == M) {
			printf("%c", 187);
		} // Upper Right
		else if (i == 0) {
			printf("%c", 201);
		} // Upper Left
		else {
			printf("%c", 205);
		} // Upper Middle
	} // Upper Borders

	printf("  Current Score: %d\n", Score);

	for (i = 0; i < N; i++) {
		printf("%c", 186); // Left Borders

		for (j = 1; j < M; j++) {

			if (Field[i][j] == 0) {
				printf(" ");
			}

			if (Field[i][j] > 0 && Field[i][j] != Head) {
				printf("%c", 177); // Printing Snake's Body 
			}

			if (Field[i][j] == Head) {
				printf("%c", 178); // Printing Snake's Head
			}

			if (Field[i][j] == -5) {
				printf("%c", 64); // Printing Apple
			}

			if (j == M - 1) {
				printf("%c\n", 186);
			} // Right Borders
		}//Side Borders
	}

	for (i = 0; i <= M; i++) {
		if (i == 0) {
			printf("%c", 200);
		} // Bottom Left

		else if (i == M) {
			printf("%c", 188);
		} // Bottom Right

		else {
			printf("%c", 205);
		} // Bottom Middle

	}//Bottom Borders
}

void ResetScreenPosition(){
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void RandomFood() {
	srand(time(0)); // Generates a random number in seconds since 1970
	a = 1 + rand() % 22;
	b = 1 + rand() % 58;

	if (Apple == 0 && Field[a][b] == 0) { // If no apple and not on body
		Field[a][b] = -5;
		Apple = 1;
	}
}

int GetCharacter() {
	if (_kbhit()) {
		return _getch();
	}

	else {
	return -1;
	}
}

void EatenApples() {
	if (NumberOfApples < 51) {
		NumberOfApples++;
	}

	if (NumberOfApples == 51) {
		EndGame();
	}
}

void Movement() {
	var = GetCharacter();
	var = tolower(var); // Function that makes uppercase char to lowercase

	if ((var == 'd' || var == 'a' || var == 'w' || var == 's') && (abs(direction - var) > 4)){
	direction = var; 
	} // Directions can be only aside of current direcion

	if (direction == 'd') {
		y++;
		if (Field[x][y] > 0){
			EndGame();
		}
		if (y == M) { // Prints on same level
			y = 0;
		}
		if (Field[x][y] == -5) {
			Apple = 0;
			EatenApples();
			Tail--;
			Score++;
		}
		Head++;
		Field[x][y] = Head;
	} // Move Right

	if (direction == 'a') {
		y--;
		if (Field[x][y] > 0) {
			EndGame();
		}
		if (y == 1) { // Prints on same level
			y = M;
		}
		if (Field[x][y] == -5) {
			Apple = 0;
			EatenApples();
			Tail--;
			Score++;
		}
		Head++;
		Field[x][y] = Head;
	} // Move Left

	if (direction == 'w') {
		x--;
		if (Field[x][y] > 0) {
			EndGame();
		}
		if (x == -1) { // Prints on same level
			x = N;
		}
		if (Field[x][y] == -5) {
			Apple = 0;
			EatenApples();
			Tail--;
			Score++;
		}
		Head++;
		Field[x][y] = Head;
	} //Move Up

	if (direction == 's') {
		x++;
		if (Field[x][y] > 0) {
			EndGame();
		}
		if (x == N) { // Prints on same level
			x = -1;
		}
		if (Field[x][y] == -5) {
			Apple = 0;
			EatenApples();
			Tail--;
			Score++;
		}
		Head++;
		Field[x][y] = Head;
	} // Move Down
}

void TailMovement() {
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			if (Field[i][j] == Tail) {
				Field[i][j] = 0;
			}
		}
	}
	Tail++;
}

	void main() {
		system("COLOR 2");
		SnakeBody();
		while (Game == 0) { // Game is played
			Borders();
			ResetScreenPosition();
			RandomFood();
			Movement();
			TailMovement();
			Sleep(99);
		}	
	}