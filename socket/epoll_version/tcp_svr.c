int main( void ) {
	int i;
	struct epoll_event ev, evs[100];
	int lfd = tcp_init();
	int epfd = epoll_create(1);
	ev.events = EPOLLIN;
	ev.data.fd = lfd;
	epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev); // 加入到红黑树
	printf("epoll ctl\n");

	for ( ; ; ) {
		int ready = epoll_wait(epfd, evs, 100, -1);
		for (i=0; i<ready; i++) {
			int fd = evs[i].data.fd;
			if ( fd == lfd ) {
				int cfd = accept(lfd, NULL, NULL);
				ev.events = EPOLLIN;
				ev.data.fd = cfd;
				epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev);
			} else {
				char buf[1024] = {};
				int n = read(fd, buf, 1024);
				if ( n <= 0 ) {
					epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL); // 对方关闭，从epoll的红黑树移除
					close(fd);
				}
				write(fd, buf, n);
			}
		}
	}
}

