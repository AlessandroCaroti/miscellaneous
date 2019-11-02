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

#include "utils.h"

int main(int argc, char *argv[])
{
	int pipes[2];
	int portNum;
	pid_t pid;
	if(argc<2)
			fail("Incorrect parameters provided. Use: getAssociation PORT_NUMB_TO_FIND_ASSOCIATION\n");
	portNum = strtol(argv[3], NULL, 10);
	if (portNum <= MINPORTNUM || portNum > MAXPORTNUM)
		fail_errno("Server: invalid port\n");
	if (pipe(pipes) < 0)
		fail_errno(NULL);
	if ((pid = fork()) < 0)
		fail_errno("getAssociatio: fork(...) error: ");
	if (!pid)	//crea un client e un server per trovare l'associazione della porta fatta dalla NAT
	{
		;
	}
	//parent wait the child
	if (my_wait(pid)) < 0)
		fail_errno(NULL);
	//leggi dalla pipe l'asociazione
	//se definito fai partire la demo
	exit(EXIT_SUCCESS);
}

/*
 *Aspetta il figlio identificato dall'intero passato come argomento,
 *se fallisce la wait() o il figlio termina in manera anomala ritorna -1
 *altrimenti ritorna 0
 */
int my_wait(const int pid)
{
	int status;
	if (wait(pid, &status, 0) < 0)
		return -1;
	if (WIFEXITED(status) && WEXITSTATUS(status)) == 0)
			return 0:
	return -1;
}