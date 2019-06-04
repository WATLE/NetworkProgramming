using namespace std;
#include<iostream>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<cstdio>
void HandleTCPCliant(int sock){
	char buf[256];
	int len_r=recv(sock,buf,256,0);
	buf[len_r]='\0';
	cout<<buf<<endl;
	
	for(int i=0;i<len_r/2;i++){
		swap(buf[i],buf[len_r-1-i]);
	}
	send(sock,buf,strlen(buf),0);
}
int main(int argc,char ** argv){
	int mysock=socket(PF_INET,SOCK_STREAM,0);
	struct sockaddr_in myaddr;
	
	myaddr.sin_family=AF_INET;
	myaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	myaddr.sin_port=htons(10001);
	bind(mysock,(struct sockaddr*)&myaddr,sizeof(myaddr));
	listen(mysock,810);//同時810接続
	struct sockaddr_in aiaddr;
	while(-1){
		int clntLen=sizeof(aiaddr);
		int clntsock=accept(mysock,(struct sockaddr*)&aiaddr,&clntLen);
		printf("%s\n",inet_ntoa(aiaddr.sin_addr));
		HandleTCPCliant(clntsock);
	}
	
	return 0;
}//g++ cliant.c -o cliant.exe
// ./cliant.exe
//\\file01.edu-kct.local\home\k16013wi\desktop\ネットワークぷろぐらみんぐ
/*
終了ステータスとして1,-1
ポートは何番が使えるか
終了ステータスとして負の値はどうなるか

*/