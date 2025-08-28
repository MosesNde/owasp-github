 	pw = getpwuid(geteuid());
         if (!pw) return -1;
         fd = open(pw->pw_dir, O_DIRECTORY);
	if (fd < 0) {
		close(fd);
		return -1;
	}
         return strlcpy(buf, pw->pw_dir, length);
 }
 
 	trash = openat(home, ".trash", O_DIRECTORY);
 	if (trash < 0) goto fail;
 
 	return trash;
 fail:
 	if (home > -1)
 
 		if (rename(src, view->entries[j].name)) {
 			char *name;
 			if (errno != EXDEV) return -1;
 			STRCPY(src, view->entries[j].name);
 			name = strrchr(src, '/');
 			name++;
 			fd = open(src, O_DIRECTORY);
 			if (fd < 0) return -1;
			if (file_move(path, client.trash, id, fd, src, name))
				return -1;
 		}
 		view->entries[j].selected = -1;
 	}