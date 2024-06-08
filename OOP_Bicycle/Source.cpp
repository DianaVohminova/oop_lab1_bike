/*************************************************************************
*                                                                        *
*               ������������ ������ �1 �� ���, 4 �������                 *
*                                                                        *
**************************************************************************
*Project type : Visual Studio Solution                                   *
*Project name : OOP_Bicycle		                                         *
*File name    : Source.cpp	                                             *
*Language     : CPP, MSVS 2022                                           *
*Programmer   : ��������� ����� ��������, �3�-210�-22	                 *
*Modified by  :                                                          *
*Created      : 14.04.2024                                               *
*Last revision: 20.05.2024                                               *
*Comment      : ���������� �������� ������� 							 *
*************************************************************************/

#include <Windows.h>
#include "Header.h"		// ���� � ������������ �������
extern HDC hdc;			// ���������� ��������� ����������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

/*----------------------------------------------------------------------*/
/*                � � � � � � � � � �    � � � � � � �                  */
/*----------------------------------------------------------------------*/
/*----------------------------------------*/
/*        ������ ������ Location          */
/*----------------------------------------*/
//�����������
Location::Location(int InitX, int InitY)
{
	//������������� �������� ���������� ������ ������
	X = InitX;
	Y = InitY;
};//Location::Location()

//����������
Location::~Location(void)  //��������� ������ ����
{
};//Location::~Location()

//�������� X ���������� �����
int Location::GetX(void)
{
	return X;
};//Location::GetX()	

//�������� Y ���������� �����
int Location::GetY(void)
{
	return Y;
}; //Location::GetY()
/*----------------------------------------*/
/*        ������ ������ Point             */
/*----------------------------------------*/
//�����������
//��� ������������� �������� ����� ���������� ����������� ������
Point::Point(int InitX, int InitY) : Location(InitX, InitY)
{
	//������������� �������� ���������� ������ ������
	Visible = false;
}//Point::Point()

 //����������
Point::~Point(void)   //��������� ������ ����
{
}//Point::~Point()

 //�������� �����
void Point::Show(void)
{
	Visible = true;
	for (int x = 0; x <= 3; x++)
		for (int y = 0; y <= 3; y++)
			SetPixel(hdc, X + x, Y + y, RGB(255, 0, 0));//������ ������� ������
}//end Point::Show()

 //������ �����
void Point::Hide(void)
{
	Visible = false;
	for (int x = 0; x <= 3; x++)
		for (int y = 0; y <= 3; y++)
			SetPixel(hdc, X, Y, RGB(0, 0, 255));//������ ����� ������ ��� ����
}//Point::Hide()

 //������ ��� ���������� �����
bool Point::IsVisible(void)
{
	return Visible;
};//Point::IsVisible()

//����������� �����
void Point::MoveTo(int NewX, int NewY)
{
	Hide();		//������� ����� ��������� 
	X = NewX;	//�������� ���������� �����
	Y = NewY;
	Show();		//�������� ����� �� ����� �����
};//Point::MoveTo()

//���������� ������
void Point::Drag(int Step)
{
	int figX, figY; //����� ���������� ������
	figX = GetX(); //�������� ��������� ���������� ������
	figY = GetY();

	//����������� ���� ���������� ������
	while (1)
	{
		if (KEY_DOWN(VK_ESCAPE)) //27 esc - ����� ������
			break;

		//����� ����������� �������� ������
		if (KEY_DOWN(VK_LEFT)) //37 ������� �����
		{
			figX -= Step;
			MoveTo(figX, figY);
			Sleep(500); //�������� ������ �� 500 ����������
		}//if

		if (KEY_DOWN(VK_RIGHT)) //39 ������� ������
		{
			figX += Step;
			MoveTo(figX, figY);
			Sleep(500); //�������� ������ �� 500 ����������
		}//if

		if (KEY_DOWN(VK_DOWN)) //40 ������� ����
		{
			figY += Step;
			MoveTo(figX, figY);
			Sleep(500); //�������� ������ �� 500 ����������
		}//if

		if (KEY_DOWN(VK_UP)) //38 ������� �����
		{
			figY -= Step;
			MoveTo(figX, figY);
			Sleep(500); //�������� ������ �� 500 ����������
		}//if
	}//while
}//Point::Drag()

