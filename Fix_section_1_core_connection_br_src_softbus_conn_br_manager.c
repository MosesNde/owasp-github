         if (pending == NULL) {
             CONN_LOGE(CONN_BR, "calloc pending object failed");
             status = SOFTBUS_MALLOC_ERR;
            SoftBusFree(copyAddr);
             break;
         }
         ListInit(&pending->node);