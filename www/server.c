using namespace std;
#include<iostream>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<cstdio>
#include<regex.h>
void HandleTCPCliant(int sock){
	regex_t regBuf;
	regmatch_t regMatch[1];
	char ret[256]="HTTP/1.1 200 OK \r\nContent-Type:text/html;charset=utf-8\r\n\r\n<!DOCTYPE html><html><head><title>ネットワークプログラムのwebさいと</title></head><body>ねっとわーくだいすき</body><html>";
	char buf[256];
	char buf2[256];
	int len_r;
	const char * pattern="GET[^\\n]+HTTP";
	if(regcomp(&regBuf,pattern,REG_EXTNDED|REG_NEWLINE)!=0){cerr<<"regcomp miss"<<endl;exit(0);}
	char result[100];
	result[0]='\0';
	
	while(len_r=recv(sock,buf2,256,0)>0){
		//なにかする
		buf2[len_r]='\0';
		sprintf(buf,"%s",buf2);
		//\n\r\n\rを検出する
		if(regexec(&regBuf,buf,regMatch,0)!=0){
			int startIndex=regMatch[0].rm_so;
			int endIndex=regMatch[0].rm_eo;
			if(endIndex-startIndex-9<0){cerr<<"nanika miss"<<endl;exit(0);}
			strncpy(result,buf+startIndex+4,endIndex-startIndex-9);
		}
	}
	cout<<result<<endl;
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
}
//g++ cliant.c -o cliant.exe
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