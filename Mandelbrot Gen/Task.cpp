#include <iostream>
#include <thread>

#include "Task.h"

CTask::CTask()
	:m_ivalue(0)
{

}

CTask::CTask(int _value, TFractalPixel& _Pixel, int ScreenSizeX, int ScreenSizeY) {

	if (_Pixel.x != ScreenSizeX || _Pixel.y != ScreenSizeY) {
		int max_iter = 100;
		double x = 0, y = 0;
		double cReal = (_Pixel.x - ScreenSizeX / 2.0)*_Pixel.zoom / ScreenSizeX;
		double cImag = (_Pixel.y - ScreenSizeY / 2.0)*_Pixel.zoom / ScreenSizeX;
		while (x * x + y * y <= 4 && _Pixel.m_count < max_iter) {
			double x_new = x * x - y * y + cReal;
			y = 2 * x*y + cImag;
			x = x_new;
			_Pixel.m_count++;
		}
		if (_Pixel.m_count < max_iter) {
			TFractalPixel::ColorType m_color;
			switch (_Pixel.m_count)
			{
			case 1: {
				m_color = _Pixel.Grey;
				break;
			}
			case 2: {
				m_color = _Pixel.White;
				break;
			}
			case 3: {
				m_color = _Pixel.Aqua;
				break;
			}
			case 4: {
				m_color = _Pixel.Blue;
				break;
			}
			case 5: {
				m_color = _Pixel.Green;
				break;
			}
			case 6: {
				m_color = _Pixel.Yellow;
				break;
			}
			case 7: {
				m_color = _Pixel.Red;
				break;
			}
			default: {
				m_color = _Pixel.Pink;
				break;
			}
			}
			_Pixel.color = m_color;
			_Pixel.type = _Pixel.Fill;
		}
		else {
			_Pixel.color = _Pixel.Pink;
			_Pixel.type = _Pixel.Empty;
		}
	}
	
}

CTask::~CTask()
{

}

void CTask::operator()()
{
	//Sleep to simulate work being done
	//std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 101));
}

int CTask::getValue() const
{
	return m_ivalue;
}
