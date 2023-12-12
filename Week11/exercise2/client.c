#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define SERVER_PORT 5550
#define BUFF_SIZE 1024

enum StatusCode {
    LOGIN_SUCCESS = 0,
    ACCOUNT_BLOCKED = 1,
    TOO_MANY_ATTEMPTS = 2,
    WRONG_CREDENTIALS = 3
};

int main(int argc, char *argv[]){
	
	if (argc < 3) {
		printf("Not enough arguments\n");
		return 1;
	}
	
	int client_sock, userLength, finish = 1;
	char buff[BUFF_SIZE + 1], read_buff[BUFF_SIZE/2-1];
	struct sockaddr_in server_addr; /* server's address information */
	int msg_len, bytes_sent, bytes_received;
	
	//Step 1: Construct socket
	client_sock = socket(AF_INET,SOCK_STREAM,0);
	
	//Step 2: Specify server address
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	
	//Step 3: Request to connect server
	if(connect(client_sock, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) < 0){
		printf("\nError!Can not connect to sever! Client exit imediately! ");
		return 0;
	}
		
	//Step 4: Communicate with server			
	while (1) {
		// Message format: userLength(2B) Username Password
		// Get username and password
		printf("Username: ");
		memset(read_buff, 0, sizeof(read_buff));
		scanf(" %[^\n]", read_buff);
		userLength = strlen(read_buff);
		memset(buff, 0, sizeof(buff));
		buff[0] = (char)((uint8_t)(userLength >> 8)); // High byte of Length
		buff[1] = (char)((uint8_t)(userLength & 0xFF)); // Low byte of Length
		memcpy(buff + 2, read_buff, userLength);

		printf("Password: ");
		memset(read_buff, 0, sizeof(read_buff));
		scanf(" %[^\n]", read_buff);
		memcpy(buff + 2 + userLength, read_buff, strlen(read_buff));

		// Send credentials to server
		bytes_sent = send(client_sock, buff, 2 + userLength + strlen(read_buff), 0);
		if (bytes_sent < 0) {
			perror("\nError: ");
			goto end;
		}

		// Receive result from server
		bytes_received = recv(client_sock, buff, BUFF_SIZE, 0);
		buff[bytes_received] = '\0';
		if (bytes_received < 0) {
			perror("\nError: ");
			goto end;
		} else if (bytes_received == 0) {
			printf("Connection closed.\n");
			goto end;
		}
		
		switch (atoi(buff)) {
			case 0:
				printf("Login success!\n\n");
				finish = 1;
				break;
			case 1:
				printf("This account is blocked.\n\n");
				finish = 1;
				break;
			case 2:
				printf("Too many fail attempts, this account is now blocked.\n\n");
				finish = 1;
				break;
			case 3:
				printf("Wrong account information.\n\n");
				finish = 0;
				break;
			default:
				printf("Error!\n\n");
				finish = 1;
				break;
		}
		memset(buff, 0, sizeof(buff));
		if (finish == 0) continue;
		else break;
	}
	//Step 4: Close socket
	end:
	close(client_sock);
	return 0;
}
