 
   namespace :site do
     resources :advertisements, only: [:show]
     resources :home, only: [:index], controller: "home"
     namespace :profile do
       resources :dashboard, only: [:index]
       resources :advertisements, except: [:show]
     end
   end
 
   devise_for :admins, skip: [:registrations]
  devise_for :members, controllers: { sessions: "members/sessions" }
 
   get "site/home"
   root "site/home#index"