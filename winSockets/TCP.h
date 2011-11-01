#ifndef WS_TCP_H
#define WS_TCP_H

#include "Sockets.h"

namespace ws
{
  class TCPServer : public TCPSocket
  {
  public:
    TCPServer(const char* ipServer, USHORT portServer, int maxNumberConnections);
    virtual ~TCPServer();

    TCPSocket* WaitNewClient();
  
  private:
    void clearSockets();
    TCPSocket* _tcpSockets[MAX_NUMBER_SOCKETS];
    int _numNewClient;
  };

  class TCPClient : public TCPSocket
  {
  public:
    TCPClient();
    virtual ~TCPClient();

    bool ConnectServer(const char* ipServer, USHORT portServer);
  };
}

#endif