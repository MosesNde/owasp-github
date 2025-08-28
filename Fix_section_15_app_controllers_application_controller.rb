 class ApplicationController < ActionController::Base
   include Pundit::Authorization
 
   layout :layout_by_resource
 
   protected
       "application"
     end
   end
 end