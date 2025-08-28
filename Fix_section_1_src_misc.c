 	struct nl_sock *sk;
 	int err = 0;
 	int fd;
	mode_t cur_umask;
 
	cur_umask = umask(0600);
 	fd = mkstemp(file);
	umask(cur_umask);
 	if (fd == -1) {
 		syslog2(LOG_ERR, "Could not generate tempfile");
 		return 1;