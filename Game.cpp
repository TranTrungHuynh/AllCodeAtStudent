#include <iostream>
#include <Windows.h>
#include <ctime>
#include <string>
#include <conio.h>

using namespace std;

char map[30][30]; // Mảng 2 chiều các ký tự

// Hàm thay đổi kích cỡ của khung cmd.
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

// Hàm tô màu.
void textcolor(int x)
{
	HANDLE mau;
	mau=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);
}

// Hàm dịch chuyển con trỏ đến tọa độ x, y.
void gotoxy(int x,int y)
{    
	HANDLE hConsoleOutput;    
	COORD Cursor_an_Pos = {x-1,y-1};   
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);    
	SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}

// Hàm xóa màn hình.
void XoaManHinh()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void veDuongDua_1(){
	// Dài 30, rộng 30.
	for(int i = 0; i < 30; i++){
		map[i][0] = '|';
		map[i][29] = '|';
		if(i % 2 == 0){
			//textcolor(10);
			map[i][15] = '|';
			//textcolor(7);
		}
		else{
			map[i][15] = ' ';
		}
		for(int j = 1; j < 29 && j != 15; j++){
			map[i][j] = ' ' ;
		}
	}
}

void veDuongDua_2(){
	// Dài 30, rộng 30.
	for(int i = 0; i < 30; i++){
		map[i][0] = '|';
		map[i][29] = '|';
		if(i % 2 != 0){
			//textcolor(10);
			map[i][15] = '|';
			//textcolor(7);
		}
		else{
			map[i][15] = ' ';
		}
		for(int j = 1; j < 29 && j != 15; j++){
			map[i][j] = ' ' ;
		}
	}
}

void inDuongDua(){
	// Dài 30, rộng 30.
	for(int i = 0; i < 30; i++){
		//cout << "\t\t\t";
		for(int j = 0; j < 30; j++){
			/*========= Vẽ đường đua =======*/
			if(j == 0 || j == 29){
				textcolor(191);
				map[i][j] = ' ';
				cout << map[i][j];
				textcolor(7);
			}
			/*======Vẽ xe player======*/
			else if(map[i][j] == 'X' || map[i][j] == '#' || map[i][j] == '@'){
					textcolor(14);
					cout << map[i][j];
					textcolor(7);
			}
			/*======Vẽ xe chướng ngại vật====*/
			else if(map[i][j] == '!'){
				//map[i][j] = ' ';
				textcolor(200);
				cout << map[i][j];
				textcolor(7);
			}
			else{
				if(map[i][j] == '|'){
					textcolor(10);
				}
				cout << map[i][j];
			}
		}
		cout << endl;
	}
}

void veXePlayer(int x, int y){
	map[x][y] = 'X'; // Thân xe
	map[x][y-1] = '#'; // Bên trái thân xe
	map[x][y+1] = '#'; // Bên phải thân xe
	map[x-1][y-1] = '@'; // Bánh xe trên bên trái
	map[x-1][y+1] = '@'; // Bánh xe trên bên phải
	map[x+1][y-1] = '@'; // Bánh xe dưới bên trái
	map[x+1][y+1] = '@'; // Bánh xe dưới bên phải
}

void veXeChuongNgaiVat(int x, int y){
	map[x][y] = '!'; // Thân xe
	map[x][y-1] = '*'; // Bên trái thân xe
	map[x][y+1] = '*'; // Bên phải thân xe
	map[x-1][y-1] = '*'; // Bánh xe trên bên trái
	map[x-1][y+1] = '*'; // Bánh xe trên bên phải
	map[x+1][y-1] = '!'; // Bánh xe dưới bên trái
	map[x+1][y+1] = '!'; // Bánh xe dưới bên phải
}

void xoaXeChuongNgaiVat(int x, int y){
	map[x][y] = ' '; // Thân xe
	map[x][y-1] = ' '; // Bên trái thân xe
	map[x][y+1] = ' '; // Bên phải thân xe
	map[x-1][y-1] = ' '; // Bánh xe trên bên trái
	map[x-1][y+1] = ' '; // Bánh xe trên bên phải
	map[x+1][y-1] = ' '; // Bánh xe dưới bên trái
	map[x+1][y+1] = ' '; // Bánh xe dưới bên phải
}

