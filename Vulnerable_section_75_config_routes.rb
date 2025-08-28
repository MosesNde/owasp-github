     resources :permissions, only: [:index]
     resources :dashboard, only: [:index]
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
    resources :home, only: [:index], controller: "home"
     namespace :profile do
       resources :dashboard, only: [:index]
       resources :advertisements, except: [:show]