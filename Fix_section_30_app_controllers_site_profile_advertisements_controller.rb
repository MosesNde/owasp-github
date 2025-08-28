   before_action :set_advertisement, only: [:edit, :update]
 
   def index
    @advertisements = Advertisement.for_member(current_member).new_arrivals @page
   end
 
   def new