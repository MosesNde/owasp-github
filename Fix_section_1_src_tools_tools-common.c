 
 				/* we are interested in .conf files, skip others */
 				file_ext = strstr(item->d_name, ".conf");
				if (!file_ext) {
					free(fullpath);
 					continue;
				}
 
				if (strcmp(file_ext, ".conf") || strlen(item->d_name) == 5) {
					free(fullpath);
 					continue;
				}
 
 				ret = cgroup_string_list_add_item(list, fullpath);
 				count++;