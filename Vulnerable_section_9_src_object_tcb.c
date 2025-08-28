 #define NULL_PRIO 0
 
 static exception_t
checkPrio(prio_t prio)
 {
     prio_t mcp;
 
    mcp = NODE_STATE(ksCurThread)->tcbMCP;
 
     /* system invariant: existing MCPs are bounded */
     assert(mcp <= seL4_MaxPrio);
         return decodeTCBConfigure(cap, length, slot, excaps, buffer);
 
     case TCBSetPriority:
        return decodeSetPriority(cap, length, buffer);
 
     case TCBSetMCPriority:
        return decodeSetMCPriority(cap, length, buffer);
 
     case TCBSetIPCBuffer:
         return decodeSetIPCBuffer(cap, length, slot, excaps, buffer);
                                     w, transferArch, buffer);
 }
 
/* SetPriority, SetMCPriority, SetIPCParams and SetSpace are all
  * specialisations of TCBConfigure. */

 exception_t
 decodeTCBConfigure(cap_t cap, word_t length, cte_t* slot,
                    extra_caps_t rootCaps, word_t *buffer)
     cap_t bufferCap, cRootCap, vRootCap;
     deriveCap_ret_t dc_ret;
     cptr_t faultEP;
    seL4_PrioProps_t props;
    prio_t prio, mcp;
     word_t cRootData, vRootData, bufferAddr;
    exception_t status;
 
    if (length < 5 || rootCaps.excaprefs[0] == NULL
             || rootCaps.excaprefs[1] == NULL
             || rootCaps.excaprefs[2] == NULL) {
         userError("TCB Configure: Truncated message.");
     }
 
     faultEP       = getSyscallArg(0, buffer);
    props         = prioPropsFromWord(getSyscallArg(1, buffer));
    cRootData     = getSyscallArg(2, buffer);
    vRootData     = getSyscallArg(3, buffer);
    bufferAddr    = getSyscallArg(4, buffer);
 
     cRootSlot  = rootCaps.excaprefs[0];
     cRootCap   = rootCaps.excaprefs[0]->cap;
     bufferSlot = rootCaps.excaprefs[2];
     bufferCap  = rootCaps.excaprefs[2]->cap;
 
    prio = seL4_PrioProps_get_prio(props);
    mcp  = seL4_PrioProps_get_mcp(props);

    status = checkPrio(prio);
    if (status != EXCEPTION_NONE) {
        userError("TCB Configure: Requested priority %lu too high (max %lu).",
                  (unsigned long) prio, (unsigned long) NODE_STATE(ksCurThread)->tcbMCP);
        return status;
    }

    status = checkPrio(mcp);
    if (status != EXCEPTION_NONE) {
        userError("TCB Configure: Requested maximum controlled priority %lu too high (max %lu),",
                  (unsigned long) mcp, (unsigned long) NODE_STATE(ksCurThread)->tcbMCP);
        return status;
    }

     if (bufferAddr == 0) {
         bufferSlot = NULL;
     } else {
     setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
     return invokeTCB_ThreadControl(
                TCB_PTR(cap_thread_cap_get_capTCBPtr(cap)), slot,
               faultEP, mcp, prio,
                cRootCap, cRootSlot,
                vRootCap, vRootSlot,
                bufferAddr, bufferCap,
               bufferSlot, thread_control_update_all);
 }
 
 exception_t
decodeSetPriority(cap_t cap, word_t length, word_t *buffer)
 {
    prio_t newPrio;
    exception_t status;

    if (length < 1) {
         userError("TCB SetPriority: Truncated message.");
         current_syscall_error.type = seL4_TruncatedMessage;
         return EXCEPTION_SYSCALL_ERROR;
     }
 
    newPrio = getSyscallArg(0, buffer);
 
    status = checkPrio(newPrio);
     if (status != EXCEPTION_NONE) {
         userError("TCB SetPriority: Requested priority %lu too high (max %lu).",
                  (unsigned long) newPrio, (unsigned long) NODE_STATE(ksCurThread)->tcbMCP);
         return status;
     }
 
 }
 
 exception_t
decodeSetMCPriority(cap_t cap, word_t length, word_t *buffer)
 {
    prio_t newMcp;
    exception_t status;

    if (length < 1) {
         userError("TCB SetMCPriority: Truncated message.");
         current_syscall_error.type = seL4_TruncatedMessage;
         return EXCEPTION_SYSCALL_ERROR;
     }
 
    newMcp = getSyscallArg(0, buffer);
 
    status = checkPrio(newMcp);
     if (status != EXCEPTION_NONE) {
         userError("TCB SetMCPriority: Requested maximum controlled priority %lu too high (max %lu).",
                  (unsigned long) newMcp, (unsigned long) NODE_STATE(ksCurThread)->tcbMCP);
         return status;
     }
 