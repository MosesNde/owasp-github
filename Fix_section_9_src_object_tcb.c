 #define NULL_PRIO 0
 
 static exception_t
checkPrio(prio_t prio, tcb_t *auth)
 {
     prio_t mcp;
 
    mcp = auth->tcbMCP;
 
     /* system invariant: existing MCPs are bounded */
     assert(mcp <= seL4_MaxPrio);
         return decodeTCBConfigure(cap, length, slot, excaps, buffer);
 
     case TCBSetPriority:
        return decodeSetPriority(cap, length, excaps, buffer);
 
     case TCBSetMCPriority:
        return decodeSetMCPriority(cap, length, excaps, buffer);
 
     case TCBSetIPCBuffer:
         return decodeSetIPCBuffer(cap, length, slot, excaps, buffer);
                                     w, transferArch, buffer);
 }
 
/* SetPriority, SetMCPriority, SetIPCBuffer and SetSpace are all
  * specialisations of TCBConfigure. */
 exception_t
 decodeTCBConfigure(cap_t cap, word_t length, cte_t* slot,
                    extra_caps_t rootCaps, word_t *buffer)
     cap_t bufferCap, cRootCap, vRootCap;
     deriveCap_ret_t dc_ret;
     cptr_t faultEP;
     word_t cRootData, vRootData, bufferAddr;
 
    if (length < 4 || rootCaps.excaprefs[0] == NULL
             || rootCaps.excaprefs[1] == NULL
             || rootCaps.excaprefs[2] == NULL) {
         userError("TCB Configure: Truncated message.");
     }
 
     faultEP       = getSyscallArg(0, buffer);
    cRootData     = getSyscallArg(1, buffer);
    vRootData     = getSyscallArg(2, buffer);
    bufferAddr    = getSyscallArg(3, buffer);
 
     cRootSlot  = rootCaps.excaprefs[0];
     cRootCap   = rootCaps.excaprefs[0]->cap;
     bufferSlot = rootCaps.excaprefs[2];
     bufferCap  = rootCaps.excaprefs[2]->cap;
 
     if (bufferAddr == 0) {
         bufferSlot = NULL;
     } else {
     setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
     return invokeTCB_ThreadControl(
                TCB_PTR(cap_thread_cap_get_capTCBPtr(cap)), slot,
               faultEP, NULL_PRIO, NULL_PRIO,
                cRootCap, cRootSlot,
                vRootCap, vRootSlot,
                bufferAddr, bufferCap,
               bufferSlot, thread_control_update_space |
               thread_control_update_ipc_buffer);
 }
 
 exception_t
decodeSetPriority(cap_t cap, word_t length, extra_caps_t excaps, word_t *buffer)
 {
    if (length < 1 || excaps.excaprefs[0] == NULL) {
         userError("TCB SetPriority: Truncated message.");
         current_syscall_error.type = seL4_TruncatedMessage;
         return EXCEPTION_SYSCALL_ERROR;
     }
 
    prio_t newPrio = getSyscallArg(0, buffer);
    cap_t authCap = excaps.excaprefs[0]->cap;
 
    if (cap_get_capType(authCap) != cap_thread_cap) {
        userError("Set priority: authority cap not a TCB.");
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    tcb_t *authTCB = TCB_PTR(cap_thread_cap_get_capTCBPtr(authCap));
    exception_t status = checkPrio(newPrio, authTCB);
     if (status != EXCEPTION_NONE) {
         userError("TCB SetPriority: Requested priority %lu too high (max %lu).",
                  (unsigned long) newPrio, (unsigned long) authTCB->tcbMCP);
         return status;
     }
 
 }
 
 exception_t
decodeSetMCPriority(cap_t cap, word_t length, extra_caps_t excaps, word_t *buffer)
 {
    if (length < 1 || excaps.excaprefs[0] == NULL) {
         userError("TCB SetMCPriority: Truncated message.");
         current_syscall_error.type = seL4_TruncatedMessage;
         return EXCEPTION_SYSCALL_ERROR;
     }
 
    prio_t newMcp = getSyscallArg(0, buffer);
    cap_t authCap = excaps.excaprefs[0]->cap;

    if (cap_get_capType(authCap) != cap_thread_cap) {
        userError("TCB SetMCPriority: authority cap not a TCB.");
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }
 
    tcb_t *authTCB = TCB_PTR(cap_thread_cap_get_capTCBPtr(authCap));
    exception_t status = checkPrio(newMcp, authTCB);
     if (status != EXCEPTION_NONE) {
         userError("TCB SetMCPriority: Requested maximum controlled priority %lu too high (max %lu).",
                  (unsigned long) newMcp, (unsigned long) authTCB->tcbMCP);
         return status;
     }
 