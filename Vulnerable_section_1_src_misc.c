 	struct nl_sock *sk;
 	int err = 0;
 	int fd;
 
 	fd = mkstemp(file);
 	if (fd == -1) {
 		syslog2(LOG_ERR, "Could not generate tempfile");
 		return 1;