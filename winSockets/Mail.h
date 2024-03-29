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

    virtual bool ConnectServer(const char* ipServer, USHORT portServer);

    const char* SendCommand(const char* command);
    const char* SendMessage(const char* message);
    bool SendAuth(const char* login, const char* password);
  };

}
#endif
