 
 static struct libmnt_table *fetch_listmount(void)
 {
	struct libmnt_table *tb = NULL;
	struct libmnt_statmnt *sm = NULL;
 
 	sm = mnt_new_statmnt();
 	if (!sm) {
 		warn(_("failed to allocate statmnt handler"));
		goto failed;
 	}
 
 	tb = mnt_new_table();
 	if (!tb) {
 		warn(_("failed to initialize libmount table"));
		goto failed;
 	}
 
 	mnt_table_refer_statmnt(tb, sm);
 
 	if (mnt_table_fetch_listmount(tb) != 0) {
 		warn(_("failed to fetch mount nodes"));
		goto failed;
 	}
 
 	return tb;
failed:
	mnt_unref_table(tb);
	mnt_unref_statmnt(sm);
	return NULL;
 }
 
 /*