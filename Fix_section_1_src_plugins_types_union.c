         }
         if (msg_len == -1) {
             LY_CHECK_ERR_GOTO(!errs, ret = LY_EMEM, cleanup);
            /* for further actions in function msg_len is just 0 */
            msg_len = 0;
         }
         for (u = 0; u < LY_ARRAY_COUNT(type_u->types); ++u) {
             if (!errs[u]) {