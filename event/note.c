#include <sys/socket.h>

int
socket(int domain, int type, int protocol);

int
bind(int socket, const struct sockaddr *address, socklen_t address_len);

int
listen(int socket, int backlog);

int
accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len);

ssize_t
recv(int socket, void *buffer, size_t length, int flags);

ssize_t
recvfrom(int socket, void *restrict buffer, size_t length, int flags, struct sockaddr *restrict address,
        socklen_t *restrict address_len);

ssize_t
recvmsg(int socket, struct msghdr *message, int flags);

ssize_t
send(int socket, const void *buffer, size_t length, int flags);

ssize_t
sendmsg(int socket, const struct msghdr *message, int flags);

ssize_t
sendto(int socket, const void *buffer, size_t length, int flags, const struct sockaddr *dest_addr,
        socklen_t dest_len);

/***/
#include <sys/select.h>

void
FD_CLR(fd, fd_set *fdset);

void
FD_COPY(fd_set *fdset_orig, fd_set *fdset_copy);

int
FD_ISSET(fd, fd_set *fdset);

void
FD_SET(fd, fd_set *fdset);

void
FD_ZERO(fd_set *fdset);

int
select(int nfds, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict errorfds,
        struct timeval *restrict timeout);

/***/
#include <fcntl.h>

int
fcntl(int fildes, int cmd, ...);

/***/
#include <arpa/inet.h>

uint32_t
htonl(uint32_t hostlong);

uint16_t
htons(uint16_t hostshort);

uint32_t
ntohl(uint32_t netlong);

uint16_t
ntohs(uint16_t netshort);

/***/
#include <stdio.h>

void
setbuf(FILE *restrict stream, char *restrict buf);

void
setbuffer(FILE *stream, char *buf, int size);

int
setlinebuf(FILE *stream);

int
setvbuf(FILE *restrict stream, char *restrict buf, int type, size_t size);
