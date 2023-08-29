/*
 * gcc client.c -o client
 *
 *   抽象名前空間を使用したソケットを使用して、client からキー入力したデータを
 *   server で受けてコンソールに表示する。
 *   client を複数立ち上げても、一つの server で受けることができることを確認。
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_NAME         "\0TestSocket"
#define SOCKET_NAME_LENGTH  11

#define SOCKET_SEND_LENGTH  256

int main(int argc, char **argv)
{
    int fd, rc, len;
    char*   msg_buf;
    size_t  msg_len = SOCKET_SEND_LENGTH;
    struct sockaddr_un  adrs;

    // socket の作成
    fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        printf("client socket error\n");
    }
    
    msg_buf = malloc(SOCKET_SEND_LENGTH);
    if (msg_buf == NULL)
    {
        printf("malloc error\n");
    }
    
    adrs.sun_family = AF_UNIX;
    memcpy(adrs.sun_path, SOCKET_NAME, SOCKET_NAME_LENGTH);
    len = sizeof(adrs.sun_family) + SOCKET_NAME_LENGTH;
    
    while(1)
    {
        getline(&msg_buf, &msg_len, stdin);
        rc = sendto(fd, msg_buf, strlen(msg_buf)+1, 0, (struct sockaddr *)&adrs, len);
        if (rc < 0)
        {
            printf("client sendto error: rc=%d, error=%d\n", rc, errno);
        }
        if (msg_buf[0] == 'q')
        {
            break;
        }
    }
    free(msg_buf);
    
    return 0;
}

