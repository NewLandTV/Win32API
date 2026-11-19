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
}

void Main(HDC hdc)
{
	char str[80 * 23];
    char strline[80];
    int running = 1;
    int row = 5;
    int i;
    int j;
    
    srand((unsigned int)time(NULL));
    memset(str, 0, sizeof(str));
    
    RECT rect = { 0, 0, 640, 480 };
    
    while (running)
	{
        row = rand() % 19 + 1;
        
        for (i = 1; i < 40; i++)
		{
            for (j = 1; j <= row; j++)
			{
                wsprintf(strline, TEXT("\n"));
                strcat(str, strline);
            }
            
            for (j = 1; j <= i; j++)
			{
                wsprintf(strline, TEXT(" "));
                strcat(str, strline);
            }
            
            wsprintf(strline, TEXT("¡ß"));
            strcat(str, strline);
            DrawText(hdc, str, strlen(str), &rect, DT_LEFT | DT_WORDBREAK);
            Sleep(50);
            wsprintf(str, TEXT(""));

        } 

        if (row >= 15)
		{
			running = 0;
		}
    }
}
