 
   protected
 
  def get_controller_name
    "#{super}/#{controller_name}"
  end

   def get_default_path
     backoffice_admins_path
   end