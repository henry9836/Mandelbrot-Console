#include <iostream>
#include <thread>
#include <mutex>

#include "Task.h"

CTask::CTask()
	:m_ivalue(0)
{

}

CTask::CTask(int _value, TFractalRow& _Row, int ScreenSizeX, int ScreenSizeY) {
	RowRef = &_Row;
	mPixel.zoom = RowRef->m_Row.at(0).zoom;
	RowRef->ScreenSizeX = ScreenSizeX;
	RowRef->ScreenSizeY = ScreenSizeY;
}

CTask::~CTask()
{

}

void CTask::operator()()
{
	for (size_t i = 0; i < RowRef->m_Row.size(); i++)
	{
		PixelRef = &RowRef->m_Row.at(i);
		mPixel.x = PixelRef->x;
		mPixel.y = PixelRef->y;
		mPixel.m_count = 0;
		if (mPixel.x != RowRef->ScreenSizeX || mPixel.y != RowRef->ScreenSizeY) {
			int max_iter = 100;
			double x = 0, y = 0;
			double cReal = (mPixel.x - RowRef->ScreenSizeX / 2.0)*mPixel.zoom / RowRef->ScreenSizeX;
			double cImag = (mPixel.y - RowRef->ScreenSizeY / 2.0)*mPixel.zoom / RowRef->ScreenSizeX;
			while (x * x + y * y <= 4 && mPixel.m_count < max_iter) {
				double x_new = x * x - y * y + cReal;
				y = 2 * x*y + cImag;
				x = x_new;
				mPixel.m_count++;
			}
			if (mPixel.m_count < max_iter) {
				TFractalPixel::ColorType m_color;
				switch (mPixel.m_count)
				{
				case 1: {
					m_color = mPixel.Grey;
					break;
				}
				case 2: {
					m_color = mPixel.White;
					break;
				}
				case 3: {
					m_color = mPixel.Aqua;
					break;
				}
				case 4: {
					m_color = mPixel.Blue;
					break;
				}
				case 5: {
					m_color = mPixel.Green;
					break;
				}
				case 6: {
					m_color = mPixel.Yellow;
					break;
				}
				case 7: {
					m_color = mPixel.Red;
					break;
				}
				default: {
					m_color = mPixel.Pink;
					break;
				}
				}
				PixelRef->color = m_color;
				PixelRef->type = mPixel.Fill;
			}
			else {
				PixelRef->color = mPixel.Black;
				PixelRef->type = mPixel.Empty;
			}
		}
	}
	
}

int CTask::getValue() const
{
	return m_ivalue;
}
