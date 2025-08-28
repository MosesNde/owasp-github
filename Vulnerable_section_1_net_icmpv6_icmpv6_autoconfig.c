       ret = icmpv6_send_message(dev, false);
       if (ret < 0)
         {
           nerr("ERROR: Failed send router solicitation: %d\n", ret);
           break;
         }