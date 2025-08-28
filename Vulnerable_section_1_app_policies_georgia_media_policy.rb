       media_user_permissions(:show_media_assets).include?(true)
     end
 
     def show?
       edit?
     end