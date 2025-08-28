   if (len) {
     host = lowmem_alloc(len + 1);
     strcpy(host, s);
     r.r_es = DOSEMU_LMHEAP_SEG;
     r.r_di = DOSEMU_LMHEAP_OFFS_OF(host);
   }
  free(s);
   r.r_ax = (DOS_HELPER_IPX_HELPER | (DOS_SUBHELPER_IPX_CONNECT << 8)) & 0xffff;
   com_intr(DOS_HELPER_INT, &r);
   if (host)