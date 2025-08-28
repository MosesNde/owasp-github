  err_reg_add:
    vm_close_log(vm);
  err_log:
   free(vm->lock_file);
  err_lock:
    free(vm->rommon_vars.filename);
  err_rommon: