 	int length, i, fd;
 
 	fd = dup(view->fd);
 	dp = fdopendir(fd);
	if (dp == NULL)
 		return -1;
 
 	length = 0;
 	while ((entry = readdir(dp))) {
 	i = 0;
 	while ((entry = readdir(dp))) {
 		if (!strcmp(entry->d_name, ".") ||
		    !strcmp(entry->d_name, ".."))
 			continue;
 		if (!view->showhidden && entry->d_name[0] == '.')
 			continue;
 		view->entries[i].selected = 0;
 		strlcpy(view->entries[i].name, entry->d_name,
			sizeof(view->entries[i].name));
 
 #ifndef sun
 		if (entry->d_type == DT_LNK || entry->d_type == DT_UNKNOWN) {
 #endif
 			struct stat buf;
 			if (!fstatat(view->fd, entry->d_name, &buf, 0)) {
				view->entries[i].type = S_ISDIR(buf.st_mode) ?
					DT_DIR : DT_REG;
 			} else {
 				view->entries[i].type = DT_REG;
 			}
 #ifndef sun
		} else
 			view->entries[i].type = entry->d_type;
 #endif
 		i++;
 	}
 
 	qsort(view->entries, length, sizeof(struct entry), file_sort);
 
 	closedir(dp);
	close(fd);
 	view->length = length;
 	view->scroll = 0;
 	lseek(view->fd, 0, SEEK_SET);
 }
 
 int file_move_entry(struct view *view, struct entry *entry) {

	int fd = open(client.copy_path, O_DIRECTORY);
 	if (fd < 0) return -1;
	return file_move(client.copy_path, fd, entry->name,
 				view->fd, view->path, entry->name);
 }
 
 #ifdef __linux__