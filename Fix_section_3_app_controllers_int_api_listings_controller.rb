   private
 
   def listing
    @listing ||= @current_community.listings.find(params[:id])
   end
 
   def working_time_slots_params
   end
 
   def ensure_current_user_is_listing_author
    return true if !listing.deleted? && (current_user?(listing.author) || @current_user.has_admin_rights?(@current_community))
 
    head(:forbidden)
   end
 end