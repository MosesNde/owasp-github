 	while ((r = c_ioq_getln(&arr, &ioq)) > 0) {
 		c_arr_trunc(&arr, c_arr_bytes(&arr) - 1, sizeof(uchar));
 		linetoabs(&arr, c_arr_data(&arr));
		if (fn(s, c_arr_data(&arr), c_arr_bytes(&arr), p)) return 1;
 		c_arr_trunc(&arr, 0, sizeof(uchar));
 	}
 
 	}
 end:
 	c_dyn_free(&arr);
 	return ret;
 }
 
 	struct rebuild *r;
 	char buf[C_TAIA_PACK];
 
 	r = data;

 	/* TYPE(+0),TAIA(+1),MD5(+34),NAME(+67) */
 	if (s[0] == '=' && !c_str_cmp(s + 67, n - 67, r->target)) {
 		if (c_nix_lstat(&st, s + 67) < 0) return 1;
 			if (C_NIX_ISDIR(st.mode)) {
 				len = c_str_len(dep, -1);
 				c_str_cpy(dep + (len - 4), len, ".src");
				c_nix_fdclose(mktemp(dep, len, 0));
 			}
 			c_nix_unlink(deptmp);
 			goto end;
 static ctype_status
 mainfunc(int argc, char **argv, ctype_status (*fn)(char *))
 {
 	ctype_status r;
 	r = 0;
 	for (; *argv; ++argv) {
 	c_fmt_install('H', &hex);
 	prog = c_gen_basename(prog);
 	if (!C_STR_SCMP("redo", prog)) {
 		opts |= FFLAG;
 		return redo(argc, argv);
 	} else if (!C_STR_SCMP("redo-always", prog)) {
 		if (argc) usage(USAGE_DEF2);
 		return always(parentfd);
 	} else if (!C_STR_SCMP("redo-ifchange", prog)) {
 		if (parentfd == -1) return redo(argc, argv);
 		noopt(argc, argv, usage(USAGE_DEF1));
 		return mainfunc(argc, argv, &ifchange);