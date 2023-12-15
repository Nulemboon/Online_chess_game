#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <limits.h>
#include <poll.h>

#define LISTENQ 5
#define BUF_SIZE 1024
#define MAX 256
#define SERV_ADDR "127.0.0.1"

char file_location[256] = "account.txt"; // Account db

typedef struct {
    uint16_t userLength;
    char userid[BUF_SIZE - 1];
    char password[BUF_SIZE - 1]; 
} Message;

Message parseMessage(const char *rcv, int bytes_rcv) {
    Message msg;
    msg.userLength = (uint16_t)((rcv[0] << 8) | rcv[1]); // Length (2B)

    // Ensure that the lengths are within bounds
    if (msg.userLength < BUF_SIZE - 1) {
        // Copy user ID with bounds checking
        memset(msg.userid, 0, sizeof(msg.userid));
        strncpy(msg.userid, rcv + 2, msg.userLength);
        msg.userid[msg.userLength] = '\0';

        // Copy password with bounds checking
        size_t passwordLength = bytes_rcv - 2 - msg.userLength;
        memset(msg.password, 0, sizeof(msg.password));
        strncpy(msg.password, rcv + 2 + msg.userLength, passwordLength);
        msg.password[passwordLength] = '\0';
    } else {
        perror("Error while parsing message: ");
    }

    return msg;
}

typedef struct account {
    char userid[MAX];
    char password[MAX];
    int status;
    int failLogin;
    struct account *next;
} account;

account *head = NULL;

void insertFirst(account *acc) {
    account *p = (account *)malloc(sizeof(account));
    strcpy(p->userid, acc->userid);
    strcpy(p->password, acc->password);
    p->failLogin = 0;
    p->status = acc->status;
    p->next = head;
    head = p;
}

void readUser() {
    account acc;
    FILE *file = fopen(file_location, "r");
    if (file == NULL) {
        printf("Account file not found\n");
    } else {
        while (fscanf(file, "%s %s %d", acc.userid, acc.password, &acc.status) == 3) {
            acc.failLogin = 0;
            insertFirst(&acc);
        }
    }
    fclose(file);
}


void writeUser() {
    FILE *file = fopen(file_location, "w");
    if (file == NULL) {
        printf("Account file not found\n");
    } else {
        account *acc;
        acc = head;
        while (acc != NULL) {
            fprintf(file, "%s %s %d\n", acc->userid, acc->password, acc->status);
            acc = acc->next;  // Move to the next node
        }
    }
    fclose(file);
}


account *findUser(char *id) {
    account *acc;
    acc = head;
    while (acc != NULL) {
        if (strcmp(id, acc->userid) == 0 && strcmp(acc->userid, id) == 0) {
            return acc;  // User found
        }
        acc = acc->next;
    }
    return NULL;  // User not found
}


void login(int connfd, char *userid, char *password) {
    account *acc;
    char buff[BUF_SIZE + 1];

    // Find user with that id
    acc = findUser(userid);
    if (acc != NULL) {
        // Check status
        if (acc->status == 0) { 
            // Blocked
            strcpy(buff, "1"); // Message for blocked acc
        } else { 
            // Check password
            if (strcmp(password, acc->password) != 0 || strcmp(acc->password, password) != 0) {
                acc->failLogin++;
                printf("%d\n", acc->failLogin);
                // Change status to blocked (0) after 5 fail attempts
                if (acc->failLogin == 5) {
                    acc->status = 0;
                    acc->failLogin = 0;
                    writeUser(); // Change status in account.txt
                    strcpy(buff, "2"); // Message for too many attempts
                } else {
                    strcpy(buff, "3"); // Message for wrong credentials
                }
            } else {
                // Login success
                acc->failLogin = 0;  // Reset failed login attempts
                strcpy(buff, "0"); // Message for successful login
            }
        }
    } else {
        strcpy(buff, "3"); // Message for wrong credentials
    }
    send(connfd, buff, strlen(buff), 0);
}



void usage(char *program) {
    fprintf(stderr, "usage: %s port\n", program);
}

