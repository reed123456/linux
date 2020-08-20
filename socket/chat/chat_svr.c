#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

typedef struct client {
	int cfd;
	char nickname[32];
}client_t;

typedef struct node {
	client_t c;
	struct node *prev;
	struct node *next;
}node_t;

node_t *head = NULL;

void list_init( void ) {
	node_t *p = malloc(sizeof(node_t));
	memset(p, 0x00, sizeof(node_t));
	p->next = p->prev = p;
	head = p;
}

void list_insert(client_t *pc) {
	node_t *newnode = (node_t*)malloc(sizeof(node_t));
	newnode->c = *pc;
	newnode->next = head->next;
	newnode->prev = head;
	head->next->prev = newnode;
	head->next = newnode;
}

void list_erase(int cfd) {
	node_t *p = head->next;
	
	while ( p != head ) {
		if ( p->c.cfd == cfd ) {
			p->next->prev = p->prev;
			p->prev->next = p->next;
			break;
		}
		p = p->next;
	}
}

void send_all(char *msg) {
	node_t *p = head->next;

	while ( p != head ) {
		write(p->c.cfd, msg, strlen(msg));
		p = p->next;
	}
}

int tcp_init() {
	int lfd = socket(AF_INET, SOCK_STREAM, 0);

	int op = 1;
	setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &op, sizeof(op));
	
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9898);
	addr.sin_addr.s_addr =htonl(INADDR_ANY);
	int r = bind(lfd, (struct sockaddr*)&addr, sizeof(addr));
	if ( r == -1 ) perror("bind"),exit(1);

	listen(lfd, SOMAXCONN);
	
	return lfd;
}

void *process(void *arg) {
	int cfd = *(int*)arg;
	free(arg);

	char *welcome = "欢迎来到聊天室\n";
	write(cfd, welcome, strlen(welcome));
	char nickname[32];
	sprintf(nickname, "昵称:");
	write(cfd, nickname, strlen(nickname));
	memset(nickname, 0x00, sizeof(nickname));
	read(cfd, nickname, 32);
	nickname[strlen(nickname)-1] = 0;
	printf("nickname=%s\n", nickname);
	
	client_t cli;
	cli.cfd = cfd;
	strcpy(cli.nickname, nickname);

	char buf[1024];
	sprintf(buf, "%s上线了\n", nickname);
	send_all(buf);
	
	list_insert(&cli);
	
	while ( 1 ) {
		char tmp[1024] = {};
		int r = read(cfd, tmp, 1024);
		if ( r <= 0 ) {
			sprintf(buf, "%s下线了\n", nickname);
			send_all(buf);
			list_erase(cfd);
			break;
		}
		memset(buf, 0x00, sizeof(buf));
		sprintf(buf, "%s:>%s", nickname, tmp);
		send_all(buf);
	}

	close(cfd);
}

int main( void ) {
	list_init();
	int lfd = tcp_init();

	for ( ; ; ) {
		int newfd = accept(lfd, NULL, NULL);
		if ( newfd == -1 ) continue;
		pthread_t tid;
		int *p = malloc(sizeof(int));
		*p = newfd;
		pthread_create(&tid, NULL, process, p);
		pthread_detach(tid);
	}
}

