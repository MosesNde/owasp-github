   # Configure public file server for tests with Cache-Control for performance.
   config.public_file_server.enabled = true
   config.public_file_server.headers = {
    'Cache-Control' => "public, max-age=#{1.hour.to_i}"
   }
 
   # Show full error reports and disable caching.
  config.consider_all_requests_local       = true
   config.action_controller.perform_caching = false
   config.cache_store = :null_store
 
   # ActionMailer::Base.deliveries array.
   config.action_mailer.delivery_method = :test
 
   # Print deprecation notices to the stderr.
   config.active_support.deprecation = :stderr
 