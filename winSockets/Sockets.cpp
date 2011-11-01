#include "Sockets.h"

using namespace ws;

UINT Socket::_refCount = 0;

Socket::Socket() :
  _socket(INVALID_SOCKET),
  _blocking(true)
{
  ZeroMemory(&_timeout, sizeof(_timeout));
  ZeroMemory(&_sockAddr, sizeof(_sockAddr));
  if (!_refCount)
  {
    ZeroMemory(&_wsd, sizeof(_wsd));
    WSAStartup(MAKEWORD(2, 2), &_wsd);
  }
  _refCount++;
}

Socket::~Socket()
{
  Close();
  _refCount--;
  if (!_refCount)
    WSACleanup();
}


bool Socket::Create(int type, int protocol)
{
  if (!IsOpen())
  {
    _socket = socket(AF_INET, type, protocol);
    if (!IsOpen())
      return false;
  }
  return true;
}

bool Socket::Close()
{
  if (!IsOpen())
    return false;

  shutdown(_socket, SD_BOTH);
  closesocket(_socket);
  _socket = INVALID_SOCKET;
  ZeroMemory(&_sockAddr, sizeof(_sockAddr));
  return true;
}

bool Socket::Connect(const char* remoteIP, USHORT remotePort)
{
  if (!IsOpen())
    return false;

  hostent* hn = gethostbyname(remoteIP);

  sockaddr_in RemoteAddr;
  ZeroMemory(&RemoteAddr, sizeof(RemoteAddr));
  RemoteAddr.sin_family = AF_INET;
  RemoteAddr.sin_port = htons(remotePort);
  RemoteAddr.sin_addr.s_addr = *(u_long *) hn->h_addr_list[0];

  return !(connect(_socket, (SOCKADDR*)&RemoteAddr, sizeof(RemoteAddr)) == SOCKET_ERROR);
}

bool Socket::Bind(const char* localIP, USHORT localPort)
{
  if (!IsOpen())
    return false;

  hostent* hn = gethostbyname(localIP);

  _sockAddr.sin_family = AF_INET;
  _sockAddr.sin_port = htons(localPort);
  _sockAddr.sin_addr.s_addr = *(u_long *) hn->h_addr_list[0];

  return !(bind(_socket, (SOCKADDR*)&_sockAddr, sizeof(_sockAddr)) == SOCKET_ERROR);
}

bool Socket::Listen(int backlog)
{
  if (!IsOpen())
    return false;

  return !(listen(_socket, backlog) == SOCKET_ERROR);
}

void Socket::Accept(Socket *newSocket)
{
  if (!IsOpen())
    return;

  int AddrLen = sizeof(newSocket->_sockAddr);
  ZeroMemory(&newSocket->_sockAddr, AddrLen);
  newSocket->_socket = accept(_socket, (SOCKADDR*)&newSocket->_sockAddr, &AddrLen);
}

int Socket::SendData(const char* data, int len)
{
  if (!IsOpen())
    return 0;

  fd_set fsd;
  FD_ZERO(&fsd);
  FD_SET(_socket, &fsd);
  if (_blocking && select(0, &fsd, 0, 0, &_timeout) == SOCKET_ERROR)
    return 0;

  return send(_socket, data, len, 0);
}

int Socket::RecvData(char* data, int len)
{
  if (!IsOpen())
    return 0;

  fd_set frd;
  FD_ZERO(&frd);
  FD_SET(_socket, &frd);
  if (_blocking && select(0, 0, &frd, 0, &_timeout) == SOCKET_ERROR)
    return 0;

  return recv(_socket, data, len, 0);
}

bool Socket::IsOpen() const
{
  return (_socket != INVALID_SOCKET);
}

int Socket::GetErrorCode() const
{
  return WSAGetLastError();
}

SOCKET Socket::GetSocket() const
{
  return _socket;
}

void Socket::SetTimeOut(long sec, long u_sec)
{
  _timeout.tv_sec = sec;
  _timeout.tv_usec = u_sec;
}

bool Socket::SetBloking(bool blocking)
{
  if (!IsOpen())
    return false;
  _blocking = blocking;
  blocking = !blocking;
  if (ioctlsocket (_socket, FIONBIO, (u_long*) &blocking) == SOCKET_ERROR)
    return false;
  return true;
}

//===============TCP==================
TCPSocket::TCPSocket() :
  Socket()
{
  Create(SOCK_STREAM, IPPROTO_TCP);
}

TCPSocket::~TCPSocket()
{
}

//===============UDP==================
UDPSocket::UDPSocket() :
  Socket()
{
  Create(SOCK_DGRAM, IPPROTO_UDP);
}

UDPSocket::~UDPSocket()
{
}