/*-----------------------------------------*/
/*        ������ ������ Bicycle            */
/*-----------------------------------------*/
//�����������
Bicycle::Bicycle(int InitX, int InitY, int hbL, int hbH, int Rad, int fL, int fH, int sL, int sH) : Point(InitX, InitY)
{
	handleBarLen = hbL;  // ����� ����
	handleBarHeight = hbH; //������ ����
	WheelRad = Rad; // ������ �����
	FrameLen = fL; //����� ����
	FrameHeight = fH; //������ ����
	SeatLen = sL;//������ �������
	SeatHeight = sH;//������ �������

	index = 0;
}//Bicycle::Bicycle()

//�����������
Bicycle::~Bicycle() {
	//empty body
}//Bicycle::~Bicycle()


//�������� ������
void Bicycle::Show()
{
	//if (Visible == true)
	//	return;
	Visible = true;

	xRightBottom = X + 5 * WheelRad;	// ���������� � (������)
	yRightBottom = Y + 2 * WheelRad;	// ���������� Y (������)
	xLeftUp = X;						// ���������� � (�����)
	yLeftUp = Y;						// ���������� Y (�������)

	HPEN penW = CreatePen(PS_SOLID, 11, RGB(0, 0, 0)); //����� ������� �����

	SelectObject(hdc, penW);

	Ellipse(hdc, X, Y, X + 2 * WheelRad, Y + 2 * WheelRad);//�������� ������
	Ellipse(hdc, X + 3 * WheelRad, Y, X + 5 * WheelRad, Y + 2 * WheelRad);//������ ������

	HPEN pen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0)); //����� ������� �����
	SelectObject(hdc, pen);
	Rectangle(hdc, X + WheelRad - 0.5 * FrameLen, Y - 0.5 * FrameHeight, X + WheelRad + 0.5 * FrameLen, Y + WheelRad);	//�������� ����
	Rectangle(hdc, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad + 0.5 * FrameLen, Y + WheelRad);//������ ����
	Rectangle(hdc, X + WheelRad + 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight + FrameLen);//�����������
	Rectangle(hdc, X + 4 * WheelRad - 2 * SeatLen, Y - 0.3 * FrameHeight - SeatHeight, X + 4 * WheelRad + 0.5 * FrameLen - SeatLen, Y - 0.3 * FrameHeight);//�������
	Rectangle(hdc, X + WheelRad - 0.3 * handleBarLen, Y - 0.5 * FrameHeight - handleBarHeight, X + WheelRad + 0.6 * handleBarLen, Y - 0.5 * FrameHeight);//����


	DeleteObject(pen);
	DeleteObject(penW);

}//Bicycle::Show()

//������ ������
void Bicycle::Hide()
{
	if (Visible == false)
		return;
	Visible = false;

	HPEN penW = CreatePen(PS_SOLID, 11, RGB(255, 255, 255)); //����� ����� ����

	SelectObject(hdc, penW);

	Ellipse(hdc, X, Y, X + 2 * WheelRad, Y + 2 * WheelRad);//�������� ������
	Ellipse(hdc, X + 3 * WheelRad, Y, X + 5 * WheelRad, Y + 2 * WheelRad);//������ ������

	HPEN pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255)); //����� ����� ����
	SelectObject(hdc, pen);
	Rectangle(hdc, X + WheelRad - 0.5 * FrameLen, Y - 0.5 * FrameHeight, X + WheelRad + 0.5 * FrameLen, Y + WheelRad);	//�������� ����
	Rectangle(hdc, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad + 0.5 * FrameLen, Y + WheelRad);//������ ����
	Rectangle(hdc, X + WheelRad + 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight + FrameLen);//�����������
	Rectangle(hdc, X + 4 * WheelRad - 2 * SeatLen, Y - 0.3 * FrameHeight - SeatHeight, X + 4 * WheelRad + 0.5 * FrameLen - SeatLen, Y - 0.3 * FrameHeight);//�������
	Rectangle(hdc, X + WheelRad - 0.3 * handleBarLen, Y - 0.5 * FrameHeight - handleBarHeight, X + WheelRad + 0.6 * handleBarLen, Y - 0.5 * FrameHeight);//����


	DeleteObject(pen);
	DeleteObject(penW);
}//Bicycle::Hide()

