#ifndef WS_SOCKETS_H
#define WS_SOCKETS_H

#include <WinSock2.h>
#pragma comment (lib, "Ws2_32.lib")

namespace ws
{
  class Socket
  {
  public:
    Socket();
    virtual ~Socket();

    virtual bool IsOpen() const;
    virtual int  GetErrorCode() const;
    SOCKET  GetSocket() const;

    virtual int SendData(const char* data, int len);
    virtual int RecvData(char* data, int len);

    bool    Create(int type, int protocol);
    bool    Close();

    bool    Connect(const char* remoteIP, USHORT remotePort);

    bool    Bind(const char* localIP, USHORT localPort);
    bool    Listen(int backlog);
    void    Accept(Socket *newSocket);

    void    SetTimeOut(long sec, long u_sec);
    bool    SetBloking(bool blocking);
    
  private:
    SOCKET      _socket;
    static UINT _refCount;
    WSADATA     _wsd;
    sockaddr_in _sockAddr;
    timeval     _timeout;
    bool        _blocking;
  };

  class TCPSocket : public Socket
  {
  public:
    TCPSocket();
    virtual ~TCPSocket();
  };

  class UDPSocket : public Socket
  {
  public:
    UDPSocket();
    virtual ~UDPSocket();
  };
}

#endif