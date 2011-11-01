#include "Mail.h"

#include "base64.h"

using namespace ws;

SMTPClient::SMTPClient() :
  TCPClient()
{
}

SMTPClient::~SMTPClient()
{
}

const char* SMTPClient::SendCommand(const char* command)
{
  if (_clientSocket.SendData(command, strlen(command)) != 0)
  {
    char* data = new char[MAX_SMTP_PACK];
    if (_clientSocket.RecvData(data, MAX_SMTP_PACK) != 0)
    {
      int i = 0;
      for(; data[i] != '\r'; i++);
      data[i] = '\0';
      return data;
    }
  }
  return "";
}

const char* SMTPClient::SendMessage(const char* message)
{
  const char* ret = SendCommand("DATA\r\n");
  _clientSocket.SendData(message, strlen(message));
  _clientSocket.SendData("\r\n.\r\n", 5);
  return ret;
}

bool SMTPClient::SendAuth(const char* login, const char* password)
{
  SendCommand("AUTH LOGIN\r\n");
  SendCommand((base64_encode(login) + "\r\n").c_str());
  SendCommand((base64_encode(password) + "\r\n").c_str());
  return true;
}

bool SMTPClient::ConnectServer(const char* ipServer, USHORT portServer)
{ 
  char* data = new char[MAX_SMTP_PACK];
  if (TCPClient::ConnectServer(ipServer, portServer) && (_clientSocket.RecvData(data, MAX_SMTP_PACK) != 0))
    return true;
  return false;
}
