// single player ping-pong game under the guidance of Mr. Kushal Pathak

#include<iostream>
#include<windows.h>
#include<conio.h>
using namespace std; 
const int h = 20; 
const int w = 35; 
char arr[h][w]; 
char play = 'y';
int gameover = 0;
int Your_Score, Bot_Score;
void init_table(); 
void render();
void bat_and_ball_display(); 
void ball_momentum();
void collision_detection();
void game_over();
void control();
void bot_player();
void menu_screen();
void reset_game();
struct ball {
	float x = w / 2,  y = h / 2; 
	float vx = -1, vy = 1; 
};
struct bat { 
	int len = 4; 
	int pos = h / 2 - len / 2 - 4;
};
ball b;
bat bt, bt2; 

int main() {
	menu_screen();
	while (play == 'y') {
		reset_game();
		while (!gameover) {
			//system("cls");
			init_table();
			bat_and_ball_display();
			render();
			collision_detection();
			ball_momentum();
			control();
			bot_player();
			Sleep(100);

		}
		game_over();
	}
	return 0; 
}

void game_over() {
	cout << "Game Over!\n";
	Sleep(2000);
	cout << "Do You Want to Play again(y):  ";
	cin >> play;
}
void menu_screen() {
	char exit; 
	cout << "How to play" << endl; 
	cout << "w: To move up \ns: To move down" << endl;
	cout << "Press Any key to start.......";
	
	play = _getch();
	play = 'y';
}
void reset_game() {
	Your_Score = 0;
	Bot_Score = 0; 
	gameover = 0;
	b.x = w / 2; b.y = h / 2;
	bt.pos = h / 2 - bt.len / 2;
}

void init_table() {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			arr[i][j] = ' ';
		    // condition of boundary
			if (j == 0 || j == w-1  || i == 0 || i == h-1)  arr[i][j] = '#';
		}
	
	}
}
void render() {
	system("cls");
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cout << arr[i][j]<<" ";
		}
		cout << endl; 
	}
	//cout << endl; 
}

void bat_and_ball_display() {
	// first let's make ball appear on centre of the table 
	arr[(int)b.y][(int)b.x] = 'O';
	// for bat to appear on left side 
	for (int i = bt.pos; i <= bt.pos + bt.len; i++) {
		arr[i][1] = '#';
	}
	// for bat to appear on right side
	for (int i = bt2.pos; i <= bt2.pos + bt2.len; i++) {
		arr[i][w - 2] = '#';
	}
}
void ball_momentum() {
	b.x += b.vx; 
	b.y += b.vy; 
}

void collision_detection() {
	// Detect collision with roof and floor
	if (b.y <= 1 || b.y >= h - 2) {
		b.vy = -b.vy;
		Beep(350, 400);
	}
	// Detect collision with left and right walls
	if (b.x <= 1 || b.x >= w - 2) {
		gameover = 1;
		Beep(500, 500);
	}
	// Detect collision with left bat
	for (int i = bt.pos; i <= bt.pos + bt.len; i++) {
		if (b.x == 2 && b.y == i) {
			b.vx = -b.vx;
			Your_Score++;
			Beep(400, 50);
		}
	}
	// Detect collision with right bat
	for (int i = bt2.pos; i <= bt2.pos + bt2.len; i++) {
		if (b.x == w - 3 && b.y == i) {
			b.vx = -b.vx;
			Bot_Score++;
			Beep(400, 50);
		}
	}
}


void control() {
	// left bat should be manually controlled
	if (_kbhit()){
		char c = _getch();
		switch (c) {
		case 'w': if (bt.pos > 1) bt.pos--; break;
		case 's':if (bt.pos + bt.len < h - 1) bt.pos++; break;
		}
	}
}

void bot_player() {
	float ball_distance = b.y - (bt2.pos + bt2.len) / 2; 
	if (ball_distance < 0 && bt2.pos > 1) bt2.pos--; 
	if (ball_distance > 0 && bt2.pos + bt2.len < h-1) bt2.pos++;
}   
