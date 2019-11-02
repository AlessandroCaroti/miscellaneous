#ifndef ASSOCIATIO_FUN_CLIENT
#define ASSOCIATIO_FUN_CLIENT

#include <string.h>
//#define SPECIALSTRING	//è necessaria una stringa segreta
#define MAXDATASIZE 100

void** genericClientFunction(const int sockfd, struct sockaddr * my_addr, struct sockaddr * addr, char* str, void** otherArgs)
{
	int numbytes;
	char buf[MAXDATASIZE];
	if ((numbytes = recv(sockfd, buf, MAXDATASIZE - 1, 0)) == -1) {
		perror("Client: recv(...) error: ");		return NULL;
	}
	buf[numbytes] = '\0';
	printf("Client: received '%s'\n", buf);
	struct sockaddr_in sin;
	socklen_t len = sizeof(sin);
	if (getsockname(sockfd, (struct sockaddr *)&sin, &len) == -1)
		perror("Client: getsockname(...) error: ");
	else
		printf("client: my port number is %d\n", ntohs(sin.sin_port));
	return NULL;
}

void** ClientFunction_NATportAssociation(const int sockfd, struct sockaddr * my_addr, struct sockaddr * extern_addr, char* secretString, void** otherArgs)
{
	int numbytes;
	char buf[MAXDATASIZE];
	if (send(sockfd, secretString, strlen(secretString), 0) == -1) {
		perror("Client: send(...) error: ");  return NULL;
	}
	debug("Client sent %s", secretString);
	if ((numbytes = recv(sockfd, buf, MAXDATASIZE - 1, 0)) == -1) {
		perror("Client: recv(...) error: ");		return NULL;
	}
	buf[numbytes] = '\0';
	debug("Client receve %s", buf);
	if (strncmp("OK", buf, 2) != 0)
		return NULL;
	char *portStr = int_to_str((int)get_in_port((struct sockaddr *)extern_addr), &numbytes);
	if (send(sockfd, portStr, numbytes, 0) == -1) {
		perror("Client: send(...) error: ");  return NULL;
	}
	debug("Client sent %s", portStr);
	free(portStr);
	return (void**)1;
}

#endif // !ASSOCIATIO_FUN_CLIENT

