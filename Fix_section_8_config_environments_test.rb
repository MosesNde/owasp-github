   # Configure public file server for tests with Cache-Control for performance.
   config.public_file_server.enabled = true
   config.public_file_server.headers = {
    "Cache-Control" => "public, max-age=#{1.hour.to_i}",
   }
 
   # Show full error reports and disable caching.
  config.consider_all_requests_local = true
   config.action_controller.perform_caching = false
   config.cache_store = :null_store
 
   # ActionMailer::Base.deliveries array.
   config.action_mailer.delivery_method = :test
 
  # Authorization
  config.default_roles = [
    { name: "Administrator", is_admin: true, is_opt: false, is_member: false },
    { name: "Operator", is_admin: false, is_opt: true, is_member: false },
    { name: "Member", is_admin: false, is_opt: false, is_member: true },
  ]

   # Print deprecation notices to the stderr.
   config.active_support.deprecation = :stderr
 