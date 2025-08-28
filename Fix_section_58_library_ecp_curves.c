     ECP_VALIDATE_RET( grp != NULL );
     mbedtls_ecp_group_free( grp );
 
    mbedtls_ecp_group_init( grp );

     grp->id = id;
 
     switch( id )