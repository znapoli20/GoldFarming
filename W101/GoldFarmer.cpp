// GoldFarmer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>

// <Prototype Functions>
void SimulateMouseClick();
void PC(int x, int y);
void b_Move(double time, char direction);
void InitializeShit();
// </Prototype Functions>

// <Global Variables>
const int KEYEVENT_KEY_W = 0x57;
const int KEYEVENT_KEY_S = 0x53;
int Res_Horizontal = 0;
int Res_Vertical = 0;
int NumCards = 0;
// </Global Variables>


using namespace std;


int main()
{
	InitializeShit();

	Sleep(3000);

	////system("pause");

	// <Main Loop>
	while (!GetKeyState('A') & 0x8000) // While the a key is not pressed down
	{

		//system("pause");

		b_Move(1.5, 'W');
		
		//system("pause");

		b_Move(1.5, 'S');

		//system("pause");

		if (NumCards <= 3) {
			PC((Res_Horizontal / 2), (Res_Vertical / 2));
			PC(((Res_Horizontal / 2) + (Res_Horizontal / 8)), ((Res_Vertical / 2)));
			PC(((Res_Horizontal / 2) - (Res_Horizontal / 8)), ((Res_Vertical / 2)));
		}
		else
		{
			for (int z = (Res_Horizontal / 8); z <= ((Res_Horizontal) - (Res_Horizontal / 8)); z += 100)
			{
				PC(z, (Res_Vertical / 2));
			}

		}

		Sleep(2000);

	}
	// </Main Loop>

	return 0;
}

void SimulateMouseClick() {
	//mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL); 

	INPUT    Input = { 0 };
	// left down 
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	::SendInput(1, &Input, sizeof(INPUT));

	// left up
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &Input, sizeof(INPUT));

}

void PC(int x, int y) {

	Sleep(100);
	SetCursorPos(x, y);
	Sleep(100);
	SimulateMouseClick();

}

void b_Move(double time, char direction) {

	if (direction == 'W') {

		keybd_event(KEYEVENT_KEY_W, 0, 0, 0);

		Sleep(time * 1000);

		keybd_event(KEYEVENT_KEY_W, 0, KEYEVENTF_KEYUP, 0);

	}
	else
	{
		
		keybd_event(KEYEVENT_KEY_S, 0, 0, 0);

		Sleep(time * 1000);

		keybd_event(KEYEVENT_KEY_S, 0, KEYEVENTF_KEYUP, 0);

	}

	

}

void InitializeShit() {

	// <Get Settings>
	ifstream Settings("Settings.txt");

	char h;

	Settings >> Res_Horizontal >> h >> Res_Vertical;
	Settings >> NumCards;
	Settings.close();
	// </Get Settings>

	if (NumCards > 7) {
		cout << "You have too many cards in your deck, you can only have a maximum of seven" << endl;
		cin >> h;
		abort();
	}

	if (Res_Horizontal < 800 || Res_Vertical < 600)
	{

		cout << "Your resolution is invalid" << endl;
		cout << "Your x is " << Res_Horizontal << " and your y is " << Res_Vertical << endl;
		cin >> h;
		abort();
	}

}
