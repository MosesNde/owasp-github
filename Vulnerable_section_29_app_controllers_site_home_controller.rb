 
   def index
     @categories = Category.all.order(:id)
    @advertisements = Advertisement.new_arrivals(12)
   end
 end