#ifndef WS_TCP_H
#define WS_TCP_H

#include "Sockets.h"

namespace ws
{
  class TCPServer
  {
  public:
    TCPServer();
    virtual ~TCPServer();

    bool CreateServer(const char* ipServer, USHORT portServer, int maxNumberConnections);
    bool CloseServer();
    TCPSocket* WaitNewClient();

  protected:
    void clearSockets();
    TCPSocket   _serverSocket;
    TCPSocket*  _tcpSockets[FD_SETSIZE];
    int         _numNewClient;
  };

  class TCPClient
  {
  public:
    TCPClient();
    virtual ~TCPClient();

    virtual bool ConnectServer(const char* ipServer, USHORT portServer);
    bool CloseClient();
    int SendData(const char* data, int len);
    int RecvData(char* data, int len);
  
  protected:
    TCPSocket _clientSocket;
  };
}

#endif