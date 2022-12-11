#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

int main()
{
    //1.创建socket，用于和服务端通信
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    //2.向服务端发起请求连接
    struct sockaddr_in serv_addr;//首先要指定一个服务端的ip地址+端口，表明是向哪个服务端发起请求
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//注意，这里是服务端的ip和端口
    serv_addr.sin_port = htons(8899);
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    //3.向服务端发送消息
    char send_buf[256] = "zhangsan";
    char recv_buf[512];
    write(sock,send_buf,sizeof(send_buf));

    //4.接收服务端发来的消息
    int len = read(sock,recv_buf,sizeof(recv_buf)-1);
    recv_buf[len] = '\0';
    printf("收到服务端的返回：%s\n",recv_buf);
    
    //5.关闭socket 
    close(sock);
    return 0; 

}
