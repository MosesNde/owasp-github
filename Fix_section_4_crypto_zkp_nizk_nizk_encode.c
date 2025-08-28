     }
 
     sk_point = sk_EC_POINT_new_reserve(NULL, 2);
    if (sk_point == NULL) {
         ERR_raise(ERR_LIB_ZKP_NIZK, ERR_R_MALLOC_FAILURE);
         return 0;
     }
 
    sk_bn = sk_BIGNUM_new_reserve(NULL, 2);
    if (sk_bn == NULL) {
        ERR_raise(ERR_LIB_ZKP_NIZK, ERR_R_MALLOC_FAILURE);
        goto end;
    }

     if ((curve_id = EC_POINT_get_curve_name(proof->A)) == NID_undef) {
         ERR_raise(ERR_LIB_ZKP_NIZK, ERR_R_PASSED_INVALID_ARGUMENT);
         goto end;
     }
 
     sk_point = sk_EC_POINT_dup(proof->sk_A);
    if (sk_point == NULL) {
         ERR_raise(ERR_LIB_ZKP_NIZK, ERR_R_MALLOC_FAILURE);
         return 0;
     }
 
    sk_bn = sk_BIGNUM_new_reserve(NULL, 2);
    if (sk_bn == NULL) {
        ERR_raise(ERR_LIB_ZKP_NIZK, ERR_R_MALLOC_FAILURE);
        goto end;
    }

     if ((curve_id = EC_POINT_get_curve_name(proof->B)) == NID_undef) {
         ERR_raise(ERR_LIB_ZKP_NIZK, ERR_R_PASSED_INVALID_ARGUMENT);
         goto end;
     }
 
     sk_point = sk_EC_POINT_new_reserve(NULL, 1);
    if (sk_point == NULL) {
         ERR_raise(ERR_LIB_ZKP_NIZK, ERR_R_MALLOC_FAILURE);
         return 0;
     }
 
    sk_bn = sk_BIGNUM_new_reserve(NULL, 1);
    if (sk_bn == NULL) {
        ERR_raise(ERR_LIB_ZKP_NIZK, ERR_R_MALLOC_FAILURE);
        goto end;
    }

     if ((curve_id = EC_POINT_get_curve_name(proof->A)) == NID_undef) {
         ERR_raise(ERR_LIB_ZKP_NIZK, ERR_R_PASSED_INVALID_ARGUMENT);
         goto end;
     }
 
     sk_point = sk_EC_POINT_new_reserve(NULL, 2);
    if (sk_point == NULL) {
         ERR_raise(ERR_LIB_ZKP_NIZK, ERR_R_MALLOC_FAILURE);
         return 0;
     }
 
    sk_bn = sk_BIGNUM_new_reserve(NULL, 1);
    if (sk_bn == NULL) {
        ERR_raise(ERR_LIB_ZKP_NIZK, ERR_R_MALLOC_FAILURE);
        goto end;
    }

     if ((curve_id = EC_POINT_get_curve_name(proof->A1)) == NID_undef) {
         ERR_raise(ERR_LIB_ZKP_NIZK, ERR_R_PASSED_INVALID_ARGUMENT);
         goto end;