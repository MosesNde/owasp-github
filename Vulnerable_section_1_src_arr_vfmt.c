 c_arr_vfmt(ctype_arr *p, char *fmt, va_list args)
 {
 	ctype_fmt f;
 	c_fmt_init(&f, p, put);
 	va_copy(f.args, args);
	return c_fmt_fmt(&f, fmt);
 }