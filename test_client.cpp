#include <iostream>	
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <string> 

int main()
{

	//ソケットの生成
	int sockfd = socket(AF_INET, SOCK_STREAM, 0); //アドレスドメイン, ソケットタイプ, プロトコル0=TCP
	if (sockfd < 0)
	{ //エラー処理

		std::cout << "Error socket:" << std::endl; 
		exit(1);
	}

	//アドレスの生成
	struct sockaddr_in addr;					   
	memset(&addr, 0, sizeof(struct sockaddr_in));  
	addr.sin_family = AF_INET;					   
	addr.sin_port = htons(1234);				   
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

	//ソケット接続要求
	connect(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));

	while (1)
	{
		//データ送信
		char s_str[] = "HelloWorld!"; 
		send(sockfd, s_str, 20, 0);	
		std::cout << s_str << std::endl;

		//データ受信
		char r_str[20];					 
		recv(sockfd, r_str, 20, 0);		 
		std::cout << r_str << std::endl; 
	}

	//ソケットクローズ
	close(sockfd);

	return 0;
}
