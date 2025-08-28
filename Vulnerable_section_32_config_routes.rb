   end
 
   namespace :site do
    resources :advertisements, only: [:show]
     resources :categories, param: :description do
       get "advertisements"
     end