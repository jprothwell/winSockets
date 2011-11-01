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

bool SMTPClient::SendCommand(const char* command)
{
  return (SendData(command, strlen(command)) != 0);
}

const char* SMTPClient::RecvLog()
{
  char* data = new char[MAX_SMTP_PACK];
  if (RecvData(data, MAX_SMTP_PACK) != 0)
  {
    int i = 0;
    for(; data[i] != '\r'; i++);
    data[i] = '\0';
    return data;
  }
  return "";
}

const char* SMTPClient::SendAndRecvCommand(const char* command)
{
  if (SendCommand(command))
    return RecvLog();
  return "";
}

bool SMTPClient::SendAuth(const char* login, const char* password)
{
  SendCommand("AUTH LOGIN\r\n");
  SendCommand((base64_encode(login) + "\r\n").c_str());
  SendAndRecvCommand((base64_encode(password) + "\r\n").c_str());
  return true;
}

