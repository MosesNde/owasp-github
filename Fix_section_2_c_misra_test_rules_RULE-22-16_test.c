     }
     mtx_unlock(&m);
   }
}

void f16(int p) {
  mtx_t *ptr;
  mtx_t *ptr_m1 = ptr;
  mtx_t *ptr_m2 = ptr;
  mtx_lock(ptr_m1); // COMPLIANT[FALSE_POSITIVE]
  mtx_unlock(ptr_m2);
 }
\ No newline at end of file