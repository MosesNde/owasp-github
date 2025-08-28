         sprintf(path, "%s/%s", src, dp->d_name);
         sprintf(path2, "%s/%s", dst, dp->d_name);
 
        if (G_recursive_copy(path, path2) != 0) {
            closedir(dirp);
             return 1;
        }
     }
 
     closedir(dirp);