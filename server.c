/*
 * gcc server.c -o server
 *
 *   抽象名前空間を使用したソケットを使用して、client からキー入力したデータを
 *   server で受けてコンソールに表示する。
 *   client を複数立ち上げても、一つの server で受けることができることを確認。
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_NAME         "\0TestSocket"
#define SOCKET_NAME_LENGTH  11

#define SOCKET_RECV_LENGTH  256

int main(int argc, char **argv)
{
    int fd, rc, len;
    char*   msg_buf;
    size_t  msg_len = SOCKET_RECV_LENGTH;
    struct sockaddr_un  adrs;
    
    // socket の作成
    fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        printf("server socket error\n");
    }
    
    msg_buf = malloc(SOCKET_RECV_LENGTH);
    if (msg_buf == NULL)
    {
        printf("malloc error\n");
    }
    
    adrs.sun_family = AF_UNIX;
    memcpy(adrs.sun_path, SOCKET_NAME, SOCKET_NAME_LENGTH);
    len = sizeof(adrs.sun_family) + SOCKET_NAME_LENGTH;

    rc = bind(fd, (struct sockaddr *)&adrs, len);
    if (rc < 0)
    {
        printf("server bind error\n");
    }
    
    while(1)
    {
        rc = recv(fd, msg_buf, SOCKET_RECV_LENGTH, 0);
        if (rc < 0)
        {
            printf("server recv error\n");
        }
        else if (rc == 0)
        {
            printf("server close\n");
        }
        else
        {
            printf("server recv : %s\n", msg_buf);
        }
    }
    free(msg_buf);
    
    return 0;
}
