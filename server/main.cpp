#include <TCP.h>

using namespace ws;

int CALLBACK WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
  TCPServer serv("192.168.195.1", 4563, 10);
  TCPSocket* socket = serv.WaitNewClient();
  if (!socket->IsOpen())
  {
    MessageBox(0, "ivalid", "invalid", 0);
    return 1;
  }
  char* data = new char[255];
  socket->RecvData(data, 256);
  MessageBox(0, data, "data", 0);
  return 0;
}