 # typed: true
 class Backoffice::CategoriesController::CategoryService
   attr_accessor :category
 
   def self.create(params)
     category = Category.new(params)
 
     category
   end
 
   def self.update(params, category)
    category.update(params)
   end
 
   def self.destroy(category)