#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

#define MAX_LINE 1024

typedef struct {
    u_int8_t opcode;
    u_int16_t length;
    char payload[MAX_LINE - 3];
} Message;

Message parseMessage (const char* rcv) {
    Message parsedMessage;
    parsedMessage.opcode = (uint8_t) rcv[0]; // Opcode (1B)
    parsedMessage.length = (uint16_t) ((rcv[1] << 8) | rcv[2]); // Length (2B)
    memcpy(parsedMessage.payload, rcv + 3, parsedMessage.length);
    return parsedMessage;
}

void constructMessage (char *send, uint8_t opcode, uint16_t length, char* payload) {
     // Construct the string message
    send[0] = (char) opcode;
    send[1] = (char)((uint8_t)(length >> 8)); // High byte of Length
    send[2] = (char)((uint8_t)(length & 0xFF)); // Low byte of Length
    memcpy(send + 3, payload, length);
}

int main (int argc, char *argv[]){
	
	// Check for server addr and port arg
    if (argc < 3) {
        perror("Not enough argument\n");
        return 0;
    }
	
	int client_sock;
	char buff[MAX_LINE + 1], file_location[MAX_LINE];
	char file_buffer[MAX_LINE - 3];
	struct sockaddr_in server_addr; /* server's address information */
	int bytes_sent, bytes_received;
	
	//Step 1: Construct socket
	client_sock = socket(AF_INET,SOCK_STREAM,0);
	
	// Initialize file descriptor set for select
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(client_sock, &read_fds);
	
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
	
	int mode, key;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~MENU~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("1. Encode\n");
	printf("2. Decode\n");
	printf("Input others to quit\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	scanf("%d", &mode);
	if (--mode < 0 || mode > 1) return 0; // Quit
	printf("Enter key: ");
	scanf("%d", &key);
	// Validate key
	if (key < 1) {
		printf("Invalid key\n");
		return 0;
	}

	//Construct and send request message
	Message rcv;
	snprintf(file_buffer, sizeof(file_buffer), "%d", key);
	constructMessage(buff, mode, strlen(file_buffer), file_buffer);

	bytes_sent = send(client_sock, buff, 3 + strlen(file_buffer), 0);
	if(bytes_sent < 0)
		perror("\nError: ");

	// Open file to read
	printf("Enter file path: ");
	scanf("%s", file_location);
	FILE *file = fopen(file_location, "r");
	if (file == NULL) {
		perror("Error in opening file");
		close(client_sock);
		return 4;
	}

	// Send file data
	int bytes_read;
    while ((bytes_read = fread(file_buffer, 1, sizeof(file_buffer), file)) >= 0) {
        // construct message to send
		constructMessage(buff, 2, bytes_read, file_buffer);

		// Use select to check for both incoming messages and the ability to send data
        fd_set tmp_fds = read_fds;
        struct timeval timeout;
        timeout.tv_sec = 5; // Adjust the timeout as needed
        timeout.tv_usec = 0;

        int ready = select(client_sock + 1, &tmp_fds, NULL, NULL, &timeout);

        if (ready == -1) {
            perror("Error in select");
            break; // Exit the loop on error
        } else if (ready > 0) {
            // Check if there is any incoming message
            if (FD_ISSET(client_sock, &tmp_fds)) {
                // Receive and process the incoming message
                bytes_received = recv(client_sock, buff, MAX_LINE, 0);
                if (bytes_received < 0) {
                    perror("Error receiving data");
                    break; // Exit the loop on error
                } else if (bytes_received == 0) {
                    printf("Connection closed.\n");
                    break; // Exit the loop if the connection is closed
                }

                buff[bytes_received] = '\0';

                // Check if the received message has opcode 3
                rcv = parseMessage(buff);
                if (rcv.opcode == 3) {
                    printf("Error encountered on server.\n");
                    break;
                }
            }
        }

		int sent_bytes = send(client_sock, buff, bytes_read + 3, 0);
		if (sent_bytes < 0) {
            perror("Error sending data");
            break; // Exit the loop if there's an error
        } else if (sent_bytes != bytes_read + 3) {
            printf("Failed to send the complete buffer\n");
            break; // Exit if the full buffer isn't sent
        }
		if (bytes_read == 0) break; // Finish sending the whole file
		memset(buff, 0, sizeof(buff)); // Reset buffer
    }
    fclose(file); // Close the file after sending
	memset(buff, 0, sizeof(buff));

	// Open the file again to write
	file = fopen(file_location, "w");
	while (1) {
		memset(buff, 0, sizeof(buff));
		bytes_received = recv(client_sock, buff, sizeof(buff), 0);
		if (bytes_received < 0) {
			perror("Error receiving file content");
			break;
		} else if (bytes_received == 0) {
			perror("Connection closed by server.\n");
			break;
		}
		rcv = parseMessage(buff);

		if (rcv.opcode == 3) {
			printf("Error encountered on server.\n");
            break;
		} else if (rcv.opcode < 2) {
			continue;
		}
		if (rcv.length == 0) {
			break; // Exit loop when all file content is received
		}

		size_t chars_written = fwrite(rcv.payload, 1, rcv.length, file);
        if (chars_written != (size_t)rcv.length) {
            perror("Error writing to file");
            break;  // Exit loop if writing to file fails
        }
	}
	fclose(file);
	
	//Step 5: Close socket
	close(client_sock);
	printf("Operation success.");
	return 0;
}
