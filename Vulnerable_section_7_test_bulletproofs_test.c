         return 0;
     }
 
    if (!(a = BP_R1CS_LINEAR_COMBINATION_dup(lc->a1))
        || !(b = BP_R1CS_LINEAR_COMBINATION_dup(lc->b1))
        || !(c = BP_R1CS_LINEAR_COMBINATION_dup(lc->c1))) {
        return 0;
     }
 
     if (!BP_R1CS_LINEAR_COMBINATION_mul(a, lc->a2, ctx)
         return 0;
     }
 
    if (!(a = BP_R1CS_LINEAR_COMBINATION_dup(lc->a1))
        || !(b = BP_R1CS_LINEAR_COMBINATION_dup(lc->b1))
        || !(c = BP_R1CS_LINEAR_COMBINATION_dup(lc->c1))) {
        return 0;
     }
 
     if (!BP_R1CS_LINEAR_COMBINATION_mul(a, lc->a2, ctx)
 
     BN_set_word(bn7, 7);
 
    if (!(a = BP_R1CS_LINEAR_COMBINATION_dup(lc->a1))
        || !(b = BP_R1CS_LINEAR_COMBINATION_dup(lc->b1))
        || !(c = BP_R1CS_LINEAR_COMBINATION_dup(lc->c1))) {
        return 0;
     }
 
     if (!BP_R1CS_LINEAR_COMBINATION_mul(a, lc->a2, ctx)
 
     BN_set_word(bn7, 7);
 
    if (!(a = BP_R1CS_LINEAR_COMBINATION_dup(lc->a1))
        || !(b = BP_R1CS_LINEAR_COMBINATION_dup(lc->b1))
        || !(c = BP_R1CS_LINEAR_COMBINATION_dup(lc->c1))) {
        return 0;
     }
 
     if (!BP_R1CS_LINEAR_COMBINATION_mul(a, lc->a2, ctx)
 
     BN_set_word(bn10, 10);
 
    if (!(a = BP_R1CS_LINEAR_COMBINATION_dup(lc->a1))) {
        return 0;
    }
 
     if (!BP_R1CS_LINEAR_COMBINATION_mul(a, lc->a2, ctx)
         || !BP_R1CS_LINEAR_COMBINATION_sub_bn(a, bn10)
         return 0;
     }
 
    if (!(a = BP_R1CS_LINEAR_COMBINATION_dup(lc->a1))) {
        return 0;
    }
 
     if (!BP_R1CS_LINEAR_COMBINATION_add(a, lc->b1)
         || !BP_R1CS_LINEAR_COMBINATION_add(a, lc->c1)
 
     BN_free(l);
     BN_free(r);
 
     return ret;
 }