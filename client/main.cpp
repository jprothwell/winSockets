#include <TCP.h>

#include "resource.h"

using namespace ws;

TCPClient _client;

INT_PTR WINAPI DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_INITDIALOG:
    ShowWindow(hWnd, SW_SHOW);
    while (!_client.ConnectServer("92.241.225.221", 1000))
      Sleep(1000);
		break;
  case WM_COMMAND:
    switch(LOWORD(wParam))
    {
      case IDC_BUTTON2:
      {
        char* data = new char[256];
        for (int i = 0; i < 256; i++)
          data[i] = '\0';
        GetDlgItemText(hWnd, IDC_EDIT1, data, 256);
        _client.SendData(data, strlen(data));
        break;
      }
    }
    break;
	case WM_CLOSE:
		EndDialog(hWnd,0);
		break;
	default:
		return false;
	}
	return true;
}

void recvFunc()
{
  while(true)
  {
    char* data = new char[256];
    for (int i = 0; i < 256; i++)
      data[i] = '\0';
    if (_client.RecvData(data, 256) > 0)
      MessageBox(0, data, "Сообщение", 0);
    Sleep(1000);
  }
}

int CALLBACK WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
  HANDLE th = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&recvFunc, 0, 0, 0);
  DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc);
  CloseHandle(th);
  return 0;
}