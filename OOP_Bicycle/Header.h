#pragma once
/*************************************************************************
*                                                                        *
*               ЛАБОРАТОРНАЯ РАБОТА №1 ПО ООП, 4 СЕМЕСТР                 *
*                                                                        *
**************************************************************************
*Project type : Visual Studio Solution                                   *
*Project name : OOP_Bicycle		                                         *
*File name    : Header.h	                                             *
*Language     : CPP, MSVS 2022                                           *
*Programmer   : Вохминова Диана Олеговна, М3О-210Б-22	                 *
*Modified by  :                                                          *
*Created      : 14.04.2024                                               *
*Last revision: 20.05.2024                                               *
*Comment      : ПРОСТЕЙШАЯ ИЕРАРХИЯ КЛАССОВ. ФИГУРА - Велосипед			 *
*************************************************************************/

/*----------------------------------------------------------------------*/
/*                        Т И П Ы    Д А Н Н Ы Х                        */
/*----------------------------------------------------------------------*/

 /*----------------------  Класс МЕСТОПОЛОЖЕНИЕ ------------------------*/
class Location
{
protected:		//предоставляет возможность потомкам (производному
	//классу) иметь доступ к частным данным
	int X;		//координата Х
	int Y;		//координата Y

public:			//эти методы доступны извне всем в программе
	Location(int InitX, int InitY);	//конструктор
	~Location();					//деструктор
	int GetX();						//получить Х координату точки
	int GetY();						//получить Y координату точки
};//class Location

/*-----------------------  Класс ТОЧКА ---------------------------------*/

// Point - производный класс от Location
class Point : public Location
{
protected:							//классам, производным от Point, потребуется доступ public
	bool Visible;					//светимость точки

public:
	Point(int InitX, int InitY);	//конструктор класса
	~Point();						//деструктор
	bool IsVisible();				//узнать про светимость точки
	void MoveTo(int NewX, int NewY);//переместить фигуру
	void Drag(int Step);			//буксировка фигуры

	//статические методы (ранне связывание)
	//void Show();					//
	//void Hide();					//

	//виртуальные методы (позднее связывание)
	virtual void Show();			// показать фигуру ТОЧКА
	virtual void Hide();			// скрыть фигуру ТОЧКА
};

/*-----------------------  Класс Велосипед --------------------------------*/
class Bicycle : public Point
{
protected:

	int handleBarLen;				// длина руля
	int handleBarHeight;			//высота руля
	int WheelRad;					// радиус колес
	int FrameLen;					//длина рамы
	int FrameHeight;				//высота рамы
	int SeatLen;					//ширина сиденья
	int SeatHeight;					//высота сиденья
	int xRightBottom;				// координата Х (право-низ)
	int yRightBottom;				// координата Y (право-низ)
	int xLeftUp;					// координата Х (лево-верх)
	int yLeftUp;					// координата Y (лево-верх)
	int index;						// индекс объекта иерархии
public:
	Bicycle(int InitX, int InitY, int hbL, int hbH, int Rad, int fL, int fH, int sL, int sH); //конструктор
	~Bicycle(); //декструктор

	virtual void Drag(int step); //перемещение фигуры
	virtual void Show(); //показать фигуру
	virtual void Hide(); //скрыть фигуру

