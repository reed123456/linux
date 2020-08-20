ssize_t readn(int fd, void *buf, size_t count) {
	size_t nleft = count;
	size_t nready;
	char *bufp = (char*)buf;

	while ( nleft > 0 ) {
		if ( (nready=read(fd, bufp, nleft)) < 0 ) {
			if ( errno == EINTR ) continue;
			return -1;
		} else if ( nready == 0 ) {
			return count - nleft;
		}

		bufp += nready;
		nleft -= nready;
	}

	return count;
}

ssize_t writen(int fd, const void *buf, size_t count) {
	size_t nlfet = count;
	size_t nready;
	char *bufp = (char*)buf;

	while ( nleft > 0 ) {
		if ( (nready = write(fd, bufp, nleft)) < 0 ) {
			if ( errno == EINTR ) continue;
			return -1;
		}
		bufp += nready;
		nleft -= nready;
	}

	return count;
}

