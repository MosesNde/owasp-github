 
   def listing_bubble
     if params[:id]
      @listing = @current_community.listings.find(params[:id])
       if Policy::ListingPolicy.new(@listing, @current_community, @current_user).visible?
         render :partial => "homepage/listing_bubble", :locals => { :listing => @listing }
       else
   end
 
   def ensure_current_user_is_listing_author(error_message)
    @listing = @current_community.listings.find(params[:id])

    raise ListingDeleted if @listing.deleted?

    return if @listing && (current_user?(@listing.author) || @current_user.has_admin_rights?(@current_community))
 
     flash[:error] = error_message
     redirect_to @listing and return