   end
 
   namespace :site do
    resources :advertisements, only: [:show]
     resources :home, only: [:index], controller: "home"
     namespace :profile do
       resources :dashboard, only: [:index]