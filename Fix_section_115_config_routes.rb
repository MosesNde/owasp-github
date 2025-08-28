     end
 
     resources :categories, except: [:show, :destroy]
    resources :members, only: [:index, :update, :edit]
     resources :admins, except: [:show]
     resources :roles, except: [:show]
     resources :permissions, only: [:index]
     get "home", to: "home#index"
   end
 
  devise_for :admins, skip: [:registrations]
  devise_for :members, controllers: { sessions: "members/sessions" }
 
   get "site/home"
   root "site/home#index"