   nns_edge_custom_test_s *custom_h;
   nns_edge_data_h data_h;
   gchar *raw_data;
  int ret = NNS_EDGE_ERROR_INVALID_PARAMETER;

   if (!priv) {
     nns_loge ("Invalid param, handle should not be null.");
    return ret;
   }
   custom_h = (nns_edge_custom_test_s *) priv;
   custom_h->is_connected = 1;
 
   /* Push dummy buffer to launch GstBaseSrc */
  ret = nns_edge_data_create (&data_h);
  if (ret != NNS_EDGE_ERROR_NONE) {
    nns_loge ("Failed to create edge data handle.");
    return ret;
  }

   raw_data = g_strdup ("Dummy data");
  ret = nns_edge_data_add (data_h, raw_data, strlen (raw_data) + 1, g_free);
  if (ret != NNS_EDGE_ERROR_NONE) {
    nns_loge ("Failed to add edge data.");
    g_free (raw_data);
    goto done;
  }
  ret = nns_edge_event_invoke_callback (custom_h->event_cb, custom_h->user_data,
       NNS_EDGE_EVENT_NEW_DATA_RECEIVED, data_h, sizeof (nns_edge_data_h), NULL);
  if (ret != NNS_EDGE_ERROR_NONE) {
    nns_loge ("Failed to invoke edge event.");
  }

done:
   nns_edge_data_destroy (data_h);
 
  return ret;
 }
 
 static int