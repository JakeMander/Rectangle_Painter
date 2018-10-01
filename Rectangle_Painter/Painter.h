#pragma once

#include "stdafx.h"
#define MAXRECTANGLE 99
//
//	Create A Type That Stores The Dimensions And Color Of A Generated Rectangle
//
//	A Note On RECT And COLORREF:
//
//		RECT = Struct That Defines Rectangle Shape. Each Variable Is The Length Of The Associated Side.
//		COLORREF = Struct That Is Used To Represent Color. Returns a Hexadecimal Value (0x00bbggrr) Which Represents The RGB Components Of The Color.
//
//

typedef struct
{
	RECT rectangle;
	COLORREF colour;
} RECTELEMENT;

int rectCount = 0;
RECTELEMENT rectArray[MAXRECTANGLE];
//
//	A Note on WM_LBUTTONDOWN, lParam, LOWORD And HIWORD:
//
//		- lParam Is Simply A Way Of Listing The Parameters Of A Particular Task or Message.
//		- For WM_LBUTTONDOWN, Windows Can Pass The lParam Variable In To Represent The (x,y) Of The Cursor.
//		- The MAKEPOINTS Macro Then Splits The Bits Used In The lParam To Create Two Seperate Values For X and Y
//		- These Are Known As LOWORD and HIWORD. In This Instance, LOWORD is the x pos, and HIWORD is the y.
//
//

void RectGen(LPARAM lParam, HWND wndIn)
{
	//	The % Operator Sets The Upper Bound For The RNG. 1 + rand() Ensures 0 Is Not Generated.
	//	It's Worth Noting, This Does Affect The Distribution Of The Random Number (Sufficient For A Program Like This)
	RECTELEMENT newRect;
	RECT windowCoords;
	POINTS mousePos;

	mousePos = MAKEPOINTS(lParam);

	//	Provide A Rect Structure To Store The Dimensions Of The Client Window And Return Values Using GetWindowRect

	GetClientRect(wndIn, &windowCoords);
	//	Generate A Number Between 0 And The Max Height/Width Of The Window To Better Vary Rectangle Size.
	//	Note: Expression Can Be Simplified By Assigning The Below Expression Directly To RECT Right And Bottom.
	//	However, For Clarification Of Code, Placed Seperate.

	int height = (rand() % (windowCoords.bottom - mousePos.y + 1)) + mousePos.y;
	int width = (rand() % (windowCoords.right - mousePos.x + 1)) + mousePos.x;
	//
	//Left And Top Are The X And Y Coords Of The Top Left Corner Of The RECT.
	//Right And Bottom Are The X And Y Coords Of The Bottom Right Corner Of The Rect.
	// Each Color Is Represented As An 8-Bit int. Therefore The Max Value is 255!
	//
	//

	newRect.rectangle.top = mousePos.y;
	newRect.rectangle.left = mousePos.x;
	newRect.rectangle.bottom = height;
	newRect.rectangle.right = width;
	newRect.colour = RGB(rand() % 256, rand() % 256, rand() % 256);

	//	Add Rect To An Array Ready For WM_Paint To Cycle Through
	rectArray[rectCount] = newRect;
	rectCount++;
}
//
//	Create A Brush and set it to the Color of the Rectangle Stored In The Array.
//	Fill Rect Using the Device Contect Of The Window By Passing The RECT Struct And The Brush To FillRect().
//	Be Sure To Remove Any Instantiated Brush To Prevent Memory Leaks Using DeleteObject()!
//
//
void PaintRectArray(HDC *hdcIn)
{
	for (int i = 0; i < MAXRECTANGLE; i++)
	{
		HBRUSH rectPainter = CreateSolidBrush(rectArray[i].colour);
		FillRect(*hdcIn, &rectArray[i].rectangle, rectPainter);
		DeleteObject(rectPainter);
	}

}