       ret = icmpv6_send_message(dev, false);
       if (ret < 0)
         {
          /* Remove our wait structure from the list (we may no longer be
           * at the head of the list).
           */

          icmpv6_rwait_cancel(&notify);

           nerr("ERROR: Failed send router solicitation: %d\n", ret);
           break;
         }