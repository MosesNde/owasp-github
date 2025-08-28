 static int session_active_segs_isempty(session_t* session);
 static int request_validate(request_t *r);
 static int request_set_path(request_t *r, const char* d, char* p, char* pp, char* path);
static int request_path_validate(request_t *r, const char* path);
 static int request_parse_gp_headers(request_t *r, int opt_g);
 static void free_session_cb(int fd, short event, void* arg);
 #ifdef GPFXDIST
 	/* decode %xx to char */
 	percent_encoding_to_char(p, pp, path);
 
	/* legit check for the path */
	if (request_path_validate(r, path) != 0)
	{
		return;
	}

 	/*
 	 * This is a debug hook. We'll get here By creating an external table with
 	 * name(a text) location('gpfdist://<host>:<port>/gpfdist/status').
 
 static int request_set_path(request_t *r, const char* d, char* p, char* pp, char* path)
 {
 	r->path = 0;
 
 	/*
 	return 0;
 }
 
static int request_path_validate(request_t *r, const char* path)
{
	const char* warn_msg = NULL;
	const char* http_err_msg = NULL;

#ifdef WIN32
	if (strstr(path, ".."))
#else
	if (strstr(path, "\\"))
	{
		/*
		 * '\' is the path separator under windows.
		 * For *nix, escape char may cause some unexpected result with
		 * the file API. e.g.: 'ls \.\.' equals to 'ls ..'.
		 */
		warn_msg = "contains escape character backslash '\\'";
		http_err_msg = "invalid request, "
			"escape character backslash '\\' is not allowed.";
	}
	else if (strstr(path, ".."))
#endif
	{
		/*
		 * disallow using a relative path in the request. CWE23
		 */
		warn_msg = "is using a relative path";
		http_err_msg = "invalid request due to relative path";
	}

	if (warn_msg)
	{
		gwarning(r, "reject invalid request from %s [%s %s] - request %s",
						r->peer,
						r->in.req->argv[0],
						r->in.req->argv[1],
						warn_msg);

		http_error(r, FDIST_BAD_REQUEST, http_err_msg);
		request_end(r, 1, 0);
		return -1;
	}

	return 0;
}

 static int request_validate(request_t *r)
 {
 	/* parse the HTTP request. Expect "GET /path HTTP/1.X" or "PUT /path HTTP/1.X" */