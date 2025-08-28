 	struct parcel rilp;
 	int i;
 
	if (contexts == NULL) {
		g_free(cbd);
 		return;
	}
 
 	parcel_init(&rilp);
 	parcel_w_int32(&rilp, length);