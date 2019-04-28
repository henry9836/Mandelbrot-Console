#include "ConsoleController.h"

void Console_gotoXY(int x, int y) //Move Console Cursor to XY
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Console_Resize(int x, int y) { //Resize Console Window
	RECT m_rect;
	HWND m_console = GetConsoleWindow();
	GetWindowRect(m_console, &m_rect); //stores the console's current dimensions
	MoveWindow(m_console, m_rect.left, m_rect.top, x, y, TRUE);

}

void Console_Clear() { //Clear console window
	system("cls");
	Console_gotoXY(0, 0);
}

/*
 
COLOR CODES:

RANGE: 0-254

0 - BLACK
1 - DARK BLUE
2 - DARK GREEN
3 - DARK AQUA
4 - DARK RED
5 - DARK PINK
6 - DARK YELLOW
7 - LIGHT GREY
8 - GREY
9 - BLUE
10 - GREEN
11 - AQUA
12 - RED
13 - PINK
14 - YELLOW
15 - WHITE

0-15 BLACK BACK
16-31 DARK BLUE BACK
32-47 DARK GREEN BACK
48-63 DARK AQUA BACK
64-79 DARK RED BACK
80-95 DARK PINK BACK
96-111 DARK YELLOW BACK
112-127 LIGHT GREY BACK
128-143 GREY BACK
144-159 BLUE BACK
160-175 GREEN BACK
176-191 AQUA BACK
192-207 RED BACK
208-223 PINK BACK
224-239 YELLOW BACK
240-254 WHITE BACK

*/

void Console_ColoredTEXT(string m_word, int m_color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), m_color);
	cout << m_word;
}

void Console_ColoredTEXTChar(char m_word, int m_color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), m_color);
	cout << m_word;
}

void Console_RainbowWrite(std::string m_word) {
	srand((unsigned int)time(NULL));
	
	for (size_t i = 0; i < m_word.length(); i++)
	{
		Console_ColoredTEXTChar(m_word[i], rand() % 15 + 1);
	}
}

void DrawConsole(FractalGrid m_grid) {
	Console_gotoXY(0, 0);
	for (signed i = 0; i < m_grid.ScreenSizeY; i++) //y
	{
		for (signed j = 0; j < m_grid.ScreenSizeX; j++) //x
		{
			Console_gotoXY(j, i);
			if (m_grid.Screen.at(i).at(j).type == m_grid.Fill) {
				int m_color = 208;
				switch (m_grid.Screen.at(i).at(j).color)
				{
				case m_grid.Grey: {
					m_color = 143;
					break;
				}
				case m_grid.Blue: {
					m_color = 159;
					break;
				}
				case m_grid.Green: {
					m_color = 160;
					break;
				}
				case m_grid.Aqua: {
					m_color = 191;
					break;
				}
				case m_grid.Red: {
					m_color = 207;
					break;
				}
				case m_grid.Pink: {
					m_color = 223;
					break;
				}
				case m_grid.Yellow: {
					m_color = 239;
					break;
				}
				case m_grid.White: {
					m_color = 240;
					break;
				}
				default: {
					cout << "COLOR NOT RECONGISED!" << m_grid.Screen.at(i).at(j).color;
					break;
				}
				}
				Console_ColoredTEXT(" ", m_color);
			}
			else {
				Console_ColoredTEXT(" ", 15);
			}
			
		}
	}
}