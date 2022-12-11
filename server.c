#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

int main()
{
  //1.创建一个socket文件，也就是打开一个网络通讯端口,类型是IPV4（AF_INET）+TCP（SOCK_STREAM）
  int serv_sock = socket(AF_INET, SOCK_STREAM,0);

  //2.绑定服务器ip和端口到这个socket
  struct sockaddr_in serv_addr;//这里因为是ipv4，使用的结构体是ipv4的地址类型sockaddr_in
  memset(&serv_addr, 0, sizeof(serv_addr));//先清空一下初始的值，写上地址和端口号，可以用bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//本机ip环回地址，这里还可以使用inet_pton函数进行地址转换
  serv_addr.sin_port = htons(8899);//随意选了一个端口8899
  bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

  //3.将socket设置为监听状态
  listen(serv_sock,128);//设置最大连接数为128

  //4.准备接收客户端的请求连接,这里的步骤可以重复进行，接收多个客户端的请求
  while(1){
    //接收客户端的请求连接后，返回一个新的socket（clnt_sock）用于和对应的客户端进行通信
    struct sockaddr_in clnt_addr;//作为一个传出参数
    socklen_t clnt_addr_size = sizeof(clnt_addr);//作为一个传入+传出参数
    int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

    //5.读取客户端发送来的数据
    char recv_buf[256];
    char send_buf[512]="hello ";
    int len = read(clnt_sock,recv_buf,sizeof(recv_buf)-1);
    recv_buf[len] = '\0';//字符串以“\0”结尾
 //6.打印出客户端发来的消息
    printf("客户端发来的：%s\n",recv_buf);

    //7.加上hello处理后返回给客户端
    strcpy(send_buf+strlen("hello "),recv_buf);//注意这里不能用sizeof，要用strlen，不然包含了‘\0’，后面的jingjing就打印不出来了。
    write(clnt_sock,send_buf,sizeof(send_buf));

    //8.关闭客户端连接
    close(clnt_sock);
    break;

  }
  //9.关闭服务端监听的socket
  close(serv_sock);
  return 0;

}
