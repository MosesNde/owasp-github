   if (params->tag_fields) {
 #ifdef HAVE_TAOSWS           /* [ */
     if (params->owner->owner->conn->cfg.url) {
      // OA_NIY(params->tag_fields == NULL);
      CALL_ws_stmt_reclaim_fields(params->owner->stmt, (struct StmtField**)&params->tag_fields, params->nr_tag_fields);
     } else {
 #endif                       /* ] */
       CALL_taos_stmt_reclaim_fields(params->owner->stmt, params->tag_fields);
       OA_NIY(stmt->params.nr_tag_fields == 0);
       stmt->params.tag_fields = tag_fields;
       stmt->params.nr_tag_fields = tagNum;
      // TODO: temp modify
      // if (tagNum == 0) stmt->params.tag_fields = NULL;
       sr = _tsdb_stmt_describe_cols(stmt);
     }
   } else {