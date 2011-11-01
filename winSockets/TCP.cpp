#include "TCP.h"

using namespace ws;

TCPServer::TCPServer(const char* ipServer, USHORT portServer, int maxNumberConnections) :
  TCPSocket(),
  _numNewClient(-1)
{
  for(int i = 0; i < MAX_NUMBER_SOCKETS; ++i)
    _tcpSockets[i] = 0;
  Bind(ipServer, portServer);
  Listen(maxNumberConnections);
}

TCPServer::~TCPServer()
{
  clearSockets();
}

TCPSocket* TCPServer::WaitNewClient()
{
  _numNewClient++;
  _tcpSockets[_numNewClient] = new TCPSocket();
  Accept(_tcpSockets[_numNewClient]);
  return _tcpSockets[_numNewClient];
}


void TCPServer::clearSockets()
{
  for(int i = 0; i < MAX_NUMBER_SOCKETS; ++i)
  {
    if (_tcpSockets[i] != 0)
    {
      delete _tcpSockets[i];
      _tcpSockets[i] = 0;
    }
  }
}


TCPClient::TCPClient() :
  TCPSocket()
{
}

TCPClient::~TCPClient()
{
}

bool TCPClient::ConnectServer(const char* ipServer, USHORT portServer)
{
  return Connect(ipServer, portServer);
}
