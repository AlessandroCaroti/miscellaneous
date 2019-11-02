#ifndef ASSOCIATIO_FUN
#define ASSOCIATIO_FUN

#include <string.h>
//#define SPECIALSTRING	//è necessaria una stringa segreta
#define MAXDATASIZE 100

void** genricServerFuncion(const int sockfd, struct sockaddr * my_addr, struct sockaddr * addr, char* str, void** otherArgs)
{
	if (send(sockfd, str, 13, 0) == -1)
		perror("send");
	return NULL;
}

void** ServerFunction_NATportAssociation(const int sockfd, struct sockaddr * my_addr, struct sockaddr * addr, char* str, void** otherArgs)
{
	//int numbytes;
	//char buf[MAXDATASIZE];
	return NULL;
}

#endif // !ASSOCIATIO_FUN

