// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the POKERDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// POKERDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef POKERDLL_EXPORTS
#define POKERDLL_API __declspec(dllexport)
#else
#define POKERDLL_API __declspec(dllimport)
#endif

#define RM_STR_MOUSE_HOOK L"HOOK_MOUSE_cdd2ca21-fbc8-4d24-b1d1-54285af5b5c4"
UINT WM_U_MOUSE_HOOK = 0;

/*
// This class is exported from the PokerDll.dll
class POKERDLL_API CPokerDll {
public:
	CPokerDll(void);
	// TODO: add your methods here.
};
*/

struct RGB
{
public: 
	int x,y,z;
};

extern "C" int POKERDLL_API changeRGB(int x,int y,int z,int windowIdent);

extern "C" HHOOK  POKERDLL_API DLL_SetHook(HWND hReceiverWnd,HWND hTargetWnd, UINT uiTHreadID,int WindowIdentifier);
extern "C"  void POKERDLL_API DLL_KillHook(HHOOK hHook);
extern "C"  UINT POKERDLL_API getLastMessage();
