   if (ret != OK)
     {
       ret = -ret;
      nxmq_free_msg(mqmsg);
       goto errout_in_critical_section;
     }
 