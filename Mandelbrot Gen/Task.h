// A functor class

#ifndef __CTASK_H__
#define __CTASK_H__

#include <windows.h> 
#include <vector>

class TFractalPixel {
public:
	int x = 0;
	int y = 0;
	int color = 6;
	int type = 1;
	float zoom = 15;
	int m_count = 0;
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

class TFractalRow {
public:
	std::vector<TFractalPixel> m_Row;
	int ScreenSizeX = 0;
	int ScreenSizeY = 0;
};



class CTask
{
public:
	CTask();
	CTask(int _value, TFractalRow& _Row, int ScreenSizeX, int ScreenSizeY);
	~CTask();
	void operator()();
	int getValue() const;

private:
	int m_ivalue;
	TFractalPixel mPixel;
	TFractalPixel * PixelRef;
	TFractalRow * RowRef;
};

#endif



