 }
 
 static PyObject *PyFF_UnParseTTFInstrs(PyObject *UNUSED(self), PyObject *args) {
    PyObject *tuple, *ret;
     int icnt, i;
     uint8_t *instrs;
     char *as_str;
 
    if ( !PyArg_ParseTuple(args,"O",&tuple) )
 return( NULL );
    if ( !PySequence_Check(tuple)) {
 	PyErr_Format(PyExc_TypeError, "Argument must be a sequence" );
 return( NULL );
     }
    if ( PyBytes_Check(tuple)) {
 	char *space; Py_ssize_t len;
	PyBytes_AsStringAndSize(tuple,&space,&len);
 	instrs = calloc(len,sizeof(uint8_t));
 	icnt = len;
 	memcpy(instrs,space,len);
     } else {
	icnt = PySequence_Size(tuple);
 	instrs = malloc(icnt);
 	for ( i=0; i<icnt; ++i ) {
	    instrs[i] = PyLong_AsLong(PySequence_GetItem(tuple,i));
	    if ( PyErr_Occurred()) {
		free(instrs);
return( NULL );
 	    }
 	}
     }
     as_str = _IVUnParseInstrs(instrs,icnt);