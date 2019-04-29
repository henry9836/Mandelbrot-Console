#include "ConsoleController.h"
#include "ThreadPool.h"
#include "WorkQueue.h"
#include "Task.h"
#include <fstream>

FractalGrid m_grid;

int main() {
	//Init Chrono
	using std::chrono::duration_cast;
	using std::chrono::milliseconds;
	typedef std::chrono::high_resolution_clock clock;

	bool manual = false;
	float zoom = 15.0;
	Console_Resize(700, 400);
	Console_FontSize(24, 24);
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

	cout << "READING CONFIG FILE...." << endl;

	ifstream configFile("CONFIG.txt");

	int m_Line = 0;
	int fx = 10;
	int fy = 10;
	int sx = 2700;
	int sy = 500;
	string str_Line = "";

	while (m_Line != 13 && getline(configFile, str_Line))
	{
		//cout << str_Line;
		switch (m_Line)
		{
		case 1: {
			m_grid.ScreenSizeX = atoi(str_Line.c_str());
			break;
		}
		case 3: {
			m_grid.ScreenSizeY = atoi(str_Line.c_str());
			break;
		}
		case 5: {
			fx = atoi(str_Line.c_str());
			break;
		}
		case 7: {
			fy = atoi(str_Line.c_str());
			break;
		}
		case 9: {
			zoom = atof(str_Line.c_str());
			break;
		}
		case 11: {
			sy = atof(str_Line.c_str());
			break;
		}
		case 13: {
			sx = atof(str_Line.c_str());
			break;
		}
		default:
			break;
		}
		m_Line++;
	}

	configFile.close();

	system("pause");

	Console_FontSize(fx, fy);
	Console_Resize(sx, sy);
	

	//Create a ThreadPool Object capable of holding as many threads as the number of cores
	ThreadPool& threadPool = ThreadPool::GetInstance();
	//Initialize the pool
	threadPool.Initialize();
	
	while (true){
		threadPool.Start();
		//Initialise and reset values
		//Create Pixels
		//Creating vector
		vector<vector<TFractalPixel>> source;
		//Resize
		source.resize(m_grid.ScreenSizeY);
		for (size_t i = 0; i < source.size(); i++)
		{
			source.at(i).resize(m_grid.ScreenSizeX);
		}
		//Referencing
		vector<vector<TFractalPixel>>& ref = source;
		// The main thread writes items to the WorkQueue
		auto start = clock::now();
		for (unsigned row = 0; row < source.size(); row++)
		{
			for (unsigned col = 0; col < source.at(0).size(); col++)
			{
				//assign pixel to TaskFractalPixel
				ref.at(row).at(col).x = col;
				ref.at(row).at(col).y = row;
				ref.at(row).at(col).zoom = zoom;
				threadPool.Submit(CTask(0, ref.at(row).at(col), m_grid.ScreenSizeX, m_grid.ScreenSizeY));
			
			}
		}

		while (threadPool.getItemsProcessed() != source.size() * source.at(0).size())
		{
			// do nothing wait till threads are all done
		}
		threadPool.Stop();

		auto end = clock::now();

		//Convert
		m_grid.Screen.resize(m_grid.ScreenSizeY);
		for (size_t i = 0; i < m_grid.Screen.size(); i++)
		{
			m_grid.Screen.at(i).resize(m_grid.ScreenSizeX);
		}
		for (size_t m_row = 0; m_row < source.size(); m_row++)
		{
			for (size_t m_col = 0; m_col < source.at(0).size(); m_col++)
			{
				m_grid.Screen.at(m_row).at(m_col).color = source.at(m_row).at(m_col).color;
				m_grid.Screen.at(m_row).at(m_col).type = source.at(m_row).at(m_col).type;
			}
		}

		//Draw Fractal
		//Console_Clear();
		Console_gotoXY(0, 0);
		DrawConsole(m_grid);
		
		if (!manual) {
			if (zoom > 0.5) {
				cout << endl << "Next step will increase zoom" << endl;
				cout << "Current Zoom: " << zoom << endl;
				cout << "Time Taken: " << duration_cast<milliseconds>(end - start).count() << "nano seconds" << endl;
				zoom = zoom - 0.1f;
			}
			else {
				cout << endl << "Next step reset zoom" << endl;
				cout << "Current Zoom: " << zoom << endl;
				cout << "Time Taken: " << duration_cast<milliseconds>(end - start).count() << "nano seconds" << endl;
				zoom = 15.0;
			}
		}
		else {
			cout << "Current Zoom: " << zoom << endl;
			cout << "Time Taken: " << duration_cast<milliseconds>(end - start).count() << "nano seconds" << endl;
			system("pause");
		}

		//OUTPUT TO REPORT TO A FILE

		std::ofstream reportFile;

		int fx = 10;
		int fy = 10;
		int sx = 2700;
		int sy = 500;

		reportFile.open("LOG.txt", std::ios_base::app);
		reportFile << "\n\n -[ " << m_grid.ScreenSizeX << "x" << m_grid.ScreenSizeY << " Resolution ]-" << "\nThreads: " << threadPool.totalThreads << "\nTime Taken: " << duration_cast<milliseconds>(end - start).count() << "ms\n Zoom: " << zoom << "\n==========================================================================================================";


	}

	return 0;
}