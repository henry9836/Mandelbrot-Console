#include <iostream>
#include <thread>
#include <mutex>

#include "Task.h"

CTask::CTask()
	:m_ivalue(0)
{

}

CTask::CTask(int _value, TFractalPixel& _Pixel, int ScreenSizeX, int ScreenSizeY) {
	PixelRef = &_Pixel;
	mPixel.x = _Pixel.x;
	mPixel.y = _Pixel.y;
	mPixel.ScreenSizeY = ScreenSizeY;
	mPixel.ScreenSizeX = ScreenSizeX;
	mPixel.zoom = _Pixel.zoom;
	
}

CTask::~CTask()
{

}

void CTask::operator()()
{

	if (mPixel.x != mPixel.ScreenSizeX || mPixel.y != mPixel.ScreenSizeY) {
		int max_iter = 100;
		double x = 0, y = 0;
		double cReal = (mPixel.x - mPixel.ScreenSizeX / 2.0)*mPixel.zoom / mPixel.ScreenSizeX;
		double cImag = (mPixel.y - mPixel.ScreenSizeY / 2.0)*mPixel.zoom / mPixel.ScreenSizeX;
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
			mPixel.color = m_color;
			PixelRef->type = mPixel.Fill;
		}
		else {
			PixelRef->color = mPixel.Black;
			mPixel.color = mPixel.Black;
			PixelRef->type = mPixel.Empty;
		}
	}
}

int CTask::getValue() const
{
	return m_ivalue;
}
