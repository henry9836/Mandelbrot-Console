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
	const int ScreenSizeX = 170;
	const int ScreenSizeY = 50;
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

void Console_ColoredTEXT(string m_word, int m_color);

void Console_RainbowWrite(string m_word);

void DrawConsole(FractalGrid m_grid);
