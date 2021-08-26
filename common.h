#ifndef COMMON_H
#define COMMON_H
#include <semaphore.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/stat.h>
#include <netdb.h>
#include <arpa/inet.h>

#define MAXLINE 1024

///////////////////////////////////////
/* Funciones de gestión de conexión */

/**
 * Open and return a listening socket on port. This function is reentrant and protocol-independent.
 *
 * @param port Character array with TCP port, decimal.
 *
 * @return A listening socker. On error, returns -1 and sets errno.
 */

typedef struct 
{
    int *buf;
    int n ;
    int front;
    int rear;
    sem_t mutex;
    sem_t slots;
    sem_t items;
}sbuf_t;




int open_listenfd(char *port);

/**
 * Open connection to server at <hostname, port> and 
 * return a socket descriptor ready for reading and writing. This
 * function is reentrant and protocol-independent.
 *
 * @param hostname Character array with IP address or hostname.
 * @param port Character array with TCP port, decimal.
 *
 * @return Socket file descriptor. On error, returns -1 and sets errno.
 */
int open_clientfd(char *hostname, char *port);

/**
 * Closes the socket, prints error on STDERR and exits.
 *
 * @param connfd Socket file descriptor.
 */
void connection_error(int connfd);
void sbuf_init(sbuf_t *sp, int n);
void sbuf_deinit(sbuf_t *sp);
int sbuf_remove(sbuf_t *sp);
void sbuf_insert(sbuf_t *sp, int item);



#endif /* COMMON_H */