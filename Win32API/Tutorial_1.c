#include <Windows.h>

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

const char* className = "MyWindowApp";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR args, int nCmdShow)
{
	HWND hWnd;
	MSG message;
	WNDCLASSEXA wndClassEx;
	
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
	
	hWnd = CreateWindowEx(0, className, "My Window App", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 544, 375, HWND_DESKTOP, NULL, hInstance, NULL);
	
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
			
			TextOut(hdc, 0, 0, "Hello Win32 API!", 16);
			
			EndPaint(hWnd, &paintStruct);
			
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
