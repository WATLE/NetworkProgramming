#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;
#define llint long long int
const int BUF_SIZE = 1024;
void DieWithError(string messege)
{cerr << messege << endl;exit(1);}

string read_until_delim(int sock, char dolimiter)
{
	string ans;
	static char buf[BUF_SIZE];
    int len_r = 0;
    int index_letter = 0;
    while (-1)
    {
		if(index_letter>=BUF_SIZE){
			printf("too long recieve");
            return string();
		}
        if ((len_r = recv(sock, buf + index_letter, 1, 0)) <= 0)
        {
            printf("接続が切れました");
            return string();
        }
		
        if (buf[index_letter] == dolimiter){break;}
        else{index_letter++;}
		ans.push_back(buf[index_letter]);
    }
    return ans;
}
llint nowbalance;
llint get_current_balance(){return nowbalance;}
void set_current_balance(llint new_balance){nowbalance=new_balance;return;}

// 待ち受け用ソケットの生成
int prepare_server_socket(int port)
{
    // ソケット生成
    int servSock = socket(PF_INET, SOCK_STREAM, 0);
    if (servSock < 0)
        DieWithError("socket() failed");

    // サーバの情報を設定
    struct sockaddr_in servAddress;
    servAddress.sin_family = AF_INET;
    servAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddress.sin_port = htons(port);

    // ソケットにサーバの情報を登録
    bind(servSock, (struct sockaddr *)&servAddress, sizeof(servAddress));

    return servSock;
}

int commun(int sock){
    char buf[BUF_SIZE];                  // 通信用バッファ
    llint balance = get_current_balance(); // 預金残高
    /*
    // 区切り文字が出るまでソケットから受信→預け入れ金額をプラス
    string azuke=read_until_delim(sock, '_');
    balance += std::stoll(azuke);

    // 区切り文字が出るまでソケットから受信→引き出し金額をマイナス
    string hiki=read_until_delim(sock, '_');
    balance -= stol(hiki);
*/

    llint kingaku;
    recv(sock,&kingaku,8,0);

    // データベースの預金残高を更新
    balance+=kingaku;
    set_current_balance(balance);
    if(send(sock,&balance,8,0)!=8){DieWithError("send() missed");}
    // クライアントへ残高を送信
    
}
int main(int argc, char *argv[])
{
	nowbalance=10000;
    struct sockaddr_in cliantAddress;
    int szClientAddr;
    int clisock;

    int servSock = prepare_server_socket(1001);
    listen(servSock, 5);
     while (1)
    {
        szClientAddr = sizeof(cliantAddress);
        // 接続要求受け入れ
        clisock = accept(servSock, (struct sockaddr *)&cliantAddress,  &szClientAddr);

        // クライアントとの通信
        commun(clisock);

        // 通信終了
        close(clisock);
    }

    // 待ち受け用ソケットを閉じる
    close(servSock);
    return 0;
}