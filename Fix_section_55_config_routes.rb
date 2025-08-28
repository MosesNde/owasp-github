 
   namespace :site do
     resources :advertisements, only: [:show]
    resources :categories, param: :description do
      get "advertisements"
    end
     resources :home, only: [:index], controller: "home"
     namespace :profile do
       resources :dashboard, only: [:index]
       resources :advertisements, except: [:show]
      resources :member_profile, only: [:show, :edit, :update]
     end
   end
 
   devise_for :admins, skip: [:registrations]
  devise_for :members, controllers: { sessions: "members/sessions", registrations: "members/registrations" }
 
   get "site/home"
   root "site/home#index"