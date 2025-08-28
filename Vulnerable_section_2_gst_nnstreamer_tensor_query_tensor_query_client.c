 gst_tensor_query_client_create_edge_handle (GstTensorQueryClient * self)
 {
   gboolean started = FALSE;
  gchar *prev_caps = NULL;
   int ret;
 
   /* Already created, compare caps string. */
   if (self->edge_h) {
     ret = nns_edge_get_info (self->edge_h, "CAPS", &prev_caps);
 
     if (ret != NNS_EDGE_ERROR_NONE || !prev_caps ||
         !g_str_equal (prev_caps, self->in_caps_str)) {
       /* Capability is changed, close old handle. */
       nns_edge_release_handle (self->edge_h);
       self->edge_h = NULL;
     } else {
       return TRUE;
     }
   }