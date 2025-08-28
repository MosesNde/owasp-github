 	ret = rw_copy_check_uvector(WRITE, _payload_iov, ioc,
 				    ARRAY_SIZE(iovstack), iovstack, &iov, 1);
 	if (ret < 0)
		return ret;
 	if (ret == 0)
 		goto no_payload_free;
 
 	ret = keyctl_instantiate_key_common(id, iov, ioc, ret, ringid);

 	if (iov != iovstack)
 		kfree(iov);
 	return ret;