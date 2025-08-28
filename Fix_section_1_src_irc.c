 /* Handle and interpret IRC events
   Copyright (C) 2014-2025 Markus Uhlin. All rights reserved.
 
    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
 
 	if (strFeed(remaining_data, requested_feeds) != requested_feeds &&
 	    strstr(remaining_data, "\nAWAY") == NULL) {
		FreeMsgCompo(compo);
 		printf_and_free(remaining_data, "In %s: strFeed: "
 		    "requested feeds mismatch feeds written", __func__);
 		return NULL;