	int get_xRB();			// Получить из protected координату Х (право-низ)
	int get_yRB();			// Получить из protected координату Y (право-низ)
	int get_xLUp();			// Получить из protected координату Х (лево-вверх)	
	int get_yLUp();			// Получить из protected координату Y (лево-вверх)
	int getIndex();			// Получить из protected индекс	
	int getHandleBarLen();  // Получить из protected длину руля
	int getHandleBarHeight(); // Получить из protected высоту руля
	int getWheelRad();		// Получить из protected радиус колес
	int getFrameLen();		// Получить из protected длину рамы
	int getFrameHeight();	// Получить из protected высоту рамы
	int getSeatLen();		// Получить из protected ширину сиденья
	int getSeatHeight();	// Получить из protected высоту сиденья

};//class Bicycle
/*-----------------------  Класс Велосипед - зеленые колеса ----------------------------------*/
class BicycleGreenWheel : public Bicycle
{
protected:
	int colorWheelRed; //цвет колес
	int colorWheelGreen; //цвет колес
	int colorWheelBlue; //цвет колес

public:
	BicycleGreenWheel(int InitX, int InitY, int hbL, int hbH, int Rad, int fL, int fH, int sL, int sH); //конструктор
	~BicycleGreenWheel(); //декструктор

	void SetColor(int r, int g, int b); //установка цвета колеса

	virtual void Show(); //показать фигуру
	virtual void Hide(); //скрыть фигуру
};//class BycicleGreenWheel
/*-----------------------  Класс Велосипед - квадратные колеса ----------------------------------*/
class BicycleSquareWheel : public Bicycle
{
protected:
	int RadiusSquareWheel; //радиус квадратного колеса

public:
	BicycleSquareWheel(int InitX, int InitY, int hbL, int hbH, int Rad, int fL, int fH, int sL, int sH); //конструктор
	~BicycleSquareWheel(); //декструктор

	virtual void Show(); //показать фигуру
	virtual void Hide(); //скрыть фигуру
};//class BicycleSquareWheel
/*-----------------------  Класс Велосипед - большое и маленькое колеса ----------------------------------*/
class BicyclePennyFart : public Bicycle
{
protected:
	int RadiusFirstWheel; //радиус первого колеса
	int RadiusSecondWheel; //радиус второго колеса

public:
	BicyclePennyFart(int InitX, int InitY, int hbL, int hbH, int Rad, int fL, int fH, int sL, int sH); //конструктор
	~BicyclePennyFart(); //декструктор

	virtual void Show(); //показать фигуру
	virtual void Hide(); //скрыть фигуру
};//class BicyclePennyFart

/*-----------------------------------  Конфликтующие объекты  ------------------------------------*/
class Object : public Point
{
protected:
	int index;								// индекс
	int xRightBottom;						// координата Х (право-низ)
	int yRightBottom;						// координата Y (право-низ)
	int xLeftUp;							// координата Х (лево-верх)
	int yLeftUp;							// координата Y (лево-верх)
public:
	Object(int InitX = 0, int InitY = 0);	// конструктор
	~Object();								// деструктор
	int getIndex();							// получить индекс из protected
	int get_xRB();			// Получить из protected координату Х (право-низ)
	int get_yRB();			// Получить из protected координату Y (право-низ)
	int get_xLUp();			// Получить из protected координату Х (лево-вверх)	
	int get_yLUp();			// Получить из protected координату Y (лево-вверх)
};//class Object

// -------------------Ведро---------------------
class Bucket : public Object
{
protected:
	int LenBucket; // ширина ведра
	int HeightBucket; //высота ведра
public:
	Bucket(int InitX, int InitY, int lB, int hB);
	~Bucket(); //деструктор

	virtual void Show();
	virtual void Hide();
}; //class Bucket

// -------------------Камень---------------------
class Stone : public Object
{
protected:
	int RadiusStone; // радиус камня
public:
	Stone(int InitX, int InitY, int rS);
	~Stone(); //деструктор

	virtual void Show();
	virtual void Hide();
}; //class Stone
// -------------------Молоток---------------------
class Hammer :public Object
{
protected:
	int StickLen; // Длина ручки
	int StickW; //Толщина ручки

	int HeadLen;//длина головы молотка
	int HeadW; // ширина головы молотка
public:
	Hammer(int InitX, int InitY, int sL, int sW, int hL, int hW);
	~Hammer(); //деструктор

	virtual void Show();
	virtual void Hide();
};// class Hammer

bool Collision(Bicycle& bicycle, Object& object);