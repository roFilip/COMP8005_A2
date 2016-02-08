#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <iostream>
#include <QtConcurrent/qtconcurrentrun.h>

#define TRUE 		1
#define FALSE 		0
#define EPOLL_QUEUE_LEN	10000
#define BUFLEN		1024
#define SERVER_PORT	7000


typedef struct thrdParams
{
    int fd;
} thrdParams;

extern void *readSocket(void *param);
extern void* UpdateConsole(void *param);
extern int numClients;

class Server :  public QThread

{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    void run();

    static struct epoll_event events[EPOLL_QUEUE_LEN], event;

private:
    int fd_server;
    int num_fds;
    int epoll_fd;
    int arg;
    int fd_new;
    int port;
    struct sockaddr_in addr, remote_addr;
    socklen_t addr_size;
    pthread_t readThread, updateConsoleThrd;
    thrdParams *thrdInfo;

    void SystemFatal (const char* message);
    void* ClearSocket (void *param);
    void close_fd (int);

signals:

public slots:
};

#endif // SERVER_H
