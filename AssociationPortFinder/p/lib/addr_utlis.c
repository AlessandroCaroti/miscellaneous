#include <netinet/in.h>
#include <arpa/inet.h>
#include "associationFinder_lib.h"

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

const char *get_str_addr(struct sockaddr *sa, char *s)
{
	char *str;/*
	if (sa->sa_family == AF_INET) {
		str = my_malloc(INET_ADDRSTRLEN);
		return inet_ntop(AF_INET, get_in_addr(sa), str, INET_ADDRSTRLEN);
	}*/
	str = my_malloc(INET6_ADDRSTRLEN);
	return inet_ntop(sa->sa_family, get_in_addr(sa), str, INET6_ADDRSTRLEN);
}
