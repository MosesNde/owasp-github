   if (req->method != WEBB_GET)
     return 404;
 
  char input_path[PATH_MAX], file[PATH_MAX];
  if (snprintf(input_path, PATH_MAX, "%s%s", WORK_DIR, req->uri) < 0)
    return 404;
  if (realpath(input_path, file) == NULL) {
    perror("realpath");
    return 404;
  }
  // check path traversal attack
  if (strstr(file, WORK_DIR) != file)
     return 404;
 
   struct stat sb;