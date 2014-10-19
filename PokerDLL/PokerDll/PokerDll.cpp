// PokerDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "PokerDll.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

using namespace std;



HHOOK g_hHook = NULL; // you can move it to shared data
//shared data segment starts here
#pragma data_seg(".Spiritinlife")
HWND g_hRecWnd = NULL;
HWND g_hTarWnd = NULL;
UINT lastMessage = -1;
HHOOK ArrayOfHooks[12] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL} ;
HWND ArrayOfWindows[12] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL} ;

RGB ArrayOfRGB[12] = { (0,100,0),(0,100,0),(0,100,0),(0,100,0),(0,100,0),(0,100,0),(0,100,0),(0,100,0),(0,100,0),(0,100,0),(0,100,0),(0,100,0)} ;
#pragma data_seg()
#pragma comment(linker, "/section:.Spiritinlife,rws")


FILE * file = NULL;

int findWindowIdentityFromHWND(HWND hWindow){
	for (int i=0; i<12; i++){
		if (ArrayOfWindows[i] !=NULL){
			if(ArrayOfWindows[i] == hWindow){
				return i;
			}
		}
	}
	return -1;
}

bool findWindowExistsFromHWND(HWND hWindow){
	for (int i=0; i<12; i++){
		if (ArrayOfWindows[i] !=NULL){
			if(ArrayOfWindows[i] == hWindow){
				return true;
			}
		}
	}
	return false;
}
static LRESULT CALLBACK PAINTPROCEDURE(int nCode, WPARAM wParam, LPARAM lParam);

HINSTANCE g_hInst = 0;
HDC hDC;
int windowIdent;

BOOL APIENTRY DllMain( HINSTANCE hInstance, 
					  DWORD  ul_reason_for_call, 
					  LPVOID lpReserved
					  )
{

	g_hInst = hInstance;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
		WM_U_MOUSE_HOOK = RegisterWindowMessage(RM_STR_MOUSE_HOOK);
		break;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

void OnDraw(HWND hWnd, HDC hDC)
{
	RECT rt;


	GetClientRect(hWnd, &rt);
	//HPEN pen;

	int wndIdent = findWindowIdentityFromHWND(hWnd);
	if (wndIdent!=-1){

		HBRUSH brush = CreateSolidBrush(RGB(ArrayOfRGB[wndIdent].x,ArrayOfRGB[wndIdent].y,ArrayOfRGB[wndIdent].z));
		//pen = CreatePen(PS_SOLID,10,RGB(RGBX,RGBY,RGBZ));

		SelectObject(hDC,brush); 

		//PolylineTo(hDC,points,5);
		FrameRect(hDC,&rt,brush);
		InflateRect(&rt,-1,-1);
		FrameRect(hDC,&rt,brush);
		InflateRect(&rt,-1,-1);
		FrameRect(hDC,&rt,brush);
		InflateRect(&rt,-1,-1);
		FrameRect(hDC,&rt,brush);
	}
}

void OnPaint(HWND hWnd)
{
	hDC =GetDC(hWnd);
	if (hDC != NULL){
		OnDraw(hWnd, hDC );
	}
}


//this is the hook to get into the paint of procedure of the window
static LRESULT CALLBACK PAINTPROCEDURE(int nCode, WPARAM wParam, LPARAM lParam)
{

	if(nCode < 0)
	{

		CallNextHookEx(g_hHook, nCode, wParam, lParam);
		return 0;
	}

	MSG* lpmsg = ( MSG * ) lParam;
	if (findWindowExistsFromHWND(lpmsg->hwnd))
		{
			switch (lpmsg->message)
			{

			case ( WM_PAINT):
				//MessageBeep(0xFFFFFF);
				RedrawWindow(lpmsg->hwnd,NULL,NULL,RDW_INTERNALPAINT);
				OnPaint(lpmsg->hwnd);

				break;
			}
		}
		//SendMessage(g_hTarWnd,lpmsg->message,wParam,lParam);
		return CallNextHookEx(g_hHook, nCode, wParam, lParam);
	}



    //This is where we set the hook for the window
	HHOOK POKERDLL_API DLL_SetHook(HWND hReceiverWnd,HWND hTargetWnd, UINT uiTHreadID,int WindowIdentifier)
	{
		windowIdent = WindowIdentifier;

		g_hRecWnd = hReceiverWnd;
		g_hTarWnd = hTargetWnd;
		if(WindowIdentifier == 0){
			g_hHook = SetWindowsHookEx(WH_GETMESSAGE, PAINTPROCEDURE, g_hInst, uiTHreadID); 
		}


		ArrayOfWindows[windowIdent] = g_hTarWnd;
		return g_hHook;
	}

	void POKERDLL_API DLL_KillHook(HHOOK hHook)
	{
		UnhookWindowsHookEx(hHook);
	}


	int POKERDLL_API changeRGB(int x,int y,int z,int windowIdent){
		ArrayOfRGB[windowIdent].x = x;
		ArrayOfRGB[windowIdent].y = y;
		ArrayOfRGB[windowIdent].z = z;
		return windowIdent;
	}

UINT POKERDLL_API getLastMessage()
{
	return lastMessage;
}
