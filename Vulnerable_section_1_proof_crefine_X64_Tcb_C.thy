    (UNIV \<inter> {s. target_' s = tcb_ptr_to_ctcb_ptr target}
          \<inter> {s. (cRoot \<noteq> None \<or> buf \<noteq> None) \<longrightarrow> slot_' s = cte_Ptr slot}
          \<inter> {s. faultep_' s = option_to_0 faultep}
         \<inter> {s. mcp_' s = case_option 0 ucast mcp}
         \<inter> {s. priority_' s = case_option 0 ucast priority}
          \<inter> {s. case cRoot of None \<Rightarrow> True | Some (cRootCap, cRootSlot) \<Rightarrow> ccap_relation cRootCap (cRoot_newCap_' s)}
          \<inter> {s. cRoot_srcSlot_' s = cte_Ptr (option_to_0 (option_map snd cRoot))}
          \<inter> {s. case vRoot of None \<Rightarrow> True | Some (vRootCap, vRootSlot) \<Rightarrow> ccap_relation vRootCap (vRoot_newCap_' s)}
       = ((\<exists>bool. from_bool bool = val) \<longrightarrow> P (val \<noteq> 0))"
   by (auto simp: from_bool_0)
 
lemma thread_control_update_all_or:
  "thread_control_update_all
     = thread_control_update_mcp
        || thread_control_update_priority
        || thread_control_update_ipc_buffer
        || thread_control_update_space"
  apply (simp add: thread_control_flag_defs)
  done

 lemma getSyscallArg_ccorres_foo':
   "ccorres (\<lambda>a rv. rv = ucast (args ! n)) (\<lambda>x. ucast (ret__unsigned_long_' x))
          (sysargs_rel args buffer and sysargs_rel_n args buffer n)
   apply (frule ctcb_ptr_to_tcb_ptr_mask[OF tcb_aligned'], simp)
   done
 
lemma prioPropsFromWord_spec:
  "\<forall>s. \<Gamma> \<turnstile> \<lbrace>s. True\<rbrace> Call prioPropsFromWord_'proc
  \<lbrace> seL4_PrioProps_lift \<acute>ret__struct_seL4_PrioProps_C =
      \<lparr>  mcp_CL =  (\<^bsup>s\<^esup>w >> 8) && mask 8,
        prio_CL = (\<^bsup>s\<^esup>w) && mask 8 \<rparr>  \<rbrace>"
  by vcg (simp add: seL4_PrioProps_lift_def mask_def)

 lemma checkPrio_ccorres:
   "ccorres (syscall_error_rel \<currency> dc) (liftxf errstate id (K ()) ret__unsigned_long_')
      \<top>
      (UNIV \<inter> {s. prio_' s = prio}) []
      (checkPrio prio)
       (Call checkPrio_'proc)"
  apply (cinit lift: prio_')
    apply (clarsimp simp: liftE_bindE)
   apply (rule ccorres_pre_getCurThread)
    apply (rule ccorres_split_nothrow_novcg[where r'="\<lambda>rv rv'. rv' = ucast rv" and xf'=mcp_'])
       apply (rule_tac P="\<lambda>s. ct = ksCurThread s" in threadGet_vcg_corres_P)
        apply (rule allI, rule conseqPre, vcg)
        apply (clarsimp simp: rf_sr_ksCurThread obj_at'_def projectKOs
                              typ_heap_simps' ctcb_relation_def)
      (decodeTCBConfigure args cp slot extraCaps
             >>= invocationCatch thread isBlocking isCall InvokeTCB)
      (Call decodeTCBConfigure_'proc)"
   apply (cinit' lift: cap_' length___unsigned_long_' slot_' rootCaps_' buffer_' simp: decodeTCBConfigure_def)
    apply csymbr
    apply (clarsimp cong: StateSpace.state.fold_congs globals.fold_congs
                         tcb_cnode_index_defs size_of_def
                         option_to_0_def rf_sr_ksCurThread
                         StrictC'_thread_state_defs mask_eq_iff_w2p word_size
                        thread_control_update_all_or
                         from_bool_all_helper)
   apply (frule(1) tcb_at_h_t_valid [OF tcb_at_invs'])
  apply (simp add: ucast_ucast_mask exception_defs)
   apply (clarsimp simp: typ_heap_simps numeral_eqs isCap_simps valid_cap'_def capAligned_def
                         objBits_simps)
   done
 
 lemma decodeSetMCPriority_ccorres:
  "ccorres (intr_and_se_rel \<currency> dc) (liftxf errstate id (K ()) ret__unsigned_long_')
        (invs' and (\<lambda>s. ksCurThread s = thread)
               and ct_active' and sch_act_simple
               and (\<lambda>s. \<forall>rf \<in> zobj_refs' cp. ex_nonz_cap_to' rf s)
               and valid_cap' cp and K (isThreadCap cp)
               and sysargs_rel args buffer)
        (UNIV
             \<inter> {s. ccap_relation cp (cap_' s)}
             \<inter> {s. unat (length___unsigned_long_' s) = length args}
             \<inter> {s. buffer_' s = option_to_ptr buffer}) []
     (decodeSetMCPriority args cp
             >>= invocationCatch thread isBlocking isCall InvokeTCB)
      (Call decodeSetMCPriority_'proc)"
  apply (cinit' lift: cap_' length___unsigned_long_' buffer_' simp: decodeSetMCPriority_def)
   apply wpc
    apply (simp add: throwError_bind invocationCatch_def)
    apply (rule ccorres_from_vcg_split_throws[where P=\<top> and P'=UNIV])
     apply vcg
    apply (rule conseqPre, vcg)
    apply (clarsimp simp: throwError_def return_def intr_and_se_rel_def
                          exception_defs syscall_error_rel_def
                          syscall_error_to_H_cases)
   apply (rule ccorres_cond_false_seq; simp)
   apply (rule ccorres_add_return,
          ctac add: getSyscallArg_ccorres_foo'[where args=args and n=0 and buffer=buffer])
     apply (simp add: invocationCatch_use_injection_handler injection_bindE[OF refl refl]
                      bindE_assoc injection_handler_returnOk
                 del: Collect_const)
     apply (ctac add: ccorres_injection_handler_csum1[OF checkPrio_ccorres])
        apply (rule_tac P="newMcp \<le> ucast (max_word :: priority)"
               in ccorres_cross_over_guard_no_st)
        apply (simp add: ccorres_invocationCatch_Inr performInvocation_def)
        apply (ctac add: setThreadState_ccorres)
          apply csymbr
          apply csymbr
          apply csymbr
          apply csymbr
          apply (ctac (no_vcg) add: invokeTCB_ThreadControl_ccorres)
            apply simp
            apply (rule ccorres_alternative2)
            apply (rule ccorres_return_CE, simp+)[1]
           apply (rule ccorres_return_C_errorE, simp+)[1]
          apply wp
          apply simp
         apply (wp sts_invs_minor')
        apply (vcg exspec=setThreadState_modifies)
       apply simp
       apply (rename_tac err_c)
       apply (rule_tac P'="{s. err_c = errstate s}" in ccorres_from_vcg_split_throws)
         apply vcg
       apply (rule conseqPre, vcg)
       apply (clarsimp simp: throwError_def return_def intr_and_se_rel_def syscall_error_rel_def)
      apply simp
      apply (rule injection_handler_wp)
      apply (rule checkPrio_wp[simplified validE_R_def])
     apply (simp; vcg)
    apply wp
   apply (simp; vcg)
  apply (clarsimp simp: Collect_const_mem intr_and_se_rel_def
                        syscall_error_rel_def syscall_error_to_H_cases
                        exception_defs)
   apply (rule conjI)
    apply (clarsimp simp: ct_in_state'_def pred_tcb_at'
                          valid_cap'_def isCap_simps)
    apply (rule conjI, clarsimp simp: sysargs_rel_n_def n_msgRegisters_def)
    apply (clarsimp simp: maxPriority_def numPriorities_def)
    apply (fold max_word_def[where 'a=8, simplified])
   apply (frule mcpriority_tcb_at'_prio_bounded, simp)
   apply (auto simp: valid_tcb_state'_def le_ucast_ucast_le
              elim!: obj_at'_weakenE pred_tcb'_weakenE
              dest!: st_tcb_at_idle_thread')[1]
  apply (simp add: StrictC'_thread_state_defs mask_eq_iff_w2p word_size
                   option_to_0_def)
   apply (frule rf_sr_ksCurThread)
   apply (simp only: cap_get_tag_isCap[symmetric], drule(1) cap_get_tag_to_H)
  apply (clarsimp simp: valid_cap'_def capAligned_def)
   apply (intro conjI impI allI)
       apply (clarsimp simp: unat_eq_0 le_max_word_ucast_id)+
   done
 
 lemma decodeSetPriority_ccorres:
  "ccorres (intr_and_se_rel \<currency> dc) (liftxf errstate id (K ()) ret__unsigned_long_')
        (invs' and (\<lambda>s. ksCurThread s = thread)
               and ct_active' and sch_act_simple
               and (\<lambda>s. \<forall>rf \<in> zobj_refs' cp. ex_nonz_cap_to' rf s)
               and valid_cap' cp and K (isThreadCap cp)
               and sysargs_rel args buffer)
        (UNIV
             \<inter> {s. ccap_relation cp (cap_' s)}
             \<inter> {s. unat (length___unsigned_long_' s) = length args}
             \<inter> {s. buffer_' s = option_to_ptr buffer}) []
     (decodeSetPriority args cp
             >>= invocationCatch thread isBlocking isCall InvokeTCB)
      (Call decodeSetPriority_'proc)"
  apply (cinit' lift: cap_' length___unsigned_long_' buffer_' simp: decodeSetPriority_def)
   apply wpc
    apply (simp add: throwError_bind invocationCatch_def)
    apply (rule ccorres_from_vcg_split_throws[where P=\<top> and P'=UNIV])
     apply vcg
    apply (rule conseqPre, vcg)
    apply (clarsimp simp: throwError_def return_def intr_and_se_rel_def
                          exception_defs syscall_error_rel_def
                          syscall_error_to_H_cases)
   apply (rule ccorres_cond_false_seq; simp)
   apply (rule ccorres_add_return,
          ctac add: getSyscallArg_ccorres_foo'[where args=args and n=0 and buffer=buffer])
     apply (simp add: invocationCatch_use_injection_handler injection_bindE[OF refl refl]
                      bindE_assoc injection_handler_returnOk
                 del: Collect_const)
     apply (ctac add: ccorres_injection_handler_csum1[OF checkPrio_ccorres])
        apply (rule_tac P="newPrio \<le> ucast (max_word :: priority)"
               in ccorres_cross_over_guard_no_st)
        apply (simp add: ccorres_invocationCatch_Inr performInvocation_def)
        apply (ctac add: setThreadState_ccorres)
          apply csymbr
          apply csymbr
          apply csymbr
          apply csymbr
          apply (ctac (no_vcg) add: invokeTCB_ThreadControl_ccorres)
            apply simp
            apply (rule ccorres_alternative2)
            apply (rule ccorres_return_CE, simp+)[1]
           apply (rule ccorres_return_C_errorE, simp+)[1]
          apply wp
          apply simp
         apply (wp sts_invs_minor')
        apply (vcg exspec=setThreadState_modifies)
       apply simp
       apply (rename_tac err_c)
       apply (rule_tac P'="{s. err_c = errstate s}" in ccorres_from_vcg_split_throws)
         apply vcg
       apply (rule conseqPre, vcg)
       apply (clarsimp simp: throwError_def return_def intr_and_se_rel_def syscall_error_rel_def)
      apply simp
      apply (rule injection_handler_wp)
      apply (rule checkPrio_wp[simplified validE_R_def])
     apply (simp; vcg)
    apply wp
   apply (simp; vcg)
  apply (clarsimp simp: Collect_const_mem intr_and_se_rel_def
                        syscall_error_rel_def syscall_error_to_H_cases
                        exception_defs)
   apply (rule conjI)
    apply (clarsimp simp: ct_in_state'_def pred_tcb_at'
                          valid_cap'_def isCap_simps)
    apply (rule conjI, clarsimp simp: sysargs_rel_n_def n_msgRegisters_def)
    apply (clarsimp simp: maxPriority_def numPriorities_def)
    apply (fold max_word_def[where 'a=8, simplified])
   apply (frule mcpriority_tcb_at'_prio_bounded, simp)
   apply (auto simp: valid_tcb_state'_def le_ucast_ucast_le
              elim!: obj_at'_weakenE pred_tcb'_weakenE
              dest!: st_tcb_at_idle_thread')[1]
  apply (simp add: StrictC'_thread_state_defs mask_eq_iff_w2p word_size
                   option_to_0_def)
   apply (frule rf_sr_ksCurThread)
   apply (simp only: cap_get_tag_isCap[symmetric], drule(1) cap_get_tag_to_H)
  apply (clarsimp simp: valid_cap'_def capAligned_def)
   apply (intro conjI impI allI)
       apply (clarsimp simp: unat_eq_0 le_max_word_ucast_id)+
   done
 
 lemma decodeSetIPCBuffer_ccorres:
    apply csymbr
    apply (rule ccorres_cond_false_seq)
    apply csymbr
    apply (simp add: interpret_excaps_test_null excaps_map_Nil if_1_0_0
                del: Collect_const)
    apply wpc
       apply (rule ccorres_return_CE, simp+)[1]
      apply (rule ccorres_return_C_errorE, simp+)[1]
     apply wp
    apply (rule ccorres_Cond_rhs)
     apply simp
     apply (rule ccorres_add_returnOk, ctac(no_vcg) add: decodeSetIPCBuffer_ccorres [where buffer=buffer])