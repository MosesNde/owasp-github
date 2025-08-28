    (UNIV \<inter> {s. target_' s = tcb_ptr_to_ctcb_ptr target}
          \<inter> {s. (cRoot \<noteq> None \<or> buf \<noteq> None) \<longrightarrow> slot_' s = cte_Ptr slot}
          \<inter> {s. faultep_' s = option_to_0 faultep}
         \<inter> {s. mcp_' s = case_option 0 (ucast o fst) mcp}
         \<inter> {s. priority_' s = case_option 0 (ucast o fst) priority}
          \<inter> {s. case cRoot of None \<Rightarrow> True | Some (cRootCap, cRootSlot) \<Rightarrow> ccap_relation cRootCap (cRoot_newCap_' s)}
          \<inter> {s. cRoot_srcSlot_' s = cte_Ptr (option_to_0 (option_map snd cRoot))}
          \<inter> {s. case vRoot of None \<Rightarrow> True | Some (vRootCap, vRootSlot) \<Rightarrow> ccap_relation vRootCap (vRoot_newCap_' s)}
       = ((\<exists>bool. from_bool bool = val) \<longrightarrow> P (val \<noteq> 0))"
   by (auto simp: from_bool_0)
 
 lemma getSyscallArg_ccorres_foo':
   "ccorres (\<lambda>a rv. rv = ucast (args ! n)) (\<lambda>x. ucast (ret__unsigned_long_' x))
          (sysargs_rel args buffer and sysargs_rel_n args buffer n)
   apply (frule ctcb_ptr_to_tcb_ptr_mask[OF tcb_aligned'], simp)
   done
 
 lemma checkPrio_ccorres:
   "ccorres (syscall_error_rel \<currency> dc) (liftxf errstate id (K ()) ret__unsigned_long_')
      (tcb_at' auth)
      (UNIV \<inter> {s. prio_' s = prio} \<inter> {s. auth_' s = tcb_ptr_to_ctcb_ptr auth}) []
      (checkPrio prio auth)
       (Call checkPrio_'proc)"
  apply (cinit lift: prio_' auth_')
    apply (clarsimp simp: liftE_bindE)
    apply (rule ccorres_split_nothrow_novcg[where r'="\<lambda>rv rv'. rv' = ucast rv" and xf'=mcp_'])
       apply (rule threadGet_vcg_corres)
        apply (rule allI, rule conseqPre, vcg)
        apply (clarsimp simp: rf_sr_ksCurThread obj_at'_def projectKOs
                              typ_heap_simps' ctcb_relation_def)
           ctac add: getSyscallArg_ccorres_foo[where args=args and n=0 and buffer=buffer])
      apply (rule ccorres_add_return,
             ctac add: getSyscallArg_ccorres_foo'[where args=args and n=1 and buffer=buffer])
        apply (rule ccorres_add_return,
               ctac add: getSyscallArg_ccorres_foo[where args=args and n=2 and buffer=buffer])
          apply (rule ccorres_add_return,
                 ctac add: getSyscallArg_ccorres_foo[where args=args and n=3 and buffer=buffer])
           apply csymbr
           apply (rule getSlotCap_ccorres_fudge_n[where vals=extraCaps and n=0])
           apply (rule ccorres_move_c_guard_cte)
           apply ctac
             apply (rule ccorres_assert2)
              apply csymbr
              apply (rule ccorres_move_c_guard_cte)
             apply (rule getSlotCap_ccorres_fudge_n[where vals=extraCaps and n=1])
              apply ctac
                apply (rule ccorres_assert2)
                apply csymbr
               apply (rule getSlotCap_ccorres_fudge_n[where vals=extraCaps and n=2])
                apply (rule ccorres_move_c_guard_cte)
                apply ctac
                  apply (rule ccorres_assert2)
                 apply (simp add: decodeSetIPCBuffer_def split_def
                                  bindE_assoc invocationCatch_use_injection_handler
                                  injection_bindE[OF refl refl] injection_handler_returnOk
                                  injection_handler_If
                             del: Collect_const cong: if_cong)
                 apply (rule_tac xf'="\<lambda>s. (bufferCap_' s, bufferSlot_' s)" and
                                 r'="\<lambda>v (cp', sl'). case v of None \<Rightarrow> args ! 3 = 0 \<and> sl' = cte_Ptr 0
                                                            | Some (cp, sl) \<Rightarrow> ccap_relation cp cp'
                                                                               \<and> args ! 3 \<noteq> 0
                                                                               \<and> sl' = cte_Ptr sl"
                                 in ccorres_splitE)
                     apply (rule ccorres_cond2[where R=\<top>])
                       apply (clarsimp simp add: Collect_const_mem numeral_eqs)
                      apply (rule_tac P="\<lambda>s. args ! 3 = 0" in ccorres_from_vcg[where P'=UNIV])
                      apply (rule allI, rule conseqPre, vcg)
                      apply (clarsimp simp: returnOk_def return_def)
                     apply (rule ccorres_rhs_assoc)+
                     apply (rule ccorres_split_nothrowE)
                          apply (simp add: numeral_eqs)
                          apply (ctac add: ccorres_injection_handler_csum1[OF deriveCap_ccorres])
                         apply ceqv
                        apply simp
                        apply (clarsimp simp: numeral_eqs)
                        apply csymbr
                        apply (rule ccorres_split_nothrowE)
                             apply (ctac add: ccorres_injection_handler_csum1[OF checkValidIPCBuffer_ccorres])
                            apply ceqv
                           apply (match premises in "ccap_relation _ (deriveCap_ret_C.cap_C ccap)" for ccap
                                    \<Rightarrow> \<open>rule ccorres_from_vcg
                                          [where P'="{s. bufferCap_' s = (deriveCap_ret_C.cap_C ccap)
                                                         \<and> bufferSlot_' s = cte_Ptr (snd (extraCaps ! 2))}"
                                             and P="\<lambda>s. args ! 3 \<noteq> 0"]\<close>)
                           apply (rule allI, rule conseqPre, vcg)
                           apply (clarsimp simp: returnOk_def return_def numeral_eqs)
                          apply (rule_tac P'="{s. err' = errstate s}"
                                          in ccorres_from_vcg_throws[where P=\<top>])
                          apply (rule allI, rule conseqPre, vcg)
                          apply (clarsimp simp: throwError_def return_def
                                                syscall_error_rel_def
                                                intr_and_se_rel_def)
                         apply wp
                        apply simp
                        apply (vcg exspec=checkValidIPCBuffer_modifies)
                       apply simp
                       apply (rule_tac P'="{s. err' = errstate s}"
                                       in  ccorres_from_vcg_split_throws[where P=\<top>])
                        apply vcg
                       apply (rule conseqPre, vcg)
                       apply (clarsimp simp: throwError_def return_def
                                             intr_and_se_rel_def syscall_error_rel_def)
                      apply simp
                      apply (wp injection_wp_E [OF refl])
                     apply (simp add: all_ex_eq_helper Collect_const_mem numeral_eqs)
                     apply (vcg exspec=deriveCap_modifies)
                    apply (rule ceqv_tuple2, ceqv, ceqv)
                   apply (rename_tac rv'dc)
                   apply (rule_tac P="P (fst rv'dc) (snd rv'dc)"
                               and P'="P' (fst rv'dc) (snd rv'dc)"
                               for P P' in ccorres_inst)
                   apply (clarsimp simp: tcb_cnode_index_defs
                                           [THEN ptr_add_assertion_positive
                                             [OF ptr_add_assertion_positive_helper]]
                                   simp del: Collect_const)
                    apply csymbr
                   apply (rule ccorres_move_array_assertion_tcb_ctes ccorres_Guard_Seq)+
                   apply (simp add: decodeSetSpace_def injection_bindE[OF refl] split_def
                                del: Collect_const)
                   apply (simp add: injection_liftE[OF refl] bindE_assoc
                                    liftM_def getThreadCSpaceRoot
                                    getThreadVSpaceRoot del: Collect_const)
                   apply (simp add: liftE_bindE del: Collect_const)
                   apply (rule ccorres_rhs_assoc)+
                   apply (ctac add: slotCapLongRunningDelete_ccorres)
                     apply (rule ccorres_move_array_assertion_tcb_ctes)
                     apply (simp del: Collect_const)
                     apply csymbr
                     apply (clarsimp simp add: if_1_0_0 from_bool_0
                                     simp del: Collect_const)
                     apply (rule ccorres_Cond_rhs_Seq)
                      apply (rule ccorres_symb_exec_l3
                                    [OF _ _ _ empty_fail_slotCapLongRunningDelete])
                        apply (simp add: unlessE_def injection_handler_throwError
                                    cong: StateSpace.state.fold_congs globals.fold_congs)
                        apply (rule ccorres_cond_true_seq)
                        apply (rule syscall_error_throwError_ccorres_n)
                        apply (simp add: syscall_error_to_H_cases)
                       apply wp+
                     apply (rule ccorres_rhs_assoc)+
                     apply csymbr
                     apply (simp del: Collect_const)
                     apply (rule ccorres_move_array_assertion_tcb_ctes ccorres_Guard_Seq
                                 ccorres_rhs_assoc)+
                     apply (ctac add: slotCapLongRunningDelete_ccorres)
                       apply (rule ccorres_move_array_assertion_tcb_ctes)
                       apply (simp del: Collect_const)
                       apply csymbr
                       apply (clarsimp simp add: if_1_0_0 from_bool_0
                                       simp del: Collect_const)
                       apply (rule ccorres_Cond_rhs_Seq)
                        apply (simp add: unlessE_def injection_handler_throwError
                                    cong: StateSpace.state.fold_congs globals.fold_congs)
                        apply (rule syscall_error_throwError_ccorres_n)
                        apply (simp add: syscall_error_to_H_cases)
                       apply (simp add: unlessE_def injection_handler_returnOk
                                   del: Collect_const)
                       apply (rule ccorres_add_return,
                              rule_tac r'="\<lambda>rv rv'. ccap_relation
                                                      (if args ! 1 = 0
                                                       then fst (hd extraCaps)
                                                       else updateCapData False (args ! 1) (fst (hd extraCaps))) rv'"
                                   and xf'="cRootCap_'"
                                   in ccorres_split_nothrow)
                           apply (rule_tac P'="{s. cRootCap = cRootCap_' s}"
                                          in ccorres_from_vcg[where P=\<top>])
                           apply (rule allI, rule conseqPre, vcg)
                           apply (subgoal_tac "extraCaps \<noteq> []")
                            apply (clarsimp simp: returnOk_def return_def hd_conv_nth false_def)
                            apply fastforce
                           apply clarsimp
                           apply ceqv
                         apply (ctac add: ccorres_injection_handler_csum1
                                            [OF deriveCap_ccorres])
                            apply (simp add: Collect_False del: Collect_const)
                            apply (csymbr, csymbr)
                            apply (simp add: cap_get_tag_isCap cnode_cap_case_if
                                        del: Collect_const)
                            apply (rule ccorres_Cond_rhs_Seq)
                             apply (simp add: injection_handler_throwError
                                         cong: StateSpace.state.fold_congs globals.fold_congs)
                             apply (rule syscall_error_throwError_ccorres_n)
                             apply (simp add: syscall_error_to_H_cases)
                            apply (simp add: injection_handler_returnOk del: Collect_const)
                            apply (rule ccorres_add_return,
                                   rule_tac r'="\<lambda>rv rv'. ccap_relation
                                                           (if args ! 2 = 0
                                                            then fst (extraCaps ! Suc 0)
                                                            else updateCapData False (args ! 2) (fst (extraCaps ! Suc 0))) rv'"
                                        and xf'="vRootCap_'"
                                        in ccorres_split_nothrow)
                                apply (rule_tac P'="{s. vRootCap = vRootCap_' s}"
                                                in ccorres_from_vcg[where P=\<top>])
                                apply (rule allI, rule conseqPre, vcg)
                                apply (clarsimp simp: returnOk_def return_def
                                                      hd_drop_conv_nth2 false_def)
                                apply fastforce
                               apply ceqv
                              apply (ctac add: ccorres_injection_handler_csum1
                                                 [OF deriveCap_ccorres])
                                 apply (simp add: Collect_False del: Collect_const)
                                 apply csymbr
                                 apply csymbr
                                 apply (simp add: from_bool_0 isValidVTableRoot_conv del: Collect_const)
                                 apply (rule ccorres_Cond_rhs_Seq)
                                  apply (simp add: injection_handler_throwError
                                              cong: StateSpace.state.fold_congs globals.fold_congs)
                                  apply (rule syscall_error_throwError_ccorres_n)
                                  apply (simp add: syscall_error_to_H_cases)
                                 apply (simp add: injection_handler_returnOk ccorres_invocationCatch_Inr
                                                  performInvocation_def)
                                 apply (ctac add: setThreadState_ccorres)
                                   apply csymbr
                                   apply (ctac(no_vcg) add: invokeTCB_ThreadControl_ccorres)
                                     apply (simp, rule ccorres_alternative2)
                                     apply (rule ccorres_return_CE, simp+)
                                    apply (rule ccorres_return_C_errorE, simp+)[1]
                                   apply wp
                                  apply (simp add: o_def)
                                  apply (wp sts_invs_minor' hoare_case_option_wp)
                                 apply (simp add: Collect_const_mem cintr_def intr_and_se_rel_def
                                                  exception_defs
                                            cong: option.case_cong)
                                 apply (vcg exspec=setThreadState_modifies)
                                 apply simp
                                apply (rule ccorres_split_throws, rule ccorres_return_C_errorE, simp+)
                                 apply vcg
                               apply simp
                               apply (wp injection_wp_E[OF refl] hoare_drop_imps)
                              apply (vcg exspec=deriveCap_modifies)
                             apply (simp add: pred_conj_def cong: if_cong)
                             apply wp
                            apply (simp add: Collect_const_mem)
                            apply (vcg)
                           apply simp
                           apply (rule ccorres_split_throws, rule ccorres_return_C_errorE, simp+)
                           apply vcg
                          apply (simp cong: if_cong)
                          apply (wp injection_wp_E[OF refl] hoare_drop_imps)
                         apply (simp add: Collect_const_mem intr_and_se_rel_def
                                          syscall_error_rel_def exception_defs
                                    cong: option.case_cong sum.case_cong)
                         apply (simp add: all_ex_eq_helper numeral_eqs)
                         apply (vcg exspec=deriveCap_modifies)
                        apply (simp cong: if_cong)
                        apply wp
                       apply (simp add: Collect_const_mem del: Collect_const)
                       apply vcg
                      apply (simp cong: if_cong)
                      apply (wp | wp_once hoare_drop_imps)+
                     apply (simp add: Collect_const_mem all_ex_eq_helper
                                cong: option.case_cong)
                     apply (vcg exspec=slotCapLongRunningDelete_modifies)
                    apply (simp cong: if_cong)
                    apply (wp | wp_once hoare_drop_imps)+
                   apply (simp add: Collect_const_mem)
                   apply (vcg exspec=slotCapLongRunningDelete_modifies)
                  apply (simp add: pred_conj_def cong: if_cong)
                  apply (wp injection_wp_E[OF refl] checkValidIPCBuffer_ArchObject_wp)
                  apply simp
                   apply (wp | wp_once hoare_drop_imps)+
                 apply (simp add: Collect_const_mem all_ex_eq_helper)
                 apply (rule_tac P="{s. cRootCap_' s = cRootCap \<and> vRootCap_' s = vRootCap
                                        \<and> bufferAddr_' s = args ! 3
                                        \<and> ccap_relation cp cap' \<and> isThreadCap cp
                                        \<and> is_aligned (capTCBPtr cp) tcbBlockSizeBits
                                        \<and> ksCurThread_' (globals s) = tcb_ptr_to_ctcb_ptr thread}"
                          in conseqPre)
                  apply (simp add: cong: option.case_cong)
                  apply (vcg exspec=deriveCap_modifies exspec=checkValidIPCBuffer_modifies)
                 apply (clarsimp simp: excaps_map_def Collect_const_mem ccHoarePost_def
                                       numeral_eqs
                                  cong: option.case_cong)
                 apply (frule interpret_excaps_eq[rule_format, where n=0], clarsimp)
                 apply (frule interpret_excaps_eq[rule_format, where n=1], clarsimp)
                 apply (frule interpret_excaps_eq[rule_format, where n=2], clarsimp)
                 apply (clarsimp simp: mask_def[where n=4] ccap_rights_relation_def
                                       rightsFromWord_wordFromRights capTCBPtr_eq
                                       ptr_val_tcb_ptr_mask2[unfolded mask_def objBits_defs, simplified]
                                       tcb_cnode_index_defs size_of_def
                                       option_to_0_def rf_sr_ksCurThread
                                       StrictC'_thread_state_defs mask_eq_iff_w2p word_size
                                       from_bool_all_helper all_ex_eq_helper
                                       ucast_ucast_mask objBits_defs)
                 apply (subgoal_tac "args \<noteq> [] \<and> extraCaps \<noteq> []")
                  apply (simp add: word_sle_def cap_get_tag_isCap numeral_eqs
                                   hd_conv_nth hd_drop_conv_nth2
                                   word_FF_is_mask split_def
                                   thread_control_update_priority_def
                                   thread_control_update_mcp_def
                                   thread_control_update_space_def
                                   thread_control_update_ipc_buffer_def)
                  apply (auto split: option.split elim!: inl_inrE)[1]
                  apply (fastforce+)[2]
                apply clarsimp
                apply (strengthen if_n_updateCapData_valid_strg)
                 apply (wp | wp_once hoare_drop_imps)+
               apply (clarsimp simp: Collect_const_mem all_ex_eq_helper
                               cong: option.case_cong)
                apply vcg
               apply simp
               apply (wp | wp_once hoare_drop_imps)+
             apply (simp add: Collect_const_mem all_ex_eq_helper)
              apply vcg
            apply simp
            apply (wp | wp_once hoare_drop_imps)+
           apply (wpsimp | vcg exspec=getSyscallArg_modifies)+
  apply (clarsimp simp: Collect_const_mem all_ex_eq_helper)
   apply (rule conjI)
    apply (clarsimp simp: idButNot_def interpret_excaps_test_null
                          excaps_map_def neq_Nil_conv)
    apply (clarsimp simp: sysargs_rel_to_n word_less_nat_alt)
    apply (frule invs_mdb')
    apply (frule(2) tcb_at_capTCBPtr_CL)
    apply (rule conjI, fastforce)
    apply (drule interpret_excaps_eq)
                         tcb_cnode_index_defs size_of_def
                         option_to_0_def rf_sr_ksCurThread
                         StrictC'_thread_state_defs mask_eq_iff_w2p word_size
                         from_bool_all_helper)
   apply (frule(1) tcb_at_h_t_valid [OF tcb_at_invs'])
   apply (clarsimp simp: typ_heap_simps numeral_eqs isCap_simps valid_cap'_def capAligned_def
                         objBits_simps)
   done
 

lemma not_isThreadCap_case:
  "\<lbrakk>\<not>isThreadCap cap\<rbrakk> \<Longrightarrow>
   (case cap of ThreadCap x \<Rightarrow> f x | _ \<Rightarrow> g) = g"
  by (clarsimp simp: isThreadCap_def split: capability.splits)

 lemma decodeSetMCPriority_ccorres:
  "\<lbrakk>interpret_excaps extraCaps' = excaps_map extraCaps\<rbrakk> \<Longrightarrow>
   ccorres (intr_and_se_rel \<currency> dc) (liftxf errstate id (K ()) ret__unsigned_long_')
        (invs' and (\<lambda>s. ksCurThread s = thread)
               and ct_active' and sch_act_simple
              and (excaps_in_mem extraCaps \<circ> ctes_of)
               and (\<lambda>s. \<forall>rf \<in> zobj_refs' cp. ex_nonz_cap_to' rf s)
               and valid_cap' cp and K (isThreadCap cp)
              and (\<lambda>s. \<forall>v \<in> set extraCaps.
                             ex_cte_cap_wp_to' isCNodeCap (snd v) s)
              and (\<lambda>s. \<forall>v \<in> set extraCaps.
                             s \<turnstile>' fst v \<and> cte_at' (snd v) s)
               and sysargs_rel args buffer)
        (UNIV
             \<inter> {s. ccap_relation cp (cap_' s)}
             \<inter> {s. unat (length___unsigned_long_' s) = length args}
            \<inter> {s. excaps_' s = extraCaps'}
             \<inter> {s. buffer_' s = option_to_ptr buffer}) []
     (decodeSetMCPriority args cp extraCaps
             >>= invocationCatch thread isBlocking isCall InvokeTCB)
      (Call decodeSetMCPriority_'proc)"
  supply Collect_const[simp del]
  supply dc_simp[simp del]
  apply (cinit' lift: cap_' length___unsigned_long_' excaps_' buffer_' simp: decodeSetMCPriority_def)
   apply (simp cong: StateSpace.state.fold_congs globals.fold_congs)
   apply (rule ccorres_rhs_assoc2)
   apply (rule_tac xf'=ret__int_' and R'=UNIV and R=\<top> and
                   val="from_bool (length args = 0 \<or> length extraCaps = 0)" in
                   ccorres_symb_exec_r_known_rv)
      apply vcg
      apply (force simp: interpret_excaps_test_null excaps_map_def from_bool_def unat_eq_0
                   split: bool.splits)
     apply ceqv
    apply clarsimp
    apply wpc
     (* Case args = [] *)
     apply (rule ccorres_cond_true_seq)
     apply (clarsimp simp: throwError_bind invocationCatch_def)
     apply (rule ccorres_rhs_assoc)
     apply (ccorres_rewrite)
     apply (rule syscall_error_throwError_ccorres_n)
     apply (simp add: syscall_error_to_H_cases)
    (* Case args is Cons *)
    apply wpc
     (* Sub-case extraCaps = [] *)
     apply (rule ccorres_cond_true_seq)
     apply (clarsimp simp: throwError_bind invocationCatch_def)
     apply (rule ccorres_rhs_assoc)
     apply (ccorres_rewrite)
     apply (rule syscall_error_throwError_ccorres_n)
     apply (simp add: syscall_error_to_H_cases)
    (* Main case where args and extraCaps are both Cons *)
    apply (rule ccorres_cond_false_seq)
    apply (simp add: split_def)
    apply (rule ccorres_add_return,
           ctac add: getSyscallArg_ccorres_foo'[where args=args and n=0 and buffer=buffer])
      apply (rule getSlotCap_ccorres_fudge_n[where vals=extraCaps and n=0])
      apply (rule ccorres_move_c_guard_cte)
      apply ctac
        apply csymbr
        apply (simp add: cap_get_tag_isCap cong: call_ignore_cong)
        apply (rule ccorres_assert2)
        apply (rule ccorres_Cond_rhs_Seq)
         apply (rule ccorres_rhs_assoc)
         apply ccorres_rewrite
         apply (clarsimp simp: not_isThreadCap_case throwError_bind invocationCatch_def
                         simp del: id_simps)
         apply (rule syscall_error_throwError_ccorres_n)
         apply (simp add: syscall_error_to_H_cases)
        apply (clarsimp simp: isCap_simps)
        apply csymbr
        apply csymbr
        (* Pre-conditions need to depend on the inner value of the thread cap *)
        apply (rule ccorres_inst[where P="Q (capTCBPtr (fst (extraCaps ! 0)))" and
                                       P'="Q' (capTCBPtr (fst (extraCaps ! 0)))" for Q Q'])
        apply (clarsimp simp: capTCBPtr_eq isCap_simps invocationCatch_use_injection_handler
                              injection_bindE[OF refl refl] bindE_assoc injection_handler_returnOk)
        apply (ctac add: ccorres_injection_handler_csum1[OF checkPrio_ccorres])
           apply (rule_tac P="hd args \<le> ucast (max_word :: priority)"
                           in ccorres_cross_over_guard_no_st)
           apply (simp add: ccorres_invocationCatch_Inr performInvocation_def)
           apply ccorres_rewrite
           apply (ctac add: setThreadState_ccorres)
             apply (simp add: invocationCatch_def)
             apply ccorres_rewrite
             apply csymbr
             apply csymbr
             apply csymbr
             apply csymbr
             apply (ctac (no_vcg) add: invokeTCB_ThreadControl_ccorres)
               (* HACK: delete rules from the simpset to avoid the RVRs getting out of sync *)
               apply (clarsimp simp del: intr_and_se_rel_simps comp_apply dc_simp)
               apply (rule ccorres_alternative2)
               apply (rule ccorres_return_CE; simp)
              apply (rule ccorres_return_C_errorE; simp)
             apply wp
            apply (wpsimp wp: sts_invs_minor')
           apply simp
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
         apply vcg
       apply (wp | simp | wpc | wp_once hoare_drop_imps)+
      apply vcg
     apply wp
    apply (vcg exspec=getSyscallArg_modifies)
   apply (clarsimp simp: EXCEPTION_SYSCALL_ERROR_def EXCEPTION_NONE_def)
   apply vcg
  apply clarsimp
   apply (rule conjI)
    apply (clarsimp simp: ct_in_state'_def pred_tcb_at'
                          valid_cap'_def isCap_simps)
    apply (rule conjI, clarsimp simp: sysargs_rel_n_def n_msgRegisters_def)
    apply (clarsimp simp: maxPriority_def numPriorities_def)
    apply (fold max_word_def[where 'a=8, simplified])
   apply (rule conjI, clarsimp)
    apply (frule mcpriority_tcb_at'_prio_bounded, simp)
    apply (auto simp: valid_tcb_state'_def le_ucast_ucast_le
                elim!: obj_at'_weakenE pred_tcb'_weakenE
                dest!: st_tcb_at_idle_thread')[1]
   apply (clarsimp simp: interpret_excaps_eq excaps_map_def)
  apply (simp add: StrictC'_thread_state_defs mask_eq_iff_w2p word_size option_to_0_def)
   apply (frule rf_sr_ksCurThread)
   apply (simp only: cap_get_tag_isCap[symmetric], drule(1) cap_get_tag_to_H)
  apply (clarsimp simp: valid_cap'_def capAligned_def interpret_excaps_eq excaps_map_def)
   apply (intro conjI impI allI)
   apply (clarsimp simp: unat_eq_0 le_max_word_ucast_id cap_get_tag_isCap_unfolded_H_cap isCap_simps)+
   done
 
 lemma decodeSetPriority_ccorres:
  "\<lbrakk>interpret_excaps extraCaps' = excaps_map extraCaps\<rbrakk> \<Longrightarrow>
   ccorres (intr_and_se_rel \<currency> dc) (liftxf errstate id (K ()) ret__unsigned_long_')
        (invs' and (\<lambda>s. ksCurThread s = thread)
               and ct_active' and sch_act_simple
              and (excaps_in_mem extraCaps \<circ> ctes_of)
               and (\<lambda>s. \<forall>rf \<in> zobj_refs' cp. ex_nonz_cap_to' rf s)
               and valid_cap' cp and K (isThreadCap cp)
              and (\<lambda>s. \<forall>v \<in> set extraCaps.
                             ex_cte_cap_wp_to' isCNodeCap (snd v) s)
              and (\<lambda>s. \<forall>v \<in> set extraCaps.
                             s \<turnstile>' fst v \<and> cte_at' (snd v) s)
               and sysargs_rel args buffer)
        (UNIV
             \<inter> {s. ccap_relation cp (cap_' s)}
             \<inter> {s. unat (length___unsigned_long_' s) = length args}
            \<inter> {s. excaps_' s = extraCaps'}
             \<inter> {s. buffer_' s = option_to_ptr buffer}) []
     (decodeSetPriority args cp extraCaps
             >>= invocationCatch thread isBlocking isCall InvokeTCB)
      (Call decodeSetPriority_'proc)"
  supply Collect_const[simp del] dc_simp[simp del]
  apply (cinit' lift: cap_' length___unsigned_long_' excaps_' buffer_' simp: decodeSetPriority_def)
     apply (simp cong: StateSpace.state.fold_congs globals.fold_congs)
   apply (rule ccorres_rhs_assoc2)
   apply (rule_tac xf'=ret__int_' and R'=UNIV and R=\<top> and
                   val="from_bool (length args = 0 \<or> length extraCaps = 0)" in
                   ccorres_symb_exec_r_known_rv)
      apply vcg
      apply (force simp: interpret_excaps_test_null excaps_map_def from_bool_def unat_eq_0
                   split: bool.splits)
     apply ceqv
    apply clarsimp
    apply wpc
     (* Case args = [] *)
     apply (rule ccorres_cond_true_seq)
     apply (clarsimp simp: throwError_bind invocationCatch_def)
     apply (rule ccorres_rhs_assoc)
     apply (ccorres_rewrite)
     apply (rule syscall_error_throwError_ccorres_n)
     apply (simp add: syscall_error_to_H_cases)
    (* Case args is Cons *)
    apply wpc
     (* Sub-case extraCaps = [] *)
     apply (rule ccorres_cond_true_seq)
     apply (clarsimp simp: throwError_bind invocationCatch_def)
     apply (rule ccorres_rhs_assoc)
     apply (ccorres_rewrite)
     apply (rule syscall_error_throwError_ccorres_n)
     apply (simp add: syscall_error_to_H_cases)
    (* Main case where args and extraCaps are both Cons *)
    apply (rule ccorres_cond_false_seq)
    apply (simp add: split_def)
    apply (rule ccorres_add_return,
           ctac add: getSyscallArg_ccorres_foo'[where args=args and n=0 and buffer=buffer])
      apply (rule getSlotCap_ccorres_fudge_n[where vals=extraCaps and n=0])
      apply (rule ccorres_move_c_guard_cte)
      apply ctac
        apply csymbr
        apply (simp add: cap_get_tag_isCap cong: call_ignore_cong)
        apply (rule ccorres_assert2)
        apply (rule ccorres_Cond_rhs_Seq)
         apply (rule ccorres_rhs_assoc)
         apply ccorres_rewrite
         apply (clarsimp simp: not_isThreadCap_case throwError_bind invocationCatch_def
                         simp del: id_simps)
         apply (rule syscall_error_throwError_ccorres_n)
         apply (simp add: syscall_error_to_H_cases)
        apply (clarsimp simp: isCap_simps)
        apply csymbr
        apply csymbr
        (* Pre-conditions need to depend on the inner value of the thread cap *)
        apply (rule ccorres_inst[where P="Q (capTCBPtr (fst (extraCaps ! 0)))" and
                                       P'="Q' (capTCBPtr (fst (extraCaps ! 0)))" for Q Q'])
        apply (clarsimp simp: capTCBPtr_eq isCap_simps invocationCatch_use_injection_handler
                              injection_bindE[OF refl refl] bindE_assoc injection_handler_returnOk)
        apply (ctac add: ccorres_injection_handler_csum1[OF checkPrio_ccorres])
           apply (rule_tac P="hd args \<le> ucast (max_word :: priority)"
                           in ccorres_cross_over_guard_no_st)
           apply (simp add: ccorres_invocationCatch_Inr performInvocation_def)
           apply ccorres_rewrite
           apply (ctac add: setThreadState_ccorres)
             apply (simp add: invocationCatch_def)
             apply ccorres_rewrite
             apply csymbr
             apply csymbr
             apply csymbr
             apply csymbr
             apply (ctac (no_vcg) add: invokeTCB_ThreadControl_ccorres)
               (* HACK: delete rules from the simpset to avoid the RVRs getting out of sync *)
               apply (clarsimp simp del: intr_and_se_rel_simps comp_apply dc_simp)
               apply (rule ccorres_alternative2)
               apply (rule ccorres_return_CE; simp)
              apply (rule ccorres_return_C_errorE; simp)
             apply wp
            apply (wpsimp wp: sts_invs_minor')
           apply simp
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
         apply vcg
       apply (wp | simp | wpc | wp_once hoare_drop_imps)+
      apply vcg
     apply wp
    apply (vcg exspec=getSyscallArg_modifies)
   apply (clarsimp simp: EXCEPTION_SYSCALL_ERROR_def EXCEPTION_NONE_def)
   apply vcg
  apply clarsimp
   apply (rule conjI)
    apply (clarsimp simp: ct_in_state'_def pred_tcb_at'
                          valid_cap'_def isCap_simps)
    apply (rule conjI, clarsimp simp: sysargs_rel_n_def n_msgRegisters_def)
    apply (clarsimp simp: maxPriority_def numPriorities_def)
    apply (fold max_word_def[where 'a=8, simplified])
   apply (rule conjI, clarsimp)
    apply (frule mcpriority_tcb_at'_prio_bounded, simp)
    apply (auto simp: valid_tcb_state'_def le_ucast_ucast_le
                elim!: obj_at'_weakenE pred_tcb'_weakenE
                dest!: st_tcb_at_idle_thread')[1]
   apply (clarsimp simp: interpret_excaps_eq excaps_map_def)
  apply (simp add: StrictC'_thread_state_defs mask_eq_iff_w2p word_size option_to_0_def)
   apply (frule rf_sr_ksCurThread)
   apply (simp only: cap_get_tag_isCap[symmetric], drule(1) cap_get_tag_to_H)
  apply (clarsimp simp: valid_cap'_def capAligned_def interpret_excaps_eq excaps_map_def)
   apply (intro conjI impI allI)
   apply (clarsimp simp: unat_eq_0 le_max_word_ucast_id cap_get_tag_isCap_unfolded_H_cap isCap_simps)+
  done

lemma ucast_le_8_32_equiv:
  "x \<le> UCAST (8 \<rightarrow> 32) max_word \<Longrightarrow>
  (UCAST (32 \<rightarrow> 8) x \<le> y) = (x \<le> UCAST (8 \<rightarrow> 32) y)"
  apply (rule iffI)
   apply (word_bitwise; simp)
  apply (simp add: le_ucast_ucast_le)
  done

lemma mcpriority_tcb_at'_le_ucast:
  "pred_tcb_at' itcbMCP (\<lambda>mcp. x \<le> UCAST(8 \<rightarrow> 32) mcp) v s \<Longrightarrow>
   pred_tcb_at' itcbMCP (\<lambda>mcp. UCAST(32 \<rightarrow> 8) x \<le> mcp) v s"
  apply (clarsimp simp: ucast_le_8_32_equiv mcpriority_tcb_at'_prio_bounded)
  done

lemma decodeSetSchedParams_ccorres:
  "\<lbrakk>interpret_excaps extraCaps' = excaps_map extraCaps\<rbrakk> \<Longrightarrow>
   ccorres (intr_and_se_rel \<currency> dc) (liftxf errstate id (K ()) ret__unsigned_long_')
       (invs' and (\<lambda>s. ksCurThread s = thread)
              and ct_active' and sch_act_simple
              and (excaps_in_mem extraCaps \<circ> ctes_of)
              and (\<lambda>s. \<forall>rf \<in> zobj_refs' cp. ex_nonz_cap_to' rf s)
              and valid_cap' cp and K (isThreadCap cp)
              and (\<lambda>s. \<forall>v \<in> set extraCaps.
                             ex_cte_cap_wp_to' isCNodeCap (snd v) s)
              and (\<lambda>s. \<forall>v \<in> set extraCaps.
                             s \<turnstile>' fst v \<and> cte_at' (snd v) s)
              and sysargs_rel args buffer)
       (UNIV
            \<inter> {s. ccap_relation cp (cap_' s)}
            \<inter> {s. unat (length___unsigned_long_' s) = length args}
            \<inter> {s. excaps_' s = extraCaps'}
            \<inter> {s. buffer_' s = option_to_ptr buffer}) []
     (decodeSetSchedParams args cp extraCaps
            >>= invocationCatch thread isBlocking isCall InvokeTCB)
     (Call decodeSetSchedParams_'proc)"
  supply Collect_const[simp del] dc_simp[simp del]
  apply (cinit' lift: cap_' length___unsigned_long_' excaps_' buffer_' simp: decodeSetSchedParams_def)
   apply (simp cong: StateSpace.state.fold_congs globals.fold_congs)
   apply (rule ccorres_rhs_assoc2)
   apply (rule_tac xf'=ret__int_' and R'=UNIV and R=\<top> and
                   val="from_bool (length args < 2 \<or> length extraCaps = 0)" in
                   ccorres_symb_exec_r_known_rv)
      apply vcg
      apply (auto simp: interpret_excaps_test_null excaps_map_def from_bool_def unat_eq_0
                  split: bool.splits)[1]
       apply (unat_arith+)[2]
     apply ceqv
    apply clarsimp
    apply (wpc,
           rule ccorres_cond_true_seq,
           clarsimp simp: throwError_bind invocationCatch_def,
           rule ccorres_rhs_assoc,
           ccorres_rewrite,
           fastforce intro: syscall_error_throwError_ccorres_n simp: syscall_error_to_H_cases)+
    (* Main case where args and extraCaps are both well-formed *)
    apply (rule ccorres_cond_false_seq)
    apply (simp add: split_def)
    apply (rule ccorres_add_return,
           ctac add: getSyscallArg_ccorres_foo'[where args=args and n=0 and buffer=buffer])
      apply (rule ccorres_add_return,
             ctac add: getSyscallArg_ccorres_foo'[where args=args and n=1 and buffer=buffer])
        apply (rule getSlotCap_ccorres_fudge_n[where vals=extraCaps and n=0])
        apply (rule ccorres_move_c_guard_cte)
        apply ctac
          apply csymbr
          apply (simp add: cap_get_tag_isCap cong: call_ignore_cong)
          apply (rule ccorres_assert2)
          apply (rule ccorres_Cond_rhs_Seq)
           apply (rule ccorres_rhs_assoc)
           apply ccorres_rewrite
           apply (clarsimp simp: not_isThreadCap_case throwError_bind invocationCatch_def
                           simp del: id_simps)
           apply (rule syscall_error_throwError_ccorres_n)
           apply (simp add: syscall_error_to_H_cases)
          apply (clarsimp simp: isCap_simps)
          apply csymbr
          apply csymbr
          (* Pre-conditions need to depend on the inner value of the thread cap *)
          apply (rule ccorres_inst[where P="Q (capTCBPtr (fst (extraCaps ! 0)))" and
                                         P'="Q' (capTCBPtr (fst (extraCaps ! 0)))" for Q Q'])
          apply (clarsimp simp: capTCBPtr_eq isCap_simps invocationCatch_use_injection_handler
                                injection_bindE[OF refl refl] bindE_assoc injection_handler_returnOk)
          apply (ctac add: ccorres_injection_handler_csum1[OF checkPrio_ccorres])
             apply (rule_tac P="args ! 0 \<le> ucast (max_word :: priority)"
                             in ccorres_cross_over_guard_no_st)
             apply (simp add: ccorres_invocationCatch_Inr performInvocation_def)
             apply ccorres_rewrite
             apply (clarsimp simp: capTCBPtr_eq isCap_simps invocationCatch_use_injection_handler
                                   injection_bindE[OF refl refl] bindE_assoc injection_handler_returnOk)
             apply (ctac add: ccorres_injection_handler_csum1[OF checkPrio_ccorres])
                apply (rule_tac P="args ! 1 \<le> ucast (max_word :: priority)"
                                in ccorres_cross_over_guard_no_st)
                apply (simp add: ccorres_invocationCatch_Inr performInvocation_def)
                apply ccorres_rewrite
                apply (ctac add: setThreadState_ccorres)
                  apply (simp add: invocationCatch_def)
                  apply ccorres_rewrite
                  apply csymbr
                  apply csymbr
                  apply csymbr
                  apply csymbr
                  apply (ctac (no_vcg) add: invokeTCB_ThreadControl_ccorres)
                    (* HACK: delete rules from the simpset to avoid the RVRs getting out of sync *)
                    apply (clarsimp simp del: intr_and_se_rel_simps comp_apply dc_simp)
                    apply (rule ccorres_alternative2)
                    apply (rule ccorres_return_CE; simp)
                   apply (rule ccorres_return_C_errorE; simp)
                  apply wp
                 apply (wpsimp wp: sts_invs_minor')
                apply simp
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
             apply vcg
            apply clarsimp
            apply ccorres_rewrite
            apply (rule ccorres_return_C_errorE; simp)
           apply simp
           apply (rule injection_handler_wp)
           apply (rule checkPrio_wp[simplified validE_R_def])
          apply vcg
         apply (wp | simp | wpc | wp_once hoare_drop_imps)+
        apply vcg
       apply simp
       apply (rule return_wp)
      apply (vcg exspec=getSyscallArg_modifies)
     apply simp
     apply (rule return_wp)
    apply simp
    apply (vcg exspec=getSyscallArg_modifies)
   apply simp
   apply (vcg exspec=getSyscallArg_modifies)
  apply clarsimp
  apply (rule conjI)
   apply (clarsimp simp: ct_in_state'_def pred_tcb_at'
      valid_cap'_def isCap_simps)
   apply (rule conjI; clarsimp simp: sysargs_rel_to_n n_msgRegisters_def)
   apply (clarsimp simp: maxPriority_def numPriorities_def)
   apply (fold max_word_def[where 'a=8, simplified])
   apply (rule conjI, clarsimp)
    apply (insert mcpriority_tcb_at'_prio_bounded[where prio="args ! 0"])
    apply (insert mcpriority_tcb_at'_prio_bounded[where prio="args ! 1"])
    apply (auto simp: valid_tcb_state'_def mcpriority_tcb_at'_le_ucast
                elim!: obj_at'_weakenE pred_tcb'_weakenE
                dest!: st_tcb_at_idle_thread')[1]
   apply (clarsimp simp: interpret_excaps_eq excaps_map_def)
  apply (simp add: StrictC'_thread_state_defs mask_eq_iff_w2p word_size option_to_0_def)
  apply (frule rf_sr_ksCurThread)
  apply (simp only: cap_get_tag_isCap[symmetric], drule(1) cap_get_tag_to_H)
  apply (clarsimp simp: valid_cap'_def capAligned_def interpret_excaps_eq excaps_map_def)
  apply (intro conjI impI allI)
                      apply (clarsimp simp: unat_eq_0 le_max_word_ucast_id
                                            thread_control_update_mcp_def thread_control_update_priority_def
                                            cap_get_tag_isCap_unfolded_H_cap isCap_simps
                                            interpret_excaps_eq excaps_map_def)+
   done
 
 lemma decodeSetIPCBuffer_ccorres:
    apply csymbr
    apply (rule ccorres_cond_false_seq)
    apply csymbr
   apply (simp del: Collect_const)
    apply (simp add: interpret_excaps_test_null excaps_map_Nil if_1_0_0
                del: Collect_const)
    apply wpc
       apply (rule ccorres_return_CE, simp+)[1]
      apply (rule ccorres_return_C_errorE, simp+)[1]
     apply wp
   apply (rule ccorres_Cond_rhs)
    apply simp
    apply (rule ccorres_add_returnOk, ctac(no_vcg) add: decodeSetSchedParams_ccorres [where buffer=buffer])
      apply (rule ccorres_return_CE, simp+)[1]
     apply (rule ccorres_return_C_errorE, simp+)[1]
    apply wp
    apply (rule ccorres_Cond_rhs)
     apply simp
     apply (rule ccorres_add_returnOk, ctac(no_vcg) add: decodeSetIPCBuffer_ccorres [where buffer=buffer])