//���������� ������
void Bicycle::Drag(int Step)
{
	int figX, figY; //����� ���������� ������

	figX = GetX(); //�������� ��������� ���������� ������
	figY = GetY();
	while (1)
	{
		//����� ����������� �������� ������
		if (KEY_DOWN(VK_LEFT)) //37 ������� �����
		{
			figX -= Step;
			xLeftUp -= Step;		// ��������� ������ ������ (�����)
			xRightBottom -= Step;	// ��������� ������ ������ (������)
			MoveTo(figX, figY);
			Sleep(50); //�������� ������ �� 500 ����������
			return;
		}//if

		if (KEY_DOWN(VK_RIGHT)) //39 ������� ������
		{
			figX += Step;
			xRightBottom += Step;				// ��������� ������ ������ (������)
			xLeftUp += Step;					// ��������� ������ ������ (�����)
			MoveTo(figX, figY);
			Sleep(50); //�������� ������ �� 500 ����������
			return;
		}//if

		if (KEY_DOWN(VK_DOWN)) //40 ������� ����
		{
			figY += Step;
			yRightBottom += Step;		// ��������� ������ ������ (�����)
			yLeftUp += Step;			// ��������� ������ ������ (������)
			MoveTo(figX, figY);
			Sleep(50); //�������� ������ �� 500 ����������
			return;
		}//if

		if (KEY_DOWN(VK_UP)) //38 ������� �����
		{
			figY -= Step;
			yRightBottom -= Step;		// ��������� ������ ������ (�����)
			yLeftUp -= Step;			// ��������� ������ ������ (������)
			MoveTo(figX, figY);
			Sleep(50); //�������� ������ �� 500 ����������
			return;
		}
	}
}// Bicycle::Drag()

// �������� �� protected ���������� � (�����-���)
int Bicycle::get_xRB()
{
	return xRightBottom;
}

// �������� �� protected ���������� Y (�����-���)
int Bicycle::get_yRB()
{
	return yRightBottom;
}

// �������� �� protected ���������� � (����-�����)
int Bicycle::get_xLUp()
{
	return xLeftUp;
}

// �������� �� protected ���������� Y (����-�����)
int Bicycle::get_yLUp()
{
	return yLeftUp;
}

// �������� �� protected ������	
int Bicycle::getIndex()
{
	return index;
}
// �������� �� protected ����� ����
int Bicycle::getHandleBarLen()
{
	return handleBarLen;
}
// �������� �� protected ������ ����
int Bicycle::getHandleBarHeight()
{
	return handleBarHeight;
}
// �������� �� protected ������ �����
int Bicycle::getWheelRad()
{
	return WheelRad;
}
// �������� �� protected ����� ����
int Bicycle::getFrameLen()
{
	return FrameLen;
}
// �������� �� protected ������ ����
int Bicycle::getFrameHeight()
{
	return FrameHeight;
}
// �������� �� protected ������ �������
int Bicycle::getSeatLen()
{
	return SeatLen;
}
// �������� �� protected ������ �������
int Bicycle::getSeatHeight()
{
	return SeatHeight;
}
/*----------------------------------------*/
/*      ������ ������ BicycleGreenWheel   */
/*----------------------------------------*/
void BicycleGreenWheel::SetColor(int r, int g, int b)
{
	colorWheelRed = r;
	colorWheelGreen = g;
	colorWheelBlue = b;
}
//�����������
BicycleGreenWheel::BicycleGreenWheel(int InitX, int InitY, int hbL, int hbH, int Rad, int fL, int fH, int sL, int sH)
	: Bicycle(InitX, InitY, hbL, hbH, Rad, fL, fH, sL, sH)
{
	index = 1;
}//BicycleGreenWheel::BicycleGreenWheel()

