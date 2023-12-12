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

#define SERVER_ADDR "127.0.0.1"
#define MAX_LINE 1024
#define TRUE             1
#define FALSE            0

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

void caesar (char* text, int shift); // Caesar algorithm
void sendError (int connfd); // Send error to client

int main (int argc, char *argv[]) {

    // Check for server port arg
    if (argc < 2) {
        perror("Not enough argument\n");
        return 0;
    }

    int    i, len, rc, on = 1;
    int    listen_sd, max_sd, new_sd;
    int    desc_ready, end_server = FALSE;
    int    close_conn;
    char   buffer[MAX_LINE + 1];
    struct sockaddr_in   addr;
    struct timeval       timeout;
    fd_set        master_set, working_set;

    listen_sd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sd < 0)
    {
       perror("socket() failed");
       exit(0);
    }

    /*************************************************************/
    /* Set socket to be nonblocking. All of the sockets for    */
    /* the incoming connections will also be nonblocking since  */
    /* they will inherit that state from the listening socket.   */
    /*************************************************************/
    rc = ioctl(listen_sd, FIONBIO, (char *)&on);
    if (rc < 0)
    {
       perror("ioctl() failed");
       close(listen_sd);
       exit(0);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    addr.sin_port        = htons(atoi(argv[1]));
    rc = bind(listen_sd, (struct sockaddr *)&addr, sizeof(addr));
    if (rc < 0)
    {
       perror("bind() failed");
       close(listen_sd);
       exit(0);
    }

    rc = listen(listen_sd, 32);
    if (rc < 0)
    {
       perror("listen() failed");
       close(listen_sd);
       exit(0);
    }

    /*************************************************************/
    /* Initialize the master fd_set                              */
    /*************************************************************/
    FD_ZERO(&master_set);
    max_sd = listen_sd;
    FD_SET(listen_sd, &master_set);

    /*************************************************************/
    /* Initialize the timeval struct to 3 minutes.  If no        */
    /* activity after 3 minutes this program will end.           */
    /*************************************************************/
    timeout.tv_sec  = 3 * 60;
    timeout.tv_usec = 0;

    /*************************************************************/
    /* Loop waiting for incoming connects or for incoming data   */
    /* on any of the connected sockets.                          */
    /*************************************************************/
    do {
       memcpy(&working_set, &master_set, sizeof(master_set));

       /**********************************************************/
       /* Call select() and wait 3 minutes for it to complete.   */
       /**********************************************************/
       printf("Waiting on select()...\n");
       rc = select(max_sd + 1, &working_set, NULL, NULL, &timeout);

       if (rc < 0)
       {
          perror("  select() failed");
          break;
       }

       /**********************************************************/
       /* Check to see if the 3 minute time out expired.         */
       /**********************************************************/
       if (rc == 0)
       {
          printf("  select() timed out.  End program.\n");
          break;
       }

       desc_ready = rc;
       for (i=0; i <= max_sd  &&  desc_ready > 0; ++i)
       {
          if (FD_ISSET(i, &working_set))
          {
             desc_ready -= 1;

             /****************************************************/
             /* Check to see if this is the listening socket     */
             /****************************************************/
             if (i == listen_sd)
             {
                printf("Listening socket is readable\n");
                do
                {
                   /**********************************************/
                   /* Accept each incoming connection.  If       */
                   /* accept fails with EWOULDBLOCK, then we     */
                   /* have accepted all of them.  Any other      */
                   /* failure on accept will cause us to end the */
                   /* server.                                    */
                   /**********************************************/
                   new_sd = accept(listen_sd, NULL, NULL);
                   if (new_sd < 0)
                   {
                      if (errno != EWOULDBLOCK)
                      {
                         perror("  accept() failed");
                         end_server = TRUE;
                      }
                      break;
                   }

                   printf("  New incoming connection - %d\n", new_sd);
                   FD_SET(new_sd, &master_set);
                   if (new_sd > max_sd)
                      max_sd = new_sd;

                   } while (new_sd != -1);
             }

             /****************************************************/
             /* This is not the listening socket, therefore an   */
             /* existing connection must be readable             */
             /****************************************************/
             else
             {
                printf("  Descriptor %d is readable\n", i);
                close_conn = FALSE;
                /*************************************************/
                /* Receive all incoming data on this socket      */
                /* before we loop back and call select again.    */
                /*************************************************/
                do {

                    /**********************************************/
                    /* Receive data on this connection until the  */
                    /* recv fails with EWOULDBLOCK.  If any other */
                    /* failure occurs, we will close the          */
                    /* connection.                                */
                    /**********************************************/
                    char buffer[MAX_LINE + 1], file_buffer[MAX_LINE - 3];
                    int rc, key;
                    uint8_t mode = 4;

                    rc = recv(i, buffer, sizeof(buffer), 0);
                    
                    if (rc < 0) {
                        if (errno != EWOULDBLOCK)
                        {
                            perror("  recv() failed");
                        }
                        sendError(i);
                        close_conn = TRUE;
                        break;
                    }

                    if (rc == 0) {
                    printf("  Connection closed\n");
                    close_conn = TRUE;
                    break;
                    }

                    /**********************************************/
                    /* Data was received                          */
                    /**********************************************/
                    Message req = parseMessage(buffer);
                    Message snd;
                    mode = req.opcode;
                    key = atoi(req.payload);

                    if (mode > 2) {
                        // No instruction of encode/decode
                        sendError(i);
                        close_conn = FALSE;
                        break;
                    }

                    // Open the temporary file
                    char file_location[256];
                    snprintf(file_location, sizeof(file_location), "Received/%d", i);
                    FILE *file = fopen(file_location, "w");

                    if (file == NULL) {
                        perror("Error in opening file for writing");
                        sendError(i);
                        break;
                    }

                    while (TRUE) {
                        rc = recv(i, buffer, sizeof(buffer), 0);
                        if (rc < 0) {
                            perror("Error receiving file content.\n");
                            sendError(i);
                            goto end;
                        } else if (rc == 0) {
                            perror("Connection closed by client.\n");
                            goto end;
                        }

                        // Encode/Decode the data
                        req = parseMessage(buffer);
                        if (req.opcode != 2) {
                            perror("Wrong opcode for data.");
                            sendError(i);
                            goto end;
                        }
                        if (req.length == 0) {
                            break; // Exit loop when all file content is received
                        }
                        caesar(req.payload, mode==0?key:-key);

                        // Write to file
                        size_t chars_written = fwrite(req.payload, 1, req.length, file);
                        if (chars_written != (size_t) req.length) {
                            perror("Error writing to file");
                            sendError(i);
                            goto end;
                        }
                    }
                    fclose(file);

                    // Open the file again to read and reply
                    file = fopen(file_location, "r");
                    int chars_read;
                    while ((chars_read = fread(file_buffer, 1, sizeof(file_buffer), file)) >= 0) {
                        // Construct message to send
                        memset(buffer, 0, sizeof(buffer)); // Reset buffer
                        constructMessage(buffer, 2, chars_read, file_buffer);

                        int sent_chars = send(i, buffer, chars_read + 3, 0);
                        if (sent_chars < 0) {
                            perror("Error sending data");
                            sendError(i);
                            break; // Exit the loop if there's an error
                        } else if (sent_chars != chars_read + 3) {
                            printf("Failed to send the complete buffer\n");
                            sendError(i);
                            break; // Exit if the full buffer isn't sent
                        }
                        if (chars_read == 0) break; // Finish sending the whole file
                    
                    }
                    end:
                    fclose(file); // Close the file after sending
                    remove(file_location); // Delete file after finishing

                    close_conn = TRUE;
                    break;

                } while (TRUE);

                if (close_conn)
                {
                   close(i);
                   FD_CLR(i, &master_set);
                   if (i == max_sd)
                   {
                      while (FD_ISSET(max_sd, &master_set) == FALSE)
                         max_sd -= 1;
                   }
                }
             } /* End of existing connection is readable */
          } /* End of if (FD_ISSET(i, &working_set)) */
       } /* End of loop through selectable descriptors */

    } while (end_server == FALSE);

    /*************************************************************/
    /* Clean up all of the sockets that are open                  */
    /*************************************************************/
    for (i=0; i <= max_sd; ++i)
    {
       if (FD_ISSET(i, &master_set))
          close(i);
    }
    return 0;
}

void caesar(char* text, int shift) {
    // Encrypt: shift > 0
    // Decrypt: shift < 0
    for (size_t i = 0; i < strlen(text); i++) {
        int adjustedValue = ((int)text[i] - 32 + shift) % 95;
        
        // Ensure the adjustedValue is non-negative
        if (adjustedValue < 0) {
            adjustedValue += 95;  // Adding 95 to make it non-negative
        }

        text[i] = (char)(adjustedValue + 32);
    }
}


void sendError(int connfd) {
    char buffer[6];
    constructMessage(buffer, 3, 0, "\0");
    send(connfd, buffer, 5, 0);
}