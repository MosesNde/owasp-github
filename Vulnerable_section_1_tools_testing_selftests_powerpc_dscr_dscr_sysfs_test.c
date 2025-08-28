 	rc = read(fd, buf, sizeof(buf));
 	if (rc == -1) {
 		perror("read() failed");
 		return 1;
 	}
 	close(fd);
 		if (access(file, F_OK))
 			continue;
 
		if (check_cpu_dscr_default(file, val))
 			return 1;
 	}
 	closedir(sysfs);
 	return 0;