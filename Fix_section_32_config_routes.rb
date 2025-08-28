   end
 
   namespace :site do
    resources :advertisements, only: [:show] do
      collection do
        get "search"
      end
    end
     resources :categories, param: :description do
       get "advertisements"
     end