//�����������
BicycleGreenWheel::~BicycleGreenWheel() {
	//empty body
}//BicycleGreenWheel::~BicycleGreenWheel()

//�������� ������
void BicycleGreenWheel::Show()
{
	// ���������� ��������
	Bicycle::Show();
	HPEN penW = CreatePen(PS_SOLID, 11, RGB(colorWheelRed, colorWheelGreen, colorWheelBlue)); //����� �������� �����

	SelectObject(hdc, penW);

	Ellipse(hdc, X, Y, X + 2 * WheelRad, Y + 2 * WheelRad);//�������� ������
	Ellipse(hdc, X + 3 * WheelRad, Y, X + 5 * WheelRad, Y + 2 * WheelRad);//������ ������

	HPEN pen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0)); //����� ������� �����
	SelectObject(hdc, pen);
	Rectangle(hdc, X + WheelRad - 0.5 * FrameLen, Y - 0.5 * FrameHeight, X + WheelRad + 0.5 * FrameLen, Y + WheelRad);	//�������� ����
	Rectangle(hdc, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad + 0.5 * FrameLen, Y + WheelRad);//������ ����
	Rectangle(hdc, X + WheelRad + 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight + FrameLen);//�����������
	Rectangle(hdc, X + 4 * WheelRad - 2 * SeatLen, Y - 0.3 * FrameHeight - SeatHeight, X + 4 * WheelRad + 0.5 * FrameLen - SeatLen, Y - 0.3 * FrameHeight);//�������
	Rectangle(hdc, X + WheelRad - 0.3 * handleBarLen, Y - 0.5 * FrameHeight - handleBarHeight, X + WheelRad + 0.6 * handleBarLen, Y - 0.5 * FrameHeight);//����


	DeleteObject(pen);
	DeleteObject(penW);

}//BicycleGreenWheel::Show()

//������ ������
void BicycleGreenWheel::Hide()
{
	Visible = false;
	HPEN penW = CreatePen(PS_SOLID, 11, RGB(255, 255, 255)); //����� ����� ����

	SelectObject(hdc, penW);

	Ellipse(hdc, X, Y, X + 2 * WheelRad, Y + 2 * WheelRad);//�������� ������
	Ellipse(hdc, X + 3 * WheelRad, Y, X + 5 * WheelRad, Y + 2 * WheelRad);//������ ������

	HPEN pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255)); //����� ����� ����
	SelectObject(hdc, pen);
	Rectangle(hdc, X + WheelRad - 0.5 * FrameLen, Y - 0.5 * FrameHeight, X + WheelRad + 0.5 * FrameLen, Y + WheelRad);	//�������� ����
	Rectangle(hdc, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad + 0.5 * FrameLen, Y + WheelRad);//������ ����
	Rectangle(hdc, X + WheelRad + 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight + FrameLen);//�����������
	Rectangle(hdc, X + 4 * WheelRad - 2 * SeatLen, Y - 0.3 * FrameHeight - SeatHeight, X + 4 * WheelRad + 0.5 * FrameLen - SeatLen, Y - 0.3 * FrameHeight);//�������
	Rectangle(hdc, X + WheelRad - 0.3 * handleBarLen, Y - 0.5 * FrameHeight - handleBarHeight, X + WheelRad + 0.6 * handleBarLen, Y - 0.5 * FrameHeight);//����


	DeleteObject(pen);
	DeleteObject(penW);
	// ������ ��������
	Bicycle::Hide();
}//BicycleGreenWheel::Hide()

