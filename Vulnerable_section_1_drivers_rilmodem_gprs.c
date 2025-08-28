 	struct parcel rilp;
 	int i;
 
	if (contexts == NULL)
 		return;
 
 	parcel_init(&rilp);
 	parcel_w_int32(&rilp, length);