 
   def new
     @object = Advertisement.new
   end
 
   def create
     @object = AdvertisementService.create(permitted_params, current_member)
 
     respond_to do |format|
       if @object.valid?
         format.html {
           redirect_to site_profile_advertisements_path,
                       notice: t("layout.action_text.created",
   end
 
   def edit
   end
 
   def update