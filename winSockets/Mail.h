#ifndef WS_MAIL_H
#define WS_MAIL_H

#include "TCP.h"

namespace ws
{
  #define MAX_SMTP_PACK 256

  class SMTPClient : public TCPClient
  {
  public:
    SMTPClient();
    virtual ~SMTPClient();

    bool SendCommand(const char* command);
    const char* RecvLog();
    const char* SendAndRecvCommand(const char* command);
    bool SendAuth(const char* login, const char* password);
  };
}
#endif
