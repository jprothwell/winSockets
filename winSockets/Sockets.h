#ifndef WS_SOCKETS_H
#define WS_SOCKETS_H

#include <WinSock2.h>
#pragma comment (lib, "Ws2_32.lib")

#define MAX_NUMBER_SOCKETS 255

namespace ws
{
  class Socket
  {
  public:
    Socket();
    virtual ~Socket();

    virtual int SendData(const char* data, int len);
    virtual int RecvData(char* data, int len);

    bool IsOpen() const;
    int  GetErrorCode() const;

  protected:
    bool Create(int type, int protocol);
    bool Close();

    bool Connect(const char* remoteIP, USHORT remotePort);

    bool Bind(const char* localIP, USHORT localPort);
    bool Listen(int backlog);
    void Accept(Socket *newSocket);

    SOCKET      _socket;

  private:
    static UINT _refCount;
    WSADATA     _wsd;
    sockaddr_in _sockAddr;
  };

  class TCPSocket : public Socket
  {
  public:
    TCPSocket();
    virtual ~TCPSocket();
  protected:
  };

  class UDPSocket : public Socket
  {
  public:
    UDPSocket();
    virtual ~UDPSocket();
  protected:
  };
}

#endif