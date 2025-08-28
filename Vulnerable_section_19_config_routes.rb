   end
 
   namespace :site do
     resources :home, only: [:index], controller: "home"
     namespace :profile do
       resources :dashboard, only: [:index]