/*----------------------------------------*/
/*      ������ ������ BicycleSquareWheel   */
/*----------------------------------------*/
//�����������
BicycleSquareWheel::BicycleSquareWheel(int InitX, int InitY, int hbL, int hbH, int Rad, int fL, int fH, int sL, int sH)
	: Bicycle(InitX, InitY, hbL, hbH, Rad, fL, fH, sL, sH)
{
	index = 2;
}//BicycleGreenWheel::BicycleGreenWheel()

//�����������
BicycleSquareWheel::~BicycleSquareWheel() {
	//empty body
}//BicycleSquareWheel::~BicycleSquareWheel()


//�������� ������
void BicycleSquareWheel::Show()
{
	Bicycle::Show(); //��������� ��������
	HPEN penW = CreatePen(PS_SOLID, 11, RGB(0, 0, 0)); //����� �������� �����

	SelectObject(hdc, penW);

	Rectangle(hdc, X, Y, X + 2 * WheelRad, Y + 2 * WheelRad);//�������� ������
	Rectangle(hdc, X + 3 * WheelRad, Y, X + 5 * WheelRad, Y + 2 * WheelRad);//������ ������

	HPEN pen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0)); //����� ������� �����
	SelectObject(hdc, pen);
	Rectangle(hdc, X + WheelRad - 0.5 * FrameLen, Y - 0.5 * FrameHeight, X + WheelRad + 0.5 * FrameLen, Y + WheelRad);	//�������� ����
	Rectangle(hdc, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad + 0.5 * FrameLen, Y + WheelRad);//������ ����
	Rectangle(hdc, X + WheelRad + 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight + FrameLen);//�����������
	Rectangle(hdc, X + 4 * WheelRad - 2 * SeatLen, Y - 0.3 * FrameHeight - SeatHeight, X + 4 * WheelRad + 0.5 * FrameLen - SeatLen, Y - 0.3 * FrameHeight);//�������
	Rectangle(hdc, X + WheelRad - 0.3 * handleBarLen, Y - 0.5 * FrameHeight - handleBarHeight, X + WheelRad + 0.6 * handleBarLen, Y - 0.5 * FrameHeight);//����


	DeleteObject(pen);
	DeleteObject(penW);

}//BicycleSquareWheel::Show()

//������ ������
void BicycleSquareWheel::Hide()
{
	HPEN penW = CreatePen(PS_SOLID, 11, RGB(255, 255, 255)); //����� ����� ����

	SelectObject(hdc, penW);

	Rectangle(hdc, X, Y, X + 2 * WheelRad, Y + 2 * WheelRad);//�������� ������
	Rectangle(hdc, X + 3 * WheelRad, Y, X + 5 * WheelRad, Y + 2 * WheelRad);//������ ������

	HPEN pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255)); //����� ����� ����
	SelectObject(hdc, pen);
	Rectangle(hdc, X + WheelRad - 0.5 * FrameLen, Y - 0.5 * FrameHeight, X + WheelRad + 0.5 * FrameLen, Y + WheelRad);	//�������� ����
	Rectangle(hdc, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad + 0.5 * FrameLen, Y + WheelRad);//������ ����
	Rectangle(hdc, X + WheelRad + 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight + FrameLen);//�����������
	Rectangle(hdc, X + 4 * WheelRad - 2 * SeatLen, Y - 0.3 * FrameHeight - SeatHeight, X + 4 * WheelRad + 0.5 * FrameLen - SeatLen, Y - 0.3 * FrameHeight);//�������
	Rectangle(hdc, X + WheelRad - 0.3 * handleBarLen, Y - 0.5 * FrameHeight - handleBarHeight, X + WheelRad + 0.6 * handleBarLen, Y - 0.5 * FrameHeight);//����


	DeleteObject(pen);
	DeleteObject(penW);
	Bicycle::Hide();//������ ��������
}//BicycleSquareWheel::Hide()

