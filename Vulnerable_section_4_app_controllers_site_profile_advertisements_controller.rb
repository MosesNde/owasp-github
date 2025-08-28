 
   def index
     @advertisements = Advertisement.for_member(current_member).new_arrivals
    respond_to do |format|
      format.js
    end
   end
 
   def new
     @object = Advertisement.new

    respond_to do |format|
      format.js
      format.html
    end
   end
 
   def create
     @object = AdvertisementService.create(permitted_params, current_member)
 
     respond_to do |format|
       if @object.valid?
        format.js {
          redirect_to site_profile_advertisements_path,
                      notice: t("layout.action_text.created",
                                object_name: Advertisement.model_name.human,
                                :gender => :n)
        }
         format.html {
           redirect_to site_profile_advertisements_path,
                       notice: t("layout.action_text.created",
   end
 
   def edit
    respond_to do |format|
      format.js
    end
   end
 
   def update