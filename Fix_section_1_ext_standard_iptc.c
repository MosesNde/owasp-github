 
 	if (spool < 2) {
 		if (zend_fstat(fileno(fp), &sb) != 0) {
			fclose(fp);
 			RETURN_FALSE;
 		}
 