/*----------------------------------------*/
/*      ������ ������ BicyclePennyFart    */
/*----------------------------------------*/
//�����������
BicyclePennyFart::BicyclePennyFart(int InitX, int InitY, int hbL, int hbH, int Rad, int fL, int fH, int sL, int sH)
	: Bicycle(InitX, InitY, hbL, hbH, Rad, fL, fH, sL, sH)
{
	index = 3;

}//BicyclePennyFart::BicyclePennyFart()

//�����������
BicyclePennyFart::~BicyclePennyFart() {
	//empty body
}//BicyclePennyFart::~BicyclePennyFart()


//�������� ������
void BicyclePennyFart::Show()
{
	Bicycle::Show();//��������� ��������
	HPEN penW = CreatePen(PS_SOLID, 11, RGB(0, 0, 0)); //����� ������� �����

	SelectObject(hdc, penW);

	Ellipse(hdc, X, Y, X + 2 * WheelRad, Y + 2 * WheelRad);//�������� ������
	Rectangle(hdc, X + 3 * WheelRad, Y, X + 5 * WheelRad, Y + 2 * WheelRad);//������ ������


	HPEN pen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0)); //����� ������� �����
	SelectObject(hdc, pen);
	Rectangle(hdc, X + WheelRad - 0.5 * FrameLen, Y - 0.5 * FrameHeight, X + WheelRad + 0.5 * FrameLen, Y + WheelRad);	//�������� ����
	Rectangle(hdc, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad + 0.5 * FrameLen, Y + WheelRad);//������ ����
	Rectangle(hdc, X + WheelRad + 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight + FrameLen);//�����������
	Rectangle(hdc, X + 4 * WheelRad - 2 * SeatLen, Y - 0.3 * FrameHeight - SeatHeight, X + 4 * WheelRad + 0.5 * FrameLen - SeatLen, Y - 0.3 * FrameHeight);//�������
	Rectangle(hdc, X + WheelRad - 0.3 * handleBarLen, Y - 0.5 * FrameHeight - handleBarHeight, X + WheelRad + 0.6 * handleBarLen, Y - 0.5 * FrameHeight);//����


	DeleteObject(pen);
	DeleteObject(penW);


}//BicyclePennyFart::Show()

//������ ������
void BicyclePennyFart::Hide()
{
	HPEN penW = CreatePen(PS_SOLID, 11, RGB(255, 255, 255)); //����� ����� ����

	SelectObject(hdc, penW);

	Ellipse(hdc, X, Y, X + 2 * WheelRad, Y + 2 * WheelRad);//�������� ������
	Rectangle(hdc, X + 3 * WheelRad, Y, X + 5 * WheelRad, Y + 2 * WheelRad);//������ ������


	HPEN pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255)); //����� ����� ����
	SelectObject(hdc, pen);
	Rectangle(hdc, X + WheelRad - 0.5 * FrameLen, Y - 0.5 * FrameHeight, X + WheelRad + 0.5 * FrameLen, Y + WheelRad);	//�������� ����
	Rectangle(hdc, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad + 0.5 * FrameLen, Y + WheelRad);//������ ����
	Rectangle(hdc, X + WheelRad + 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight + FrameLen);//�����������
	Rectangle(hdc, X + 4 * WheelRad - 2 * SeatLen, Y - 0.3 * FrameHeight - SeatHeight, X + 4 * WheelRad + 0.5 * FrameLen - SeatLen, Y - 0.3 * FrameHeight);//�������
	Rectangle(hdc, X + WheelRad - 0.3 * handleBarLen, Y - 0.5 * FrameHeight - handleBarHeight, X + WheelRad + 0.6 * handleBarLen, Y - 0.5 * FrameHeight);//����


	DeleteObject(pen);
	DeleteObject(penW);
	Bicycle::Hide();//������ ��������
}//BicyclePennyFart::Hide()