int main(int argc, char **argv)
{
        int nready, i, maxi, port, listenfd, connfd, sockfd;
        socklen_t clilen;
        struct sockaddr_in cliaddr, servaddr;
        char buf[BUF_SIZE];
        const int OPEN_MAX = sysconf(_SC_OPEN_MAX);  // maximum number of opened files 
        struct pollfd *clients = (struct pollfd *)malloc(OPEN_MAX * sizeof(struct pollfd));
        ssize_t n;
        int INFTIM = -1;
        readUser(); // Init user link list
        
        if (argc != 2) {
                usage(argv[0]);
                return EXIT_FAILURE;
        }

        // Get TCP port number 
        port = atoi(argv[1]);
        if (port <= 0 || port > 65535) {
                fprintf(stderr, "Invalid port number %d\n", port);
                return EXIT_FAILURE;
        }

        // Create listen socket 
        if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                fprintf(stderr, "Error: socket\n");
                return EXIT_FAILURE;
        } else {
                printf("Create listen socket %d\n", listenfd);
        }

        // Initialize server socket address
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr(SERV_ADDR);
        servaddr.sin_port = htons(port);

        // Bind socket to an address
        if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
                fprintf(stderr, "Error: bind\n");
                return EXIT_FAILURE;
        }

        // Listen
        if (listen(listenfd, LISTENQ) < 0) {
                fprintf(stderr, "Error: listen\n");
                return EXIT_FAILURE;
        }

        clients[0].fd = listenfd;
        clients[0].events = POLLRDNORM;

        for (i = 1; i < OPEN_MAX; i++) {
                clients[i].fd = -1;     // -1 indicates available entry
        }
        maxi = 0;       // max index into clients[] array

        while (1) {
                nready = poll(clients, maxi + 1, INFTIM);

                if (nready <= 0) {
                        continue;
                } 

                // Check new connection
                if (clients[0].revents & POLLRDNORM) {
                        clilen = sizeof(cliaddr);
                        if ((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen)) < 0) {
                                fprintf(stderr, "Error: accept\n");
                                return EXIT_FAILURE;
                        }

                        printf("Accept socket %d (%s : %hu)\n", 
                               connfd, 
                               inet_ntoa(cliaddr.sin_addr),
                               ntohs(cliaddr.sin_port));

                        // Save client socket into clients array
                        for (i = 0; i < OPEN_MAX; i++) {
                                if (clients[i].fd < 0) {
                                        clients[i].fd = connfd;
                                        break;
                                }
                        }

                        // No enough space in clients array
                        if (i == OPEN_MAX) {
                                fprintf(stderr, "Error: too many clients\n");
                                close(connfd);
                        }

                        clients[i].events = POLLRDNORM;

                        if (i > maxi) {
                                maxi = i;
                        }

                        // No more readable file descriptors
                        if (--nready <= 0) {
                                continue;
                        }
                } 

                // Check all clients to read data
                for (i = 1; i <= maxi; i++) {
                        if ((sockfd = clients[i].fd) < 0) {
                                continue;
                        }

                        // If the client is readable or errors occur
                        if (clients[i].revents & (POLLRDNORM | POLLERR)) {
                                n = read(sockfd, buf, BUF_SIZE);
                                
                                if (n < 0) {
                                        fprintf(stderr, "Error: read from socket %d\n", sockfd);
                                        close(sockfd);
                                        clients[i].fd = -1;
                                } else if (n == 0) {    // connection closed by client
                                        printf("Close socket %d\n", sockfd);
                                        close(sockfd);
                                        clients[i].fd = -1;                                        
                                } else {
                                        Message rcv = parseMessage(buf, n);
                                        login(sockfd, rcv.userid, rcv.password);
                                }

                                // No more readable file descriptors
                                if (--nready <= 0) {
                                        break;
                                }
                        }
                }

        }
        
        free(clients);
        // Free memory allocated for the linked list
        while (head != NULL) {
            account *temp = head;
            head = head->next;
            free(temp);
        }
        close(listenfd);
        return 0;
}