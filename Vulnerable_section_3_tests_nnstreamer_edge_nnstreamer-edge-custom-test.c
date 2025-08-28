   nns_edge_custom_test_s *custom_h;
   nns_edge_data_h data_h;
   gchar *raw_data;
   if (!priv) {
     nns_loge ("Invalid param, handle should not be null.");
    return NNS_EDGE_ERROR_INVALID_PARAMETER;
   }
   custom_h = (nns_edge_custom_test_s *) priv;
   custom_h->is_connected = 1;
 
   /* Push dummy buffer to launch GstBaseSrc */
  nns_edge_data_create (&data_h);
   raw_data = g_strdup ("Dummy data");
  nns_edge_data_add (data_h, raw_data, strlen (raw_data) + 1, g_free);
  nns_edge_event_invoke_callback (custom_h->event_cb, custom_h->user_data,
       NNS_EDGE_EVENT_NEW_DATA_RECEIVED, data_h, sizeof (nns_edge_data_h), NULL);
   nns_edge_data_destroy (data_h);
 
  return NNS_EDGE_ERROR_NONE;
 }
 
 static int