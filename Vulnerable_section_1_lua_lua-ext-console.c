   int num = ibus_engine_plugin_call(plugin, lua_function_name, string);
   g_assert(num == ibus_engine_plugin_get_n_result(plugin));
   for (i = 0; i < num ; ++i){
    printf("%d.%s >\t", i, ibus_engine_plugin_get_nth_result(plugin, i));
   }
   printf("\n");
   ibus_engine_plugin_clear_results(plugin);