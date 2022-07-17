#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include<unistd.h>

int main(int m , char *arg[]){
	int client_socket;
	char str[1024] , str2[1024];
	client_socket = socket(AF_INET , SOCK_STREAM , 0);
	if(client_socket < 0){
		printf("Failed to create a socket");
		return 0;
	}
	struct sockaddr_in client_address;
	client_address.sin_family = AF_INET;
	client_address.sin_addr.s_addr = htonl(arg[1]);
	client_address.sin_port = htons(1200);

	if(connect(client_socket , (struct sockaddr_in *) &client_address , sizeof(client_address)) < 0){
		printf("Failed to connect");
		return 0;
	}
	else{
		printf("Success connecting to the server! " , &arg[1]);
		scanf("%s" , str);
	}
	if(write(client_socket , str , sizeof(str)) < 0){
		printf("Data could not be reached");
	}
	int a;
	do{
		listen(client_socket , 5);
		read(client_socket , str2 , sizeof(str2));
		printf("server message , : " ,str2);
		printf("Client message\n");
		scanf("%s" , str);
		a = strcmp(str2 , "...");
		write(client_socket , str2 , sizeof(str2));
	}while(a != 0);
	shutdown(client_socket , 0);
	return 0;
}
