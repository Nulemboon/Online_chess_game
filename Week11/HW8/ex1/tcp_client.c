#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/uio.h>

// #define SERVER_ADDR "127.0.0.1"
// #define SERVER_PORT 12345
#define BUFF_SIZE 1024

int main(int argc, char **argv){
	if (argc != 3) {
		printf("The correct usage is ./client IP_ADDRESS PORT_NUMBER\n");
		return 1;
	}

	int client_sock;
	char buff[2 * BUFF_SIZE + 4];
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
		memset(buff, 0, sizeof(buff));
		printf("\nInsert string to send:");
		fgets(buff, BUFF_SIZE, stdin);		
		msg_len = strlen(buff);
		buff[msg_len - 1] = '\0';
		bytes_sent = send(client_sock, buff, msg_len, 0);
		if(bytes_sent < 0)
			perror("\nError: ");
		else if (msg_len == 1) 
			break;

		//receive reply
		// Receive results from the server using readv
		struct iovec result_iov[3];
		memset(buff, 0, sizeof(buff)); // Clear the buffer

		// Set up iov for receiving the result strings
		result_iov[0].iov_base = buff;     // Alphabet string
		result_iov[0].iov_len = BUFF_SIZE;
		result_iov[1].iov_base = buff + BUFF_SIZE; // Digit string
		result_iov[1].iov_len = BUFF_SIZE;
		result_iov[2].iov_base = buff + 2 * BUFF_SIZE; // Special char count
		result_iov[2].iov_len = sizeof(int);
		bytes_received = readv(client_sock, result_iov, 3);
		// bytes_received = recv(client_sock, buff, BUFF_SIZE, 0);
		if (bytes_received < 0) {
			perror("\nError: ");
			break;
		}
			
		else if (bytes_received == 0) {
			printf("Connection closed.\n");
			break;
		}
				
			
		// buff[bytes_received] = '\0';
		// printf("Reply from server: %s", buff);
		
		if (*(int*)result_iov[2].iov_base > 0) {
			printf("There is %d undefined character\n", *(int *) result_iov[2].iov_base);
		} else {
			printf("Alphabet: %s\nDigit: %s\n", (char *)result_iov[0].iov_base, (char *)result_iov[1].iov_base);
		}
	}
	//send message
	
	//Step 4: Close socket
	close(client_sock);
	return 0;
}
