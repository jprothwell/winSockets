#include "TCP.h"

using namespace ws;

TCPServer::TCPServer() :
  _numNewClient(-1)
{
  for(int i = 0; i < FD_SETSIZE; ++i)
    _tcpSockets[i] = 0;
}

TCPServer::~TCPServer()
{
  CloseServer();
}

bool TCPServer::CreateServer(const char* ipServer, USHORT portServer, int maxNumberConnections)
{
  if (_serverSocket.Bind(ipServer, portServer) && 
      _serverSocket.Listen(maxNumberConnections))
    return true;

  return false;
}

bool TCPServer::CloseServer()
{
  clearSockets();
  return _serverSocket.Close();
}

TCPSocket* TCPServer::WaitNewClient()
{
  _numNewClient++;
  _tcpSockets[_numNewClient] = new TCPSocket();
  _serverSocket.Accept(_tcpSockets[_numNewClient]);
  return _tcpSockets[_numNewClient];
}

void TCPServer::clearSockets()
{
  for(int i = 0; i < FD_SETSIZE; ++i)
  {
    if (_tcpSockets[i] != 0)
    {
      delete _tcpSockets[i];
      _tcpSockets[i] = 0;
    }
  }
}


TCPClient::TCPClient()
{
}

TCPClient::~TCPClient()
{
  CloseClient();
}

bool TCPClient::ConnectServer(const char* ipServer, USHORT portServer)
{
  return _clientSocket.Connect(ipServer, portServer);
}

bool TCPClient::CloseClient()
{
  return _clientSocket.Close();
}

int TCPClient::SendData(const char* data, int len)
{
  return _clientSocket.SendData(data, len);
}

int TCPClient::RecvData(char* data, int len)
{
  return _clientSocket.RecvData(data, len);
}
