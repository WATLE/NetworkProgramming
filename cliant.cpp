#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
#define llint long long int
void DieWithError(string messege)
{
	cerr << messege << endl;
	exit(1);
}
void commun(int sock)
{
	string cmd;

	cout << "0:引き出し　1:預入　2:残高照会 そのた:終了";
	cout << " 何をしますか?";
	cin >> cmd;
	llint hikigaku;
	llint aaa=0;
	llint azugaku;
	switch (cmd[0])
	{
	case '0':
		//引き出し処理
		cout << "いくら" << endl;
		cin >> hikigaku;
		if (hikigaku <= 0){cout << "金額エラー" << endl;}
		hikigaku*=-1;
		if(send(sock,&hikigaku,8,0)!=8){DieWithError("send() missed");}
		break;
	case '1':
		//預入処理
		cout << "いくら" << endl;
		cin >> azugaku;
		if (azugaku <= 0){cout << "金額エラー" << endl;}
		if(send(sock,&azugaku,8,0)!=8){DieWithError("send() missed");}
		break;
	case '2':
		//残高紹介
		
		if(send(sock,&aaa,8,0)!=8){DieWithError("send() missed");}
		break;
	default:
		//エラー
		cerr<<"error"<<endl;
	}
	llint zandaka;
	recv(sock,&zandaka,8,0);
	// 表示処理
	printf("残高は%lld円になりました", zandaka);
}
int prepare_client_socket(char *ipaddr, int port) {
	// ソケット生成
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        DieWithError("socket() failed");
    
	// サーバの情報を設定
    struct sockaddr_in target;
    target.sin_family = AF_INET;
    target.sin_addr.s_addr = inet_addr(ipaddr);
    target.sin_port = htons(port);

	// サーバへ接続
    if (connect(sock, (struct sockaddr*)&target, sizeof(target)) < 0)
        DieWithError("connect() failed");

    return sock;
}
int main(int argc,char **argv)
{
	if (argc < 3)
	{
		DieWithError("usage: ./cliant ip_address port");
	}
	int sock = prepare_client_socket(argv[1], atoi(argv[2]));
	commun(sock);
}
// 10.13.64.26