 		if (p_fpga == NULL) {
 			NT_LOG(ERR, NTHW, "%s: Unsupported FPGA: %s (%08X)", p_adapter_id_str,
 				s_fpga_prod_ver_rev_str, p_fpga_info->n_fpga_build_time);
			nthw_fpga_mgr_delete(p_fpga_mgr);
			p_fpga_mgr = NULL;
 			return -1;
 		}
 