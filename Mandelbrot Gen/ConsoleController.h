#pragma once
#include <windows.h> 
#include <iostream>
#include <chrono>
#include <string>
#include <vector>  
#include <stdlib.h>  
#include <time.h>  
#include <stdio.h>

using namespace std;

class FractalPixel {
public:
	int color = 0;
	int type = 0;
};

class FractalGrid {
public:
	int ScreenSizeX = 1000;
	int ScreenSizeY = 300;
	vector<vector<FractalPixel>> Screen;
	enum ColorType {
		Black,
		Blue,
		Green,
		Aqua,
		Red,
		Pink,
		Yellow,
		Grey,
		White
	};
	enum Type {
		Empty,
		Fill
	};
};

void Console_gotoXY(int x, int y);

void Console_Resize(int x, int y);

void Console_Clear();

void Console_FontSize(int a, int b);

void Console_ColoredTEXT(string m_word, int m_color);

void Console_RainbowWrite(string m_word);

void DrawConsole(FractalGrid m_grid);
