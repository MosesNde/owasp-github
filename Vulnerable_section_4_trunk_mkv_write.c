         return res == -EINVAL ? 0 : res;
     res = json_value_get_type(elm.v, &jvt);
     if (res != 0)
        goto err;
     if (jvt != JSON_NUMBER_T)
        return -EILSEQ;
     res = json_numeric_get(elm.v);
     json_value_put(elm.v);
 
         return res;
     res = json_value_get_type(elm.v, &jvt);
     if (res != 0)
        goto err;
     if (jvt != JSON_NUMBER_T)
        return -EILSEQ;
     sz = json_numeric_get(elm.v);
     json_value_put(elm.v);
 
         return res;
     res = json_value_get_type(elm.v, &jvt);
     if (res != 0)
        goto err;
     if (jvt != JSON_NUMBER_T)
        return -EILSEQ;
     off = json_numeric_get(elm.v);
     json_value_put(elm.v);
 
         return res;
     res = json_value_get_type(elm.v, &jvt);
     if (res != 0)
        goto err;
     if (jvt != JSON_NUMBER_T)
        return -EILSEQ;
     sz = json_numeric_get(elm.v);
     json_value_put(elm.v);
 
         return res;
     res = json_value_get_type(elm.v, &jvt);
     if (res != 0)
        goto err;
     if (jvt != JSON_NUMBER_T)
        return -EILSEQ;
     res = json_numeric_get(elm.v);
     json_value_put(elm.v);
 
 
     return 0;
 
err:
     json_value_put(elm.v);
     return res;
 }