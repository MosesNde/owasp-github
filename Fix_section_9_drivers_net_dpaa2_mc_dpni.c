 /* SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0)
  *
  * Copyright 2013-2016 Freescale Semiconductor Inc.
 * Copyright 2016-2025 NXP
  *
  */
 #include <fsl_mc_sys.h>
 
 	return mc_send_command(mc_io, &cmd);
 }

int dpni_get_mac_speed_capability(struct fsl_mc_io *mc_io, uint32_t cmd_flags, uint16_t token,
				  uint32_t *speed_cap)
{
	struct dpni_rsp_mac_speed_cap *rsp_params;
	struct mc_command cmd = { 0 };
	int err;

	cmd.header = mc_encode_cmd_header(DPNI_CMDID_GET_MAC_SPEED_CAPABILITY,
					  cmd_flags, token);

	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	rsp_params = (struct dpni_rsp_mac_speed_cap *)cmd.params;
	*speed_cap = le32_to_cpu(rsp_params->speed_cap);

	return 0;
}