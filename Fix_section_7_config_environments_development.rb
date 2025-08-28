 
   # Devise
   # config.action_mailer.default_url_options = { host: 'localhost', port: 3000 }

   # Mailcatcher
   config.action_mailer.delivery_method = :smtp
   config.action_mailer.smtp_settings = { :address => "escamboapp_devcontainer-mailcatcher-1", :port => 1025 }
   config.action_mailer.raise_delivery_errors = false
   config.action_mailer.default_url_options = { :host => "localhost:3000" }
 
  # Authorization
  config.default_roles = [
    { name: "Administrator", is_admin: true, is_opt: false, is_member: false },
    { name: "Operator", is_admin: false, is_opt: true, is_member: false },
    { name: "Member", is_admin: false, is_opt: false, is_member: true },
  ]

   # Print deprecation notices to the Rails logger.
   config.active_support.deprecation = :log
 