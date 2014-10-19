#include "stdafx.h"
#include "PokerDll.h"



class POKERDLL_API ClassWorkerThread{

private:
	HHOOK g_hHook ; // you can move it to shared data
	//shared data segment starts here
	HWND g_hRecWnd ;
	HWND g_hTarWnd;
	HWND ArrayTargetWnd[12];


	HINSTANCE g_hInst ;
	HDC hDC;
	int RGBEquivAtArrayList;
	LRESULT CALLBACK PAINTPROCEDURE(int nCode, WPARAM wParam, LPARAM lParam);



}