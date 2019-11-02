#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>

#define DEBUG

#include "associationFinder_lib.h"
#include "server_function.h"

void init_variables(int, char **, bool *, int *, int *, int *);

void sigchld_handler(int s)
{
	// waitpid() might overwrite errno, so we save and restore it:
	int saved_errno = errno;
	while (waitpid(-1, NULL, WNOHANG) > 0);
	errno = saved_errno;
}

int main(int argc, char **argv)	//server serverMode MinPortNum MaxPortNum backlog [new_stdout new_stdin funzione_da_eseguire messaggio] ... argv[argc] = specialString if defined
{
#ifdef SPECIALSTRING
	const char* specialStr = argv[argc - 1];
	const int Vargc = argc - 1;  //argc virtuale
#else
	const int Vargc = argc;  //argc virtuale
#endif // !SPECIALSTRING
	if (Vargc < 4) {
		fprintf(stderr, "%s incorrect syntax. Use: %s serverMode{0,1} MinPortNum MaxPortNum\n", argv[0], argv[0]);		return -1;
	}
	bool serverMood;
	void** (*server_action)(const int sockfd, struct sockaddr * my_addr, struct sockaddr * addr, char* str, void** otherArgs) = genricServerFuncion;      //defined in server_function.h
	int MinPortNum, MaxPortNum, backlog;
	init_variables(Vargc, argv, &serverMood, &MinPortNum, &MaxPortNum, &backlog);
	int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
	int yes = 1;
	struct addrinfo hints, *servinfo = NULL;
	struct sockaddr_storage their_addr; // connector's address information
	socklen_t sin_size;
	struct sigaction sa;
	char s[INET6_ADDRSTRLEN];
	int rv;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // use my IP
	//cerca una porta disponibile tra il range passato per argomento
	for (int currPort = MinPortNum; currPort < MaxPortNum; ++currPort)
	{		
		freeaddrinfo(servinfo);
		char port_number_as_str[6];
		sprintf(port_number_as_str, "%d", currPort);
		if ((rv = getaddrinfo(NULL, port_number_as_str, &hints, &servinfo)) != 0) {
			debug("Server: getaddrinfo(...) error: %s\n", gai_strerror(rv));			continue;
		}
		if ((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1) {
			debug("server: socket(...) error: %s\n", strerror(errno));			continue;
		}
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1) {
			close(sockfd);		debug("Server: setsockopt(...) error: %s\n", strerror(errno));		continue;
		}
		if (bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
			close(sockfd);			debug("server: bind(..) error: %s\n", strerror(errno));			continue;
		}
		break;
	}

	if (listen(sockfd, backlog) == -1)
		fail_errno("Server: listen(...) error: ");

	sa.sa_handler = sigchld_handler; // reap all dead processes
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1)
		fail_errno("Server: sigaction(...) error: ");
	debug("server: waiting for connections on port %d...\n", ntohs(get_in_port((struct sockaddr *)servinfo->ai_addr)));

	do {  // main accept() loop
		sin_size = sizeof their_addr;
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
		if (new_fd == -1) {
			debug("Server: accept(...) :%s", strerror(errno));		continue;
		}
		char *ipStr;
		if ((ipStr = get_str_addr((struct sockaddr *)&their_addr, s)) == NULL) {
			debug("Server: inet_ntop error:%s", strerror(errno));		continue;
		}
		unsigned short port = ntohs(get_in_port((struct sockaddr *)&their_addr));
		debug("server: got connection from %s, port: %d\n", ipStr, port);
		if (!fork()) { // this is the child process
			close(sockfd);
			server_action(new_fd, NULL, NULL, "Hello, world!", NULL);
			//server_action(new_fd, (struct sockaddr *)&servinfo->ai_addr, (struct sockaddr *)&their_addr, "Hello, world!", NULL);
			close(new_fd);
			exit(0);
		}
		close(new_fd);
		free(ipStr);
	} while (serverMood);
	freeaddrinfo(servinfo);
	return 0;
} // MAIN

void init_variables(int argc, char *argv[], bool *serverMood, int *MinPortNum, int *MaxPortNum, int *backlog)
{
	*serverMood = strtol(argv[1], NULL, 10) == 1 ? false : true; //IF serverMode == 0 THEN modalità unico ciclo ELSE modalità standard
	*MinPortNum = strtol(argv[2], NULL, 10);
	*MaxPortNum = strtol(argv[3], NULL, 10);
	if (*MinPortNum <= MINPORTNUM || *MaxPortNum <= MINPORTNUM || *MinPortNum > MAXPORTNUM || *MaxPortNum > MAXPORTNUM || *MinPortNum > *MaxPortNum)
		fail_errno("Server: invalid port\n");
	if (argc > 4)	//set backlog
	{
		*backlog = strtol(argv[4], NULL, 10);
		if (*backlog<0 || *backlog > MAXBACKLOG)
			fail_errno("Server: invalid backlog\n");
	}
	*backlog = DEFAULTBACKLOG;
	//ancora da implemenrate 5<=argc<=9
}

void wait_for_termination_of_children(int pid)
{
	int status, exit_status;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
		{
			if ((exit_status = WEXITSTATUS(status)) != 0)
				fprintf(stderr, "bush--: A child return with an exit_status = %d\n", exit_status);
		}
		else
			fprintf(stderr, "bush--: A Program exited abnormally\n");
	}
	if (errno != ECHILD)
		fail_errno("wait() failed");
	/*** TO BE DONE END ***/
}/*

in_port_t get_in_port(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return (((struct sockaddr_in*)sa)->sin_port);
	}

	return (((struct sockaddr_in6*)sa)->sin6_port);
}

void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
*/
