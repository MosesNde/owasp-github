 	return NULL;
 #endif
 }

/*
 * return 1 if the specified uid is a uid that may own a system directory
 * otherwise 0.
 */
int
platform_sys_dir_uid(uid_t uid)
{
	if (uid == 0)
		return 1;
#ifdef PLATFORM_SYS_DIR_UID
	if (uid == PLATFORM_SYS_DIR_UID)
		return 1;
#endif
	return 0;
}