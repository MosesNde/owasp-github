         return res == -EINVAL ? 0 : res;
     res = json_value_get_type(elm.v, &jvt);
     if (res != 0)
        goto err1;
     if (jvt != JSON_NUMBER_T)
        goto err2;
     res = json_numeric_get(elm.v);
     json_value_put(elm.v);
 
         return res;
     res = json_value_get_type(elm.v, &jvt);
     if (res != 0)
        goto err1;
     if (jvt != JSON_NUMBER_T)
        goto err2;
     sz = json_numeric_get(elm.v);
     json_value_put(elm.v);
 
         return res;
     res = json_value_get_type(elm.v, &jvt);
     if (res != 0)
        goto err1;
     if (jvt != JSON_NUMBER_T)
        goto err2;
     off = json_numeric_get(elm.v);
     json_value_put(elm.v);
 
         return res;
     res = json_value_get_type(elm.v, &jvt);
     if (res != 0)
        goto err1;
     if (jvt != JSON_NUMBER_T)
        goto err2;
     sz = json_numeric_get(elm.v);
     json_value_put(elm.v);
 
         return res;
     res = json_value_get_type(elm.v, &jvt);
     if (res != 0)
        goto err1;
     if (jvt != JSON_NUMBER_T)
        goto err2;
     res = json_numeric_get(elm.v);
     json_value_put(elm.v);
 
 
     return 0;
 
err2:
    res = -EILSEQ;
err1:
     json_value_put(elm.v);
     return res;
 }