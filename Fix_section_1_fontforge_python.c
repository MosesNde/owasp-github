 }
 
 static PyObject *PyFF_UnParseTTFInstrs(PyObject *UNUSED(self), PyObject *args) {
    PyObject *seq_any, *ret;
     int icnt, i;
     uint8_t *instrs;
     char *as_str;
 
    if ( !PyArg_ParseTuple(args,"O",&seq_any) )
 return( NULL );
    if ( !PySequence_Check(seq_any)) {
 	PyErr_Format(PyExc_TypeError, "Argument must be a sequence" );
 return( NULL );
     }

    if ( PyBytes_Check(seq_any)) {
 	char *space; Py_ssize_t len;
	PyBytes_AsStringAndSize(seq_any,&space,&len);
 	instrs = calloc(len,sizeof(uint8_t));
 	icnt = len;
 	memcpy(instrs,space,len);
     } else {
	PyObject *seq_fast = PySequence_Fast(seq_any,__func__);
	if (seq_fast == NULL) {
return( NULL );
	}
	icnt = PySequence_Fast_GET_SIZE(seq_fast);
 	instrs = malloc(icnt);
 	for ( i=0; i<icnt; ++i ) {
	    long val = PyLong_AsLong(PySequence_Fast_GET_ITEM(seq_fast,i));
	    if (val==-1 && PyErr_Occurred()) {
	    break;
 	    }
	    instrs[i] = val;
	    }
	Py_DECREF(seq_fast);

	if (i!=icnt) {
	    free(instrs);
return( NULL );
 	}
     }
     as_str = _IVUnParseInstrs(instrs,icnt);