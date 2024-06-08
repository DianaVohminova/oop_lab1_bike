/*************************************************************************
*                                                                        *
*               ЛАБОРАТОРНАЯ РАБОТА №1 ПО ООП, 4 СЕМЕСТР                 *
*                                                                        *
**************************************************************************
*Project type : Visual Studio Solution                                   *
*Project name : OOP_Bicycle		                                         *
*File name    : main.cpp	                                             *
*Language     : CPP, MSVS 2022                                           *
*Programmer   : Вохминова Диана Олеговна, М3О-210Б-22	                 *
*Modified by  :                                                          *
*Created      : 14.04.2024                                               *
*Last revision: 20.05.2024                                               *
*Comment      : ПРОСТЕЙШАЯ ИЕРАРХИЯ КЛАССОВ. ФИГУРА - Велосипед			 *
*************************************************************************/

#include <iostream>
#include <windows.h>
#include "Header.h"
using namespace std;

//макрос для определения кода нажатой клавиши
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*++*/
/*   Г Л О Б А Л Ь Н Ы Е   П Е Р Е М Е Н Н Ы Е  И  К О Н С Т А Н Т Ы    */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*+*/
HDC hdc;
HWND GetConcolWindow(); //указатель на консольное окно

// Матрица перехода (по строкам конфликтные объекты, по столбцам велосипеды)

const int ArrSize = 4;

int transitionMatrix[ArrSize][ArrSize]
{
	{1, 0, 1, 1},		// Камень - велосипед с квадратными колесами
	{3, 3, 3, 0},		// Молоток - велосипед с разными колесами
	{2, 2, 0, 2}		// Ведро - велосипед с зелеными колесами
};
/************************************************************************/
/*               О С Н О В Н А Я    П Р О Г Р А М М А                   */
/************************************************************************/

int main()
{
	system("color F0");
	HWND hwnd = GetConcolWindow(); //получим дескриптор консольного окна 

	if (hwnd != NULL) //если дескриптор существует 
	{
		hdc = GetWindowDC(hwnd); //получим контекст устройства для консольного окна 

		if (hdc != NULL)
		{
			int x = 350; //начальные координаты
			int y = 350;
			int handleBarLen = 70; //длина руля
			int handleBarHeight = 10;//высота руля
			int WheelRad = 50; //радиус колес
			int FrameLen = 10; //длина рамы
			int FrameHeight = 100; //высота рамы
			int SeatLen = 30;//длина сиденья
			int SeatHeight = 10;//высота сиденья

			// Экземпляры вылосипедов
			//обычный велосипед
			Bicycle ABicycle(x, y, handleBarLen, handleBarHeight, WheelRad, FrameLen, FrameHeight, SeatLen, SeatHeight);
			//велосипед с зелеными колесами
			BicycleGreenWheel ABicycleGreenWheel(x, y, handleBarLen, handleBarHeight, WheelRad, FrameLen, FrameHeight, SeatLen, SeatHeight);
			ABicycleGreenWheel.SetColor(80, 220, 100); //устанавливаем цвет колес на зеленый
			//велосипед с квадратными колесами
			BicycleSquareWheel ABicycleSquareWheel(x, y, handleBarLen, handleBarHeight, WheelRad, FrameLen, FrameHeight, SeatLen, SeatHeight);
			//Велосипед с большим и маленьким колесами
			BicyclePennyFart ABicyclePennyFart(x, y, handleBarLen, handleBarHeight, WheelRad, FrameLen, FrameHeight, SeatLen, SeatHeight);


			Bicycle* bicycles[ArrSize] = { &ABicycle, &ABicycleGreenWheel, &ABicycleSquareWheel, &ABicyclePennyFart};

			// Конфликтные объекты
			Bucket ABucket(200, 270, 60, 80);
			Stone AStone(900, 400, 30);
			int x1 = 200; int y1 = 700;
			Hammer AHammer(x1, y1, 100, 20, 50, 30);
			MoveToEx(hdc, x1, y1, NULL);


			Object* objects[ArrSize - 1] = { &ABucket, &AStone, &AHammer };

			Bicycle* pBicycle = &ABicycle;
			pBicycle->Show();

			for (int i = 0; i < 3; i++) { objects[i]->Show(); }

			while (true)
			{
				pBicycle->Drag(20);
				for (int i = 0; i < 3; i++) { objects[i]->Show(); }
				for (int i = 0; i < 3; i++)
				{
					if (Collision(*pBicycle, *objects[i]))
					{
						pBicycle->MoveTo(x, y);	// переход в начальную точку 
						pBicycle->Hide();
						pBicycle = bicycles[transitionMatrix[objects[i]->getIndex()][pBicycle->getIndex()]];
						pBicycle->Show();
						for (int i = 0; i < 3; i++) { objects[i]->Show(); }
						break;
					}//if
				}
			}
		}
	}
	return 0;
}//main()

HWND GetConcolWindow()
{

	char str[128];
	//char title[128]="xxxxxxxxxxxxxxxxxx";
	LPWSTR title = (LPWSTR)"xxxxxxxxxxxxxxxxxx";	//новая версия Windows
	GetConsoleTitle((LPWSTR)str, sizeof((LPWSTR)str)); // получить заголовок окна
	SetConsoleTitle(title);						// установить новый заголовок окна
	Sleep(100);									// ждем смены заголовка окна (100 мс);

	HWND hwnd = FindWindow(NULL, (LPWSTR)title);// определяем дескриптор окна
	SetConsoleTitle((LPWSTR)str);				//возвращаем прежний заголовок

	return hwnd;//вернуть дескриптор окна
}//end GetConcolWindow()