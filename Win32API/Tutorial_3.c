#include <Windows.h>

const char* className = "MyWindowApp";

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void Main(HDC hdc);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR args, int nCmdShow)
{
	HWND hWnd;
	MSG message;
	WNDCLASSEX wndClassEx;
	
	wndClassEx.hInstance = hInstance;
	wndClassEx.lpszClassName = className;
	wndClassEx.lpfnWndProc = WindowProcedure;
	wndClassEx.style = CS_DBLCLKS;
	wndClassEx.cbSize = sizeof(WNDCLASSEX);
	wndClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClassEx.lpszMenuName = NULL;
	wndClassEx.cbClsExtra = 0;
	wndClassEx.cbWndExtra = 0;
	wndClassEx.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
	
	if (!RegisterClassEx(&wndClassEx))
	{
		return 0;
	}
	
	hWnd = CreateWindowEx(0, className, "My Window App", WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, HWND_DESKTOP, NULL, hInstance, NULL);
	
	ShowWindow(hWnd, nCmdShow);
	
	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		
		DispatchMessage(&message);
	}
	
	return message.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT paintStruct;
	
	switch (message)
	{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &paintStruct);
			
			Main(hdc);
			
			EndPaint(hWnd, &paintStruct);
			
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	
	return 0;
}

void Main(HDC hdc)
{
	LPCTSTR str = TEXT("*\n")
	TEXT("**\n")
	TEXT("***\n")
	TEXT("****\n")
	TEXT("*****\n")
	TEXT("******\n")
	TEXT("*******\n");
	
	RECT rect = { 0, 0, 640, 480 };
	
	DrawText(hdc, str, -1, &rect, DT_WORDBREAK);
}
