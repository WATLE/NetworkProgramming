using namespace std;
#include<iostream>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<cstdio>
void commun(int sock){
	char message[500]="test test";
	char buf[256];
	send(sock,message,strlen(message),0);
	//送信完了
	int len_r=recv(sock,buf,256,0);
	buf[len_r]='\0';
	cout<<buf<<endl;
	//受信完了
	//printf("%s\n",buf);
}
int main(int argc,char ** argv){
	int sock=socket(PF_INET,SOCK_STREAM,0);
	struct sockaddr_in target;
	
	target.sin_family=AF_INET;
	target.sin_addr.s_addr=inet_addr("10.13.64.20");
	target.sin_port=htons(10001);
	//サーバーの構造体を作成している
	connect(sock,(struct sockaddr*)&target,sizeof(target));
	commun(sock);
	//cout<<sock<<endl;
	close(sock);
	
	//bind(terget,(struct terget*)&terget,sizeof(terget));
	//listen(terget,5);
	
	
	
	return 0;
}//g++ cliant.c -o cliant.exe
// ./cliant.exe
//\\file01.edu-kct.local\home\k16013wi\desktop\ネットワークぷろぐらみんぐ
/*
終了ステータスとして1,-1
ポートは何番が使えるか
終了ステータスとして負の値はどうなるか

*/