#include <iostream>	    
#include <sys/socket.h> 
#include <sys/types.h>	
#include <arpa/inet.h>	
#include <unistd.h>
#include <cstring>
#include <string>
#include <stdio.h>
#include <unistd.h>

int main()
{

	//ソケットの生成
	int sockfd = socket(AF_INET, SOCK_STREAM, 0); //アドレスドメイン, ソケットタイプ, プロトコル
	if (sockfd < 0)
	{ //エラー処理

		std::cout << "Error socket:" << std::endl;
		exit(1);
	}

	//アドレスの生成
	struct sockaddr_in addr;					   //接続先の情報用の構造体(ipv4)
	memset(&addr, 0, sizeof(struct sockaddr_in));  
	addr.sin_family = AF_INET;					   
	addr.sin_port = htons(50000);				   
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

	//ソケット登録
	if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{ //ソケット, アドレスポインタ, アドレスサイズ //エラー処理
		std::cout << "Error bind:" << std::endl;
		exit(1);																 
	}

	//受信待ち
	if (listen(sockfd, SOMAXCONN) < 0)
	{ 
		std::cout << "Error listen:" << std::endl;
		close(sockfd);
		exit(1);
	}

	//接続待ち
	struct sockaddr_in get_addr;																		
	socklen_t len = sizeof(struct sockaddr_in);											
	int connect = accept(sockfd, (struct sockaddr *)&get_addr, &len);

	if (connect < 0)
	{
		std::cout << "Error accept:" << std::endl; 
		exit(1);
	}
	while (1)
	{
		//受信
		char str[20];
		recv(connect, str, 20, 0);
		std::cout << str << std::endl;

		//スリープ
		sleep(3);

		//送信
		send(connect, str, 20, 0);
		std::cout << str << std::endl;
	}
	//ソケットクローズ
	close(connect);
	close(sockfd);

	return 0;
}
