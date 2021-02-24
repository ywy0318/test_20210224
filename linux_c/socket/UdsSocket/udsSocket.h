#ifndef __UDSSOCKET_H_
#define __UDSSOCKET_H_
 
#include <sys/socket.h>
#include <sys/un.h>
 
int udsBind(const char* _path, int _len);
int udsSendMessage(int _socketFd, char* _data, int _len, const char * _destAddr);
int udsRecv(int _socketFd, char *sBuf);
 
 
#endif //__UDSSOCKET_H_