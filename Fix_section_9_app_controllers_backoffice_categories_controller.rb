 # typed: false
 class Backoffice::CategoriesController < BackofficeController
   def index
    super
   end
 
   def new
   def get_default_path
     backoffice_categories_path
   end
 end