/*----------------------------------------*/
/*         ������ ������ Object           */
/*----------------------------------------*/

Object::Object(int InitX, int InitY) : Point(InitX, InitY)
{
}

Object::~Object() {}

int Object::getIndex() {
	return index;
}

// �������� �� protected ���������� � (�����-���)
int Object::get_xRB()
{
	return xRightBottom;
}

// �������� �� protected ���������� Y (�����-���)
int Object::get_yRB()
{
	return yRightBottom;
}

// �������� �� protected ���������� � (����-�����)
int Object::get_xLUp()
{
	return xLeftUp;
}

// �������� �� protected ���������� Y (����-�����)
int Object::get_yLUp()
{
	return yLeftUp;
}

/*----------------------------------------*/
/*      ������ ������ Bucket			  */
/*----------------------------------------*/
//�����������
Bucket::Bucket(int InitX, int InitY, int lB, int hB) : Object(InitX, InitY)
{
	LenBucket = lB;
	HeightBucket = hB;

	index = 0;
}

//����������
Bucket::~Bucket(){}//Bucket::~Bucket()

//�������� ������
void Bucket::Show()
{
	Visible = true;

	xLeftUp = X;
	yLeftUp = Y;
	xRightBottom = xLeftUp + LenBucket;
	yRightBottom = yLeftUp + HeightBucket;

	HPEN penW = CreatePen(PS_SOLID, 5, RGB(0, 0, 0)); //����� ������� �����
	SelectObject(hdc, penW);

	//������ �����
	Rectangle(hdc, X, Y, X + LenBucket, Y+HeightBucket);

	DeleteObject(penW);
}//Bucket::Show()

//������ ������
void Bucket::Hide()
{
	Visible = false;
	HPEN penW = CreatePen(PS_SOLID, 5, RGB(255, 255, 255)); //����� ����� ����
	SelectObject(hdc, penW);

	Rectangle(hdc, X, Y, X + LenBucket, Y + HeightBucket);

	DeleteObject(penW);

}//Bucket::Hide()

/*----------------------------------------*/
/*       ������ ������ Stone		     */
/*----------------------------------------*/
//�����������
Stone::Stone(int InitX, int InitY, int rS) : Object(InitX, InitY)
{
	RadiusStone = rS;
	index = 1;
}
//����������
Stone::~Stone()
{
	//empty body
}//Bucket::~Bucket()

//�������� ������
void Stone::Show()
{
	Visible = true;

	xLeftUp = X;
	yLeftUp = Y;
	xRightBottom = xLeftUp + 2*RadiusStone;
	yRightBottom = yLeftUp + RadiusStone;

	HPEN penW = CreatePen(PS_SOLID, 5, RGB(0, 0, 0)); //����� ������� �����
	SelectObject(hdc, penW);

	Ellipse(hdc, X, Y, X + 2*RadiusStone, Y + RadiusStone);

	DeleteObject(penW);
}//Stone::Show()

//������ ������
void Stone::Hide()
{
	Visible = false;
	HPEN penW = CreatePen(PS_SOLID, 5, RGB(255, 255, 255)); //����� ������� �����
	SelectObject(hdc, penW);

	Ellipse(hdc, X - RadiusStone, Y - 0.5 * RadiusStone, X + RadiusStone, Y + 0.5 * RadiusStone);

	DeleteObject(penW);

}//Stone::Hide()

/*----------------------------------------*/
/*       ������ ������ Hammer		     */
/*----------------------------------------*/
//�����������
Hammer::Hammer(int InitX, int InitY, int sL, int sW, int hL, int hW) : Object(InitX, InitY)
{
	StickLen = sL;
	StickW = sW;

	HeadLen = hL;
	HeadW = hW;

	index = 2;
}
//����������
Hammer::~Hammer(){}//Hammer::~Hammer()

