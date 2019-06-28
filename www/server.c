using namespace std;
#include<iostream>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<cstdio>
//string httpkaesu="HTTP/1.1 200 OK \r\nContent-Type:text/html;charset=utf-8\r\n\r\n<!DOCTYPE html><html><head><title>ネットワークプログラムのwebさいと</title></head><body>ねっとわーくだいすき</body><html>";
void HandleTCPCliant(int sock){
	char ret[256]="HTTP/1.1 200 OK \r\nContent-Type:text/html;charset=utf-8\r\n\r\n<!DOCTYPE html><html><head><title>ネットワークプログラムのwebさいと</title></head><body>ねっとわーくだいすき</body><html>";
	char buf[256];
	int len_r=recv(sock,buf,256,0);
	
	send(sock,ret,strlen(ret),0);
}
int main(int argc,char ** argv){
	int mysock=socket(PF_INET,SOCK_STREAM,0);
	struct sockaddr_in myaddr;
	
	myaddr.sin_family=AF_INET;
	myaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	myaddr.sin_port=htons(80);
	bind(mysock,(struct sockaddr*)&myaddr,sizeof(myaddr));
	listen(mysock,810);//同時810接続
	struct sockaddr_in aiaddr;
	while(-1){
		int clntLen=sizeof(aiaddr);
		int clntsock=accept(mysock,(struct sockaddr*)&aiaddr,&clntLen);
		printf("%s\n",inet_ntoa(aiaddr.sin_addr));
		HandleTCPCliant(clntsock);
		//close(clntsock);
	}
	
	return 0;
}//g++ cliant.c -o cliant.exe
// ./cliant.exe
//\\file01.edu-kct.local\home\k16013wi\desktop\ネットワークぷろぐらみんぐ
/*
終了ステータスとして1,-1
ポートは何番が使えるか
終了ステータスとして負の値はどうなるか

3 3 3 3 2
3 3 3 3 2

40116600
*/