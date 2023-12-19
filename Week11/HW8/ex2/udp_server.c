#define _GNU_SOURCE
#include <stdio.h>          
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>

#define	QSIZE	   8		/* size of input queue */
#define	MAXDG	4096		/* max datagram size */
// #define SERV_PORT 5500

typedef struct {
  void		*dg_data;		/* ptr to actual datagram */
  size_t	dg_len;			/* length of datagram */
  struct sockaddr  *dg_sa;	/* ptr to sockaddr{} w/client's address */
  socklen_t	dg_salen;		/* length of sockaddr{} */
} DG;
static DG	dg[QSIZE];			/* queue of datagrams to process */

static int	iget;		/* next one for main loop to process */
static int	iput;		/* next one for signal handler to read into */
static int	nqueue;		/* # on queue for main loop to process */
static socklen_t clilen;/* max length of sockaddr{} */
static int		sockfd;

static void	sig_io(int);

int validate_number(char *str)
{
    while (*str)
    {
        if (!isdigit(*str))
        { // if the character is not a number, return false
            return 0;
        }
        str++; // point to next character
    }
    return 1;
}

int checkIP(char *ip) 
{
    char temp[100];
    strcpy(temp, ip);
    int j = 0;
    for (int i = 0; i < strlen(temp); i++) {
        if (temp[i] != '.') {
            temp[j] = temp[i];
            j++;
        }
    }

    temp[j] = '\0';
    return validate_number(temp);
}

void getHostByIP(char *ip)
{
    struct in_addr targetAddr;
    char temp[40];
    strcpy(temp, ip);
    // Check valid IP address
    if (inet_pton(AF_INET, temp, &(targetAddr.s_addr)) != 1)
    {
        printf("Invalid IP address\n");
        sprintf(ip, "IP address is invalid");
        return;
    }

    struct hostent *target = gethostbyaddr(&targetAddr, sizeof(targetAddr), AF_INET);

    // Check information
    if (target == NULL)
    {
        printf("Not found information\n");
        sprintf(ip, "Not found information");
        return;
    }

    // Print information
    // printf("Official name: %s\n", target->h_name);
    sprintf(ip, "Official name: %s\nAliases name: \n", target->h_name);
    // printf("Alias name: \n");
    for (int i = 0; target->h_aliases[i] != NULL; i++)
    {
        // printf("%s\n", target->h_aliases[i]);
        strcat(ip, target->h_aliases[i]);
        strcat(ip, "\n");
    }
}

int getHostByDomainName(char *name)
{
    name[strcspn(name, "\n")] = '\0';
    struct hostent *host = gethostbyname(name);

    if (host == NULL)
    {
        printf("Invalid domain name\n");
        sprintf(name, "Invalid domain name");
        return 1;
    }

    sprintf(name, "Official IP: %s\nAlias IP: \n", inet_ntoa(*(struct in_addr *)host->h_addr));
    
    printf("Alias IP: \n");
    for (int i = 1; host->h_addr_list[i] != NULL; i++)
    {
        strcat(name, inet_ntoa(*(struct in_addr *)host->h_addr_list[i]));
        strcat(name, "\n");
    }
    return 0;
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("The correct usage is ./server PORT_NUMBER\n");
		return 1;
	}



	int			i;
	const int	on = 1;
	sigset_t	zeromask, newmask, oldmask;
	
	struct sockaddr_in	servaddr, cliaddr;
	
	if ((sockfd=socket(AF_INET, SOCK_DGRAM, 0)) == -1 ){  /* calls socket() */
		perror("socket() error\n");
		return 0;
	}
	
	// bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(atoi(argv[1]));
	
	if(bind(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr))==-1){ /* calls bind() */
		perror("bind() error\n");
		return 0;
	}
		
	clilen = sizeof(cliaddr);
	
	for (i = 0; i < QSIZE; i++) {	/* init queue of buffers */
		dg[i].dg_data = malloc(MAXDG);
		dg[i].dg_sa = malloc(clilen);
		dg[i].dg_salen = clilen;
	}
	iget = iput = nqueue = 0;
	
	/* Signal handlers are established for SIGIO. The socket owner is
	 * set using fcntl and the signal-driven and non-blocking I/O flags are set using ioctl
	 */
	signal(SIGIO, sig_io);
	fcntl(sockfd, F_SETOWN, getpid());
	ioctl(sockfd, FIOASYNC, &on);
	ioctl(sockfd, FIONBIO, &on);
	
	/* Three signal sets are initialized: zeromask (which never changes),
	 * oldmask (which contains the old signal mask when we block SIGIO), and newmask.
	 */
	sigemptyset(&zeromask);		
	sigemptyset(&oldmask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGIO);	/* signal we want to block */
	
	/* Stores the current signal mask of the process in oldmask and then
	 * logically ORs newmask into the current signal mask. This blocks SIGIO
	 * and returns the current signal mask. We need SIGIO blocked when we test
	 * nqueue at the top of the loop
	 */
	sigprocmask(SIG_BLOCK, &newmask, &oldmask);
	
	for ( ; ; ) {
		while (nqueue == 0)
			sigsuspend(&zeromask);	/* wait for datagram to process */

		/* unblock SIGIO by calling sigprocmask to set the signal mask of
		 * the process to the value that was saved earlier (oldmask).
		 * The reply is then sent by sendto.
		 */
		sigprocmask(SIG_SETMASK, &oldmask, NULL);

		sendto(sockfd, dg[iget].dg_data, dg[iget].dg_len, 0,
			   dg[iget].dg_sa, dg[iget].dg_salen);

		if (++iget >= QSIZE)
			iget = 0;

		/* SIGIO is blocked and the value of nqueue is decremented.
		 * We must block the signal while modifying this variable since
		 * it is shared between the main loop and the signal handler.
		 */
		sigprocmask(SIG_BLOCK, &newmask, &oldmask);
		nqueue--;
	}
}

static void sig_io(int signo)
{
	ssize_t		len;
	DG			*ptr;

	for (; ; ) {
		if (nqueue >= QSIZE){
			perror("receive overflow");
			break;
		}

		ptr = &dg[iput];
		ptr->dg_salen = clilen;
		len = recvfrom(sockfd, ptr->dg_data, MAXDG, 0,
					   ptr->dg_sa, &ptr->dg_salen);
		if (len < 0) {
			if (errno == EWOULDBLOCK)
				break;		/* all done; no more queued to read */
			else{
				perror("recvfrom error");
				break;
			}
		}
		
		if (checkIP(ptr->dg_data)) {
			getHostByIP(ptr->dg_data);
		} else {
			getHostByDomainName(ptr->dg_data);
		}

		ptr->dg_len = strlen(ptr->dg_data);

		nqueue++;
		if (++iput >= QSIZE)
			iput = 0;

	}	
}