void diChuyenXe(int& x, int& y){ // x, y la tọa độ hiện tại của xe
	if(GetAsyncKeyState(VK_LEFT)){
		if(	map[x][y] == '!' || map[x][y-1] == '!' || map[x][y+1] == '!' || 
			map[x-1][y-1] == '!'|| map[x-1][y+1] == '!' || map[x+1][y-1] =='!' || 
			map[x+1][y+1] == '!')
		{
			return;;
		}

		map[x][y] = ' ';
		map[x][y-1] = ' ';
		map[x][y+1] = ' ';
		map[x-1][y-1] = ' ';
		map[x-1][y+1] = ' ';
		map[x+1][y-1] = ' ';
		map[x+1][y+1] = ' ';

		if(y > 2)
			y--;
		veXePlayer(x, y);
	}
	else if(GetAsyncKeyState(VK_RIGHT)){
		if(	map[x][y] == '!' || map[x][y-1] == '!' || map[x][y+1] == '!' || 
			map[x-1][y-1] == '!'|| map[x-1][y+1] == '!' || map[x+1][y-1] =='!' || 
			map[x+1][y+1] == '!')
		{
			return;
		}

		map[x][y] = ' ';
		map[x][y-1] = ' ';
		map[x][y+1] = ' ';
		map[x-1][y-1] = ' ';
		map[x-1][y+1] = ' ';
		map[x+1][y-1] = ' ';
		map[x+1][y+1] = ' ';

		if(y < 27)
			y++;
		veXePlayer(x, y);
	}
	else if(GetAsyncKeyState(VK_UP)){
		if(	map[x][y] == '!' || map[x][y-1] == '!' || map[x][y+1] == '!' || 
			map[x-1][y-1] == '!'|| map[x-1][y+1] == '!' || map[x+1][y-1] =='!' || 
			map[x+1][y+1] == '!')
		{
			return;
		}

		map[x][y] = ' ';
		map[x][y-1] = ' ';
		map[x][y+1] = ' ';
		map[x-1][y-1] = ' ';
		map[x-1][y+1] = ' ';
		map[x+1][y-1] = ' ';
		map[x+1][y+1] = ' ';

		if(x > 1)
			x--;
		veXePlayer(x, y);
	}
	else if(GetAsyncKeyState(VK_DOWN)){
		if(	map[x][y] == '!' || map[x][y-1] == '!' || map[x][y+1] == '!' || 
			map[x-1][y-1] == '!'|| map[x-1][y+1] == '!' || map[x+1][y-1] =='!' || 
			map[x+1][y+1] == '!')
		{
			return;
		}

		map[x][y] = ' ';
		map[x][y-1] = ' ';
		map[x][y+1] = ' ';
		map[x-1][y-1] = ' ';
		map[x-1][y+1] = ' ';
		map[x+1][y-1] = ' ';
		map[x+1][y+1] = ' ';

		if(x < 28)
			x++;
		veXePlayer(x, y);
	}
}

int main()
{

	resizeConsole(800, 600);

	gotoxy(50, 1);
	cout << "ESC      - Exit\n";
	gotoxy(50, 2);
	cout << "p or P	  - Pause\n";
	gotoxy(50, 3);
	cout << "space    - Continue\n";

	int x = 28, y = 15; // Tọa độ xe player
	int x1 = 1, y1; // Tọa độ xe chướng ngại vật động
	int x2 = 1, y2 = 2, x3 = 3, y3 = 25, x4 = 5, y4 = 10; // Tọa độ xe chướng ngại vật tĩnh
	int a = 0;
	int diem = 0;
	while(true){
		a++;
		if(a % 2 == 0){
			veDuongDua_1();
		}
		else{
			veDuongDua_2();
		}

		// Random xe chướng ngại vật
		srand(time(0));
		y1 = 2 + rand() % 26;

		veXePlayer(x, y);
		veXeChuongNgaiVat(x1, y1);
		veXeChuongNgaiVat(x2, y2);
		veXeChuongNgaiVat(x3, y3);
		veXeChuongNgaiVat(x4, y4);

		diChuyenXe(x, y);

		XoaManHinh();
		
		Sleep(50);
		inDuongDua();

		// Kiểm tra tính đụng độ của xe player và xe chướng ngại vật
		if(map[x-1][y-1] == '!'|| map[x-1][y+1] == '!' || map[x][y] == '!')
		{
			gotoxy(60, 20);
			cout << "Game Over !";
			gotoxy(60, 21);
			cout << "Restart game after 2 seconds !";
			Sleep(2000);
			gotoxy(60, 20);
			cout << "           ";
			gotoxy(60, 21);
			cout << "\t\t\t\t\t\t";
			XoaManHinh();
			diem = 0;

		}

		if(a >= 30){
			a = 0;
		}

		gotoxy(90, 30);
		cout << "Point: " << diem;
		xoaXeChuongNgaiVat(x1, y1);
		x1++;
		if(x1 == 31){
			x1 = 1;
			diem++;
		}

		gotoxy(90, 30);
		cout << "Point: " << diem;
		xoaXeChuongNgaiVat(x2, y2);
		x2++;
		if(x2 == 31){
			x2 = 1;
			y2 = 17 + rand() % 26;
			diem++;
		}

		gotoxy(90, 30);
		cout << "Point: " << diem;
		xoaXeChuongNgaiVat(x3, y3);
		x3++;
		if(x3 == 31){
			x3 = 3;
			y3 = 10 + rand() % 16;
			diem++;
		}

		gotoxy(90, 30);
		cout << "Point: " << diem;
		xoaXeChuongNgaiVat(x4, y4);
		x4++;
		if(x4 == 31){
			x4 = 5;
			y4 = 2 + rand() % 9;
			diem++;
		}

		if(GetAsyncKeyState(VK_ESCAPE)){
			exit(0);
		}
		if(kbhit()){
			char c = getch();
			while(c == 'p' || c == 'P'){
				if(GetAsyncKeyState(VK_SPACE)){
					break;
				}
			}
		}
	}

	system("pause");
	return 0;
}
