// Test vGenInterface - Unified API for vJoy and vXbox
#include "../stdafx.h"
#include <Xinput.h>
#include "../vGenInterface.h"
#include "../../../inc/public.h"

int main()
{
	SHORT vJoyVer = GetvJoyVersion();
	BOOL exist = isVBusExists();
	BYTE Led[4];
	XINPUT_VIBRATION Vib;
	LONG MaxX;
	
	UnPlugForce(1);
	UnPlugForce(2);
	UnPlugForce(3);
	UnPlugForce(4);

	BOOL Plugged, UnPlugged, Pressed, GetN;
	UCHAR nSlots;

	int res1 = GetVJDDiscPovNumber(1);
	int res80 = GetVJDDiscPovNumber(80);
	int res2 = GetVJDDiscPovNumber(2);

	Plugged = PlugIn(1);
	int resX1 = GetVJDDiscPovNumber(1001);
	int resX2 = GetVJDDiscPovNumber(1002);


	Pressed = SetBtnA(1, TRUE);
	GetN  = GetNumEmptyBusSlots(&nSlots);
	UnPlugged = UnPlug(1);	
	Plugged = PlugIn(1);
	SetBtnA(1, TRUE);
	//SetBtnA(1, FALSE);
	SetDpad(1, DPAD_UP);

	SetTriggerR(1, 100);
	SetTriggerL(1, 200);
	SetAxisX(1, 10000);
	SetAxisY(1, 30000);
	SetAxisRx(1, 10001);
	SetAxisRy(1, 30002);

	GetVJDAxisMax(1, HID_USAGE_X, &MaxX);

	UnPlugged = UnPlug(2);
	Plugged = PlugIn(4);

	Plugged = PlugIn(5);
	SetDpadLeft(1);
	SetDpadOff(1);
	GetLedNumber(1, &(Led[0]));
	GetLedNumber(4, &(Led[3]));
	GetVibration(1, &Vib);
	GetVibration(4, &Vib);
}