 c_str_vfmtcnt(char *fmt, va_list ap)
 {
 	ctype_fmt f;
 	c_fmt_init(&f, nil, put);
 	va_copy(f.args, ap);
	return c_fmt_fmt(&f, fmt);
 }