//�������� ������
void Hammer::Show()
{
	Visible = true;

	xLeftUp = X;
	yLeftUp = Y;
	xRightBottom = xLeftUp + 1.5*HeadLen;
	yRightBottom = yLeftUp + +HeadW+StickLen;

	HPEN penW = CreatePen(PS_SOLID, 5, RGB(0, 0, 0)); //����� ������� �����
	SelectObject(hdc, penW);

	LineTo(hdc, X + HeadLen, Y);
	LineTo(hdc, X + 1.5 * HeadLen, Y + HeadW);
	LineTo(hdc, X, Y + HeadW);
	LineTo(hdc, X, Y);
	Rectangle(hdc, X + 0.5 * HeadLen, Y + HeadW, X + 0.5 * HeadLen + StickW, Y + HeadW + StickLen);

	DeleteObject(penW);
}//Hammer::Show()

//������ ������
void Hammer::Hide()
{
	Visible = false;
	HPEN penW = CreatePen(PS_SOLID, 5, RGB(255, 255, 255)); //����� ������� �����
	SelectObject(hdc, penW);

	LineTo(hdc, X + HeadLen, Y);
	LineTo(hdc, X + 1.5 * HeadLen, Y + HeadW);
	LineTo(hdc, X, Y + HeadW);
	LineTo(hdc, X, Y);
	Rectangle(hdc, X + 0.5 * HeadLen, Y + HeadW, X + 0.5 * HeadLen + StickW, Y + HeadW + StickLen);

	DeleteObject(penW);

}//Hammer::Hide()

bool Collision(Bicycle& bicycle, Object& object)
{
	// ����������� ������������ �����
	bool left = object.get_xLUp() <= bicycle.get_xRB() && object.get_xRB() >= bicycle.get_xRB()
		&& (object.get_yLUp() <= bicycle.get_yRB() && object.get_yLUp() >= bicycle.get_yLUp()
			|| object.get_yRB() >= bicycle.get_yLUp() && object.get_yRB() <= bicycle.get_yRB());
	// ����������� ������������ ������
	bool right = object.get_xRB() >= bicycle.get_xLUp() && object.get_xLUp() <= bicycle.get_xLUp()
		&& (object.get_yLUp() <= bicycle.get_yRB() && object.get_yLUp() >= bicycle.get_yLUp()
			|| object.get_yRB() >= bicycle.get_yLUp() && object.get_yRB() <= bicycle.get_yRB());
	// ����������� ������������ ������
	bool top = object.get_yLUp() <= bicycle.get_yLUp() && object.get_yRB() >= bicycle.get_yLUp()
		&& (object.get_xLUp() <= bicycle.get_xRB() && object.get_xLUp() >= bicycle.get_xLUp()
			|| object.get_xLUp() >= bicycle.get_xLUp() && object.get_xRB() <= bicycle.get_xRB());
	// ����������� ������������ �����
	bool bottom = object.get_yRB() >= bicycle.get_yRB() && object.get_yLUp() <= bicycle.get_yRB()
		&& (object.get_xLUp() <= bicycle.get_xRB() && object.get_xLUp() >= bicycle.get_xLUp()
			|| object.get_xRB() >= bicycle.get_xLUp() && object.get_xRB() <= bicycle.get_xRB());
	// ����������� ����, ��������� �� ����������� "������" ������
	bool inside = object.get_xLUp() >= bicycle.get_xLUp() && object.get_yLUp() >= bicycle.get_yLUp() &&
		object.get_xRB() <= bicycle.get_xRB() && object.get_yRB() <= bicycle.get_yRB();
	// ���� ���� ���� ������� �����������, �� ������������ ����
	return left || right || top || bottom || inside;
}