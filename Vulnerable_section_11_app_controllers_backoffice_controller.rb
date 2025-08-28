 # typed: false
 class BackofficeController < ApplicationController
   before_action :authenticate_admin!
   before_action :user_can_read, only: [:index]
   layout "backoffice"
 
   def policy(user)
    UserPolicy.new(user, controller_name)
   end
 
   def pundit_user