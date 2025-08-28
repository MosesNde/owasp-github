 
   def layout_by_resource
     if devise_controller? && resource_name == :user
      "custom_devise"
     else
       "application"
     end