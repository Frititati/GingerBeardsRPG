#include "gingerbeards.h"
#include "map.h"
#include <windows.h>
#include <iostream>
#include <fstream>
using namespace std;

const char g_szClassName[] = "myWindowClass";
HWND static area;
Map* mapConstructor = new Map();
GingerBeards* wtfamidoing = new GingerBeards();
char textToBePrinted[1000000];

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch(msg){
    	case WM_CREATE:
    		area = CreateWindow("static", "broken",
    			WS_VISIBLE| WS_CHILD ,
    			0 , 0 , 630 , 680,
    			hwnd, (HMENU) 1, NULL, NULL
			);
    	break;

    	case WM_COMMAND:
    		switch(LOWORD(wParam)){

    		case 1:
    			cout << "magic and work" << endl;
    			::MessageBeep(MB_ICONERROR);
    		break;
    		}
    	break;

        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    WNDCLASSEX wc;
    HWND window;
    MSG Msg;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc)){
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    window = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "ASCII RPG",
        WS_OVERLAPPEDWINDOW,
        0, 0, 650, 723,
        NULL, NULL, hInstance, NULL);

	HFONT hfReg = CreateFont(15, 0, 0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0, TEXT("CONSOLAS"));
	SendMessage(area,WM_SETFONT,(WPARAM)hfReg,MAKELPARAM(FALSE,0));

	wtfamidoing->mapRefresh();

    if(window == NULL){
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(window, nCmdShow);
    UpdateWindow(window);

    while(GetMessage(&Msg, NULL, 0, 0) > 0){
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}

void GingerBeards::mapRefresh(){
	mapConstructor->mapInCharFunc();
	mapConstructor->mapViewPoint(0,0,textToBePrinted);
	SetWindowText(area, TEXT(textToBePrinted));
}
