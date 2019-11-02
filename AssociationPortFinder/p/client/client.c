#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <net/if.h>

#define DEBUG

#include "associationFinder_lib.h"
#include "client_function.h"

#define TOPORT ServerPort
#define MYPORT MyPort

int main(int argc, char *argv[])
{
#ifdef SPECIALSTRING
	const char* specialStr = argv[argc - 1];
	const int Vargc = argc - 1;  //argc virtuale
#else
	const int Vargc = argc;  //argc virtuale
#endif // !SPECIALSTRING
	int sockfd;
	int MyPort, ServerPort;
	int yes = 1;
	void** (*client_action)(const int sockfd, struct sockaddr * my_addr, struct sockaddr * addr, char* str, void** otherArgs) = genericClientFunction;   //defined in client_function.h
	if (Vargc != 4) {
		fprintf(stderr, "Sender: Client-Usage: %s <hostname> <myport> <server_port>\n", argv[0]);
		exit(1);
	}
	MyPort = strtol(argv[2], NULL, 10);
	ServerPort = strtol(argv[3], NULL, 10);
	if (MyPort <= MINPORTNUM || ServerPort <= MINPORTNUM || MyPort > MAXPORTNUM || ServerPort > MAXPORTNUM)
		fail_errno("Client: invalid port\n");
	/*CREATE CLIENT SOCKET*/	
	struct sockaddr_in localaddr;
	localaddr.sin_family = AF_INET;
	localaddr.sin_port = htons(MYPORT);
	localaddr.sin_addr.s_addr = INADDR_ANY;
	memset(&(localaddr.sin_zero), '\0', 8);
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		fail_errno("Client: socket() error: ");
	debug("Client: socket() sockfd is OK...\n");
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1) {
		close(sockfd);		fail_errno("Client: setsockopt(...) error: ");
	}
	if (bind(sockfd, (struct sockaddr *)&localaddr, sizeof localaddr) == -1) {
		close(sockfd);		fail_errno("Client: bind() error: ");
	}
	debug("Client: bind() sockfd is OK...\n");
	/*CREATE SERVER SOCKET*/
	struct sockaddr_in their_addr;
	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(TOPORT);
	their_addr.sin_addr.s_addr = inet_addr(argv[1]);
	memset(&(their_addr.sin_zero), '\0', 8);
	/*CONNECT TO THE SERVER*/
	if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof their_addr) == -1) {
		close(sockfd);		fail_errno("Client: connect(...) error: ");
	}
	debug("Client: connect() whit %s is OK...\n", argv[1]);
	//client_action(sockfd, (struct sockaddr *)&localaddr, (struct sockaddr *)&their_addr, specialStr, NULL);
	client_action(sockfd, NULL, NULL, NULL, NULL);
	close(sockfd);
	return 0;
}