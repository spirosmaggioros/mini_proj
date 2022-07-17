#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main(){
	char server_message[256] = "Parta malaka ti katalaves";
	int server_socket;
	server_socket = socket(AF_INET , SOCK_STREAM , 0);
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	int binding = bind(server_socket , (struct sockaddr*) &server_address , sizeof(server_address));
	listen(server_socket , 5);
	int client_socket = accept(server_socket , NULL , NULL);
	send(client_socket , server_message , sizeof(server_message) , 0);
	shutdown(server_socket, 0);
}
