# typed: false
 Rails.application.configure do
   # Settings specified here will take precedence over those in config/application.rb.
 
   config.action_mailer.default_url_options = { :host => "localhost:3000" }
 
   # Authorization
   config.default_roles = [
    { name: "Administrator", is_admin: true, is_opt: false, is_member: false },
    { name: "Operator", is_admin: false, is_opt: true, is_member: false },
    { name: "Member", is_admin: false, is_opt: false, is_member: true },
   ]
 
   # Print deprecation notices to the Rails logger.