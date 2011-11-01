#include <Mail.h>

using namespace ws;

char data1[] = "HELO ya.ru\r\n";
char data2[] = "MAIL FROM:<wmp.bot@mail.ru>\r\n";
char data3[] = "RCPT TO:<wmp.bot@mail.ru>\r\n";
char data4[] = "DATA\r\n";
char data5[] = "Subject:hello\r\n";
char data6[] = "message\r\n";
char data7[] = "\r\n.\r\n";
char data8[] = "QUIT\r\n";

int CALLBACK WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
  SMTPClient client;
  client.ConnectServer("smtp.mail.ru", 25);
  const char* otv = client.RecvLog();
  otv = client.SendAndRecvCommand(data1);
  client.SendAuth("wmp.bot@mail.ru", "rjkjdhfn");
  otv = client.SendAndRecvCommand(data2);
  otv = client.SendAndRecvCommand(data3);
  otv = client.SendAndRecvCommand(data4);
  client.SendCommand(data5);
  client.SendCommand(data6);
  client.SendCommand(data7);
  client.SendCommand(data8);

  return 0;
}