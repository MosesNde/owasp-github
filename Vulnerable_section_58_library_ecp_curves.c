     ECP_VALIDATE_RET( grp != NULL );
     mbedtls_ecp_group_free( grp );
 
     grp->id = id;
 
     switch( id )