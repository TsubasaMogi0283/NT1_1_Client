#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <cassert>
#include <iostream>

#pragma comment(lib,"WSock32.lib")

int main() {

	//基本的にはサーバー側と同じだけど
	//bind、listenはやらないよ

	WSADATA wsaData;

	//Winsockの初期化
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
		//初期化エラー
		std::cout << "WinSockの初期化に失敗しました" << std::endl;
		return 1;
	}



	unsigned short uport= 8000;
	std::cout << "ポート番号を入力してください" << std::endl;
	std::cin >> uport;





	// サーバ名またはサーバのIPアドレスを入力
	char sizeServer[1024] = {};
	std::cout<<"IPアドレス -->";
	std::cin >> sizeServer;
	fflush(stdin);



	//socket(アドレスファミリ,ソケットタイプ,プロトタイプ)
	//失敗するとINVALID_SOCKET
	// 
	//アドレスファミリ...ネットワークのアドレスの種類を表す
	//ソケットタイプ...SOCK_STREAMとSOCK_DREAMの2つがある
	//SOCK_STREAM...信頼性が高いTCP通信
	//SOCK_DREAM...信頼性が高いTCP通信

	//プロトコル...基本的に0。デフォルトのプロトコルが使われる
	//ソケットの作成
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	assert(s != INVALID_SOCKET);
	std::cout << "ソケット生成に成功しました" << std::endl;


	

	//サーバーを名前で取得する
	HOSTENT* lpHost;
	unsigned int addr=0u;
	lpHost = gethostbyname(sizeServer);
	if (lpHost == NULL) {
		/* サーバーをIPアドレスで取得する */
		addr = inet_addr(sizeServer);
		lpHost = gethostbyaddr((char*)&addr, 4, AF_INET);
	}

	//クライアントソケットをサーバーに接続
	SOCKADDR_IN saddr;
	memset(&saddr, 0, sizeof(SOCKADDR_IN));
	saddr.sin_family = lpHost->h_addrtype;
	saddr.sin_port = htons(uport);
	saddr.sin_addr.s_addr = *((u_long*)lpHost->h_addr);


	if (connect(s, (SOCKADDR*)&saddr, sizeof(saddr)) == SOCKET_ERROR) {
		std::cout << "サーバーと接続できませんでした" << std::endl;
		//ソケットを閉じる
		closesocket(s);
		return 1;
	}





	//接続後のクライアント側との文字列やりとり
	//accept関数の返り値はSOCKET変数「s」に格納
	while (1) {
		int nRcv;
		char sizeBuffer[1024] = {};

		//接続後の処理(データ送信)
		//recv(acceptの返り値,受信文字列ポインタ,受信文字列の長さ,受信フラグ)
		std::cout << "送信-->" << sizeBuffer;
		std::cin >> sizeBuffer;
		fflush(stdin);

		send(s, sizeBuffer, (int)strlen(sizeBuffer), 0);

		//recv(acceptの返り値,受信文字列ポインタ,受信文字列の長さ,受信フラグ)
		nRcv = recv(s, sizeBuffer, sizeof(sizeBuffer) - 1, 0);
		sizeBuffer[nRcv] = '\0';
		std::cout << "受信-->"<< sizeBuffer << std::endl;;



	}

	//ソケットを閉じる
	closesocket(s);

	//Winsockの終了
	WSACleanup();

	return 0;


}
