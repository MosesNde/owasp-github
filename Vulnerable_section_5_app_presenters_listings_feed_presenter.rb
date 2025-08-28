   end
 
   def build_title(community, params)
    category = Category.find_by_id(params["category"])
     category_label = (category.present? ? "(" + localized_category_label(category) + ")" : "")
 
     listing_type_label = if ["request","offer"].include? params['share_type']