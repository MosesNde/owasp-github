 
 	if (spool < 2) {
 		if (zend_fstat(fileno(fp), &sb) != 0) {
 			RETURN_FALSE;
 		}
 