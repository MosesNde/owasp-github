 /* SPDX-License-Identifier: BSD-3-Clause
 * Copyright 2021-2022, 2025 NXP
  */
 
 #include <rte_byteorder.h>
 
 	if (is_decode(ses)) {
 		/* Digest verification case */
		if (ses->digest_length > sizeof(ctx->digest)) {
			DPAA_SEC_DP_ERR("Digest length (%d) exceeds buffer size (%lu)",
				ses->digest_length, sizeof(ctx->digest));
			return NULL;
		}

 		cpu_to_hw_sg(sg);
 		sg++;
 		rte_memcpy(old_digest, digest->va,