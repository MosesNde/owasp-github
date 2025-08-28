       media_user_permissions(:show_media_assets).include?(true)
     end
 
    def search?
      index?
    end

     def show?
       edit?
     end