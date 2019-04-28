#include "ConsoleController.h"

FractalGrid m_grid;

void CalcFractal(float zoom) {
	for (signed row = 0; row < m_grid.ScreenSizeY; row++)
	{
		for (signed col = 0; col < m_grid.ScreenSizeX; col++)
		{
			if (col == m_grid.ScreenSizeX || row == m_grid.ScreenSizeY) {
				break;
			}
			int count = 0;
			int max_iter = 100;
			double x = 0, y = 0;
			double cReal = (col - m_grid.ScreenSizeX / 2.0)*zoom / m_grid.ScreenSizeX;
			double cImag = (row - m_grid.ScreenSizeY / 2.0)*zoom / m_grid.ScreenSizeX;
			while (x * x + y * y <= 4 && count < max_iter) {
				double x_new = x * x - y * y + cReal;
				y = 2 * x*y + cImag;
				x = x_new;
				count++;
			}
			if (count < max_iter) {
				FractalGrid::ColorType m_color;
				switch (count)
				{
				case 1: {
					m_color = m_grid.Grey;
					break;
				}
				case 2: {
					m_color = m_grid.White;
					break;
				}
				case 3: {
					m_color = m_grid.Aqua;
					break;
				}
				case 4: {
					m_color = m_grid.Blue;
					break;
				}
				case 5: {
					m_color = m_grid.Green;
					break;
				}
				case 6: {
					m_color = m_grid.Yellow;
					break;
				}
				case 7: {
					m_color = m_grid.Red;
					break;
				}
				default: {
					m_color = m_grid.Pink;
					break;
				}
				}
				m_grid.Screen.at(row).at(col).color = m_color;
				m_grid.Screen.at(row).at(col).type = m_grid.Fill;
			}
			else {
				m_grid.Screen.at(row).at(col).color = m_grid.Black;
				m_grid.Screen.at(row).at(col).type = m_grid.Empty;
			}
		}
	}
}

int main() {
	bool manual = false;
	Console_Resize(1500, 900);

	m_grid.Screen.resize(m_grid.ScreenSizeY);
	for (size_t i = 0; i < m_grid.Screen.size(); i++)
	{
		m_grid.Screen.at(i).resize(m_grid.ScreenSizeX);
	}
	Console_RainbowWrite("Mandelbrot Generator\n~ Henry Oliver");

	Console_ColoredTEXT("\n\n1. Auto Zoom \n2. Manual Zoom\n Please input a select an option: ", 14);
	Console_ColoredTEXT("", 15);
	int inp = 0;
	cin >> inp;
	while (inp != 1 && inp != 2) {
		Console_ColoredTEXT("\nIncorrect Option\n1. Auto Zoom \n2. Manual Zoom\nPlease input a select an option: ", 15);
		cin >> inp;
	}

	if (inp == 2) {
		manual = true;
	}

	Console_Clear();

	Console_RainbowWrite("Generating...\n");

	float zoom = 15.0;
	
	while (true) {
		CalcFractal(zoom);
		DrawConsole(m_grid);
		if (zoom > 0.5) {
			cout << endl << "Next step will increase zoom" << endl;
			zoom = zoom - 0.1;
		}
		else {
			cout << endl << "Next step reset zoom" << endl;
			zoom = 15.0;
		}
		if (manual) {
			system("pause");
		}
	}
	cout << "\n";

	system("pause");

	return 0;
}
