 
 static struct libmnt_table *fetch_listmount(void)
 {
	struct libmnt_table *tb;
	struct libmnt_statmnt *sm;
 
 	sm = mnt_new_statmnt();
 	if (!sm) {
 		warn(_("failed to allocate statmnt handler"));
		return NULL;
 	}
 
 	tb = mnt_new_table();
 	if (!tb) {
 		warn(_("failed to initialize libmount table"));
		return NULL;
 	}
 
 	mnt_table_refer_statmnt(tb, sm);
 
 	if (mnt_table_fetch_listmount(tb) != 0) {
 		warn(_("failed to fetch mount nodes"));
		mnt_unref_table(tb);
		mnt_unref_statmnt(sm);
		return NULL;
 	}
 
 	return tb;
 }
 
 /*